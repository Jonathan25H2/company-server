#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string calledAs = argv[0];

    bool isReboot = calledAs.find("reboot") != std::string::npos;
    bool isShutdown = calledAs.find("shutdown") != std::string::npos;

    if (!isReboot && !isShutdown) {
        std::cout << "Run this program as shutdown or reboot.\n";
        return 1;
    }

    std::string action = isReboot ? "reboot" : "shutdown";

    std::cout << "\n=========================================\n";
    std::cout << "               WARNING\n";
    std::cout << "=========================================\n";
    std::cout << "You are about to " << action << " this server.\n\n";
    std::cout << "This may:\n";
    std::cout << "- Disconnect all active users\n";
    std::cout << "- Stop running services\n";
    std::cout << "- Interrupt file transfers\n";
    std::cout << "- Cause data loss if data is being written\n";
    std::cout << "- Make the server temporarily unavailable\n";
    std::cout << "=========================================\n\n";

    for (int i = 5; i >= 1; --i) {
        std::cout << "Confirmation available in " << i << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    char confirm;

    std::cout << "\nContinue with " << action << "? (y/n): ";
    std::cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "\n" << action << " cancelled.\n";
        return 0;
    }

    if (isReboot) {
        std::cout << "\nRebooting server...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        system("/usr/bin/systemctl reboot");
    } else {
        std::cout << "\nShutting down server...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        system("/usr/bin/systemctl poweroff");
    }

    return 0;
}
