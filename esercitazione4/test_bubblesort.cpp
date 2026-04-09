#include <iostream>
#include <vector>
#include <cstdlib>
#include "sort.hpp"
#include "randfiller.h"
using namespace std;
int main(void)
{
    randfiller rf; // inizializzo il randfiller
    //test vettori di numeri
    for (int k=0; k<100; k++) {
        int dimensione=rand() % 1000 +1 ;  // scelgo la dimensione del vettore a caso tra 1 e 1001
        vector<int> vec(dimensione);
        rf.fill(vec, -1000,1000); //lo riempio in modo randomico
        bubble_sort(vec);
        if (!is_sorted(vec)) {    //verifica che il vettore sia effettivamente ordinato
            return EXIT_FAILURE;
        }
    }
    // test stringa
    vector<string> vec_stringa={"elisa", "aurora", "denise", "sofia", "luca", "marco", "pasqua", "cioccolata", "relax"};
    bubble_sort(vec_stringa);
    if (!is_sorted(vec_stringa)){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}