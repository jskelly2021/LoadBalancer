#include "request_generator.h"

RequestGenerator::RequestGenerator(int min_time, int max_time)
    : min_time(min_time),
    max_time(max_time),
    next_request_id(0)
{}

Request RequestGenerator::generate_request() {
    Request req;
    req.id = next_request_id++;
    req.ip_in = ip_gen();
    req.ip_out = ip_gen();
    req.time = rand() % (max_time - min_time + 1) + min_time;

    return req;
}

std::vector<Request> RequestGenerator::generate_traffic() {
    std::vector<Request> reqs;
    if (rand() % TRAFFIC_FREQ == 0) {
        int num_reqs = rand() % MAX_NUM_NEW_REQS;
        for (int i = 0; i < num_reqs; i++) {
            reqs.push_back(generate_request());
        }
    }
    return reqs;
}

std::string RequestGenerator::ip_gen() {
    return  std::to_string(rand() % 256) + "." +
            std::to_string(rand() % 256) + "." + 
            std::to_string(rand() % 256) + "." +
            std::to_string(rand() % 256);
}
