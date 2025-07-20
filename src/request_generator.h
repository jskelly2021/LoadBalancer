#pragma once

#include <string>
#include <vector>
#include "request.h"

#define TRAFFIC_FREQ 4
#define MAX_NUM_NEW_REQS 20

class RequestGenerator {
private:
    int min_time;
    int max_time;
    int next_request_id;

public:
    RequestGenerator(int min_time, int max_time);
    Request generate_request();
    std::vector<Request> generate_traffic();

private:
    std::string ip_gen();
};
