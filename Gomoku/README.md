# Gomoku Game Board

This repository contains C++ code for a simple Gomoku game board implementation. The project consists of two main files:

## `GameBoard.hpp`

This header file defines a `GameBoard` class for managing the game board. It includes the following functionalities:

- **Constructor:** Initializes the game board with a specified width and height.
- **Operators:** Allows access to cells in the game board using the `[]` operator.
- **Width and Height Retrieval:** Provides methods to get the width and height of the game board.
- **Clear Board:** Resets the game board to its initial state.
- **Get Rows:** Retrieves the entire vector of vectors representing the game board.

### Usage Example

```cpp
#include "GameBoard.hpp"

// Create a Gomoku game board with a width of 15 and height of 15
Gomoku::GameBoard gameBoard(15, 15);

// Access and manipulate the game board
gameBoard[0][0] = Gomoku::GameBoard::PLAYER;

// Get the width and height of the game board
unsigned int width = gameBoard.getWidth();
unsigned int height = gameBoard.getHeight();

// Clear the game board
gameBoard.clear();
```

## `Position.hpp`

This header file defines a simple Position struct with x and y coordinates. It is used to represent positions on the game board.

### Usage Example

```cpp
#include "Position.hpp"

// Create a position with x=3 and y=4
Gomoku::Position position(3, 4);
```

Feel free to explore and modify the code as needed for your Gomoku game development. If you have any questions or suggestions, please feel free to open an issue or contribute to the project!

## License

This project is licensed under the MIT License - see the LICENSE file for details.
