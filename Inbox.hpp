//
//  Inbox.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Inbox_hpp
#define Inbox_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Name.hpp"
#include "Message.hpp"
#include "BaseFolder.hpp"
#include "EmailAccount.hpp"

class EmailAccount;
class BaseFolder;
class Message;
class Inbox;

using namespace std;


// Inbox class
class Inbox : public BaseFolder {
public:
    Inbox(EmailAccount *ac) : BaseFolder(ac) { };               //public constructor
    
protected:
    //inline definition
    virtual string type() const { return "inbox"; }
    virtual const Name& tofrom(const Message *m) const {return m->from(); }
};

#endif /* Inbox_hpp */
