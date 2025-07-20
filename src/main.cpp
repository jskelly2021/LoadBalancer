#include <printf.h>
#include <iostream>

int main() {
    int num_servers = 0;
    int run_time = 0;

    printf("Enter the number of servers: ");
    std::cin >> num_servers;

    printf("Enter the load balancer run time (clock cycles): ");
    std::cin >> run_time;
}
