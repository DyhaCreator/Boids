#include <iostream>
#include <vector>
#include <cmath>

class Boids{
public:
    int MAX_LENGTH = 200;
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
    void update(std::vector<Boids>all_boids){
        std::vector<Boids>boids = std::vector<Boids>();
        for(int i = 0; i < all_boids.size(); i++){
            if(this->length(this->x, this->y, all_boids[i].x, all_boids[i].y) < MAX_LENGTH && (this->x != all_boids[i].x && this->y != all_boids[i].y)){
                boids.push_back(all_boids[i]);
            }
        }

        this->separation(x, y, boids);

        x += cos(this->rotate) * 1;
        y -= sin(this->rotate) * 1;
        //rotate += 0.01;
    }

    void separation(int x, int y, std::vector<Boids>boids){
        float vectorX = 0, vectorY = 0;
        for(int i = 0; i < boids.size(); i++){
            vectorX += this->x - boids[i].x;
            vectorY += this->y - boids[i].y;
        }
        if(boids.size() > 0){
            this->rotate = acos(vectorX / sqrt(vectorX * vectorX + vectorY * vectorY));
            if(vectorX < 0 && vectorY >= 0)this->rotate = -this->rotate;
            else if(vectorX >= 0 && vectorY >= 0)this->rotate = -this->rotate;
        }
        //std::cout << vectorX << " " << vectorY << " " << this->rotate << std::endl;
    }
};