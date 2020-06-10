//
//  EmailAccount.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef EmailAccount_hpp
#define EmailAccount_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Name.hpp"
#include "Message.hpp"
#include "Drafts.hpp"
#include "BaseFolder.hpp"

using namespace std;

class BaseFolder;
class Drafts;
class EmailAccount;
class Message;
class Name;

class EmailAccount {
public:
    EmailAccount(string s);
    ~EmailAccount();
    
    const Name& owner() const { return _owner; }  // accessor
    Drafts& drafts()  { return *_drafts; }
    BaseFolder& in()  { return *_in; }
    BaseFolder& out() { return *_out; }
    
    void send(Message *m);
    void receive(Message *m);
    void insert(Message *m);
    
private:
    Name _owner;
    Drafts * _drafts;
    BaseFolder  * _in;
    BaseFolder * _out;
    
    //make functions private
    EmailAccount (const EmailAccount& orig) {};
    EmailAccount&  operator = (const EmailAccount& rhs) {return *this;}
};


#endif /* EmailAccount_hpp */
