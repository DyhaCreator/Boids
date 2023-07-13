class Boids{
public:
    int x, y;
    float rotate;
    Boids(int x, int y, float rotate){
        this->x = x;
        this->y = y;
        this->rotate = rotate;
    }
    void update(){
        rotate+=0.01;
    }
};