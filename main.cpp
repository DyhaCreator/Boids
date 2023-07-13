#include <iostream>
#include "Graph.h"
#include "random.h"

int main(){
    const int MAX_BOIDS = 10;
    int frame = 0;
    Graph gr = Graph();
    std::vector<Boids>boids = std::vector<Boids>();
    Boids boid = Boids(0, 0, 0);
    for(int i = 0; i < MAX_BOIDS; i++){
        boid = Boids(rnd(0,gr.Width), rnd(0,gr.Height), rnd(0,10));
        boids.push_back(boid);
    }
    while(gr.isOpen){
        gr.update();
        gr.render(frame, boids);
        for(int i = 0; i < boids.size(); i ++){
            boids[i].update();
        }
        frame ++;
    }
    return 0;
}