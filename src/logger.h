#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <mutex>

/**
 * @class Logger
 * @brief A thread-safe static logging utility for writing messages to a file.
 *
 * The Logger class provides static methods to initialize, write to, and close a log file.
 * It uses a mutex to ensure thread-safe writes from multiple threads or components.
 */
class Logger {
private:
    /**
     * @brief Output file stream used for writing log messages.
     */
    static std::ofstream out_stream;

    /**
     * @brief Mutex for thread-safe logging.
     */
    static std::mutex mtx;

public:
    /**
     * @brief Initializes the logger by opening the specified log file.
     * 
     * This will overwrite any existing content in the file.
     *
     * @param file_name Path to the log file.
     */
    static void init(std::string &file_name);

    /**
     * @brief Closes the log file if it's open.
     *
     * Should be called at the end of the program or when logging is complete.
     */
    static void close();

    /**
     * @brief Writes a message to the log file.
     *
     * This method is thread-safe and will automatically lock the file during write operations.
     * If the logger has not been initialized, it will print an error to std::cerr.
     *
     * @param msg The message to write to the log file.
     */
    static void log(const std::string &msg);
};
