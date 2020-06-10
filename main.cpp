/*
 Karishma Muni
 CS 211
 Project 3 Email
 This project utilizes classes, inheritance, polymorphism, operator overloading, pointers, vectors, static variable, templates, strings, maps and time to display when the email was sent/received.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "Name.hpp"
#include "Vec.hpp"
#include "Message.hpp"
#include "BaseFolder.hpp"
#include "Inbox.hpp"
#include "Outbox.hpp"
#include "Drafts.hpp"
#include "EmailAccount.hpp"
#include "ISP.hpp"

using namespace std;

//Forward Declaration
template<class T> class Vec;
class Message;
class Name;
class BaseFolder;
class Inbox;
class Outbox;
class Drafts;
class EmailAccount;
class ISP;



int main() {
    
    EmailAccount e1("Bob");
    EmailAccount e2("Alice");
    
    Message m1 ("Carol", "David", "hello", "Using constructor, but this works!");
    m1.send();
    m1.print();
    
    Message *e1email = new Message(e1.owner().name());
    
    e1email->setRecipient("Alice");
    e1email->setSender("Bob");
    e1email->setSubject("First Email");
    e1email->setText("This is my first email.");
     
    
    e1.insert(e1email);
    cout << endl;
    e1.drafts().display();
    cout << endl;
    
    e1.drafts().send(1);
    
    e1.out().display();
    cout << endl;
    e1.drafts().display();
    cout << endl;
    
    e2.in().display();
    e2.in().print(1);
    
    e2.in().reply(1);
    e2.drafts().display();
    
    /*
    e2.drafts().send(1);
    
    e1.in().display();
    e1.in().print(1);
    */
    
    
    e2.in().erase(1);
    e2.in().display();
    /*
    e2.in().reply(1);
   
    e2.drafts().display();
    e2.drafts().erase(1);
    e2.drafts().send(1);
    
    e1.in().display();
*/
    
    
    return 0;
}


