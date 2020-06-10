//
//  ISP.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "ISP.hpp"

//static variable initialization outside of the ISP class.
map<Name, EmailAccount*> ISP:: _accounts;

//class ISP mesthod definition.
void ISP :: send(Message *m) {
    EmailAccount *ac;
    ac = _accounts[m->to()];
    if (ac == NULL) {
        cout << "Delivery failed, to recipient: " << m->to().name() << endl;
        return;
    } else {
        Message *clone = new Message(*m);
        ac->receive(clone);
        return;
    }
}
