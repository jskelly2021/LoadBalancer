#pragma once

#include <queue>
#include "request.h"
#include "server.h"
#include "logger.h"
#include "request_generator.h"

#define MIN_SERVERS 1
#define MAX_SERVERS 80
#define MIN_TASK_TIME 10
#define MAX_TASK_TIME 50
#define SCALE_INTERVAL 50

class LoadBalancer {
private:
    RequestGenerator request_generator;
    std::queue<Request> request_queue;
    std::vector<Server*> servers;
    int run_time;
    int next_server_id;

public:
    LoadBalancer(int run_time, int num_servers);
    ~LoadBalancer();
    void run();
    void generate_traffic();

private:
    void distribute_requests();
    void scale_servers();
    void scale_up(size_t current_server_count, size_t max_additional_servers);
    void scale_down();
};
