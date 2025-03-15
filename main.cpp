#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

constexpr unsigned int wWidth {800};
constexpr unsigned int wHeight {800};
constexpr float boxWidth {49.0f};
constexpr float boxHeight {49.0f};
constexpr int boxAmountX {13};
constexpr int boxAmountY {13};


struct Box
{
    sf::RectangleShape shape;

    Box(float bX, float bY)
    {
        shape.setPosition({bX,bY});
        shape.setFillColor(sf::Color::Transparent);
        shape.setSize({boxWidth,boxHeight});
        //shape.setOrigin(shape.getGeometricCenter());
        shape.setOutlineThickness(5.0f);
        shape.setOutlineColor(sf::Color::Black);
    }
};


//Tvorba tvarov

//Box box1{wHeight/2,wWidth/2};
//Box box2{300,420};







int main()
{
    sf::RenderWindow window (sf::VideoMode({wWidth,wHeight}),"TicTacToe");
    window.setFramerateLimit(30);

    std::vector<Box> boxes;
    int gapX {0};
    int gapY {0};
    for(int i {0}; i<boxAmountY; ++i)
        {
        for(int i {0};i<boxAmountX; ++i)
            {
                boxes.emplace_back(10+gapX,gapY+10);
                gapX += 60;
            }

        gapX  = 0;
        gapY += 60;
        }

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

    //RENDER
    window.clear(sf::Color::White);

    //KRESLENIE

    for(int i {0};i<boxes.size();++i)
        {
            window.draw(boxes[i].shape);
        }

    window.display();

}
}
