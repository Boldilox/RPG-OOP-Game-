// // CombatWindow.cpp
// #include "CombatWindow.hpp"
// #include <SFML/Graphics.hpp>
// #include <iostream>

// // Constructor: Initializes the window and sprite resources
// CombatWindow::CombatWindow() {
//     window = new sf::RenderWindow(sf::VideoMode(800, 600), "Turn-Based RPG Game - Combat System");
//     knightTexture = new sf::Texture();
//     enemyTexture = new sf::Texture();
//     knightSprite = new sf::Sprite();
//     enemySprite = new sf::Sprite();

//     loadTextures();
//     createSprites();
// }

// // Destructor: Cleans up dynamically allocated resources
// CombatWindow::~CombatWindow() {
//     delete window;
//     delete knightTexture;
//     delete enemyTexture;
//     delete knightSprite;
//     delete enemySprite;
// }

// // Starts the game loop
// void CombatWindow::run() {
//     gameLoop();
// }

// // Loads textures for the knight and enemy from files
// void CombatWindow::loadTextures() {
//     if (!knightTexture->loadFromFile("knight.png")) {
//         std::cerr << "Failed to load knight texture" << std::endl;
//         exit(-1);
//     }
//     if (!enemyTexture->loadFromFile("enemy.png")) {
//         std::cerr << "Failed to load enemy texture" << std::endl;
//         exit(-1);
//     }
// }

// // Creates and positions knight and enemy sprites
// void CombatWindow::createSprites() {
//     knightSprite->setTexture(*knightTexture);
//     enemySprite->setTexture(*enemyTexture);
//     knightSprite->setPosition(100, 300);
//     enemySprite->setPosition(600, 300);
// }

// // Main game loop: Handles window events and renders sprites
// void CombatWindow::gameLoop() {
//     while (window->isOpen()) {
//         sf::Event event;
//         while (window->pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window->close();
//         }

//         window->clear();
//         window->draw(*knightSprite);
//         window->draw(*enemySprite);
//         window->display();
//     }
// }
