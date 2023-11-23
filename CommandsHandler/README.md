# CommandsHandler

This repository contains C++ code for a simple `CommandsHandler` class. The `CommandsHandler` is designed to handle and dispatch commands received from standard input. The project consists of two main files:

## `CommandsHandler.hpp` and `CommandsHandler.cpp`

These files define and implement the `CommandsHandler` class, which facilitates the subscription and processing of commands.

### Usage Example

```cpp
#include "CommandsHandler.hpp"

int main() {
    CommandsHandler handler;

    // Subscribe to a command named "START" with a corresponding function
    handler.subscribe("START", [](const std::vector<std::string> &arguments) {
        // Handle the "START" command
        // ...
    });

    // Subscribe to a default handler for unknown commands
    handler.subscribe("NotFound", [](const std::vector<std::string> &arguments) {
        std::cout << "Unknown command: " << arguments.front() << std::endl;
    });

    // Continuously update and process commands from standard input
    while (true) {
        handler.update();
    }

    return 0;
}
```

## Functionalities

- Subscription: The subscribe method allows functions to be associated with specific command names.
- Update: The update method reads a line from standard input, extracts the command name, and invokes the corresponding function with the provided arguments. If the    command is not subscribed, it invokes the "NotFound" handler.

## Contributing

Contributions to the project are welcome! If you have suggestions, bug reports, or enhancements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.