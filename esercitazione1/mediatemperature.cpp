#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc<2) {
        cerr << "Errore: nessun file inserito!\n";
        return 1;
    } 

    string filename= argv[1];
    ifstream ifs(filename);
    if (ifs.is_open() ) {
        cout << "Il file e' stato aperto correttamente\n";
        while( !ifs.eof() ) {
            string location;
            double temp1;
            double temp2;
            double temp3;
            double temp4;
            ifs >> location >> temp1 >> temp2 >>temp3 >> temp4;
            if (ifs.fail() ) {
                cerr << "Errore nel file\n";
                break;
            }
            double media_temp=(temp1 + temp2 + temp3 +temp4)/4;
            cout << "Citta': " << location << ", media temperature: " << media_temp << "\n";
        }
    }
    else {
        cout << "Impossibile aprire il file";
        return 1;
    }
    return 0;
}