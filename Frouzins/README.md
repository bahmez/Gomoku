# Gomoku AI Controller

This repository contains C++ code for a Gomoku AI Controller. The project is organized into the following files:

## `Controller.hpp` and `Controller.cpp`

These files define and implement the `Controller` class, which serves as the main controller for the Gomoku AI. The controller handles various commands and game logic, including starting the game, taking turns, managing the game board, and making strategic moves.

### Usage Example

```cpp
#include "Controller.hpp"

int main() {
    try {
        Controller controller;

        // Start the Gomoku game with a danger level of 3
        controller.start(3);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
```

## `GameBoard.hpp` and `GameBoard.cpp`

These files define and implement the `GameBoard` class, representing the game board for Gomoku. The board can be cleared, and positions can be marked for both the player and the opponent.

## `Position.hpp`

This file defines the Position struct, representing coordinates on the game board.

## `CommandsHelper.hpp` and `CommandsHandler.cpp`

These files define and implement the CommandsHandler class, which handles commands for the Gomoku AI. Commands such as "START," "TURN," "BEGIN," "BOARD," and others are processed by the handler.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
