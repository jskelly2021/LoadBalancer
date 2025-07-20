#pragma once

#include <string>

/**
 * @struct Request
 * @brief Represents a unit of work or a simulated web request in the load balancer system.
 *
 * Each request contains a unique ID, source and destination IP addresses,
 * and the time (in clock cycles) required to process the request.
 */
struct Request {
    /**
     * @brief Unique identifier for the request.
     */
    int id;

    /**
     * @brief IP address of the incoming request source.
     */
    std::string ip_in;

    /**
     * @brief IP address of the outgoing destination.
     */
    std::string ip_out;

    /**
     * @brief Amount of time (in clock cycles) required to process the request.
     */
    int time;
};
