#include <iostream>
#include "game_window.h"

int main(int argc, char** argv) {
    std::cout << "Starting Chess Game..." << std::endl;
    try {
        ChessUI::GameWindow game(640, 640, "Chess");
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Chess Game Exited." << std::endl;
    return EXIT_SUCCESS;
}
