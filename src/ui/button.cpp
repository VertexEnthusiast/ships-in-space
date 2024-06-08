#include <ui/button.hpp>
#include <iostream>

Button::Button(int x, int y, int width, int height, sf::RenderWindow &window,
               const char *str, const char *fontPath, int xOffset, int yOffset, int fontSize) : window(window), buttonString(str)
{
    buttonRect = sf::FloatRect(x, y, width, height);
    buttonShape = sf::RectangleShape(sf::Vector2f(buttonRect.width, buttonRect.height));
    buttonShape.setPosition(x, y);
    buttonShape.setFillColor(sf::Color::Cyan);
    buttonShape.setOutlineColor(sf::Color::White);
    buttonShape.setOutlineThickness(3.0f);

    // Add button text
    if (!font.loadFromFile(fontPath))
    {
        std::cout << "Error loading font" << std::endl;
    }

    buttonString = str;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setPosition(x + xOffset, y + yOffset);
    text.setString(buttonString);
    // text.setFillColor(sf::Color::Black);
    // text.setStyle(sf::Text::Bold);
}

Button::~Button()
{
    std::cout << "Button destroyed at (" << buttonRect.left << ", " << buttonRect.top << ")\n";
}

bool Button::update()
{
    hovered = false;
    clicked = false;
    if (buttonShape.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
    {
        hovered = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicked = true;
        }
    }
    else
    {
        hovered = false;
    }

    if (clicked)
    {
        buttonShape.setFillColor(sf::Color(255, 255, 255, 64));
        return true;
    }

    if (hovered)
    {
        buttonShape.setFillColor(sf::Color(255, 255, 255, 128));
    }
    else
    {
        buttonShape.setFillColor(sf::Color(255, 255, 255, 0));
    }
    return false;
}

void Button::draw()
{
    window.draw(buttonShape);
    window.draw(text);
}