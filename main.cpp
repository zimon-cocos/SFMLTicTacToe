#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

constexpr unsigned int wWidth {800};
constexpr unsigned int wHeight {800};
constexpr float boxWidth {60.0f};
constexpr float boxDiagonal {boxWidth * sqrt(2)};
constexpr int boxAmountX {6};
constexpr int boxAmountY {6};
constexpr float outlineThickness{4.0f};
constexpr float tempCircleRadius{boxWidth/3};
bool isNotCross {true};
constexpr float objectsSize {boxWidth/10};



struct Circle
{
    sf::CircleShape shape;

    Circle(float sX, float sY,sf::Color color)
    {

        shape.setPosition({sX,sY});
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(color);
        shape.setOutlineThickness(objectsSize);
        shape.setRadius(tempCircleRadius);
        shape.setOrigin(shape.getGeometricCenter());
    }
};

struct Cross
{
    sf::RectangleShape line1;
    sf::RectangleShape line2;

    Cross(float sX, float sY)
    {

        line1.setSize({boxDiagonal-objectsSize,objectsSize});
        line1.setOrigin(line1.getGeometricCenter());
        line1.setPosition({sX,sY});
        line1.setFillColor(sf::Color::Red);
        line1.rotate(sf::degrees(45));


        line2.setSize({boxDiagonal-objectsSize,objectsSize});
        line2.setOrigin(line2.getGeometricCenter());
        line2.setPosition({sX,sY});
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
    bool isCrossed {false};
    bool isCircled {false};

    int gridXValue {0};
    int gridYValue {0};

    Box(float bX, float bY)
    {
        shape.setPosition({bX,bY});
        shape.setFillColor(sf::Color::Transparent);
        shape.setSize({boxWidth,boxWidth});
        shape.setOutlineThickness(outlineThickness);
        shape.setOutlineColor(sf::Color::Black);
        centerPosX = (bX + (boxWidth/2));
        centerPosY = (bY + (boxWidth/2));
    }

};


void checkForWin(unsigned int index2Check, std::vector<Box>& vct2Check)
{
    std::cout<< "[" << vct2Check[index2Check].gridXValue << "," << vct2Check[index2Check].gridYValue << "] is crossed: " << vct2Check[index2Check].isCrossed << ",is circled:" << vct2Check[index2Check].isCircled << '\n';
    //Check x axis, win type of middle placement
    if((vct2Check[index2Check-1].gridYValue == vct2Check[index2Check].gridYValue) && (vct2Check[index2Check+1].gridYValue == vct2Check[index2Check].gridYValue))
       {
           if(vct2Check[index2Check-1].isCrossed && vct2Check[index2Check].isCrossed && vct2Check[index2Check+1].isCrossed)
            {
             std::cout << "Cross wins.\n";
            }
       }

    //Check y axis, win type of middle placement
    if((vct2Check[index2Check-boxAmountY].gridXValue == vct2Check[index2Check].gridXValue) && (vct2Check[index2Check+boxAmountY].gridXValue == vct2Check[index2Check].gridXValue))
       {
           if(vct2Check[index2Check-boxAmountY].isCrossed && vct2Check[index2Check].isCrossed && vct2Check[index2Check+boxAmountY].isCrossed)
            {
             std::cout << "Cross wins.\n";
            }
       }


}




int main()
{

    sf::RenderWindow window (sf::VideoMode({wWidth,wHeight}),"TicTacToe");
    window.setFramerateLimit(60);

    sf::Font font("Roboto-Italic-VariableFont_wdth,wght.ttf");




    std::vector<Box> boxes;

    float gapX {0};
    float gapY {0};
    for(int i {0}; i<boxAmountY; ++i)
        {
        for(int i {0};i<boxAmountX; ++i)
            {
                boxes.emplace_back(outlineThickness*2+gapX+100,outlineThickness*2+gapY+100);
                gapX += boxWidth+outlineThickness*2;

            }

        gapX  = 0;
        gapY += boxWidth+outlineThickness*2;
        }

    int boxesX {0};
    int boxesY {0};

    for(int i {0}; i<boxes.size(); ++i)
        {
            if(boxesX < boxAmountX)
            {
                boxes[i].gridXValue = boxesX;
                boxes[i].gridYValue = boxesY;
                ++boxesX;
            }
            else
            {
                boxesX = 0;
                ++boxesY;
                boxes[i].gridXValue = boxesX;
                boxes[i].gridYValue = boxesY;
                ++boxesX;
            }

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
                    if(boxes[i].shape.getGlobalBounds().contains(transMousePos)) //&& !(boxes[i].wasClicked))
                        {
                            boxes[i].wasClicked = true;

                            if(isNotCross)
                            {
                                crosses.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY);
                                isNotCross = false;
                                boxes[i].isCrossed = true;
                            }
                            else{
                                circles.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY,sf::Color::Blue);
                                isNotCross = true;
                                boxes[i].isCircled = true;
                            }
                            checkForWin(i,boxes);
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


