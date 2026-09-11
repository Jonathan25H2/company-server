#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

int main() {
    std::cout << "\n========== WARNING ==========\n";
    std::cout << "You are about to shut down this server.\n";
    std::cout << "All users will be disconnected.\n";
    std::cout << "Running services will stop.\n";
    std::cout << "Active transfers may be interrupted.\n";
    std::cout << "Unsaved data may be lost.\n";
    std::cout << "=============================\n\n";

    for (int i = 5; i > 0; --i) {
        std::cout << "Confirmation available in " << i << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    char answer;
    std::cout << "\nContinue shutdown? (y/n): ";
    std::cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        std::cout << "Shutting down...\n";

        // IMPORTANT: call the real shutdown command by absolute path
        system("/usr/sbin/shutdown -h now");
    }
    else {
        std::cout << "Shutdown cancelled.\n";
    }

    return 0;
}
