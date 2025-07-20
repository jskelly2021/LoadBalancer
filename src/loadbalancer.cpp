#include "loadbalancer.h"

LoadBalancer::LoadBalancer(int run_time, int num_servers)
    : request_generator(RequestGenerator(10, 40)),
    run_time(run_time),
    next_server_id(0)
{
    for (int i = 0; i < num_servers; i++) {
        servers.push_back(new Server(next_server_id++));
    }

    int num_requests = num_servers * 100;
    Logger::log("Initial number of requests: " + std::to_string(num_requests));

    for (int i = 0; i < num_requests; i++) {
        request_queue.push(request_generator.generate_request());
    }
}

LoadBalancer::~LoadBalancer() {
    for (Server* server : servers) {
        delete server;
    }
}

void LoadBalancer::run() {
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

        elapsed++;
        run_time--;
    }
}

void LoadBalancer::receive_request(Request &req) {

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

    else if (servers.size() > MIN_SERVERS) {
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
