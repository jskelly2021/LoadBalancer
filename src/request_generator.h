#pragma once

#include "request.h"

class RequestGenerator {
private:
    int next_request_id;

public:
    Request generate_request();
};
