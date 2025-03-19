#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

constexpr unsigned int wWidth {800};
constexpr unsigned int wHeight {800};
constexpr float boxWidth {50.0f};
constexpr float boxHeight {50.0f};
constexpr float boxDiagonal {boxWidth * sqrt(2)};
constexpr int boxAmountX {13};
constexpr int boxAmountY {13};
constexpr float outlineThickness{4.0f};
constexpr float tempCircleRadius{15.0f};
bool isNotCross {true};

//placeholder na sprite
struct Circle
{
    sf::CircleShape shape;


    Circle(float sX, float sY,sf::Color color)
    {
        //shape.setOrigin(shape.getGeometricCenter());
        shape.setPosition({sX,sY});
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(color);
        shape.setOutlineThickness(8.0f);
        shape.setRadius(tempCircleRadius);
    }
};

struct Cross
{
    sf::RectangleShape line1;
    sf::RectangleShape line2;

    Cross(float sX, float sY)
    {

        line1.setSize({boxDiagonal,8.0f});
        line1.setOrigin(line1.getGeometricCenter());
        line1.setPosition({sX+(boxWidth/4)+(boxWidth/22),sY+(boxHeight/4)+(boxHeight/22)});
        line1.setFillColor(sf::Color::Red);
        line1.rotate(sf::degrees(45));


        line2.setSize({boxDiagonal,8.0f});
        line2.setOrigin(line2.getGeometricCenter());
        line2.setPosition({sX+(boxWidth/4)+(boxWidth/22),sY+(boxHeight/4)+(boxHeight/22)});
        line2.setFillColor(sf::Color::Red);
        line2.rotate(sf::degrees(135));
    }
};




struct Box
{

    //!DOLEZITE!
    sf::RectangleShape shape;
    //!DOLEZITE!

    float centerPosX {0};
    float centerPosY {0};
    bool wasClicked {false};
    Box(float bX, float bY)
    {
        shape.setPosition({bX,bY});
        shape.setFillColor(sf::Color::Transparent);
        shape.setSize({boxWidth,boxHeight});
        shape.setOutlineThickness(outlineThickness);
        shape.setOutlineColor(sf::Color::Black);
        centerPosX = (bX + (boxWidth/2) - (outlineThickness*(tempCircleRadius/outlineThickness)));
        centerPosY = (bY + (boxHeight/2) - (outlineThickness*(tempCircleRadius/outlineThickness)));
    }

};





int main()
{

    sf::RenderWindow window (sf::VideoMode({wWidth,wHeight}),"TicTacToe");
    window.setFramerateLimit(60);

    std::vector<Box> boxes;
    int gapX {0};
    int gapY {0};
    for(int i {0}; i<boxAmountY; ++i)
        {
        for(int i {0};i<boxAmountX; ++i)
            {
                boxes.emplace_back(outlineThickness*2+gapX,outlineThickness*2+gapY);
                gapX += 60;
            }

        gapX  = 0;
        gapY += 60;
        }

    std::vector<Circle> circles;
    std::vector<Cross> crosses;



    sf::Clock clock;
    while (window.isOpen())
    {

        sf::Time timeElapsed = clock.getElapsedTime();
        while(const std::optional event = window.pollEvent()){

        if(event->is<sf::Event::Closed>()){
            window.close();
            }

        else if(const auto*keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                window.close();
            }
            }

        }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if(timeElapsed.asSeconds() > 0.2)
        {
            clock.restart();
            auto mousePos = sf::Mouse::getPosition(window);
            auto transMousePos = window.mapPixelToCoords(mousePos);
            for(unsigned int i {0};i<boxes.size();++i)
                {
                    if(boxes[i].shape.getGlobalBounds().contains(transMousePos))
                    {
                        boxes[i].wasClicked = true;
                        if(isNotCross)
                        {
                            crosses.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY);
                            isNotCross = false;

                            std::cout << boxes[i].centerPosX << "," << boxes[i].centerPosY << '\n';
                        }
                        else{
                            circles.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY,sf::Color::Blue);
                            isNotCross = true;
                            std::cout << boxes[i].centerPosX << "," << boxes[i].centerPosY << '\n';
                        }

                        }

                }
        }


    }


    //RENDER
    window.clear(sf::Color::White);

    //KRESLENIE

    for(unsigned int i {0};i<boxes.size();++i)
        {

            window.draw(boxes[i].shape);
        }




    for(unsigned int i {0};i<circles.size();++i)
        {
            window.draw(circles[i].shape);
        }

    for(unsigned int i {0};i<crosses.size();++i)
        {
            window.draw(crosses[i].line1);
            window.draw(crosses[i].line2);
        }




    window.display();

}
}


