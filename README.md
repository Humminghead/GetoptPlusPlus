# GetoptPlusPlus

This is the C++ equivalent of the old good C getopt library. This library parses command line options and has the ability to add handlers to each option.

#### Example of usage:

```C++
#include <cassert>
#include <iostream>
#include <GetOptPP/ConsoleKeyOption.h>
#include <GetOptPP/ConsoleOptionsHandler.h>

//Run arguments: -a --some --dummy dummy0 -d dummy1 --extended ext0 -e ext1

int main(int argc, char **argv) {
    // Create the handler
    GetOptPlusPlus::ConsoleOptionsHandler consoleHandler(argc, argv);

    // Add handlers
    consoleHandler.AddKey({nullptr, "a", 0}, [](const char*) { std::cout << R"("-a" flag without long opt and param)" << std::endl; });
    consoleHandler.AddKey({"some", nullptr, 0}, [](const char*) { std::cout << R"("--some" opt without short arg and param)" << std::endl; });
    consoleHandler.AddKey({"dummy", nullptr, 1}, [](const char* p) { std::cout <<  R"("--dummy" opt without short arg and with param:)" << p << std::endl; });
    consoleHandler.AddKey({nullptr, "d", 1}, [](const char* p) { std::cout <<  R"("-d" opt without long arg and with param:)" << p << std::endl; });
    consoleHandler.AddKey({"extended", "e", 1}, [](const char* p) { std::cout << R"("extended" opt and "e" param:)" << p << std::endl; });

    // Re-adding the handler
    bool isAdded = consoleHandler.AddKey({"some", nullptr, 0}, [](const char*) { std::cout << R"("--some" opt without short arg and param)" << std::endl; });
    assert( isAdded == false );

    // Process the args and their options
    if (auto argcnt = consoleHandler.ProcessCmdLine(); consoleHandler.HandlersCount() > 0) {
        std::cout << "Successfully processed: " << std::to_string(argcnt) << std::endl;
    }

    return 0;
}
```
