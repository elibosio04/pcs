#include <iostream>
#include "razionali.hpp"

int main(void)
{
rational<int> r(3,6);
rational<int> a(3,0);
rational<int> b(1,0);
rational<int> e(0,0);

std::cout << "Semplificazione (3/6): " << r << "\n";  //stampo il razionale per vedere se lo semplifica correttamente
std::cout << "Infinito (1/0): " << b << "\n";  //provo a vedere se stampa inf
std::cout << "NaN (0/0): " << e << "\n";  //provo a vedere se stampa NaN

std::cout << "\n" << "--Test operazioni con inf--"<< "\n";
std::cout << "num/inf: " << (r/b) << "\n";   //provo a dividere r per inf
std::cout << "inf - inf: " << (b-a) << "\n";   //provo a fare inf - inf
std::cout << "num*inf: " << (r*a) << "\n";  //num * inf
std::cout << "inf/inf: " << (a/b) << "\n";  // inf/inf

rational<int> c(-3,9);
rational<int> d(4,17);
rational<int> f(0,1);
std::cout << "\n" << "--Test operazioni--"<< "\n";
std::cout << "Prodotto: " << (c*d) << "\n";  //moltiplico i due razionali
std::cout << "Somma: " << (c+d) << "\n"; //sommo i due razionali
std::cout << "Sottrazione: " << (c-d) << "\n";  //sottraggo i due razionali
std::cout << "Divisione: " << (c/d) << "\n";  // divido i due razionali
std::cout << "num/0: " << (d/f) << "\n";  // divido per zero
std::cout << "0/inf: " << (f/b) << "\n";  // 0 / inf

std::cout << "\n" << "--Test operazioni con NaN--"<< "\n";
std::cout << "NaN*num: " << (e*d) << "\n";  //Nan * num
std::cout << "NaN+num: " << (e+d) << "\n"; //Nan + num
std::cout << "NaN-num: " << (e-d) << "\n";  //Nan - num
std::cout << "num/Nan: " << (d/e) << "\n";  // num/NaN

return 0; 
}