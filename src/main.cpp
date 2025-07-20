#include <printf.h>
#include <iostream>
#include <string>
#include "loadbalancer.h"
#include "logger.h"

int main() {
    int num_servers = 0;
    int run_time = 0;

    std::string log_file_name = "logs/log.txt";
    Logger::init(log_file_name);

    printf("Enter the number of servers: ");
    std::cin >> num_servers;

    printf("Enter the load balancer run time (clock cycles): ");
    std::cin >> run_time;

    LoadBalancer load_balancer = LoadBalancer(run_time, num_servers);

    std::string blocked_range;
    std::cout << "Enter an IP address range to block (e.g., 134.219), or type 'done' to finish:\n";

    while (true) {
        std::cout << "> ";
        std::cin >> blocked_range;
        if (blocked_range == "done") {
            break;
        }
        load_balancer.add_blocked_addr_range(blocked_range);
    }

    load_balancer.run();

    Logger::close();
}
