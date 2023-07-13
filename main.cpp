#include <iostream>
#include "Graph.h"

int main(){
    int frame = 0;
    Graph gr = Graph();
    std::vector<Boids>boids = std::vector<Boids>();
    Boids boid = Boids(gr.Width / 2, gr.Height / 2, 0);
    boids.push_back(boid);
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