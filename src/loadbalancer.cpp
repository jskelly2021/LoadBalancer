#include "loadbalancer.h"

LoadBalancer::LoadBalancer(int run_time, int num_servers)
    : request_generator(RequestGenerator(MIN_TASK_TIME, MAX_TASK_TIME)),
    run_time(run_time),
    next_server_id(0)
{
    for (int i = 0; i < num_servers; i++) {
        servers.push_back(new Server(next_server_id++));
    }

    for (int i = 0; i < num_servers * 100; i++) {
        request_queue.push(request_generator.generate_request());
    }
}

LoadBalancer::~LoadBalancer() {
    for (Server* server : servers) {
        delete server;
    }
}

void LoadBalancer::run() {
    Logger::log("Blocked address ranges:");
    for (const auto& addr : blocked_ranges) {
        Logger::log(" - " + addr);
    }
    Logger::log("Task times range (cycles): " + std::to_string(MIN_TASK_TIME) + " -- " + std::to_string(MAX_TASK_TIME));
    Logger::log("Initial number of requests: " + std::to_string(request_queue.size()));
    Logger::log("---Beginning Load Balancer---");

    int elapsed = 0;
    while (run_time > 0) {
        if (elapsed % SCALE_INTERVAL == 0) {
            scale_servers();

            Logger::log("Cycle " + std::to_string(elapsed) +
                " | Servers: " + std::to_string(servers.size()) +
                " | Queue: " + std::to_string(request_queue.size()));
        }

        distribute_requests();

        for (Server* server : servers) {
            if (server->server_status() == ServerStatus::PROCESSING) {
                server->process_request();
            }
        }

        generate_traffic();

        elapsed++;
        run_time--;
    }

    Logger::log("---Ending Load Balancer---");
    Logger::log("Remaining requests: " + std::to_string(request_queue.size()));
    Logger::log("Active Servers: " + std::to_string(servers.size()));
    Logger::log("Total dropped requests: " + std::to_string(dropped_reqs.size()));
    Logger::log("Dropped Requests:");
    for (const auto& req : dropped_reqs) {
        Logger::log(" - Origin: " + req.ip_in);
    }
}

void LoadBalancer::generate_traffic() {
    std::vector<Request> traffic = request_generator.generate_traffic();

    if (traffic.empty()) {
        return;
    }

    Logger::log("Load Balancer recieved " + std::to_string(traffic.size()) + " new requests");

    for (Request req : traffic) {
        if (is_blocked(req.ip_in)) {
            Logger::log("Request #" + std::to_string(req.id) + " from blocked IP range: " + req.ip_in + " — dropped.");
            dropped_reqs.push_back(req);
            return;
        }
        request_queue.push(req);
    }
}

void LoadBalancer::distribute_requests() {
    for (Server* server : servers) {
        if (request_queue.empty())
            return;

        if (server->server_status() == ServerStatus::IDLE) {
            server->receive_request(request_queue.front());
            request_queue.pop();
        }
    }
}

void LoadBalancer::scale_servers() {
    size_t current_server_count = servers.size();
    size_t max_additional_servers = MAX_SERVERS - current_server_count;
    const int QUEUE_LOAD_FACTOR = 2;

    if (request_queue.size() > current_server_count * QUEUE_LOAD_FACTOR && max_additional_servers > 0) {
        scale_up(current_server_count, max_additional_servers);
    }

    else if (request_queue.size() < servers.size() * QUEUE_LOAD_FACTOR && servers.size() > MIN_SERVERS) {
        scale_down();
    }
}

void LoadBalancer::scale_up(size_t current_server_count, size_t max_additional_servers) {
    size_t servers_to_add = std::min(current_server_count, max_additional_servers);

    Logger::log("Scaling up: Adding " + std::to_string(servers_to_add) + " servers (from " + std::to_string(current_server_count) + ")");

    for (size_t i = 0; i < servers_to_add; ++i) {
        servers.push_back(new Server(next_server_id++));
    }
}

void LoadBalancer::scale_down() {
    const double SCALE_DOWN_RATIO = 0.25;
    int current_count = static_cast<int>(servers.size());
    int max_removable = static_cast<int>(current_count * SCALE_DOWN_RATIO);
    int removed_count = 0;

    if (max_removable == 0) {
        return;
    }

    Logger::log("Scaling down: Up to " + std::to_string(max_removable) + " servers may be removed");

    auto it = servers.begin();
    while (it != servers.end() && removed_count < max_removable) {
        Server* server = *it;

        if (server->server_status() == ServerStatus::IDLE) {
            Logger::log("Removing IDLE server #" + std::to_string(server->get_id()));

            delete server;
            it = servers.erase(it);
            ++removed_count;
        } else {
            ++it;
        }
    }

    if (removed_count > 0) {
        Logger::log("Scaled down: " + std::to_string(removed_count) + " IDLE servers removed");
    }
}

void LoadBalancer::add_blocked_addr_range(std::string &addr_range) {
    blocked_ranges.insert(addr_range);
}

bool LoadBalancer::is_blocked(std::string &addr_range) {
    for (const auto& range : blocked_ranges) {
        if (addr_range.rfind(range, 0) == 0) {
            return true;
        }
    }
    return false;
}
