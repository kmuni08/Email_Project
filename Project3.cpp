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

template<class T> class Vec {
    
public:
    Vec();
    Vec(int n);
    Vec(int n, const T &a);
    
    Vec(const Vec &orig);
    Vec& operator= (const Vec &rhs);
    ~Vec();
    
    int capacity() const { return _capacity; }  //inline
    int size() const     { return _size; }      //inline
    
    T front() const;
    T back() const;
    
    void erase(int n);
    void clear();
    void pop_back();
    void push_back(const T &a);
    
    T& at(int n);
    T& operator[] (int n);
    const T& operator[] (int n) const;
    
private:
    void allocate();
    void release();
    
    int _capacity;
    int _size;
    T * _vec;
};

class Name {
public:
    Name() {}
    Name(string s) { set(s); }
    
    void set(string s);
    string name() const {return _name; }
    string address() const {return _address; }
    
private:
    string _name;
    string _address;
};

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

class BaseFolder {
    
public:
    //virtual destructor and loop to release dynamic memory
    virtual ~BaseFolder() {
        for(int i = 0; i < _msg.size(); i++) {
            delete _msg[i];
        }
    }
    
    int size() const { return _msg.size(); }
    
    void display() const;
    void erase(int n);
    void forward(int n) const;
    void print(int n) const;
    void receive(const Message *m);
    void reply(int n) const;
    
private:
    BaseFolder (const BaseFolder& orig) {};
    BaseFolder& operator = (const BaseFolder& rhs) {return *this;}
    
protected:
    virtual string type() const = 0; //pure virtual function
    virtual const Name& tofrom(const Message *m) const = 0;  // pure virtual function
    
    Vec<const Message*> _msg;
    EmailAccount *_ac;
    
    //Makes this into an Abstract Class
    BaseFolder(EmailAccount *ac) : _ac(ac) { _msg.push_back(NULL);
    }
};

// Inbox class
class Inbox : public BaseFolder {
public:
    Inbox(EmailAccount *ac) : BaseFolder(ac) { };               // public constructor
    
protected:
    //inline definition
    virtual string type() const { return "inbox"; }
    virtual const Name& tofrom(const Message *m) const {return m->from(); }
};

// Outbox class
class Outbox : public BaseFolder {
public:
    Outbox(EmailAccount *ac) : BaseFolder(ac) { };
    
protected:
    //inline definition
    virtual string type() const {return "outbox"; }
    virtual const Name& tofrom(const Message *m) const {return m->to(); }
};

class Drafts {
public:
    Drafts(EmailAccount *ac);
    ~Drafts();
    
    void display() const;
    void send(int n);
    void erase(int n);
    
    Message* addDraft();
    Message* addDraft(Message *m);
    Message* getDraft(int n) { return _drafts[n];}
    Message* operator[](int n) { return _drafts[n];}
    
private:
    int newKey();
    
    //data
    int _newKey;
    map<int, Message*> _drafts;
    EmailAccount *_ac;
    
    //functions made private to disable copies.
    Drafts(const Drafts& orig) {};
    Drafts operator = (const Drafts& rhs) {return *this;}
};

class EmailAccount {
public:
    EmailAccount(string s);
    ~EmailAccount();
    
    const Name& owner() const { return _owner; }  // accessor
    Drafts& drafts()  { return *_drafts; }
    BaseFolder& in()  { return *_in; }
    BaseFolder& out() { return *_out; }
    
    void send(Message *m);
    void receive(Message *m);
    void insert(Message *m);
    
private:
    Name _owner;
    Drafts * _drafts;
    BaseFolder  * _in;
    BaseFolder * _out;
    
    //make functions private
    EmailAccount (const EmailAccount& orig) {};
    EmailAccount&  operator = (const EmailAccount& rhs) {return *this;}
};

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

//static variable initialization outside of the ISP class.
map<Name, EmailAccount*> ISP:: _accounts;

//class template method definitions.
template<typename T>

T Vec<T> :: front() const {
    if(_size <= 0) {
        T default_obj;
        return default_obj;
    } else
        return _vec[0];
    
}

template<typename T>

T Vec<T> :: back() const {
    if(_size <= 0) {
        T default_obj;
        return default_obj;
    } else
        return _vec[_size-1];
    
}

template<typename T>

void Vec<T> :: erase(int n) {
    if (n >= 0 && n < _size)
    {
        //copy _vec[n+1] to _vec[n] etc...
        for(int i = n; i < _size; ++i) {
            _vec[i] = _vec[i+1];
        }
        _size = _size -1;
    } else {
        return;
    }
}

template<typename T>

void Vec<T> :: clear() {
    _size = 0;
}

template<typename T>

void Vec<T> :: pop_back() {
    if (_size > 0) {
        _size--;
    }
}

template<typename T>

void Vec<T> :: allocate() {
    if(_capacity <= 0) {
        _vec = NULL;
    } else if (_capacity > 0) {
        _vec = new T[_capacity];
    }
}

template<typename T>

void Vec<T> :: release() {
    if(_vec == NULL) {
        return;
    } else if (_vec != NULL) {
        delete [] _vec;
        _vec = NULL;
    }
}

template<typename T>
Vec<T> :: Vec() : _capacity(0), _size(0), _vec(0) {}

template<typename T>

Vec<T> :: Vec(int n) {
    if (n <= 0) {
        _capacity = 0;
        _size = 0;
        _vec = NULL;
    } else if (n > 0) {
        _capacity = n;
        _size = n;
        allocate();
    }
}

template<typename T>

Vec<T> :: Vec(int n, const T &a) {
    if (n <= 0) {
        _capacity = 0;
        _size = 0;
        _vec = NULL;
    } else if (n > 0) {
        _capacity = n;
        _size = n;
        allocate();
        for(int i = 0; i < _capacity; i++){
            _vec[i] = a;
        }
    }
}

template<typename T>

Vec<T> :: ~Vec() {
    release();
}

template<typename T>

Vec<T> :: Vec(const Vec &orig) {
    _capacity = orig._size;
    _size = orig._size;
    allocate();
    
    for(int i = 0; i < _size; i++) {
        _vec[i] = orig._vec[i];
    }
}

template<typename T>

Vec<T>& Vec<T>:: operator= (const Vec &rhs) {
    if (this == &rhs) {
        return *this;
    }
    _capacity = rhs._size;
    _size = rhs._size;
    release();
    allocate();
    for(int i = 0; i < _size; i++) {
        _vec[i] = rhs._vec[i];
    }
    return *this;
}

template<typename T>

void Vec<T> :: push_back(const T &a) {
    
    if(_size < _capacity) {
        _vec[_size] = a;
        _size = _size + 1;
        return;
    } else if (_size == _capacity) {
        if (_capacity == 0) {
            _capacity = 1;
        } else if (_capacity > 0) {
            _capacity *= 2;
        }
    }
    
    T *oldvec = _vec;
    allocate();
    if (oldvec != NULL) {
        for (int i = 0; i < _size; ++i) {
            _vec[i] = oldvec[i];
        }
    }
    delete [] oldvec;
    
    _vec[_size] = a;
    _size++;
}

template<typename T>

T& Vec<T> :: at(int n) {
    if (n >= 0 && n < _size) {
        return _vec[n];
    } else {
        T *pnull = NULL;
        return *pnull;
    }
}

template<typename T>

T& Vec<T> :: operator[] (int n) {
    return at(n);
}

template<typename T>

const T& Vec<T> :: operator[] (int n) const {
    if (n >= 0 && n < _size) {
        return _vec[n];
    } else {
        T *pnull = NULL;
        return *pnull;
    }
}

//operators for comparing address of n1 and n2.
bool operator == (const Name& n1, const Name& n2) {
    return n1.address() == n2.address();
}

bool operator < (const Name& n1, const Name& n2) {
    return n1.address() < n2.address();
}

//class Name method definitions
void Name:: set(string s) {
    const string _domain = "@qc.cuny.edu";
    istringstream iss(s);
    iss >> _name; // remove leading and trailing blank spaces
    
    if (_name == "") {
        _address = "";
        return;
    } else {
        _address = _name + _domain;
    }
    
    //convert _address to lowercase
    for(int i = 0; i < _address.length(); i++) {
        _address[i] = tolower(_address[i]);
    }
}

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

int main() {
    
    //Testing code.
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

