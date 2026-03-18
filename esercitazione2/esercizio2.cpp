#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // esercizio 2.0
    static const int N = 10; 
    double a[N] = {3.2, 6, 9.4, 3, 9.8, 7.5, 5.3, 2, 1.6, 9.3};
    double massimo=a[0];
    double minimo=a[0];
    double somma=a[0];
    double dev=0;
    // faccio un ciclo per calcolare minimo, massimo e media
    for (int i=1; i<=N-1; i=i+1) {
        minimo=min(minimo, a[i]);
        massimo=max(massimo, a[i]);
        somma=somma+a[i];
    }
    double media=somma/N;
    double somma2=0; 
    // faccio un ciclo per calcolare la somma di (ogni elemento di a - media)^2
    for (int i=0; i<=N-1; i=i+1) {
        somma2=somma2+(media-a[i])*(media-a[i]);
    }
    dev=sqrt(somma2/(N-1));
    cout << "Il minimo di a e': " << minimo << "\n";
    cout << "Il massimo di a e': " << massimo<< "\n";
    cout << "La media di a e': " << media << "\n";
    cout << "La deviazione standard di a e': " << dev << "\n";

    // esercizio 2.1
    int flag=1;  // inizializzo una flag che mi conta il numero di scambi effettuati
    while (flag>=1) {   //faccio un ciclo while che mi va avanti fino a che non ho la flag=0
        flag=0; // rimetto la flag a 0 dopo che ho finito di eseguire il ciclo for
        for (int i=0; i<=N-2; i=i+1) {
            if (a[i]>a[i+1]){
                double b=a[i];  // salvo gli elementi per poi scambiarli
                double c=a[i+1];
                a[i]=c;
                a[i+1]=b;
                flag=flag+1;
            }

        }
    }
    cout << "Il mio array ordinato è: ";
    for (int i=0; i<=N-1; i=i+1) {
        cout << a[i] << ", ";
    }

    return 0;
}