//
//  debugging.h
//  LSTM
//
//  Created by Mohamed Abou Samak on 24/07/2019.
//  Copyright © 2019 Gaia Solutions. All rights reserved.
//

#ifndef debugging_h
#define debugging_h
#include "datastructures.h"

void print_synapse(string a, dMatrix b)
{
    std::cout<<"--------------------------------"<<endl;
    std::cout<<a<<endl;
    for (int x = 0; x < b.size(); x++)
    {
        for (int y = 0; y < b[x].size(); y++)
        {
            std::cout<< "[" << x << "]"<< "[" << y << "]" << b[x][y] << endl;
        }
    }
}

void print_vector_int(string a,vector<int> b)
{
    std::cout<<"--------------------------------"<<endl;
    std::cout<<a<<endl;
    for (int x = 0; x < b.size(); x++)
    {
        std::cout<< "[" << x << "]" << b[x] << endl;
    }
}

void print_vector(string a,vector<long double> b)
{
    std::cout<<"--------------------------------"<<endl;
    std::cout<<a<<endl;
    for (int x = 0; x < b.size(); x++)
    {
        std::cout<< "[" << x << "]" << b[x] << endl;
    }
}





void two_rep_print(int decimal, vector<int> binary)
{
    std::cout<< "Decimal:" << decimal << " Binary: ";
    for (int x = 0; x < 8; x++) {
        std::cout<< binary[x];
    }
    std::cout<<endl;
}

void bin_rep_print(vector<int> binary)
{
    for (int x = 0; x < 8; x++) {
        std::cout<< binary[x];
    }
    std::cout<<endl;
}


#endif /* debugging_h */
