#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Turn-Based RPG Game - Combat System");

    // Load textures for knight and enemy
    sf::Texture knightTexture, enemyTexture;
    if (!knightTexture.loadFromFile("knight.png")) {
        std::cerr << "Failed to load knight texture" << std::endl;
        return -1;
    }
    if (!enemyTexture.loadFromFile("enemy.png")) {
        std::cerr << "Failed to load enemy texture" << std::endl;
        return -1;
    }

    // Create sprites for knight and enemy
    sf::Sprite knightSprite(knightTexture), enemySprite(enemyTexture);

    // Positioning the knight and enemy
    knightSprite.setPosition(100, 300); // Knight's position
    enemySprite.setPosition(600, 300);  // Enemy's position

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(knightSprite); // Draw the knight
        window.draw(enemySprite);  // Draw the enemy
        window.display();
    }

    return 0;
}
