//
// Created by youba on 15/11/2023.
//


#include <iostream>
#include "CommandsHandler.hpp"
#include "Controller.hpp"

int main() {
    try {
        Controller controller;

        controller.start(3);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}