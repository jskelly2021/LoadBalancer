#pragma once

#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include "request.h"
#include "server.h"
#include "logger.h"
#include "request_generator.h"

#define MIN_SERVERS 1              /**< Minimum number of servers allowed in the system. */
#define MAX_SERVERS 80             /**< Maximum number of servers allowed in the system. */
#define MIN_TASK_TIME 10           /**< Minimum processing time for requests. */
#define MAX_TASK_TIME 50           /**< Maximum processing time for requests. */
#define SCALE_INTERVAL 50          /**< Interval (in cycles) at which server scaling is evaluated. */

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes web requests to available servers.
 *
 * The LoadBalancer generates and filters traffic, assigns requests to servers, and dynamically scales
 * the number of servers based on current demand. It supports banning IP address ranges and logs
 * activity throughout the simulation.
 */
class LoadBalancer {
private:
    RequestGenerator request_generator;              /**< Utility for generating simulated web requests. */
    std::unordered_set<std::string> blocked_ranges;  /**< Set of IP address prefixes to block. */
    std::queue<Request> request_queue;               /**< Queue of pending requests waiting for processing. */
    std::vector<Server*> servers;                    /**< Pool of server pointers used to handle requests. */
    int run_time;                                    /**< Total number of cycles to simulate. */
    int next_server_id;                              /**< ID to assign to the next newly created server. */

public:
    /**
     * @brief Constructs a LoadBalancer with a specified run time and starting server count.
     * @param run_time Total number of cycles to simulate.
     * @param num_servers Initial number of servers.
     */
    LoadBalancer(int run_time, int num_servers);

    /**
     * @brief Destructor that deallocates any dynamic server objects.
     */
    ~LoadBalancer();

    /**
     * @brief Starts the load balancing simulation.
     *
     * Runs the simulation loop, generating traffic, assigning requests, and managing server scaling.
     */
    void run();

    /**
     * @brief Generates new traffic and enqueues requests that are not blocked.
     */
    void generate_traffic();

    /**
     * @brief Adds a blocked IP address range prefix (e.g., "192.168").
     * @param addr_range The prefix to block.
     */
    void add_blocked_addr_range(std::string &addr_range);

private:
    /**
     * @brief Distributes requests in the queue to idle servers.
     */
    void distribute_requests();

    /**
     * @brief Evaluates the system load and decides whether to scale up or down the number of servers.
     */
    void scale_servers();

    /**
     * @brief Adds new servers to the system up to the allowed maximum.
     * @param current_server_count The current number of servers.
     * @param max_additional_servers The number of servers allowed to be added in this cycle.
     */
    void scale_up(size_t current_server_count, size_t max_additional_servers);

    /**
     * @brief Removes idle servers from the system to conserve resources.
     */
    void scale_down();

    /**
     * @brief Checks whether a given IP address prefix is in the blocked list.
     * @param addr_range IP address prefix to check.
     * @return true if the address is blocked, false otherwise.
     */
    bool is_blocked(std::string &addr_range);
};
