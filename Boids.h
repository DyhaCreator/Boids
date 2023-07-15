#include <iostream>
#include <vector>
#include <cmath>

class Boids{
public:
    int MAX_LENGTH = 150;
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
        y -= sin(this->rotate) * 1;
        //rotate += 0.01;
    }

    void separation(std::vector<Boids>boids){
        
    }
};