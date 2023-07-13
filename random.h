#include <random>
#include <iostream>
#include <vector>

using namespace std;

/*std::vector<Units> del(std::vector<Units>units1, int index){
    std::vector<Units>units2 = std::vector<Units>();

    for(int i = 0; i < units1.size(); i ++){
        if(i != index){
            units2.push_back(units1[i]);
        }
    }

    return units2;
}*/

int rnd(int min, int max){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(rng);
}