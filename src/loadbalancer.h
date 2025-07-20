#pragma once

#include <queue>
#include "request.h"
#include "server.h"
#include "logger.h"

#define MAX_SERVERS 40
#define MIN_SERVERS 1
#define SCALE_INTERVAL 100

class LoadBalancer {
private:
    std::queue<Request> request_queue;
    std::vector<Server*> servers;
    int run_time;
    int next_server_id;

public:
    LoadBalancer(int run_time, int num_servers);
    ~LoadBalancer();
    void run();
    void receive_request(Request &req);

private:
    void distribute_requests();
    void scale_servers();
    void scale_up(size_t current_server_count, size_t max_additional_servers);
    void scale_down();
};
