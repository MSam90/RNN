//
//  trainingData.h
//  LSTM
//
//  Created by Mohamed Abou Samak on 04/08/2019.
//  Copyright © 2019 Gaia Solutions. All rights reserved.
//

#ifndef trainingData_h
#define trainingData_h

#include <iostream>
#include <vector>
#include <fstream>

void print_bin(vector<int> rep)
{
    for (int i = 0; i < rep.size(); i++)
    {
        std::cout<<rep[i];
    }
    std::cout<<endl;
}

vector<int> TextToBinary(string words)
{
    vector<int> output;
    
    for (char& _char : words)
    {
        output.push_back(int(_char) - 48);
    }
    return output;
}

string BinaryToText(vector<int> binary)
{
    string output;
    
    for (int i = 0; i < binary.size(); i++)
    {
        output+= std::to_string(binary[i]);
    }
    //std::cout<<"Binary to text = "<<output<<endl;
    return output;
}

int find_bin(string input, vector<string> dict)
{
    int found;
    for (int i = 0; i < dict.size(); i++)
    {
        if (input == dict[i])
        {
            //std::cout<<"input = "<<input<<" : dict = "<<dict[i]<<endl;
            found = i;
        }
    }
    
    return found;
}

int find_word(string input, vector<string> bin_rep)
{
    int found;
    for (int i = 0; i < bin_rep.size(); i++)
    {
        if (input == bin_rep[i])
        {
            //std::cout<<"input = "<<input<<" : bin_rep = "<<bin_rep[i]<<endl;
            found = i;
        }
    }
    
    return found;
}

vector<string> get_dict()
{
    vector<string> dict;
    std::string line;
    std::ifstream myfile_input ("/Users/mas/Desktop/OneDrive - University of Birmingham/MSc Thesis/C++/Backup/LSTM/LSTM/new_data/trials_dict.txt");
    if (myfile_input.is_open())
    {
        while ( getline (myfile_input,line) )
        {
            dict.push_back(line);
        }
        myfile_input.close();
    }
    else std::cout << "Unable to open file\n";
    
    std::cout<<"Size = "<<dict.size() <<endl;
    for (int it = 0; it < dict.size(); it++)
        std::cout<<"["<<it<<"] "<< dict[it]<<endl;
    
    return dict;
}

vector<string> get_bin_rep()
{
    vector<string> binary;
    std::string line;
    std::ifstream myfile2_input ("/Users/mas/Desktop/OneDrive - University of Birmingham/MSc Thesis/C++/Backup/LSTM/LSTM/new_data/trials_binary.txt");
    if (myfile2_input.is_open())
    {
        while ( getline (myfile2_input,line))
        {
            binary.push_back(line);
        }
        myfile2_input.close();
    }
    
    else std::cout << "Unable to open file\n";
    
    std::cout<<"Size = "<<binary.size() <<endl;
    for (int it = 0; it < binary.size(); it++)
        std::cout<<"["<<it<<"] "<< binary[it]<<endl;
    
    return binary;
}

vector<string> get_training_data()
{
    vector<string> training_data;
    std::string line;
    std::ifstream myfile3_input ("/Users/mas/Desktop/OneDrive - University of Birmingham/MSc Thesis/C++/Backup/LSTM/LSTM/new_data/trials.txt");
    if (myfile3_input.is_open())
    {
        while ( getline (myfile3_input,line) )
        {
            training_data.push_back(line);
        }
        myfile3_input.close();
    }
    
    else std::cout << "Unable to open file\n";
    
    std::cout<<"Size = "<<training_data.size() <<endl;
    for (int it = 0; it < training_data.size(); it++)
        std::cout<<"["<<it<<"] "<< training_data[it]<<endl;
    
    return training_data;
}

#endif /* trainingData_h */
