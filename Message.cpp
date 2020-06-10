//
//  Message.cpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#include "Message.hpp"

//Class Message definitions

void Message::  setDate () {
    auto t_now = std:: chrono::system_clock::now();
    _date = std::chrono::system_clock::to_time_t(t_now);
}

void Message:: send() {
    setDate();
}

string Message :: date() const {
    if (_date > 0) {
        return std::ctime(&_date);
    } else {
        return "";
    }
}

void Message :: print() const
{
    cout << "From: " << _from.name() << "   <" <<  _from.address() << ">" <<endl;
    cout << "To:   " << _to.name() << "   <" << _to.address() << ">" << endl;
    cout << "Subject: " << _subject << endl;
    cout << "Date: "    << date()   << endl;
    cout << _text << endl;
    cout << endl;
}


void Message :: prependText(string t)
{
    //concatenating strings. Declared a temp variable to store existing string.
    string message = _text;
    //store new text after the concatenation
    _text = t + " " + message;
    
}

void Message :: appendText(string t)
{
    //concatenating strings, changed the order from prepend method in order to append.
    string message = _text;
    //new text after the concatenation
    _text = message + " " + t;
    
}

Message :: Message()
{
    _date = 0;
}

Message :: Message(string f) {
    _from.set(f);
    _date = 0;
}

Message :: Message(string f, string t)
{
    _from.set(f);
    _to.set(t);
    _date = 0;
}

Message :: Message(string f, string t, string s)
{
    _from.set(f);
    _to.set(t);
    _subject = s;
    _date = 0;
}

Message :: Message(string f, string t, string s, string txt) {
    _from.set(f);
    _to.set(t);
    _subject = s;
    _text = txt;
    _date = 0;
}
