#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Hello Kitty Adventure");
    window.setFramerateLimit(60);

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("login_screen.png")) {
        return -1;
    }
    sf::Sprite background(bgTexture);

    sf::Font font;
    if (!font.loadFromFile("sniglet.ttf")) {
        return -1;
    }

    sf::Text playButton;
    playButton.setFont(font);
    playButton.setString("PLAY");
    playButton.setCharacterSize(100);

    playButton.setFillColor(sf::Color::White);
    playButton.setOutlineColor(sf::Color(255, 105, 180));
    playButton.setOutlineThickness(5);
    playButton.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = playButton.getLocalBounds();
    playButton.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);

    playButton.setPosition(250.f, 450.f);

    bool gameStarted = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (playButton.getGlobalBounds().contains(mousePos)) {
                        gameStarted = true;
                    }
                }
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (playButton.getGlobalBounds().contains(mousePos)) {
            playButton.setFillColor(sf::Color(255, 105, 180));
            playButton.setOutlineColor(sf::Color::White);
            playButton.setScale(1.1f, 1.1f);
        } else {
            playButton.setFillColor(sf::Color::White);
            playButton.setOutlineColor(sf::Color(255, 105, 180));
            playButton.setScale(1.0f, 1.0f);
        }

        window.clear();

        if (!gameStarted) {
            window.draw(background);
            window.draw(playButton);
        } else {
            window.clear(sf::Color(255, 230, 240));
        }

        window.display();
    }

    return 0;
}