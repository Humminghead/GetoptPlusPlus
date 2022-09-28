# GetoptPlusPlus

This is the C++ equivalent of the old good C getopt library. This library parses command line options and has the ability to add handlers to each option.

#### Example of usage:

```C++
#include <iostream>
#include <GetOptPP/ConsoleKeyOption.h>
#include <GetOptPP/ConsoleOptionsHandler.h>
#include <netinet/ip6.h>

//Run arguments: -t --param 741

int main(int argc, char **argv) {
    GetOptPlusPlus::ConsoleOptionsHandler consoleHandler(argc, argv);
    consoleHandler.AddKey({"test", "t", 0}, [](const char*) { std::cout << "Has arg without param" << std::endl; });
    consoleHandler.AddKey({"param", "p", 1}, [](const char* arg) { std::cout << "Has arg: "<<arg << std::endl; });

    if (auto argcnt = consoleHandler.HandlersCount(); consoleHandler.ProcessCmdLine(argcnt)) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Fail!" << std::endl;
    }

    return 0;
}
```
