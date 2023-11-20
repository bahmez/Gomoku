//
// Created by youba on 14/11/2023.
//

#pragma once

#include <vector>

namespace Gomoku {
    struct Position {
        Position(int _x, int _y): x(_x), y(_y) {}
        int x;
        int y;
    };
    class GameBoard {
    public:
        enum Cell {
            EMPTY,
            PLAYER,
            OPPONENT
        };
        GameBoard(unsigned int _width, unsigned int _height);
        const std::vector<Cell> &operator[](std::size_t y) const;
        std::vector<Cell> &operator[](std::size_t y);
        unsigned int getWidth() const;
        unsigned int getHeight() const;
        void clear();
        std::vector<std::vector<Cell>> &getRows();
    private:
        std::vector<std::vector<Cell>> _gameBoard;
        unsigned int _width;
        unsigned int _height;
    };
} // Gomoku
