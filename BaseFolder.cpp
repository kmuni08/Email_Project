//
//  BaseFolder.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "BaseFolder.hpp"

//class BaseFolder definitions.
void BaseFolder :: receive(const Message *m) {
    _msg.push_back(m);
}

void BaseFolder :: print(int n) const {
    if ((n < 1) || (n >= _msg.size())) {
        return;
    } else if ((n >= 1) && (n < _msg.size())) {
        //invoke print method for message n.
        _msg[n]->print();
    }
}

void BaseFolder :: erase(int n) {
    if ((n < 1) || (n >= _msg.size())) {
        return;
    } else if ((n >= 1) && (n < _msg.size())) {
        delete _msg[n];
        _msg.erase(n);
    }
}

void BaseFolder :: display() const {
    cout << _ac->owner().name() << " " << type() << endl;
    if(_msg.size() <= 1) {
        cout << "no messages to display." << endl;
    } else {
        for (int i = 1; i < _msg.size(); ++i) {
            const Name &tmp = tofrom(_msg[i]);
            cout << i << " " << tmp.name()<< " " << _msg[i]->subject() << endl;
        }
    }
}

void BaseFolder :: forward(int n) const {
    if ((n<1) || (n>=_msg.size())) {
        return;
    } else if ((n >= 1) || (n < _msg.size())) {
        const Message *m = _msg[n];
        string fwd_subject = "Fwd: " + m->subject();
        Message *ptr = new Message(_ac->owner().name(), " ", fwd_subject, m->text());
        //tell account to insert message into Drafts folder.
        _ac->insert(ptr);
    }
}

void BaseFolder :: reply(int n) const {
    if ((n < 1) || (n >= _msg.size())) {
        return;
    } else if ((n >= 1) || (n < _msg.size())) {
        const Message *m = _msg[n];
        string subject = "Re: " + m->subject();
        const Name& tmp = tofrom(m);
        Message *ptr = new Message(_ac->owner().name(), tmp.name(), subject, m->text());
        //tell account to insert message into Drafts folder.
        _ac->insert(ptr);
    }
}
