#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Boids.h"

class Graph{
public:
    bool isOpen = true;
    const int Width = 1080;
    const int Height = 720;
    const int FrameRate = 25;
    const int BOIDS_SIZE = 25;
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
        
        DrawMainBoid(boids);

        for(int i = 1; i < boids.size(); i++){
            Draw_Boids(boids[i].x, boids[i].y, boids[i].rotate, this->BOIDS_SIZE, sf::Color(255,255,255));
        }

        this->window.display();
    }

    void DrawMainBoid(std::vector<Boids>boids){
        sf::CircleShape circle(boids[0].MAX_LENGTH, 100);
        circle.setPosition(boids[0].x - boids[0].MAX_LENGTH, boids[0].y - boids[0].MAX_LENGTH);
        circle.setFillColor(sf::Color(255, 255, 255, 50));
        this->window.draw(circle);

        Draw_Boids(boids[0].x, boids[0].y, boids[0].rotate, this->BOIDS_SIZE, sf::Color(150,150,255));

        std::vector<Boids>b = std::vector<Boids>();

        for(int i = 1; i < boids.size(); i ++){
            if(sqrt((boids[0].x - boids[i].x) * (boids[0].x - boids[i].x) + (boids[0].y - boids[i].y) * (boids[0].y - boids[i].y)) < boids[0].MAX_LENGTH)
                b.push_back(boids[i]);
        }

        for(int i = 0; i < b.size(); i++){
            float l = sqrt((boids[0].x - boids[i].x) * (boids[0].x - boids[i].x) + (boids[0].y - boids[i].y) * (boids[0].y - boids[i].y));
            drawLine(boids[0].x, boids[0].y, b[i].x, b[i].y, 1, sf::Color(250, 100, 100, 255));
        }
    }

    void drawLine(int x1, int y1, int x2, int y2, int s, sf::Color color){
        sf::ConvexShape convex;

        convex.setPointCount(4);

        convex.setPoint(0, sf::Vector2f(x1, y1));
        convex.setPoint(1, sf::Vector2f(x2, y2));
        convex.setPoint(2, sf::Vector2f(x2, y2));
        convex.setPoint(3, sf::Vector2f(x1, y1));

        convex.setOutlineThickness(1);
        convex.setOutlineColor(color);

        this->window.draw(convex);
    }

    void Draw_Boids(int x, int y, float angle, int size, sf::Color color){
        //std::cout << x << " " << y << " " << angle << std::endl;
        const float BOTTOM_ANGLE = 0.6;

        sf::ConvexShape convex;

        convex.setPointCount(3);
        convex.setFillColor(color);

        convex.setPoint(0, sf::Vector2f(cos(angle) * size / 2 + x, y - sin(angle) * size / 2));
        convex.setPoint(1, sf::Vector2f(cos(angle - M_PI + BOTTOM_ANGLE) * size / 2 + x, y - sin(angle - M_PI + BOTTOM_ANGLE) * size / 2));
        convex.setPoint(2, sf::Vector2f(cos(angle - M_PI - BOTTOM_ANGLE) * size / 2 + x, y - sin(angle - M_PI - BOTTOM_ANGLE) * size / 2));

        this->window.draw(convex);
        /*
        size /= 20;

        sf::CircleShape circle(size);
        circle.setPosition(x - size, y - size);
        circle.setFillColor(sf::Color(250, 0, 0));
        this->window.draw(circle);*/
    }
};