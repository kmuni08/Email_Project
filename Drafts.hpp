//
//  Drafts.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Drafts_hpp
#define Drafts_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Message.hpp"
#include "EmailAccount.hpp"
#include "Vec.hpp"

class EmailAccount;
class Drafts;
class Message;

class Drafts {
public:
    Drafts(EmailAccount *ac);
    ~Drafts();
    
    void display() const;
    void send(int n);
    void erase(int n);
    
    Message* addDraft();
    Message* addDraft(Message *m);
    Message* getDraft(int n) { return _drafts[n];}
    Message* operator[](int n) { return _drafts[n];}
    
private:
    int newKey();
    
    //data
    int _newKey;
    map<int, Message*> _drafts;
    EmailAccount *_ac;
    
    //functions made private to disable copies.
    Drafts(const Drafts& orig) {};
    Drafts operator = (const Drafts& rhs) {return *this;}
};

#endif /* Drafts_hpp */
