#include <SFML/Graphics.hpp>
#include <random>
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
    sf::Clock clock;
    sf::Texture texture;
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
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        handle_movement(player);
        window.clear();
        window.draw(player);
        // window.draw(sprite);
        window.display();
    }

    return 0;
}
