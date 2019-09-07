//
//  main.cpp
//  LSTM
//
//  Created by Mohamed Abou Samak on 10/07/2019.
//  Copyright © 2019 Gaia Solutions. All rights reserved.
//

#include <iostream>
#include <ostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include "Maths.h"
#include "Random_generator.h"
#include "debugging.h"
#include "trainingData.h"
#include <chrono>

double alpha = 0.1;
int input_dim = 1;
int hidden_dim = 8;
int output_dim = 1;
int binary_dim = 7;

dMatrix synapse_0_update = zero_weights(input_dim, hidden_dim);
dMatrix synapse_1_update = zero_weights(hidden_dim, output_dim);
dMatrix synapse_h_update = zero_weights(hidden_dim, hidden_dim);

layer layer_1;
vector<layer> layer_1_values;
layer future_layer_1_delta (hidden_dim,0);
layer layer_2_deltas;
double overallerror;
double layer_2_error;

vector<string> dict = get_dict();
vector<string> str_bin = get_bin_rep();
vector<string> data = get_training_data();

int max_correct = 0;
bool display = false;
int main()
{
    std::cout<<"Data size = "<<data.size()<<endl;
    // used to generate pseudo random integers
    srand(static_cast<unsigned int>(clock()));
    
    dMatrix synapse_0 = random_weights(input_dim, hidden_dim);
    dMatrix synapse_1 = random_weights(hidden_dim, output_dim);
    dMatrix synapse_h = random_weights(hidden_dim, hidden_dim);
    
    layer init (hidden_dim,0);
     future_layer_1_delta.assign(hidden_dim, 0);
    
    for (int t = 0; t < data.size(); t++) {
        std:cout<<data[t] <<" ";
    }
    std::cout<<endl<<"In one hot encoding"<<endl;
    for (int t = 0; t < data.size(); t++)
    {
        std::cout<< str_bin[find_bin(data[t],dict)]<<" ";
    }
    std::cout<<endl;

    // Training Logic
    for (int epoch = 0; epoch < 200; epoch++)
    {
        //auto start = std::chrono::high_resolution_clock::now();
        
        int correct_ones = 0;
        vector<int> a_bin;
        vector<int> c_bin;
        vector<int> d_bin (binary_dim,0);

        overallerror = 0.0;

        for (int batch = 0; batch < data.size()-1; batch++)
        {
            layer_1_values.clear();
            layer_1_values.push_back(init);
            a_bin = TextToBinary(str_bin[find_bin(data[batch],dict)]);
            c_bin = TextToBinary(str_bin[find_bin(data[batch+1],dict)]);
            // Forward Propogate
            for (int pos = 0; pos < binary_dim; pos++)
            {
                vector<int> X = {a_bin[binary_dim - pos - 1]};
                int Y [1] = {c_bin[binary_dim - pos - 1]};
                //std::cout<<"X = "<<X[0]<<endl;
                //std::cout<<"Y = "<<Y[0]<<endl;
                //hidden layer (input + prev_hidden)
                layer_1 = sigmoid_vector(add_vectors(dot_product_int_mat(X, synapse_0), dot_product_db_mat(layer_1_values[layer_1_values.size() - 1], synapse_h)),false);
                //print_vector("layer_1", layer_1);
                //output layer
                double layer_2 = dot_product_double(layer_1, synapse_1);
                layer_2_error = Y[0] - layer_2;
                layer_2_deltas.push_back((layer_2_error * sigmoid(layer_2,false)));
                overallerror += abs(layer_2_error);
                d_bin[binary_dim - pos - 1] = round(layer_2);
                layer_1_values.push_back(layer_1);

            }

            // Back Propogate through time
            for (int pos = 0; pos < binary_dim; pos++)
            {
                vector<int> X = {a_bin[pos]};
                layer_1 = layer_1_values[layer_1_values.size() - 1 - pos];
                layer prev_layer_1 = layer_1_values[layer_1_values.size() - 2 - pos];
                double layer_2_delta = layer_2_deltas[binary_dim - 1 - pos];
                layer layer_1_delta = multiply_vectors(add_vectors(dot_product_dm(layer_2_delta, synapse_1), dot_product_vm(future_layer_1_delta, synapse_h)), sigmoid_vector(layer_1, true));
                synapse_0_update = add_syn0(synapse_0_update, dot_product_am(X, layer_1_delta));
                synapse_1_update = add_mat_vector(transpose(synapse_1_update), dot_product_dl(layer_2_delta, layer_1), false);
                synapse_h_update = add_matrices(synapse_h_update,dot_product_2d(prev_layer_1, layer_1_delta));
                future_layer_1_delta = layer_1_delta;
            }

            synapse_0 = add_matrices(synapse_0, multiply_dM(synapse_0_update, alpha));
            synapse_h = add_matrices(synapse_h, multiply_dM(synapse_h_update, alpha));
            synapse_1 = add_matrices(synapse_1, multiply_dM(synapse_1_update, alpha));
            synapse_0_update = zero_weights(input_dim, hidden_dim);
            synapse_1_update = zero_weights(hidden_dim, output_dim);
            synapse_h_update = zero_weights(hidden_dim, hidden_dim);
            
            if(str_bin[find_word(BinaryToText(d_bin), str_bin)] == str_bin[find_word(BinaryToText(c_bin), str_bin)])
            {
                correct_ones += 1;

            }
            
            layer_2_deltas.clear();
            
        }
        
        //auto finish = std::chrono::high_resolution_clock::now();
       // std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish-start).count() << ", ";

        std::cout<<overallerror<<",";
       if (correct_ones !=   max_correct)
        {
            max_correct = correct_ones;
            //std::cout<<"*** Epoch "<<epoch<<" ***"<<endl;
            //std::cout<<"Total Correct Predictions This Epoch : "<<correct_ones<<endl;
        }else
        {
            display = false;
        }
        
        
    }
    return 0;
}
