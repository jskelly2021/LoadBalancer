#pragma once

#include <string>

struct Request {
    int id;
    std::string ip_in;
    std::string ip_out;
    int time;
};
