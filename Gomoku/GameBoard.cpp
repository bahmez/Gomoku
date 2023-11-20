//
// Created by youba on 14/11/2023.
//

#include "GameBoard.hpp"

namespace Gomoku {
    GameBoard::GameBoard(unsigned int _width, unsigned int _height):
    _height(_height),
    _width(_width) {
        std::vector<GameBoard::Cell> row;

        row.resize(this->_width, GameBoard::EMPTY);
        this->_gameBoard.resize(this->_height, row);
    }

    const std::vector<GameBoard::Cell> &GameBoard::operator[](std::size_t y) const {
        return this->_gameBoard[y];
    }

    std::vector<GameBoard::Cell> &GameBoard::operator[](std::size_t y) {
        return this->_gameBoard[y];
    }

    unsigned int GameBoard::getWidth() const {
        return this->_width;
    }

    unsigned int GameBoard::getHeight() const {
        return this->_height;
    }

    void GameBoard::clear() {
        std::vector<GameBoard::Cell> row;

        row.resize(this->_width, GameBoard::EMPTY);
        this->_gameBoard.resize(this->_height, row);
    }

    std::vector<std::vector<GameBoard::Cell>> &GameBoard::getRows() {
        return this->_gameBoard;
    }
}