#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <array>
#include <cmath>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

//int screen_x = GetSystemMetrics(0);
//int screen_y = GetSystemMetrics(1);
int screen_x = GetSystemMetrics(SM_CXSCREEN);
int screen_y = GetSystemMetrics(SM_CYSCREEN);
const size_t img_num = 32;

array<sf::Image, img_num> imgProcessing()
{
    
    array<sf::Image, img_num> splitImg;
    splitImg.fill(sf::Image({99, 64}, sf::Color::Black));
    sf::Image tiles2("preview.jpg");

    array<int, 2> imgNum2d = {8, 4};
    array<int, 2> startingPos = {34, 443};
    int i = 0;

    for (int y = 0; y < imgNum2d[1]; y++)
    {
        for (int x = 0; x < imgNum2d[0]; x++)
        {   
            if (!splitImg[i].copy(tiles2, {0,0}, sf::IntRect(sf::Vector2i({startingPos[0]+(x*110), startingPos[1]+(y*75)}), sf::Vector2i({100, 65}))))
            {
                cout << x << ", " << y << ", " << "i: " << i << "not working\n";
            }
                
            i++;
        }
    }
    

    return splitImg;
}


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window", sf::Style::Default);
    array<sf::Image, img_num> tileImg = imgProcessing();
    sf::Texture tilesTexture({99, 64});
    sf::Sprite tilesSprite(tilesTexture);
    sf::Clock clock;
    sf::Font font("arial/ARIAL.ttf");
    sf::Text text(font);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (event->is<sf::Event::Resized>())
            {
                sf::View view(sf::FloatRect({0.f,0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
                //std::cout << window.getView().getSize().x << ", " << window.getView().getSize().y;
            }
        }
        
        
        sf::Time elapsed = clock.restart();
        // clear the window with black color
        window.clear(sf::Color::Black);

        for (int i = 0; i < img_num; i++)
        {
            tilesTexture.update(tileImg[i]);
            window.draw(tilesSprite);
            tilesSprite.setPosition({(i%6)*100.f, floor(i/6.f)*65.f});
        }

        text.setString(to_string(1.f/elapsed.asSeconds()));
        window.draw(text);
        // draw everything here...
        // window.draw(...);

        // end the current frame
        
        window.display();

    }
}