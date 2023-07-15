#include <iostream>
#include <vector>
#include <cmath>

class Boids{
public:
    int MAX_LENGTH = 100;
    float MAX_TURN = 0.025;
    float x, y;
    float rotate;
    float speedX = 0, speedY = 0;
    float maxSpeed = 1;
    Boids(int x, int y, float rotate){
        this->x = x;
        this->y = y;
        this->rotate = rotate;
    }
    float length(int x1, int y1, int x2, int y2){
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    void update(std::vector<Boids>all_boids, int my_index, int frame, int Width, int Height, float Mx, float My){
        std::vector<Boids>boids = std::vector<Boids>();
        for(int i = 0; i < all_boids.size(); i++){
            if(this->length(this->x, this->y, all_boids[i].x, all_boids[i].y) < MAX_LENGTH && i != my_index){
                boids.push_back(all_boids[i]);
            }
        }

        this->seek(Mx, My);
        this->move();

        //this->evasion(Width, Height);
        
        //this->separation(boids);
        //this->coherence(boids);

        //rotate += 0.01;

        if(this->rotate > M_PI * 2){
            this->rotate -= M_PI * 2;
        }
        if(this->rotate < 0){
            this->rotate += M_PI * 2;
        }
    }

    void seek(float mx, float my){
        float speed = 0.003;

        float x = mx - this->x;
        float y = my - this->y;

        if(x > 0)speedX += speed;
        else if(x < 0)speedX -= speed;
        if(y > 0)speedY += speed;
        else if(y < 0)speedY -= speed;

        float l = sqrt(speedX * speedX + speedY * speedY);
        this->rotate = acos(speedX / l);
        if(speedY < 0)this->rotate = M_PI * 2 - this->rotate;

        if(l > this->maxSpeed){
            speedX = cos(this->rotate) * maxSpeed;
            speedY = sin(this->rotate) * maxSpeed;
        }
    }

    void move(){
        this->x += this->speedX;
        this->y += this->speedY;
    }

    void evasion(int Width, int Height){
        float turn = 0.01;
        if(this->x < this->MAX_LENGTH){
            this->rotate += (this->rotate > M_PI) ? turn * (this->MAX_LENGTH / this->x) : -turn * (this->MAX_LENGTH / this->x);
        }
        if(this->y < this->MAX_LENGTH){
            this->rotate += (this->rotate > M_PI / 2 && this->rotate < M_PI / 2 + M_PI) ? -turn * (this->MAX_LENGTH / this->y): turn * (this->MAX_LENGTH / this->y);
        }
        if(this->y > Height - this->MAX_LENGTH){
            this->rotate += (this->rotate > M_PI / 2 && this->rotate < M_PI / 2 + M_PI) ? turn * (this->MAX_LENGTH / (Height - this->y)): -turn * (this->MAX_LENGTH / (Height - this->y));
        }
        if(this->x > Width - this->MAX_LENGTH){
            this->rotate += (this->rotate > M_PI) ? -turn * (this->MAX_LENGTH / (Width - this->x)): turn * (this->MAX_LENGTH / (Width - this->x));
        }
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

    void coherence(std::vector<Boids>boids){
        float cohX = this->x, cohY = this->y;

        for(int i = 0; i < boids.size(); i++){
            cohX += boids[i].x;
            cohY += boids[i].y;
            cohX /= 2;
            cohY /= 2;
        }

        cohX -= this->x;
        cohY -= this->y;

        float l = sqrt(cohX * cohX + cohY * cohY);
        float r = this->rotate;
        if(l > 0)r = acos(cohX / l);
        if(cohY < 0)r = M_PI * 2 - r;
        if(l > 0)r = (r - this->rotate) * 0.01 + this->rotate;

        this->rotate = r;
    }
};