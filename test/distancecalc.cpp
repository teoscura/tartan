#include "../src/minecraft/world/vector.hpp"
#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <random>

#define MAXSIZE_A 500

double alg2(std::array<v2<double>, MAXSIZE_A> a, std::array<v2<double>, MAXSIZE_A> b){
    v2<double> tmp;
    double min=v2distancefrom(v2(b[0].x-a[0].x,b[0].z-a[0].z), v2(0.0,0.0)),l;
    for(v2<double> tmp1 : a){
        for(v2<double> tmp2 : b){
            tmp = v2(tmp2.x-tmp1.x,tmp2.z-tmp1.z);
            l = tmp.norm();
            if((l < min)){
                min = l;
            }
        }
    }
    return min;
}

void populateRandom(std::array<v2<double>, MAXSIZE_A>&a){
    auto dev = std::random_device();
    auto eng = std::default_random_engine(dev());
    auto rand = std::uniform_real_distribution<double>(0, 1000);
    for(int i=0;i<MAXSIZE_A;i++){
        a[i] = v2(rand(eng),rand(eng));
    }
}


int main(){
    srand((long)std::chrono::system_clock::now().time_since_epoch().count());
    std::array<v2<double>, MAXSIZE_A> a,b;
    populateRandom(a);
    populateRandom(b);
    std::cout<<"Starting test\n";
    std::chrono::duration<double, std::milli> dur2;

    for(int i=0;i<20;i++){
        std::cout<<i<<std::endl;
        auto t1 = std::chrono::high_resolution_clock::now();
        alg2(a, b);
        auto t2 = std::chrono::high_resolution_clock::now();
        dur2 = (t2 - t1)/100;
    }

    std::cout<< dur2.count() <<std::endl;
}