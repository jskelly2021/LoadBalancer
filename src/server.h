#pragma once

#include "request.h"

enum ServerStatus {
    PROCESSING,
    IDLE
};

class Server {
private:
    int server_id;
    Request req;
    ServerStatus status;
    int req_time;

public:
    Server(int id);
    void recieve_request(Request &req);
    void process_request();
    ServerStatus server_status();

private:
    void complete_request();
};
