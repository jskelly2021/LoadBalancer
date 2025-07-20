#pragma once

#include <queue>
#include "request.h"
#include "server.h"
#include "logger.h"

#define MAX_SERVERS 40

class LoadBalancer {
private:
    std::queue<Request> request_queue;
    std::vector<Server*> servers;
    int run_time;
    int num_requests;
    int num_servers;

public:
    LoadBalancer(int run_time, int num_servers);
    ~LoadBalancer();
    void run();
    void receive_request(Request &req);

private:
    void distribute_requests();
    bool scale_servers();
};
