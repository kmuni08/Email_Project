//
//  Message.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

#include "Name.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>

using namespace std;

class Name;

class Message {
    
public:
    //class declarations:
    
    Message();
    Message(string f);
    Message(string f, string t);
    Message(string f, string t, string s);
    Message(string f, string t, string s, string txt);
    
    const Name& from() const { return _from; }
    const Name& to() const { return _to; }
    string subject() const { return _subject; }
    string text() const {return _text;}
    
    string date() const;
    void send();
    
    void setRecipient(string t) { _to.set(t);}
    void setSender(string f) { _from.set(f);}
    void setSubject(string s) { _subject = s;}
    void setText(string txt) { _text = txt;}
    
    void prependText(string t);
    void appendText(string t);
    void print() const;
    
private:
    void setDate();
    
    Name _from;
    Name _to;
    string _subject;
    string _text;
    time_t _date;
};


#endif /* Message_hpp */
