#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Hello Kitty Adventure");
    window.setFramerateLimit(60);

    sf::Texture bgMenuTex, custBgTex, texPrev, texNext, texSelect, texPlay;

    if (!bgMenuTex.loadFromFile("login_screen.png") ||
        !custBgTex.loadFromFile("customizer.png") ||
        !texPrev.loadFromFile("btn_prev.png") ||
        !texNext.loadFromFile("btn_next.png") ||
        !texSelect.loadFromFile("btn_select.png") ||
        !texPlay.loadFromFile("btn_play.png")) return -1;

    sf::Sprite background(bgMenuTex);

    sf::Sprite playBtn(texPlay);
    playBtn.setOrigin(playBtn.getLocalBounds().width / 2.f, playBtn.getLocalBounds().height / 2.f);
    playBtn.setPosition(250.f, 450.f);

    sf::Texture animTex1, animTex2;
    animTex1.loadFromFile("kitty_hello1.png");
    animTex2.loadFromFile("kitty_hello2.png");
    sf::Sprite animKitty(animTex1);
    animKitty.setPosition(800.f, 170.f);
    animKitty.setScale(1.2f, 1.2f);
    sf::Clock animClock;

    sf::Sprite custBg(custBgTex);
    sf::Sprite sPrev(texPrev), sNext(texNext), sSelect(texSelect);
    sPrev.setPosition(450, 450);
    sNext.setPosition(850, 450);
    sSelect.setPosition(730, 650);
    sSelect.setOrigin(sSelect.getLocalBounds().width / 2.f, sSelect.getLocalBounds().height / 2.f);

    std::vector<sf::Texture> kTex(5);
    std::string files[] = {"classic_kitty.png", "adventure_kitty.png", "sweet_kitty.png", "cozy_kitty.png", "magical_kitty.png"};
    for (int i = 0; i < 5; i++) kTex[i].loadFromFile(files[i]);

    int current = 0;
    sf::Sprite kitty(kTex[current]);

    auto updateView = [&]() {
        kitty.setTexture(kTex[current]);
        kitty.setPosition(370.f, 60.f);
        kitty.setScale(1.5f, 1.5f);
    };
    updateView();

    bool gameStarted = false, customizationFinished = false;

    while (window.isOpen()) {
        sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!gameStarted) {
                    if (playBtn.getGlobalBounds().contains(mPos)) gameStarted = true;
                }
                else if (!customizationFinished) {
                    if (sPrev.getGlobalBounds().contains(mPos)) { current = (current - 1 + 5) % 5; updateView(); }
                    if (sNext.getGlobalBounds().contains(mPos)) { current = (current + 1) % 5; updateView(); }
                    if (sSelect.getGlobalBounds().contains(mPos)) customizationFinished = true;
                }
            }
        }

        if (!gameStarted) {
            if (animClock.getElapsedTime().asSeconds() > 0.5f) {
                animKitty.setTexture(animKitty.getTexture() == &animTex1 ? animTex2 : animTex1);
                animClock.restart();
            }

            bool hover = playBtn.getGlobalBounds().contains(mPos);
            playBtn.setScale(hover ? 1.1f : 1.0f, hover ? 1.1f : 1.0f);
        }

        window.clear();

        if (!gameStarted) {
            window.draw(background);
            window.draw(playBtn);
            window.draw(animKitty);
        }
        else if (!customizationFinished) {
            window.draw(custBg);
            window.draw(kitty);
            window.draw(sPrev); window.draw(sNext); window.draw(sSelect);
        }
        else {
            window.clear(sf::Color(255, 192, 203));
        }

        window.display();
    }
    return 0;
}