//
// Created by youba on 14/11/2023.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "CommandsHandler.hpp"

CommandsHandler::CommandsHandler() {}

void
CommandsHandler::subscribe(const std::string &name, std::function<void(const std::vector<std::string> &)> function) {
    this->_events[name] = function;
}

void CommandsHandler::update() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream commandStream(line);
    std::string commandName;
    std::string argument;
    std::vector<std::string> arguments;

    std::ofstream outfile;

    outfile.open("test.txt", std::ios_base::app);
    outfile << line << "\n";
    commandStream >> commandName;
    if (!this->_events.contains(commandName))
        arguments.push_back(commandName);
    while (commandStream >> argument)
        arguments.push_back(argument);
    if (!this->_events.contains(commandName))
        return this->_events["NotFound"](arguments);
    this->_events[commandName](arguments);
}
