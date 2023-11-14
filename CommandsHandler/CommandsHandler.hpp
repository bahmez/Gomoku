//
// Created by youba on 14/11/2023.
//

#pragma once

#include <map>
#include <string>
#include <vector>
#include <functional>

class CommandsHandler {
public:
    CommandsHandler();
    ~CommandsHandler() = default;
    void subscribe(const std::string &name, std::function<void (const std::vector<std::string> &)> function);
    void update();
private:
    std::map<std::string, std::function<void (const std::vector<std::string> &)>> _events;
};
