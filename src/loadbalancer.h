#pragma once

#include <queue>
#include "request.h"
#include "server.h"

#define MAX_SERVERS 40

class LoadBalancer {
private:
    std::queue<Request> request_queue;
    int run_time;
    int num_requests;
    int num_servers;

public:
    LoadBalancer(int run_time, int num_servers);
    void run(int run_time);
    void receive_request(Request &req);

private:
    void distribute_requests();
    bool scale_servers();
};
