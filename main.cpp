#include <iostream>
#include "Graph.h"

int main(){
    int frame = 0;
    Graph gr = Graph();
    while(gr.isOpen){
        gr.update();
        gr.render(frame);
        frame ++;
    }
    return 0;
}