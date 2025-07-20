#include "logger.h"

std::ofstream Logger::out_stream;
std::mutex Logger::mtx;

void Logger::init(std::string &file_name) {
    out_stream.open(file_name, std::ios::trunc);
    if (!out_stream.is_open()) {
        std::cerr << "Failed to open log file: " << file_name << "\n";
    }
}

void Logger::close() {
    std::unique_lock<std::mutex> lock(mtx);
    if (out_stream.is_open()) {
        out_stream.close();
    }
}

void Logger::log(const std::string &msg) {
    std::unique_lock<std::mutex> lock(mtx);

    if (!out_stream.is_open()) {
        std::cerr << "Logger not initialized.\n";
        return;
    }

    out_stream << msg << std::endl;
}
