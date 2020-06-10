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
#include "EmailAccount.hpp"

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
