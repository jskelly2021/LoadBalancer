#include "server.h"

Server::Server(int id)
    : server_id(id),
    req({}),
    status(IDLE),
    req_time(0) {}

void Server::receive_request(Request &req) {
    Logger::log("Server #" + std::to_string(server_id) + " received request #" + std::to_string(req.id));
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
    Logger::log("Server #" + std::to_string(server_id) + " completed request #" + std::to_string(req.id));
    status = IDLE;
    req_time = 0;
    req = {};
}

ServerStatus Server::server_status() { return status; }
