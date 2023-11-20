//
// Created by youba on 18/11/2023.
//

#include <iostream>
#include <algorithm>
#include "Controller.hpp"

Controller::Controller() {
    this->_handler.subscribe("START", [&](const std::vector<std::string> &argument) {
        try {
            int size = std::stoi(argument.at(0));
            if (size <= 0) {
                printError("invalid size");
            } else {
                this->_gameBoard = std::make_unique<Gomoku::GameBoard>(size, size);
                std::cout << "OK" << std::endl;
            }
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("TURN", [&](const std::vector<std::string> &argument) {
        try {
            std::string xString = argument.at(0).substr(0, argument.at(0).find(","));
            std::string yString = argument.at(0).substr(argument.at(0).find(",") + 1, argument.at(0).back());
            int x = std::stoi(xString);
            int y = std::stoi(yString);
            this->turn(x, y);
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("BEGIN", [&](const std::vector<std::string> &argument) {
        try {
            this->begin();
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("BOARD", [&](const std::vector<std::string> &argument) {
        try {
            this->_listenBoard = true;
            this->_gameBoard->clear();
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("DONE", [&](const std::vector<std::string> &argument) {
        try {
            this->_listenBoard = false;
            this->nextMove();
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("INFO", [&](const std::vector<std::string> &argument) {
        // TODO : Remplir les informations avec les éléments d'info
    });
    this->_handler.subscribe("END", [&](const std::vector<std::string> &argument) {
        try {
            this->_isEnded = true;
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("ABOUT", [&](const std::vector<std::string> &argument) {
        try {
            this->about();
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
    this->_handler.subscribe("NotFound", [&](const std::vector<std::string> &argument) {
        try {
            if (this->_listenBoard) {
                this->board(std::stoi(argument.at(0)), std::stoi(argument.at(1)), std::stoi(argument.at(2)));
            }
        } catch (std::exception &e) {
            printError(std::string(e.what()));
        }
    });
}

void Controller::start(int danger) {
    this->_danger = danger;
    while (!this->_isEnded)
        this->_handler.update();
}

std::vector<Controller::Possibility> Controller::getPossibilities(const Gomoku::Position &position, Gomoku::GameBoard::Cell cell) {
    std::vector<Controller::Possibility> possibilities;
    std::vector<Gomoku::Position> tmp;
    int force = 0;

    // ligne de gauche vers la droite
    for (int x = position.x; x - position.x < 5; x++) {
        if (x == this->_gameBoard->getWidth()) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](position.y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, position.y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne de droite vers la gauche
    for (int x = position.x, i = 0; i < 5; x--, i++) {
        if (x == -1) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](position.y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, position.y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne de haut vers le bas
    for (int y = position.y; y - position.y < 5; y++) {
        if (y == this->_gameBoard->getHeight()) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(position.x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(position.x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne de bas vers le haut
    for (int y = position.y, i = 0; i < 5; y--, i++) {
        if (y == -1) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(position.x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(position.x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne du haut gauche vers le bas droite
    for (int x = position.x, y = position.y, i = 0; i < 5; y++, x++, i++) {
        if (x == this->_gameBoard->getWidth() || y == this->_gameBoard->getWidth()) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne du bas gauche vers le haut droite
    for (int x = position.x, y = position.y, i = 0; i < 5; y--, x++, i++) {
        if (x == this->_gameBoard->getWidth() || y == -1) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne du bas droite vers le haut gauche
    for (int x = position.x, y = position.y, i = 0; i < 5; y--, x--, i++) {
        if (x == -1 || y == -1) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    tmp.clear();
    force = 0;
    // ligne du haut droite vers le bas gauche
    for (int x = position.x, y = position.y, i = 0; i < 5; y++, x--, i++) {
        if (x == -1|| y == this->_gameBoard->getWidth()) {
            tmp.clear();
            break;
        }
        auto it = this->_gameBoard->operator[](y).at(x);
        if (it == Gomoku::GameBoard::EMPTY) {
            if (tmp.empty())
                tmp.emplace_back(x, y);
            continue;
        }
        if (it == cell) {
            force++;
            continue;
        }
        tmp.clear();
        break;
    }
    for (const auto &pos : tmp)
        possibilities.emplace_back(pos.x, pos.y, force);
    return possibilities;
}

std::vector<Controller::Possibility> Controller::getPossibilities(Gomoku::GameBoard::Cell cell) {
    std::vector<Possibility> possibilities;
    int y = 0;
    int x = 0;

    for (const auto &row : this->_gameBoard->getRows()) {
        for (const auto &element : row) {
            if (element == cell) {
                auto tmp = this->getPossibilities({x, y}, cell);
                possibilities.insert(possibilities.end(), tmp.begin(), tmp.end());
            }
            x++;
        }
        y++;
        x = 0;
    }
    return possibilities;
}

std::optional<Gomoku::Position> Controller::getWinPosition(const std::vector<Possibility> &possibilities) {
    for (const auto &possibility : possibilities) {
        if (possibility.force == 4) {
            return possibility.position;
        }
    }
    return std::nullopt;
}

void Controller::getDefensePositions() {
    auto possibilities = this->getPossibilities(Gomoku::GameBoard::OPPONENT);
    Possibility finalMove = {0, 0, -1};
    for (auto &move : possibilities) {
        if (move.force >= finalMove.force && move.force >= this->_danger) {
            for (const auto &otherMove : possibilities)
                if (otherMove.position.x == move.position.x && otherMove.position.y == move.position.y)
                    move.subForce++;
            if (move.force > finalMove.force || finalMove.subForce < move.subForce)
                finalMove = move;
        }
    }
    if (finalMove.force >= this->_danger)
        this->_possibilities.push_back(finalMove);
}

void Controller::getAttackPositions(const std::vector<Possibility> &possibilities) {
    if (possibilities.empty()) {
        auto possibilitiesOpponents = this->getPossibilities(Gomoku::GameBoard::OPPONENT);

        if (possibilitiesOpponents.empty()) {
            int y = 0;
            int x = 0;

            for (const auto &row : this->_gameBoard->getRows()) {
                for (const auto &element: row) {
                    if (element == Gomoku::GameBoard::EMPTY) {
                        this->_possibilities.emplace_back(x, y, 1);
                        return;
                    }
                    x++;
                }
                y++;
                x = 0;
            }
        } else {
            Possibility finalMove = {0, 0, -1};
            for (const auto &move : possibilitiesOpponents)
                if (move.force > finalMove.force)
                    finalMove = move;
            this->_possibilities.push_back(finalMove);
        }
    } else {
        this->_possibilities.insert(this->_possibilities.end(), possibilities.begin(), possibilities.end());
    }
}

void Controller::begin() {
    if (!this->_gameBoard) return printError("GameBoard not initialized");
    unsigned int middle = this->_gameBoard->getWidth() / 2;
    std::cout << middle << "," << middle << std::endl;
    this->_gameBoard->operator[](middle).at(middle) = Gomoku::GameBoard::PLAYER;
}

void Controller::turn(int x, int y) {
    if (!this->_gameBoard) return printError("GameBoard not initialized");
    this->_gameBoard->operator[](y).at(x) = Gomoku::GameBoard::OPPONENT;
    this->nextMove();
}

void Controller::board(int x, int y, int field) {
    if (!this->_gameBoard) return printError("GameBoard not initialized");
    if (field) {
        this->_gameBoard->operator[](y).at(x) = Gomoku::GameBoard::PLAYER;
    } else {
        this->_gameBoard->operator[](y).at(x) = Gomoku::GameBoard::OPPONENT;
    }
}

void Controller::nextMove() {
    auto possibilities = this->getPossibilities(Gomoku::GameBoard::PLAYER);
    auto winnerMove = this->getWinPosition(possibilities);
    if (winnerMove) {
        std::cout << winnerMove.value().x << "," << winnerMove.value().y << std::endl;
    } else {
        this->getDefensePositions();
        if (this->_possibilities.empty())
            this->getAttackPositions(possibilities);
        Possibility finalMove = {0, 0, -1};
        for (const auto &move : this->_possibilities)
            if (move.force > finalMove.force)
                finalMove = move;
        if (finalMove.force == -1) {
            this->printError("Invalid scenario");
        } else {
            std::cout << finalMove.position.x << "," << finalMove.position.y << std::endl;
            this->_gameBoard->operator[](finalMove.position.y).at(finalMove.position.x) = Gomoku::GameBoard::PLAYER;
        }
        this->_possibilities.clear();
    }
}

void Controller::about() {
    std::cout << "name=\"FrouzinsBrain\", version=\"0.1\", author=\"Y.Bahri\", country=\"FR\"" << std::endl;
}

void Controller::printError(const std::string &message) {
    std::cout << "ERROR " << message << std::endl;
}
