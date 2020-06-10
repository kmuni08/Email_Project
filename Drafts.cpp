//
//  Drafts.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "Drafts.hpp"

//class Drafts method definitions.

Drafts :: Drafts(EmailAccount *ac){
    _ac = ac;
    _newKey= 0;
    _drafts[0] = NULL;
}

Drafts :: ~Drafts() {
    //iterator to deallocate memory.
    map<int, Message*> :: iterator m_drafts;
    for(m_drafts = _drafts.begin(); m_drafts != _drafts.end(); ++ m_drafts) {
        delete (m_drafts->second);
        }
    }

int Drafts :: newKey() {
    return ++_newKey;
    //Because _newKey is not static, each email account would have it's own value of newKey. This newKey is guaranteed to be distinct from all the other newKeys.
}

void Drafts:: erase(int n) {
    delete _drafts[n];
    _drafts.erase(n);
}

Message* Drafts:: addDraft() {
    int key = newKey();
    Message *ptr = new Message(_ac->owner().name());
    _drafts[key] = ptr;
    return ptr;
}

Message* Drafts:: addDraft(Message *m) {
    //used when user invokes reply or forward.
    int key = newKey();
    _drafts[key] = m;
    return m;
}

void Drafts:: display() const {
    cout << _ac-> owner().name() << " drafts: " << endl;
    if(_drafts.size() <= 1) {
        cout << "no messages to display" << endl;
    } else {
        map<int, Message*> :: const_iterator mit;
        for(mit = _drafts.cbegin(); mit != _drafts.cend(); ++ mit) {
            if (mit->first == 0) {
                continue;
            }
            const Message *ptr = mit->second;
            cout << mit-> first << " " << ptr->to().name() << " " << ptr->subject() << endl;
        }
    }
}

void Drafts:: send(int n) {
    Message* ptr = _drafts[n];
    if (ptr == NULL) {
        cout << "Message not found. " << endl;
        return;
    } else if (ptr->to().address() == "") {
        cout << "You must specify a recipient" << endl;
        return;
    } else {
        ptr->send();
        _drafts.erase(n);
        _ac->send(ptr);
    }
}
