//
//  Name.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Name_hpp
#define Name_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;

class Name {
public:
    Name() {}
    Name(string s) { set(s); }
    
    void set(string s);
    string name() const {return _name; }
    string address() const {return _address; }
    
private:
    string _name;
    string _address;
};


#endif /* Name_hpp */