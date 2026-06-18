#pragma once
#include <iostream>
#include <numeric>
#include <concepts>
#include <algorithm>
#include <list>
#include <set>
using namespace std;

template <typename T> requires integral<T> || floating_point<T>
class fifo {
    list<T> coda;
public:
    // costruttore di default
    fifo() {}
    //metodo put
    void put (const T& val){
        coda.push_back(val);
    }
    //metodo get
    T get() {
        T val= coda.front();
        coda.pop_front();
        return val;
    }

    bool empty() const{
        return coda.empty();
    }
};

template <typename T> requires integral<T> || floating_point<T>
class lifo{
    list<T> pila;
public:
    //costruttore di default
    lifo() {}
    //metodo put
    void put(const T& val){
        pila.push_back(val);
    }
    //metodo get
    T get() {
        T x=pila.back();
        pila.pop_back();
        return x;
    }
    //metodo empty
    bool empty() const{
        return pila.empty();
    }
};
