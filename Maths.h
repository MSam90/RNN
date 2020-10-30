//
//  Maths.hpp
//  RNN
//
//  Created by Mohamed Abou Samak on 18/06/2019.
//  Copyright © 2019 Mohamed Abou Samak. All rights reserved.
//

#ifndef Maths_h
#define Maths_h
#include <math.h>
#include <cmath>
#include "Random_generator.h"
using namespace std;

/**
 * Performs Rectified linear unit (ReLu).
 *
 * This performs ReLu on a single double.
 *
 * @param x
 * @return x:0
 */

double ReLu(double x)
{
    if (x > 0) {
        return x;
    }
    return 0;
}

/**
 * Performs Rectified linear unit (ReLu).
 *
 * This performs ReLu on a vector of doubles and can adapt to derivatives.
 *
 * @param x
 * @param deriv
 * @return output
 */

vector<double> ReLu_vector(vector<double> x, bool deriv)
{
    vector<double> output;
    
    if(deriv == false)
    {
        for (int i = 0; i < x.size(); i++)
        {
            
            if (x[i] > 0)
            {
                output.push_back(x[i]);
            }
            else
            {
                output.push_back(0);
            }
        }

    }
    else if(deriv == true)
    {
        for (int i = 0; i < x.size(); i++)
        {
            
            if (x[i] > 0)
            {
                output.push_back(1);
            }
            else
            {
                output.push_back(0);
            }
        }
    }
    
    return output;
}

double sigmoid(double x,bool deriv)
{
    if (deriv == true)
    {
        return x * (1 - x);
    }
    
    return 1/(1 + exp(-x));
}

vector<double> sigmoid_vector(vector<double> x, bool deriv)
{
    vector<double> output;
    for (int i = 0; i < x.size(); i++)
    {

        if (deriv == true)
        {
            output.push_back(x[i] *(1.0 - x[i]));
        }
        else if (deriv == false)
        {
            output.push_back(1.0/(1.0+exp(-x[i])));
        }
    }
    return output;
}

vector<int> dec2bin(int dec)
{
    
    vector<int> bin(8);
    
    int i = 7;
    while (dec > 0) {
        bin[i] = dec % 2;
        dec = dec / 2;
        i--;
    }
    return bin;
}

int bin2dec(vector<int> input)
{
    int s = int(input.size());
    int dec = 0;
    for(int it = s-1; it >= 0; --it)
    {
        if(input[it] == 1)
            dec += pow(2, it);
    }
    return dec;
}

vector<double> dot_product_int_mat(vector<int> a, dMatrix b)
{
    vector<double> output(b[0].size());
    for (int i=0; i < b.size() ;i++)
    {
        for (int j = 0; j < b[i].size() ;j++)
        {

            output[j]  += a[i]*b[i][j];
        }
    }
    
    return output;
}

vector<double> dot_product_db_mat(vector<double> a, dMatrix b)
{
    vector<double> output;
    double temp = 0.0;
    for (int i=0; i < b.size() ;i++)
    {
        for(int j = 0; j < b[0].size(); j++)
            temp += a[j]*b[j][i];
        
        output.push_back(temp);
        temp = 0.0;
    }
    return output;
}


double dot_product_double(layer a, dMatrix b)
{
    double output = 0.0;
    double temp = 0.0;
    for (int i=0; i < b.size() ;i++)
    {
        for (int j = 0; j < b[i].size() ;j++)
        {
            temp += (a[i]*b[i][j]);
        }
        
        output = sigmoid(temp,false);
    }
    
    return output;
}
vector<double> dot_product_dm(double a, dMatrix b)
{
    vector<double> output;

    for (int i=0; i < b.size() ;i++)
    {
        
        for (int j = 0; j < b[i].size() ;j++)
        {
            output.push_back((a*b[i][j]));
            
        }
        
    }
    
    return output;
}

vector<double> dot_product_ll(layer a, layer b)
{
    vector<double> output;
    
    for (int i=0; i < b.size() ;i++)
    {
        output.push_back((a[i]*b[i]));
        
    }
    
    return output;
}

dMatrix dot_product_2d(layer a, layer b)
{
    dMatrix output(a.size(),vector<double>(b.size()));
    
    for (int i=0; i < a.size() ;i++)
    {
        for (int j=0; j < b.size() ;j++)
        output[i][j] = ((a[i]*b[j]));
        
    }
    
    return output;
}

vector<double> dot_product_dl(double a, layer b)
{
    vector<double> output;

    for (int i=0; i < b.size() ;i++)
    {
        output.push_back((a*b[i]));
    }
    
    return output;
}


vector<double> dot_product_vm(vector<double> a, dMatrix b)
{
    vector<double> output;

    for (int i = 0; i < a.size() ;i++)
    {
        double temp = 0.0;
        for (int j = 0; j < b[i].size() ;j++)
        {
            temp += (a[i]*b[i][j]);
        }
        output.push_back(temp);
    }
    
    return output;
}

dMatrix dot_product_am(vector<int> a, layer b)
{
    
    dMatrix output = zero_weights(int(a.size()), int(b.size()));
    
    for (int i = 0; i < b.size() ;i++)
    {
        for (int j = 0; j < a.size(); j ++) {
            output[j][i] = (a[j]*b[i]);
        }
        
    }
    
    return output;
}

dMatrix add_matrices(dMatrix a, dMatrix b)
{
    dMatrix output = zero_weights(int(a.size()), int(a[0].size()));
    output.resize(a.size(), std::vector<double>(a[0].size(), 0));
    for (int x = 0; x < a.size(); x++)
    {
        for (int y = 0; y < a[0].size(); y++) {
            output[x][y] = a[x][y] + b[x][y];
        }
    }
    return output;
}


vector<double> add_vectors(vector<double> a, vector<double> b)
{
    vector<double> output;
    for (int x = 0; x < a.size(); x++)
    {
        output.push_back(a[x]+b[x]);
    }
    return output;
}

vector<double> multiply_vectors(vector<double> a, vector<double> b)
{
    vector<double> output;
    for (int x = 0; x < a.size(); x++)
    {
        output.push_back(a[x]*b[x]);
    }
    return output;
}

dMatrix add_mat_vector(dMatrix a, vector<double> b, bool twodim)
{
    dMatrix output;
    output.resize(a[0].size(), std::vector<double>(a.size(), 0));
    
    if(twodim == true)
    {
        for (int x = 0; x < b.size(); x++)
        {
            for (int y = 0; y < a[x].size(); y++)
            {
                output[x][y] = a[x][y] + b[y];
            }
        }
        
    }else if(twodim == false)
    {
        for (int x = 0; x < a[0].size(); x ++)
        {
            output[x][0] = a[0][x] + b[x];
        }
    }
    return output;
}

dMatrix transpose(dMatrix b)
{
    
    dMatrix trans_vec(b[0].size(),vector<double>(b.size()));
    
    for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b[0].size(); ++j)
            trans_vec[j][i] = b[i][j];
    return trans_vec;
}

dMatrix multiply_dM(dMatrix a, double b)
{
    for (int x = 0; x < a.size(); x++) {
        for (int y = 0; y < a[0].size(); y++) {
            a[x][y] = a[x][y] * b;
        }
    }
    
    return a;
}


dMatrix add_syn0(dMatrix a, dMatrix b)
{
    
    dMatrix trans_vec(b.size(),vector<double>(b[0].size()));
    for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b[0].size(); ++j)
            trans_vec[i][j] = a[i][j] + b[i][j];
    return trans_vec;
}



#endif /* Maths_hpp */
