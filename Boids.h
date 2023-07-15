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
    float targetX = 0, targetY = 0;
    float maxSpeed = 1;
    Boids(int x, int y, float rotate){
        this->x = x;
        this->y = y;
        this->rotate = rotate;
        this->targetX = this->x;
        this->targetY = this->y;
        //std::cout << targetX - this->x << " " << targetY - this->y << std::endl;
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

        //this->evasion(Width, Height);

        std::cout << targetX - this->x << " " << targetY - this->y << " " << this->rotate << std::endl;
        this->seek(this->targetX, this->targetY);
        this->move(Mx, My);
        
        //this->separation(boids);
        //this->coherence(boids);

        //rotate += 0.01;

        /*if(this->rotate > M_PI * 2){
            this->rotate -= M_PI * 2;
        }
        if(this->rotate < 0){
            this->rotate += M_PI * 2;
        }*/
        //this->targetX = Mx;
        //this->targetY = My;
    }

    void seek(float mx, float my){
        float speed = 0.3;
        float min_speed = 1;

        float x = mx - this->x;
        float y = my - this->y;

        if(x > 0)speedX += speed;
        else if(x < 0)speedX -= speed;
        if(y > 0)speedY += speed;
        else if(y < 0)speedY -= speed;

        float l = sqrt(speedX * speedX + speedY * speedY);
        if(x != 0 && y != 0){
            this->rotate = acos(speedX / l);
            if(speedY < 0)this->rotate = M_PI * 2 - this->rotate;
        }
        if(l > this->maxSpeed){
            speedX = cos(this->rotate) * maxSpeed;
            speedY = sin(this->rotate) * maxSpeed;
        }
        if(x == 0 && y == 0){
            speedX = cos(this->rotate) * min_speed;
            speedY = sin(this->rotate) * min_speed;
        }
    }

    void move(float Mx, float My){
        this->x += this->speedX;
        this->y += this->speedY;
        //std::cout << targetX - this->x << " " << targetY - this->y << " " << this->rotate << std::endl;
        this->targetX = this->x;
        this->targetY = this->y;
        //std::cout << targetX - this->x << " " << targetY - this->y << " " << this->rotate << std::endl;
    }

    void evasion(int Width, int Height){
        float max_distance = 200;
        float force = 10;

        if(this->x < max_distance){
            this->targetX += force;
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