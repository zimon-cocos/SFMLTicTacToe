#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

constexpr unsigned int wWidth {900};
constexpr unsigned int wHeight {900};
constexpr float boxWidth {15.0f};
constexpr float boxDiagonal {boxWidth * sqrt(2)};
constexpr int boxAmountX {47};
constexpr int boxAmountY {47};
constexpr float outlineThickness{2.0f};
constexpr float tempCircleRadius{boxWidth/3};
bool isNotCross {true};
constexpr float objectsSize {boxWidth/10};
constexpr int toWin {3};


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
unsigned int conStatesXY {0};
void compareStates(int state,std::string toPrint)
{
    if(state>= toWin)
    {
        int i {0};
        while(i<6)
        {
            ++i;
            std::cout << toPrint << '\n';
        }
    }

}

void checkForWin(int index2Check, std::vector<Box>& vct2Check, boxState toCheck4)
{
    std::cout<< "[" << vct2Check[index2Check].gridXValue << "," << vct2Check[index2Check].gridYValue << "] is crossed: " << vct2Check[index2Check].isCrossed << ",is circled:" << vct2Check[index2Check].isCircled << '\n';

    // check x axis WIP

    //stredovy win
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - (toWin/2))}; index2CheckInLoop <= (index2Check + (toWin/2)); ++index2CheckInLoop)
        {
            //std::cout << "(stredovy win X) Skontrolovany index je: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
              //  std::cout << "(stredovy win X) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesX;
            }
        }
        compareStates(conStatesX,"***WIN detected STREDOVY X***");
        conStatesX = 0;

    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - toWin + 1)}; index2CheckInLoop <= index2Check; ++index2CheckInLoop)
            {

                //std::cout << "(pravy bok win X) Skontrolovany index: " << index2CheckInLoop << '\n';
                if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
                {
                   //std::cout << "(pravy bok win X) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                    vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                    ++conStatesX;
                }

            }
    compareStates(conStatesX,"***WIN detected PRAVOBOKY X***");
    conStatesX = 0;

    for(int index2CheckInLoop {negativeIndexPrevention(index2Check + toWin - 1)}; index2CheckInLoop >= index2Check; --index2CheckInLoop)
            {

                //std::cout << "(lavy bok win X) Skontrolovany index: " << index2CheckInLoop << '\n';
                if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
                {
                   // std::cout << "(lavy bok win X) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                    vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                    ++conStatesX;
                }

            }

    compareStates(conStatesX,"***WIN detected LAVOBOKY X***");
    conStatesX = 0;

    //check y axis
    //stredovy win
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - ((toWin/2)*boxAmountX))}; index2CheckInLoop <= (index2Check + ((toWin/2))*boxAmountX); index2CheckInLoop = index2CheckInLoop+boxAmountX)
        {
           // std::cout << "(stredovy win Y) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
               // std::cout << "(stredovy win Y) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesY;
            }
        }
    compareStates(conStatesY,"***WIN detected STREDOVY Y***");
    conStatesY = 0;

    for(int index2CheckInLoop {negativeIndexPrevention(index2Check + (boxAmountX*(toWin-1)))}; index2CheckInLoop >= index2Check; index2CheckInLoop = index2CheckInLoop - boxAmountX)
        {
            //std::cout << "(horny bok win Y) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
               // std::cout << "(horny bok win Y) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesY;
            }
        }
    compareStates(conStatesY,"***WIN detected HORNY Y***");
    conStatesY = 0;

    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - (boxAmountX*(toWin-1)))}; index2CheckInLoop <= index2Check; index2CheckInLoop = index2CheckInLoop + boxAmountX)
        {
           // std::cout << "(dolny bok win Y) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
                //std::cout << "(dolny bok win Y) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesY;
            }
        }
    compareStates(conStatesY,"***WIN detected DOLNY Y***");
    conStatesY = 0;

    //WIN NA Diagonalne storce
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - ((boxAmountX)-1)*(toWin-1))}; index2CheckInLoop <= index2Check; index2CheckInLoop = index2CheckInLoop + boxAmountX-1)
        {
            //std::cout << "(lavy dolny bok win XY) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
                //std::cout << "(lavy dolny bok win XY) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesXY;
            }
        }
    compareStates(conStatesXY,"***WIN detected DOLNY LAVY XY***");
    conStatesXY = 0;

    //win ked das na pravy horny okraj  diagonalnej postupnosti, toto mi mozno riadne dosere algoritmus, bez tohto ale stredove winy idu dobre
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check + ((boxAmountX)-1)*(toWin-1))}; index2CheckInLoop >= index2Check; index2CheckInLoop = index2CheckInLoop - (boxAmountX-1))
        {
           // std::cout << "(pravy horny bok win XY) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
                //std::cout << "(pravy horny bok win XY) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesXY;
            }
        }
    compareStates(conStatesXY,"***WIN detected HORNY PRAVY XY***");
    conStatesXY = 0;

    //win ked das na lavy horny okraj  diagonalnej postupnosti, toto mi mozno riadne dosere algoritmus, bez tohto ale stredove winy idu dobre
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check + ((boxAmountX)+1)*(toWin-1))}; index2CheckInLoop >= index2Check; index2CheckInLoop = index2CheckInLoop - (boxAmountX+1))
        {

           // std::cout << "(lavy horny bok win XY) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
               // std::cout << "(lavy horny bok win XY) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesXY;
            }
        }
    compareStates(conStatesXY,"***WIN detected HORNY LAVY XY***");
    conStatesXY = 0;

    //win ked das na pravy dolny okraj  diagonalnej postupnosti, toto mi mozno riadne dosere algoritmus, bez tohto ale stredove winy idu dobre
    for(int index2CheckInLoop {negativeIndexPrevention(index2Check - ((boxAmountX)+1)*(toWin-1))}; index2CheckInLoop <= index2Check; index2CheckInLoop = index2CheckInLoop + (boxAmountX+1))
        {
            //std::cout << "(pravy dolny bok win XY) Skontrolovany index: " << index2CheckInLoop << '\n';
            if(vct2Check[index2CheckInLoop].state == vct2Check[index2Check].state)
            {
               // std::cout << "(pravy dolny bok win XY) Index ktory dava constate+: " << index2CheckInLoop << '\n';
                vct2Check[index2CheckInLoop].shape.setFillColor(sf::Color::Green);
                ++conStatesXY;
            }
        }
    compareStates(conStatesXY,"***WIN detected DOLNY PRAVY XY***");

    std::cout << "End of win checking.\n";
    conStatesX = 0;
    conStatesY = 0;
    conStatesXY = 0;


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
                boxes.emplace_back(outlineThickness*2+gapX,outlineThickness*2+gapY);
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


