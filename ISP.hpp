//
//  ISP.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef ISP_hpp
#define ISP_hpp

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Message.hpp"
#include "Name.hpp"
#include "EmailAccount.hpp"
#include "Vec.hpp"

template<class T> class Vec;
class EmailAccount;
class Message;
class Name;

class ISP {
public:
    static void addAccount(EmailAccount *e) {
        _accounts[e->owner()] = e;
    }
    
    static void send(Message *m);
    
private:
    ISP() {}
    static map<Name, EmailAccount*> _accounts;
};

#endif /* ISP_hpp */
