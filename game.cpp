#include <SFML/Graphics.hpp>
#include <random>

using sf::Vector2f;
using sf::Vector2;
using sf::Color;

// In pixels
constexpr int WIDTH = 1200;
constexpr int HEIGHT = 800;

int randint(int max, int min=1)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

int main() 
{
    sf::Clock clock;
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "Frank Boss Fight"
    );
    sf::RectangleShape rect(Vector2(200.f, 100.f));
    rect.setPosition(Vector2f(300.f, 200.f));
    rect.setFillColor(Color::Magenta);
    rect.setOutlineColor(Color::White);
    rect.setOutlineThickness(5.f);
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}
