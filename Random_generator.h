//
//  Random_generator.hpp
//  
//
//  Created by Mohamed Abou Samak on 19/06/2019.
//

#ifndef Random_generator_h
#define Random_generator_h
#include "datastructures.h"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<double>> random_weights(int M, int N){
    dMatrix output;
    output.resize(M, std::vector<double>(N, 0));
    
    for(int it = 0; it < M; ++it){
        for(int it2 = 0; it2 < N; it2 ++){
            output[it][it2] = 2* double(rand()) / (double(RAND_MAX))-1;
        }
    }
    return output;
}

std::vector<std::vector<double>> full(int M, int N, float x){
    dMatrix output;
    output.resize(M, std::vector<double>(N, 0));
    
    for(int it = 0; it < M; ++it){
        for(int it2 = 0; it2 < N; it2 ++){
            output[it][it2] = x;
        }
    }
    return output;
}

std::vector<std::vector<double>> zero_weights(int M, int N){
    dMatrix output;
    output.resize(M, std::vector<double>(N, 0));
    return output;
}

double random_weight(){
    double out = 2* double(rand()) / (double(RAND_MAX))-1;
    return out;
}

int get_int(){
    
    int a = rand() % 127 ;
    return a;
}

std::vector<std::vector<double>> generate_weight(int M, int N){
    dMatrix output;
    output.resize(M, std::vector<double>(N, 0));
    int x = 1;
    int y = 0;
    int z = N + 1;
    int cnt = 0;
    for (int i = 0; i < M; i++){
        
        for (int a = x; a < z; a++){
            output[i][cnt] = (double(a)/1000);
            y = a;
            cnt = cnt + 1;
        }
        
        x = y;
        z = x + 16;
        cnt = 0;
    }
    
    return output;
}

#endif /* Random_generator_hpp */
