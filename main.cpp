#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // ТВОЙ КОД (без изменений)
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Hello Kitty Adventure");
    window.setFramerateLimit(60);

    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("login_screen.png")) return -1;
    sf::Sprite background(bgTexture);

    sf::Font font;
    if (!font.loadFromFile("sniglet.ttf")) return -1;

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

    // --- НОВАЯ ЧАСТЬ: КАСТОМИЗАЦИЯ (для студента) ---
    bool customizationFinished = false;

    // Загружаем фон комнаты
    sf::Texture custBgTex;
    custBgTex.loadFromFile("customizer.png");
    sf::Sprite custBg(custBgTex);

    // Загружаем кнопки (просто картинки)
    sf::Texture texPrev, texNext, texSelect;
    texPrev.loadFromFile("btn_prev.png");
    texNext.loadFromFile("btn_next.png");
    texSelect.loadFromFile("btn_select.png");

    sf::Sprite sPrev(texPrev), sNext(texNext), sSelect(texSelect);
    sPrev.setPosition(450, 400);
    sNext.setPosition(850, 400);
    sSelect.setPosition(600, 600);

    // Список персонажей
    std::vector<sf::Texture> kittyTextures(5);
    std::string files[] = {"classic_kitty.png", "adventure_kitty.png", "sweet_kitty.png", "cozy_kitty.png", "magical_kitty.png"};

    for (int i = 0; i < 5; i++) {
        if (!kittyTextures[i].loadFromFile(files[i])) {
            std::cout << "Error: " << files[i] << " not found!" << std::endl;
        }
    }

    int currentKitty = 0;
    sf::Sprite currentSprite(kittyTextures[currentKitty]);
    currentSprite.setScale(1.5f, 1.5f);
    currentSprite.setPosition(450, 180);

    // --- ГЛАВНЫЙ ЦИКЛ ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Логика кликов
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (!gameStarted) {
                    // ТВОЙ КОД: Клик по PLAY
                    if (playButton.getGlobalBounds().contains(mPos)) {
                        gameStarted = true;
                        std::cout << "Starting customization..." << std::endl;
                    }
                }
                else if (!customizationFinished) {
                    // КЛИКИ В КАСТОМИЗАЦИИ
                    if (sPrev.getGlobalBounds().contains(mPos)) {
                        currentKitty = (currentKitty - 1 + 5) % 5;
                        currentSprite.setTexture(kittyTextures[currentKitty]);
                        std::cout << "Switched to: " << files[currentKitty] << std::endl;
                    }
                    if (sNext.getGlobalBounds().contains(mPos)) {
                        currentKitty = (currentKitty + 1) % 5;
                        currentSprite.setTexture(kittyTextures[currentKitty]);
                        std::cout << "Switched to: " << files[currentKitty] << std::endl;
                    }
                    if (sSelect.getGlobalBounds().contains(mPos)) {
                        customizationFinished = true;
                        std::cout << "Final choice: " << files[currentKitty] << ". Starting quest!" << std::endl;
                    }
                }
            }
        }

        // ТВОЙ КОД: Эффект наведения для кнопки PLAY
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (!gameStarted) {
            if (playButton.getGlobalBounds().contains(mousePos)) {
                playButton.setFillColor(sf::Color(255, 105, 180));
                playButton.setOutlineColor(sf::Color::White);
                playButton.setScale(1.1f, 1.1f);
            } else {
                playButton.setFillColor(sf::Color::White);
                playButton.setOutlineColor(sf::Color(255, 105, 180));
                playButton.setScale(1.0f, 1.0f);
            }
        }

        // ОТРИСОВКА
        window.clear();

        if (!gameStarted) {
            // Рисуем меню
            window.draw(background);
            window.draw(playButton);
        }
        else if (!customizationFinished) {
            // Рисуем кастомизацию
            window.draw(custBg);
            window.draw(currentSprite);
            window.draw(sPrev);
            window.draw(sNext);
            window.draw(sSelect);
        }
        else {
            // Рисуем сам Квест (белый экран с Китти)
            window.clear(sf::Color::White);
            currentSprite.setPosition(100, 300); // Китти в начале уровня
            window.draw(currentSprite);
        }

        window.display();
    }

    return 0;
}