#include <printf.h>
#include <iostream>
#include "loadbalancer.h"
#include <string>

int main() {
    int num_servers = 0;
    int run_time = 0;

    printf("Enter the number of servers: ");
    std::cin >> num_servers;

    printf("Enter the load balancer run time (clock cycles): ");
    std::cin >> run_time;

    std::string log_file_name = "logs/log.txt";
    Logger::init(log_file_name);

    LoadBalancer load_balancer = LoadBalancer(run_time, num_servers);
    load_balancer.run();
}
