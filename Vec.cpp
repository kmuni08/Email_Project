#include "Vec.hpp"

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
