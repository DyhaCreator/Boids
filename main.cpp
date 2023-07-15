#include <iostream>
#include "Graph.h"
#include "random.h"

int main(){
    const int MAX_BOIDS = 20;
    int frame = 0;
    Graph gr = Graph();
    std::vector<Boids>boids = std::vector<Boids>();
    Boids boid = Boids(100, gr.Height - 100, 4);
    boids.push_back(boid);
    for(int i = 0; i < MAX_BOIDS; i++){
        boid = Boids(rnd(0,gr.Width), rnd(0,gr.Height), (float)rnd(0,100) / 10);
        boids.push_back(boid);
    }
    while(gr.isOpen){
        gr.update();
        gr.render(frame, boids);
        for(int i = 0; i < boids.size(); i ++){
            boids[i].update(boids, i, frame);
            if(int(boids[i].x) <= 0)boids[i].x = gr.Width - 1;
            if(int(boids[i].x) >= gr.Width)boids[i].x = 1;
            if(int(boids[i].y) <= 0)boids[i].y = gr.Height - 1;
            if(int(boids[i].y) >= gr.Height)boids[i].y = 1;
        }
        frame ++;
    }
    return 0;
}