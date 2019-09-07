//
//  input_handler.h
//  LSTM
//
//  Created by Mohamed Abou Samak on 28/07/2019.
//  Copyright © 2019 Gaia Solutions. All rights reserved.
//

#ifndef input_handler_h
#define input_handler_h
#include "datastructures.h"
#include <fstream>
#include <string>

void convertToASCII(std::string letter)
{
    for (int i = 0; i < letter.length(); i++)
    {
        char x = letter.at(i);
        int y = int(x);
        temp_bin = dec2bin(y);
        
        for (int it = 7; it >= 0; --it)
        {
            temp += std::to_string(temp_bin[it]);
        }
        
        bin_out.push_back(temp);
        temp = "";
    }
}

vector<char> readFile(string input_file){
    vector<char> output;
    string line;
    ifstream myfile_input (input_file);
    if (myfile_input.is_open())
    {
        while ( getline (myfile_input,line) )
        {
            output.push_back(line);
        }
        myfile_input.close();
    }
    
    else std::cout << "Unable to open file\n";
    
    
    return output;
}



#endif /* input_handler_h */
