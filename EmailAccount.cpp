//
//  EmailAccount.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "EmailAccount.hpp"
#include "ISP.hpp"

//class EmailAccount method definitions.
EmailAccount:: EmailAccount(string s) {
    _owner.set(s);
    _drafts = new Drafts(this);
    _in = new Inbox(this);
    _out = new Outbox(this);
    ISP:: addAccount(this);
}

EmailAccount :: ~EmailAccount() {
    delete _drafts;
    delete _in;
    delete _out;
}

void EmailAccount :: receive(Message *m) {
    _in->receive(m);
}

void EmailAccount :: insert(Message *m) {
    _drafts->addDraft(m);
}

void EmailAccount :: send(Message *m) {
    _out->receive(m);
    ISP:: send(m);
}
