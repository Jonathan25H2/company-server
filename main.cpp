#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

int main() {
    std::string command;

    while (true) {
        std::cout << "Command (shutdown / reboot / exit): ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        if (command != "shutdown" && command != "reboot") {
            std::cout << "Unknown command.\n";
            continue;
        }
        std::cout << "\n================ WARNING ================\n";
        std::cout << "You are about to " << command << " this server.\n\n";
        std::cout << "Possible consequences:\n";
        std::cout << "- All active users will be disconnected\n";
        std::cout << "- Running services and applications will stop\n";
        std::cout << "- Active file transfers may be interrupted\n";
        std::cout << "- Unsaved data may be lost\n";
        std::cout << "- The server will be temporarily unavailable\n\n";
        std::cout << "Only continue if you are sure it is safe to do so.\n";
        std::cout << "=========================================\n";
        std::cout << "Confirmation available in:\n";

        for (int i = 5; i > 0; i--) {
            std::cout << i << "...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        char confirm;
        std::cout << "Continue? (y/n): ";
        std::cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            if (command == "shutdown") {
                std::cout << "Shutting down...\n";
                system("sudo systemctl poweroff");
            }
            else {
                std::cout << "Rebooting...\n";
                system("sudo systemctl reboot");
            }
        }
        else {
            std::cout << "Cancelled.\n";
        }
    }

    return 0;
}
