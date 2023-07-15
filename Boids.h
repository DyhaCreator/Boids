#include <iostream>
#include <vector>
#include <cmath>

class Boids{
public:
    int MAX_LENGTH = 100;
    float MAX_TURN = 0.025;
    float x, y;
    float rotate;
    Boids(int x, int y, float rotate){
        this->x = x;
        this->y = y;
        this->rotate = rotate;
    }
    float length(int x1, int y1, int x2, int y2){
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    void update(std::vector<Boids>all_boids, int my_index, int frame){
        std::vector<Boids>boids = std::vector<Boids>();
        for(int i = 0; i < all_boids.size(); i++){
            if(this->length(this->x, this->y, all_boids[i].x, all_boids[i].y) < MAX_LENGTH && i != my_index){
                boids.push_back(all_boids[i]);
            }
        }
        
        this->separation(boids);

        x += cos(this->rotate) * 1;
        y += sin(this->rotate) * 1;
        //rotate += 0.01;
    }

    void separation(std::vector<Boids>boids){
        float vectorX = 0, vectorY = 0;

        for(int i = 0; i < boids.size(); i++){
            float l = sqrt((this->x - boids[i].x) * (this->x - boids[i].x) + (this->y - boids[i].y) * (this->y - boids[i].y));
            vectorX += this->x - boids[i].x;
            vectorY += this->y - boids[i].y;
        }

        float a = sqrt(vectorX * vectorX + vectorY * vectorY);
        float r = this->rotate;

        if(a > 0)r = acos(vectorX / a);
        if(vectorY < 0)r = M_PI * 2 - r;
        if(a > 0)r = (r - this->rotate) * (1 / a) + this->rotate;

        this->rotate = r;
    }
};