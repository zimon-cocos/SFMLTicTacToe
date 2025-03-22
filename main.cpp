#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

constexpr unsigned int wWidth {800};
constexpr unsigned int wHeight {800};
constexpr float boxWidth {30.0f};
constexpr float boxDiagonal {boxWidth * sqrt(2)};
constexpr int boxAmountX {12};
constexpr int boxAmountY {12};
constexpr float outlineThickness{4.0f};
constexpr float tempCircleRadius{boxWidth/3};
bool isNotCross {true};
constexpr float objectsSize {boxWidth/10};
constexpr int toWin {5};



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

    enum boxState
        {
            notClicked,
            Crossed,
            Circled,
        };



struct Box
{

    //!DOLEZITE!
    sf::RectangleShape shape;
    //!DOLEZITE!

    float centerPosX {0};
    float centerPosY {0};


    boxState state {notClicked};
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

int negativeIndexPrevention(int n)
{
    while(n<0)
    {
        ++n;
    }
    return n;
}

unsigned int conStatesX {0};
unsigned int conStatesY {0};
void checkForWin(int index2Check, std::vector<Box>& vct2Check, boxState toCheck4)
{
    std::cout<< "[" << vct2Check[index2Check].gridXValue << "," << vct2Check[index2Check].gridYValue << "] is crossed: " << vct2Check[index2Check].isCrossed << ",is circled:" << vct2Check[index2Check].isCircled << '\n';

    // check x axis WIP

    //stredovy win
    for(int index2CheckInLoop {index2Check - (toWin/2)}; index2CheckInLoop <= (index2Check + (toWin/2)); ++index2CheckInLoop)
        {
           //prevent negative index
            while(index2CheckInLoop<0)
            {
                ++index2CheckInLoop;
            }

            if((vct2Check[index2CheckInLoop].gridYValue == vct2Check[index2Check].gridYValue) && (vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state))
            {
                std::cout << "Index to check je: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesX;
            }
        }
    //pravobocny win
    for(int index2CheckInLoop {index2Check - toWin + 1}; index2CheckInLoop <= index2Check; ++index2CheckInLoop)

            while(index2CheckInLoop<0)
            {
                ++index2CheckInLoop;
            }

            if((vct2Check[index2CheckInLoop].gridYValue == vct2Check[index2Check].gridYValue) && (vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state))
            {
                std::cout << "Index to check je: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesX;
            }


    //check y axis WIP
    for(int index2CheckInLoop {index2Check - ((toWin/2)*boxAmountX)}; index2CheckInLoop <= (index2Check + ((toWin/2))*boxAmountX); index2CheckInLoop = index2CheckInLoop+boxAmountX)
        {
           //prevent negative index
            while(index2CheckInLoop<0)
            {
                index2CheckInLoop = index2CheckInLoop+boxAmountX;
            }

            if((vct2Check[index2CheckInLoop].gridXValue == vct2Check[index2Check].gridXValue) && (vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state))
            {
                std::cout << "Index to check je: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesY;
            }
        }
    if((conStatesX == toWin) || (conStatesY == toWin))
    {
        std::cout << "conStatesX" << conStatesX << '\n';
        std::cout << "conStatesY" << conStatesY << '\n';
        std::cout << "Win detected\n";
    }
    else
    {
        conStatesX = 0;
        conStatesY = 0;
    }
    /*//Check x axis, win type of middle placement
    if(toCheck4 == boxState::Crossed)
    {
        if((vct2Check[index2Check-1].gridYValue == vct2Check[index2Check].gridYValue) && (vct2Check[index2Check+1].gridYValue == vct2Check[index2Check].gridYValue))
           {
               if(vct2Check[index2Check-1].state == Crossed && vct2Check[index2Check].state == Crossed && vct2Check[index2Check+1].state == Crossed)
                {
                 std::cout << "Cross wins.\n";
                }
           }

        //Check y axis, win type of middle placement
        if((vct2Check[index2Check-boxAmountY].gridXValue == vct2Check[index2Check].gridXValue) && (vct2Check[index2Check+boxAmountY].gridXValue == vct2Check[index2Check].gridXValue))
           {
               if(vct2Check[index2Check-boxAmountY].state == Circled && vct2Check[index2Check].state == Circled && vct2Check[index2Check+boxAmountY].state == Circled)
                {
                 std::cout << "Cross wins.\n";
                }
           }
    }
    else
    {
        if((vct2Check[index2Check-1].gridYValue == vct2Check[index2Check].gridYValue) && (vct2Check[index2Check+1].gridYValue == vct2Check[index2Check].gridYValue))
           {
               if(vct2Check[index2Check-1].state == Circled && vct2Check[index2Check].state == Circled && vct2Check[index2Check+1].state == Circled)
                {
                 std::cout << "Circle wins.\n";
                }
           }

        //Check y axis, win type of middle placement
        if((vct2Check[index2Check-boxAmountY].gridXValue == vct2Check[index2Check].gridXValue) && (vct2Check[index2Check+boxAmountY].gridXValue == vct2Check[index2Check].gridXValue))
           {
               if(vct2Check[index2Check-boxAmountY].state == Circled && vct2Check[index2Check].state == Circled && vct2Check[index2Check+boxAmountY].state == Circled)
                {
                 std::cout << "Circle wins.\n";
                }
           }
    }*/



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

    for(long unsigned int i {0}; i<boxes.size(); ++i)
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
        if(timeElapsed.asSeconds() > 0.2);
        {
            clock.restart();
            auto mousePos = sf::Mouse::getPosition(window);
            auto transMousePos = window.mapPixelToCoords(mousePos);
            for(unsigned int i {0};i<boxes.size();++i)
                {
                    if(boxes[i].shape.getGlobalBounds().contains(transMousePos) && (boxes[i].state == boxState::notClicked))
                        {
                            //boxes[i].wasClicked = true;
                            std::cout << "Klikol si na: " << i << '\n';
                            if(isNotCross)
                            {
                                crosses.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY);
                                isNotCross = false;
                                boxes[i].state = boxState::Crossed;
                                checkForWin(i,boxes,boxState::Crossed);
                            }
                            else{
                                circles.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY,sf::Color::Blue);
                                isNotCross = true;
                                boxes[i].state = boxState::Circled;
                                checkForWin(i,boxes,boxState::Circled);
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


