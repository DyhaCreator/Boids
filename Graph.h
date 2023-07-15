#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Boids.h"

class Graph{
public:
    bool isOpen = true;
    int Mx = 0;
    int My = 0;
    const int Width = 1080;
    const int Height = 720;
    const int FrameRate = 250;
    const int BOIDS_SIZE = 25;
    sf::Event ev;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1080,720), "Test Gen");

    Graph(){
        this->window.setFramerateLimit(FrameRate);
    }

    void update(){
        this->isOpen = this->window.isOpen();
        this->Mx = sf::Mouse::getPosition(this->window).x;
        this->My = sf::Mouse::getPosition(this->window).y;
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

        sf::CircleShape circle(30, 100);
        circle.setPosition(sf::Mouse::getPosition(this->window).x - 30, sf::Mouse::getPosition(this->window).y - 30);
        circle.setFillColor(sf::Color(255, 255, 255, 100));
        this->window.draw(circle);
        
        DrawMainBoid(boids, frame);

        for(int i = 1; i < boids.size(); i++){
            Draw_Boids(boids[i].x, boids[i].y, boids[i].rotate, this->BOIDS_SIZE, sf::Color(255,255,255));
        }

        this->window.display();
    }

    void DrawMainBoid(std::vector<Boids>boids, int frame){
        sf::CircleShape circle(boids[0].MAX_LENGTH, 100);
        circle.setPosition(boids[0].x - boids[0].MAX_LENGTH, boids[0].y - boids[0].MAX_LENGTH);
        circle.setFillColor(sf::Color(255, 255, 255, 50));
        this->window.draw(circle);

        std::vector<Boids>b = std::vector<Boids>();

        for(int i = 1; i < boids.size(); i ++){
            if(sqrt((boids[0].x - boids[i].x) * (boids[0].x - boids[i].x) + (boids[0].y - boids[i].y) * (boids[0].y - boids[i].y)) < boids[0].MAX_LENGTH)
                b.push_back(boids[i]);
        }

        /*float vectorX = 0, vectorY = 0;

        for(int i = 0; i < b.size(); i++){
            float l = sqrt((boids[0].x - b[i].x) * (boids[0].x - b[i].x) + (boids[0].y - b[i].y) * (boids[0].y - b[i].y));
            drawLine(boids[0].x, boids[0].y, b[i].x, b[i].y, 1, sf::Color(250, 100, 100, 255));
            vectorX += boids[0].x - b[i].x;
            vectorY += boids[0].y - b[i].y;
        }
        float a = sqrt(vectorX * vectorX + vectorY * vectorY);
        float r = boids[0].rotate;
        if(a > 0)r = acos(vectorX / a);
        if(vectorY < 0)r = M_PI * 2 - r;
        if(a > 0)r = (r - boids[0].rotate) * (1 / a) + boids[0].rotate;
        //std::cout << r << std::endl;

        drawLine(boids[0].x, boids[0].y, cos(r) * 100 + boids[0].x, sin(r) * 100 + boids[0].y, 1, sf::Color(250, 250, 100, 255));
        //drawLine(boids[0].x, boids[0].y, vectorX + boids[0].x, vectorY + boids[0].y, 1, sf::Color(250, 250, 250, 255));

        float cohX = boids[0].x, cohY = boids[0].y;

        for(int i = 0; i < b.size(); i++){
            cohX += b[i].x;
            cohY += b[i].y;
            cohX /= 2;
            cohY /= 2;
        }

        cohX -= boids[0].x;
        cohY -= boids[0].y;

        float l = sqrt(cohX * cohX + cohY * cohY);
        float r = boids[0].rotate;
        if(l > 0)r = acos(cohX / l);
        if(cohY < 0)r = M_PI * 2 - r;
        if(l > 0)r = (r - boids[0].rotate) * 0.1 + boids[0].rotate;
        
        drawLine(boids[0].x, boids[0].y, cohX + boids[0].x, cohY + boids[0].y, 1, sf::Color(250,250,100,255));
        drawLine(boids[0].x, boids[0].y, cos(r) * 100 + boids[0].x, sin(r) * 100 + boids[0].y, 1, sf::Color(250, 100, 100, 255));*/

        Draw_Boids(boids[0].x, boids[0].y, boids[0].rotate, this->BOIDS_SIZE, sf::Color(150,150,255));
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

        convex.setPoint(0, sf::Vector2f(cos(angle) * size / 2 + x, y + sin(angle) * size / 2));
        convex.setPoint(1, sf::Vector2f(cos(angle - M_PI + BOTTOM_ANGLE) * size / 2 + x, y + sin(angle - M_PI + BOTTOM_ANGLE) * size / 2));
        convex.setPoint(2, sf::Vector2f(cos(angle - M_PI - BOTTOM_ANGLE) * size / 2 + x, y + sin(angle - M_PI - BOTTOM_ANGLE) * size / 2));

        this->window.draw(convex);
        /*
        size /= 20;

        sf::CircleShape circle(size);
        circle.setPosition(x - size, y - size);
        circle.setFillColor(sf::Color(250, 0, 0));
        this->window.draw(circle);*/
    }
};