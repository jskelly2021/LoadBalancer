#pragma once

#include <string>
#include "request.h"

class RequestGenerator {
private:
    int min_time;
    int max_time;
    int next_request_id;

public:
    RequestGenerator(int min_time, int max_time);
    Request generate_request();

private:
    std::string ip_gen();
};
