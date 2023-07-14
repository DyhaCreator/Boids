#include <iostream>
#include <vector>
#include <cmath>

class Boids{
public:
    int MAX_LENGTH = 100;
    float MAX_TURN = 0.1;
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
    void update(std::vector<Boids>all_boids, int my_index){
        std::vector<Boids>boids = std::vector<Boids>();
        for(int i = 0; i < all_boids.size(); i++){
            if(this->length(this->x, this->y, all_boids[i].x, all_boids[i].y) < MAX_LENGTH && i != my_index){
                boids.push_back(all_boids[i]);
            }
        }

        this->separation(boids);
        //this->alignment(boids);

        x += cos(this->rotate) * 1;
        y -= sin(this->rotate) * 1;
        //rotate += 0.01;
    }

    void separation(std::vector<Boids>boids){
        float r = this->rotate;
        float vectorX = 0, vectorY = 0;
        for(int i = 0; i < boids.size(); i++){
            vectorX += this->x - boids[i].x;
            vectorY += this->y - boids[i].y;
        }
        if(boids.size() > 0){
            float b = sqrt(vectorX * vectorX + vectorY * vectorY);
            if(b != 0)r = acos(vectorX / b);
            //b == b ? std::cout << "real" << std::endl : std::cout << b << std::endl;
            //std::cout << r << std::endl;
            if(vectorX < 0 && vectorY >= 0)r = -r;
            else if(vectorX >= 0 && vectorY >= 0)r = -r;
        }
        if(abs(r - this->rotate) < this->MAX_TURN){
            this->rotate += r - this->rotate;
        }
        else{
            if(r - this->rotate < 0){
                this->rotate += -MAX_TURN;
            }
            else{
                this->rotate += MAX_TURN;
            }
        }

        //std::cout << vectorX << " " << vectorY << " " << this->rotate << std::endl;
    }

    void alignment(std::vector<Boids>boids){
        float average_rotate = 0;
        for(int i = 0; i < boids.size(); i++){
            average_rotate += boids[i].rotate;
        }
        if(boids.size() != 0)average_rotate /= boids.size();
        this->rotate = average_rotate;
    }
};