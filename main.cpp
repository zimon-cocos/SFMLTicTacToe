#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

constexpr unsigned int wWidth {800};
constexpr unsigned int wHeight {800};
constexpr float boxWidth {50.0f};
constexpr float boxHeight {50.0f};
constexpr int boxAmountX {3};
constexpr int boxAmountY {3};
constexpr float outlineThickness{5.0f};
constexpr float tempCircleRadius{15.0f};
bool isNotCross {true};


//placeholder na sprite
struct Sprites
{
    sf::CircleShape shape;


    Sprites(float sX, float sY,sf::Color color)
    {
        //shape.setOrigin(shape.getGeometricCenter());
        shape.setPosition({sX,sY});
        shape.setFillColor(color);
        shape.setRadius(tempCircleRadius);
    }
};




struct Box
{

    //!DOLEZITE!
    sf::RectangleShape shape;
    //!DOLEZITE!
    bool wasHit {false};

    void makeHit()
    {
        wasHit = true;
    }
    float centerPosX {0};
    float centerPosY {0};
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

    std::vector<Sprites> sprites;

    while (window.isOpen())
    {

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
        auto mousePos = sf::Mouse::getPosition(window);
        auto transMousePos = window.mapPixelToCoords(mousePos);
        for(unsigned int i {0};i<boxes.size();++i)
            {
                if(boxes[i].shape.getGlobalBounds().contains(transMousePos))
                {
                    if(isNotCross)
                    {
                        sprites.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY,sf::Color::Red);
                        isNotCross = false;
                        std::cout << boxes[i].centerPosX << "," << boxes[i].centerPosY << '\n';
                        boxes[i].makeHit();
                    }
                    else{
                        sprites.emplace_back(boxes[i].centerPosX,boxes[i].centerPosY,sf::Color::Blue);
                        isNotCross = true;
                    }

                    }

            }

    }


    //RENDER
    window.clear(sf::Color::White);

    //KRESLENIE

    for(unsigned int i {0};i<boxes.size();++i)
        {
            if(!(boxes[i].wasHit))
            {

                window.draw(boxes[i].shape);
            }
        }



    for(unsigned int i {0};i<sprites.size();++i)
        {
            window.draw(sprites[i].shape);
        }



    window.display();

}
}


