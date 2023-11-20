//
// Created by youba on 18/11/2023.
//

#pragma once


#include <memory>
#include <optional>
#include "CommandsHandler.hpp"
#include "GameBoard.hpp"

class Controller {
public:
    struct Possibility {
        Possibility(int x, int y, int _force): position(x, y), force(_force), subForce(1) {}
        Gomoku::Position position;
        int force;
        int subForce;
    };
    Controller();
    void start(int danger = 0);
    std::optional<Gomoku::Position> getWinPosition(const std::vector<Possibility> &possibilities);
    void getDefensePositions();
    void getAttackPositions(const std::vector<Possibility> &possibilities);
    void begin();
    void turn(int x, int y);
    void board(int x, int y, int field);
    void about();
    void nextMove();
private:
    std::vector<Possibility> getPossibilities(const Gomoku::Position &position, Gomoku::GameBoard::Cell cell);
    std::vector<Possibility> getPossibilities(Gomoku::GameBoard::Cell cell);
    void printError(const std::string &message);
    bool _isEnded = false;
    bool _listenBoard = false;
    int _danger = 0;
    std::vector<Possibility> _possibilities;
    CommandsHandler _handler;
    std::unique_ptr<Gomoku::GameBoard> _gameBoard;
};
