#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>

// In pixels
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

int randint(int max, int min=1)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

int main() 
{
    using sf::Vector2f;

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Frank Boss Fight"
    );
    sf::RectangleShape rect(sf::Vector2(200.f, 100.f));
    rect.setPosition(Vector2f(300.f, 200.f));
    rect.setFillColor(sf::Color::Magenta);
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
