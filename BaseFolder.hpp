//
//  BaseFolder.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef BaseFolder_hpp
#define BaseFolder_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Name.hpp"
#include "Vec.hpp"
#include "Message.hpp"
#include "EmailAccount.hpp"

class EmailAccount;
class Name;
class Message;
class BaseFolder;

class BaseFolder {
    
public:
    //virtual destructor and loop to release dynamic memory
    virtual ~BaseFolder() {
        for(int i = 0; i < _msg.size(); i++) {
            delete _msg[i];
        }
    }
    
    int size() const { return _msg.size(); }
    
    void display() const;
    void erase(int n);
    void forward(int n) const;
    void print(int n) const;
    void receive(const Message *m);
    void reply(int n) const;
    
private:
    BaseFolder (const BaseFolder& orig) {};
    BaseFolder& operator = (const BaseFolder& rhs) {return *this;}
    
protected:
    virtual string type() const = 0; //pure virtual function
    virtual const Name& tofrom(const Message *m) const = 0;  // pure virtual function
    
    Vec<const Message*> _msg;
    EmailAccount *_ac;
    
    //Makes this into an Abstract Class
    BaseFolder(EmailAccount *ac) : _ac(ac) { _msg.push_back(NULL);
    }
};

#endif /* BaseFolder_hpp */
