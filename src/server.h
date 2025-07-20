#pragma once

#include "request.h"
#include "logger.h"

/**
 * @enum ServerStatus
 * @brief Represents the status of a server (either processing a request or idle).
 */
enum ServerStatus {
    PROCESSING,
    IDLE
};

/**
 * @class Server
 * @brief Represents a server that can receive and process requests.
 *
 * Each Server has a unique ID, maintains its current status, and handles a single request at a time.
 * Logging is performed during request receipt and completion.
 */
class Server {
private:
    int server_id;      /**< Unique identifier for the server. */
    Request req;        /**< The current request assigned to this server. */
    ServerStatus status;/**< Current status of the server (IDLE or PROCESSING). */
    int req_time;       /**< Time remaining to process the current request. */
public:
    /**
     * @brief Constructs a new Server object.
     * @param id The unique identifier for this server.
     */
    Server(int id);

    /**
     * @brief Assigns a new request to this server.
     * 
     * The server logs the event, stores the request, and sets its status to PROCESSING.
     * 
     * @param req Reference to the request to be handled.
     */
    void receive_request(Request& req);

    /**
     * @brief Processes the current request by decrementing the remaining time.
     *
     * If the request time reaches zero or below, the server completes the request.
     */
    void process_request();

    /**
     * @brief Gets the current status of the server.
     * @return ServerStatus The current status (IDLE or PROCESSING).
     */
    ServerStatus server_status() const;

    int get_id() const;

private:
    /**
     * @brief Completes the current request.
     *
     * Logs the completion, resets the request data, and marks the server as IDLE.
     */
    void complete_request();
};
