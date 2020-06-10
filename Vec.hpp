//
//  Vec.hpp
//  Email
//
//  Created by Karishma Muni on 6/10/20.
//  Copyright © 2020 Karishma Muni. All rights reserved.
//

#ifndef Vec_hpp
#define Vec_hpp

#include <iostream>
#include <string>

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

#endif /* Vec_hpp */
