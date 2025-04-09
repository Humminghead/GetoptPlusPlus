#include <iostream>
#include <GetOptPP/ConsoleKeyOption.h>
#include <GetOptPP/ConsoleOptionsHandler.h>

//Run arguments: -a --some --dummy dummy0 -d dummy1 --extended ext0 -e ext1

int main(int argc, char **argv) {
    GetOptPlusPlus::ConsoleOptionsHandler consoleHandler(argc, argv);

    consoleHandler.AddKey({nullptr, "a", 0}, [](const char*) { std::cout << R"("-a" flag without long opt and param)" << std::endl; });
    consoleHandler.AddKey({"some", nullptr, 0}, [](const char*) { std::cout << R"("--some" opt without short arg and param)" << std::endl; });
    consoleHandler.AddKey({"dummy", nullptr, 1}, [](const char* p) { std::cout <<  R"("--dummy" opt without short arg and with param:)" << p << std::endl; });
    consoleHandler.AddKey({nullptr, "d", 1}, [](const char* p) { std::cout <<  R"("-d" opt without long arg and with param:)" << p << std::endl; });
    consoleHandler.AddKey({"extended", "e", 1}, [](const char* p) { std::cout << R"("extended" opt and "e" param:)" << p << std::endl; });

    if (auto argcnt = consoleHandler.HandlersCount(); consoleHandler.ProcessCmdLine(argcnt)) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Fail!" << std::endl;
    }

    return 0;
}
