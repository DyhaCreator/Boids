#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Boids.h"

class Graph{
public:
    bool isOpen = true;
    const int Width = 1080;
    const int Height = 720;
    const int FrameRate = 100;
    const int BOIDS_SIZE = 50;
    sf::Event ev;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1080,720), "Test Gen");

    Graph(){
        this->window.setFramerateLimit(FrameRate);
    }

    void update(){
        this->isOpen = this->window.isOpen();
        while(this->window.pollEvent(this->ev)){
            switch(this->ev.type){
            case sf::Event::Closed:
                this->window.close();
                break;
            }
        }
    }

    void render(int frame, std::vector<Boids>boids){
        this->window.clear(sf::Color(50,50,50));
        
        for(int i = 0; i < boids.size(); i++){
            Draw_Boids(boids[i].x, boids[i].y, boids[i].rotate, this->BOIDS_SIZE);
        }

        this->window.display();
    }

    void Draw_Boids(int x, int y, float angle, int size){
        const float BOTTOM_ANGLE = 0.6;

        sf::ConvexShape convex;

        convex.setPointCount(3);

        convex.setPoint(0, sf::Vector2f(sin(angle) * size / 2 + x, y - cos(angle) * size / 2));
        convex.setPoint(1, sf::Vector2f(sin(angle - M_PI + BOTTOM_ANGLE) * size / 2 + x, y - cos(angle - M_PI + BOTTOM_ANGLE) * size / 2));
        convex.setPoint(2, sf::Vector2f(sin(angle - M_PI - BOTTOM_ANGLE) * size / 2 + x, y - cos(angle - M_PI - BOTTOM_ANGLE) * size / 2));

        this->window.draw(convex);
        /*
        size /= 20;

        sf::CircleShape circle(size);
        circle.setPosition(x - size, y - size);
        circle.setFillColor(sf::Color(250, 0, 0));
        this->window.draw(circle);*/
    }
};