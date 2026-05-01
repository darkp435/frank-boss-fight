#include <SFML/Graphics.hpp>
#include <random>
#include <bits/stdc++.h>
#include <windows.h>
#include <print>
#include "debug.hpp"

using sf::Vector2f;
using sf::Vector2;
using sf::Color;

// In pixels
constexpr int   WIDTH     = 1200;
constexpr int   HEIGHT    = 800;
constexpr float MOVESPEED = 0.5f;

int randint(int max, int min=1)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

// Player may not actually be RentangleShape in the future
void handle_movement(sf::RectangleShape& player) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        player.move({0.f, -MOVESPEED});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        player.move({0.f, MOVESPEED});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player.move({MOVESPEED, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player.move({-MOVESPEED, 0.f});
    }
}

int main()
{
    sf::Font font;
    if (!font.openFromFile("uifont.ttf")) {
        Debug::error("UI font failed to load.");
        return 1;
    }
    sf::Text text(font);
    text.setString("SIR FRANK JIN, THE ALL-CALCULATING");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Red);
    text.setPosition(Vector2f(100, 0));
    sf::Clock clock;
    sf::Texture texture;
    // sf::View world_view;
    // world_view.setSize(Vector2f(WIDTH, HEIGHT));
    // sf::View ui_view;
    // ui_view.setSize(Vector2f(WIDTH, HEIGHT));
    // texture.loadFromFile("fear.png");
    // sf::Sprite sprite(texture);
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "Frank Boss Fight"
    );
    sf::RectangleShape player(Vector2(200.f, 100.f));
    player.setPosition(Vector2f(300.f, 200.f));
    player.setFillColor(Color::Magenta);
    player.setOutlineColor(Color::White);
    player.setOutlineThickness(5.f);
    
    /*
    View system
    View world_view is used for drawing game objects.
    View ui_view is used for drawing the UI, called after drawing the world.
    They should function completely independently. It is a bug if the ui_view
    affects the world_view and vice versa.
    */
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        handle_movement(player);
        window.clear();
        window.draw(player);
        window.draw(text);
        // window.draw(sprite);
        window.display();
    }

    return 0;
}
