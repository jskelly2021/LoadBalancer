#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <mutex>

class Logger {
private:
    static std::ofstream out_stream;
    static std::mutex mtx;;

public:
    static void init(std::string &file_name);
    static void close();
    static void log(std::string &msg);
};
