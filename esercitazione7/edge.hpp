#pragma once
#include <iostream>
#include <algorithm>
#include <concepts>
using namespace std;

template<typename I> requires integral<I> 
class unidirected_edge{
    I n1;
    I n2;
public:
    //costruttore di default
    unidirected_edge() : n1(0), n2(0) {} 
    
    unidirected_edge(const I& u, const I& v){
        //troviamo qual è il nodo più piccolo
        n1=min(u,v);
        n2=max(u,v);
    }

    I from() const{
        return n1;
    }
    I to() const{
        return n2;
    }

    //definisco l'operatore <
    bool operator<(const unidirected_edge<I>& other) const{
        if (n1 != other.n1){
            return n1<other.n1;
        }
        return n2<other.n2;
    }

    //definisco l'operatore ==
    bool operator==(const unidirected_edge<I>& other) const{
        return (n1==other.n1) && (n2==other.n2);
    }
};

// stampa
template<typename I>
ostream& operator<<(ostream& os, const unidirected_edge<I>& v) 
{
    os <<"(" << v.from() << " - " << v.to() << ")";
    return os;
}