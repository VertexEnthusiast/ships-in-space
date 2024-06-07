#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <manager/manager.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    // sf::Texture texture;
    // texture.loadFromFile("assets/Alyssa.png");
    GameManager manager(&window);
    // change the size of the window
    window.setFramerateLimit(60);
    // window.setSize(sf::Vector2u(800, 600));

    // run the program as long as the window is open
    while (window.isOpen() and !manager.quit)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        manager.update();
        manager.draw();
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}