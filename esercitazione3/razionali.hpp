#include <numeric>
#include <concepts>
#include <iostream>
using namespace std;

template<typename I> requires integral<I> 
class rational { 
    I num_; 
    I den_; 

public: 
    // funzione per semplificare la frazione
    void semplifica() {
        if (den_ ==0) return; //controllo che non sia inf o nan
        I max_comune = gcd(num_, den_);
        num_ /= max_comune;
        den_ /= max_comune;
    }

    // verifica se e' un Not a Number
    bool ver_nan() const {
        return (den_==0 && num_==0);
    }

    // verifica se e' infinito 
    bool ver_inf() const {
        return (den_==0 && num_!=0);
    }

   // costruttore di default
   rational ()
            : num_(I{0}), den_(I{1})
   {}

   // costruttore user-defined
   rational(const I& pnum, const I& pden)
           : num_(pnum), den_(pden) {
            if (den_!=0) {
                semplifica();
            }
    }

   // restituiamo i valori di num e den
   I num() const { return num_;}
   I den() const { return den_; }

   // somma
   rational& operator+=(const rational& other){

    if (this->ver_nan() || other.ver_nan()) { // nan + numero = nan
    num_ = 0;
    den_ = 0; 
    return *this;
    }
    
    if (this->ver_inf() || other.ver_inf()) { // inf + numero = inf
    num_ = 1;
    den_ = 0;
    return *this;
    }
    // somma fra frazioni normali
    num_ = num_*other.den_ +other.num_*den_;
    den_= den_*other.den_;
    semplifica();
    return *this;
   }

   rational operator+(const rational& other) const{
    rational ret= *this;
    ret += other;
    return ret;
   }

   // differenza
   rational& operator-=(const rational& other){
    if (this->ver_nan() || other.ver_nan()) {  // NaN - numero
    num_ = 0;
    den_ = 0; 
    return *this;
    }

    if (this->ver_inf() && other.ver_inf()) {  //Inf - Inf
    num_ = 0;
    den_ = 0;
    return *this;
    }
    
    if (this->ver_inf() || other.ver_inf()) {  //Inf - numero
    num_ = 1;
    den_ = 0;
    return *this;
    }

    // differenza fra frazioni normali
    num_ = num_*other.den_ -other.num_*den_;
    den_= den_*other.den_;
    semplifica();
    return *this;
   }

   rational operator-(const rational& other) const{
    rational ret= *this;
    ret -= other;
    return ret;
   }

   //prodotto
   rational& operator*=(const rational& other){
    if (this->ver_nan() || other.ver_nan()) { //NaN *num= NaN
    num_ = 0;
    den_ = 0; 
    return *this;
    }
    if ((this->ver_inf() && other.num_ == 0) || (other.ver_inf() && this->num_ == 0)) { //se uno dei due num=0
        num_ = 0; 
        den_ = 0;
        return *this;
		}
    
    if (this->ver_inf() || other.ver_inf()) { // inf*num= inf
    num_ = 1;
    den_ = 0;
    return *this;
    }
    //prodotto fra frazionali normali
    num_ = num_*other.num_;
    den_= den_*other.den_;
    semplifica();
    return *this;
   }

   rational operator*(const rational& other) const{
    rational ret= *this;
    ret *= other;
    return ret;
   }

   //divisione
   rational& operator/=(const rational& other){
    if (this->ver_nan() || other.ver_nan()) {  // NaN/num o num/NaN
    num_ = 0;
    den_ = 0; 
    return *this;
    }
    // razionali/0=inf
    if (other.num_ == 0 && other.den_ != 0) {
    num_ = 1; 
    den_ = 0;
    return *this;
    }
    
    // 0/inf= 0
    if (this->num_ == 0 && other.ver_inf()) {
    num_ = 0; 
    den_ = 1;
    return *this;
    }
    // Inf/Inf=NaN oppure 0/0=NaN   
    if ((this->ver_inf() && other.ver_inf()) || (this->num_ == 0 && other.num_ == 0)) {
    num_ = 0; 
    den_ = 0; 
    return *this;
    }
    // divisione fra frazionali normali
    num_ = num_*other.den_;
    den_= den_*other.num_;
    semplifica();
    return *this;
   }

   rational operator/(const rational& other) const{
    rational ret= *this;
    ret /= other;
    return ret;
   }

};

// stampa
template<typename I>
ostream& operator<<(ostream& os, const rational<I>& r) 
{
	if (r.ver_nan()) os << "NaN";
    else if (r.ver_inf()) os << "Inf";
    else os << r.num() << "/" << r.den();
    return os;
}