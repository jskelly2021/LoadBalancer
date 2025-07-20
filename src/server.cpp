#include "server.h"

Server::Server(int id)
    : server_id(id),
    req({}),
    status(IDLE),
    req_time(0) {}

void Server::recieve_request(Request &req) {
    this->req = req;
    status = PROCESSING;
    req_time = req.time;
}

void Server::process_request() {
    req_time -= 1;
    if (req_time <= 0) {
        complete_request();
    }
}

void Server::complete_request() {
    status = IDLE;
    req_time = 0;
    req = {};
}

ServerStatus Server::server_status() { return status; }
