//
//  Outbox.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Outbox_hpp
#define Outbox_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Message.hpp"
#include "Name.hpp"
#include "BaseFolder.hpp"
#include "EmailAccount.hpp"

class EmailAccount;
class BaseFolder;
class Message;
class Outbox;

// Outbox class
class Outbox : public BaseFolder {
public:
    Outbox(EmailAccount *ac) : BaseFolder(ac) { };
    
protected:
    //inline definition
    virtual string type() const {return "outbox"; }
    virtual const Name& tofrom(const Message *m) const {return m->to(); }
};

#endif /* Outbox_hpp */
