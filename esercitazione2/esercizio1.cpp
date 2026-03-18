#include <iostream>

int main()
{
    double ad[4]= {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7}; 
    int ai[3] = {0, 1, 2}; 

    int x = 1; 
    float y = 1.1; 

    (&y)[1] = 0;  // è qua il problema per x: mi considera y come un array e cerca di cambiare il suo elemento in posizione 1, 
    // ma se io mi sposto di 4 byte in memoria trovo x e quindi il programamma mi cambia il valore di x con 0

    std::cout << "address ad[0]=" << &ad[0] << "\n";
    std::cout << "address af[0]=" << &af[0] << "\n";
    std::cout << "address ai[0]=" << &ai[0] << "\n";
    std::cout << "address x=" << &x << "\n";
    std::cout << "address y=" << &y << "\n";
    // stampo gli address del primo elemento di ogni array per vedere la loro posizione in memoria

    std::cout << x << "\n"; 

    return 0; 
}