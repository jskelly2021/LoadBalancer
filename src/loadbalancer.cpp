#include "loadbalancer.h"

LoadBalancer::LoadBalancer(int run_time, int num_servers)
    : run_time(run_time),
    num_requests(num_servers * 100),
    num_servers(num_servers)
{
    for (int i = 0; i < num_servers; i++) {
        servers.push_back(new Server(i));
    }

    for (int i = 0; i < num_requests; i++) {
        Request req;
        req.id = i;
        req.ip_in = "192.168.0." + std::to_string(i % 255);
        req.ip_out = "10.0.0." + std::to_string((i + 5) % 255);
        req.time = rand() % 10 + 1;

        request_queue.push(req);
    }

    Logger::log("Initial number of requests: " + std::to_string(num_requests));
}

LoadBalancer::~LoadBalancer() {
    for (Server* server : servers) {
        delete server;
    }
}

void LoadBalancer::run() {
    while (run_time > 0) {
        distribute_requests();
        for (Server* server : servers) {
            if (server->server_status() == ServerStatus::PROCESSING) {
                server->process_request();
            }
        }

        scale_servers();
        run_time -= 1;
    }
}

void LoadBalancer::receive_request(Request &req) {

}

void LoadBalancer::distribute_requests() {
    for (Server* server : servers) {
        if (num_requests <= 0)
            return;

        if (server->server_status() == ServerStatus::IDLE) {
            server->receive_request(request_queue.front());
            request_queue.pop();
            num_requests -= 1;
        }
    }
}

bool LoadBalancer::scale_servers() {
    return false;
}
