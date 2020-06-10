//
//  Name.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "Name.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;

//class Name method definitions
void Name:: set(string s) {
    const string _domain = "@qc.cuny.edu";
    istringstream iss(s);
    iss >> _name; // remove leading and trailing blank spaces
    
    if (_name == "") {
        _address = "";
        return;
    } else {
        _address = _name + _domain;
    }
    
    //convert _address to lowercase
    for(int i = 0; i < _address.length(); i++) {
        _address[i] = tolower(_address[i]);
    }
}
