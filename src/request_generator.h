#pragma once

#include <string>
#include <vector>
#include "request.h"

#define TRAFFIC_FREQ 5        /**< Frequency modifier that determines how often traffic is generated. */
#define MAX_NUM_NEW_REQS 5   /**< Maximum number of new requests generated in one traffic event. */
#define SPIKE_FREQ 6000
#define SPIKE_NUM_REQS 1500

/**
 * @class RequestGenerator
 * @brief Generates simulated web requests with random attributes.
 *
 * Used to simulate incoming traffic for a load balancer. Requests are created with randomized IP addresses
 * and processing times. Supports generation of traffic bursts at randomized intervals.
 */
class RequestGenerator {
private:
    int min_time;            /**< Minimum processing time for a generated request. */
    int max_time;            /**< Maximum processing time for a generated request. */
    int next_request_id;     /**< Counter to ensure unique request IDs. */

public:
    /**
     * @brief Constructs a RequestGenerator with configurable request time bounds.
     * @param min_time Minimum request processing time.
     * @param max_time Maximum request processing time.
     */
    RequestGenerator(int min_time, int max_time);

    /**
     * @brief Generates a single request with random IP addresses and time duration.
     * @return Request A randomly generated request.
     */
    Request generate_request();

    /**
     * @brief Conditionally generates a burst of random requests to simulate traffic.
     *
     * Traffic is generated based on a random condition influenced by TRAFFIC_FREQ.
     * 
     * @return std::vector<Request> A vector of newly generated requests.
     */
    std::vector<Request> generate_traffic();

private:
    /**
     * @brief Generates a random IPv4 address string.
     * @return std::string A randomly generated IP address.
     */
    std::string ip_gen();
};
