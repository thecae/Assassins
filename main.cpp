#include <iostream>
#include "include/Container.h"

int main()
{
    Container container;

    // the shell
    for (;;) {
        std::cout << "Assassins V2 $ ";
        std::string line;
        std::getline(std::cin, line);

        // special exit command
        if (line == "exit")
            break;

        if (line.substr(0,5) == "kill ") {
            std::string name = line.substr(5);
            container.kill(name);
            continue;
        }
        if (line.substr(0,7) == "wither ") {
            std::string name = line.substr(7);
            container.wither(name);
            continue;
        }
        if (line.substr(0, 3) == "map") {
            std::cout << container.getMap() << std::endl;
            continue;
        }
        if (line.substr(0, 4) == "get ") {
            std::string name = line.substr(4);
            std::cout << container.getPlayer(name).getInfo() << std::endl;
            continue;
        }
        // if it gets here, invalid command
        std::cerr << "Invalid command: " << line << std::endl;
    }

    return 0;
}