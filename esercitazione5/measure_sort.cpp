#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "randfiller.h"
#include "timecounter.h"
#include "sort.hpp"
#include <algorithm> //per poter usare sort
using namespace std;

int main(void) {
    timecounter tc;  //inizializzo il time counter
    randfiller rf;    //inizializzo il randfiller
    for (int dim=2; dim<=100; dim=dim+2){
        vector<vector<int>> vec_vettori(100, vector<int>(dim));
        for (int n=0; n<100; n++){
            rf.fill(vec_vettori[n], -1000,1000);
        }
        vector<vector<int>> vec_bubble=vec_vettori; //creo delle copie del vettore di vettori in modo da poter calcolare i tempi per ogni tipo di sort
        vector<vector<int>> vec_sel=vec_vettori;
        vector<vector<int>> vec_ins=vec_vettori;
        vector<vector<int>> vec_sort=vec_vettori;
        vector<vector<int>> vec_merge=vec_vettori;
        vector<vector<int>> vec_quick=vec_vettori;
        
        //misuro il tempo di bubble
        tc.tic();
        for (int i=0; i<100; i++){
            bubble_sort(vec_bubble[i]);
        }
        double t_bubble=tc.toc()/100;

        //misuro il tempo di insertion
        tc.tic();
        for (int i=0; i<100; i++){
            insertion_sort(vec_ins[i]);
        }
        double t_ins=tc.toc()/100;

        //misuro il tempo di selection
        tc.tic();
        for (int i=0; i<100; i++){
            selection_sort(vec_sel[i]);
        }
        double t_sel=tc.toc()/100;

        //misuro il tempo di sort
        tc.tic();
        for (int i=0; i<100; i++){
            sort(vec_sort[i].begin(), vec_sort[i].end());
        }
        double t_sort=tc.toc()/100;

        //misuro il tempo di mergesort
        tc.tic();
        for (int i=0; i<100; i++){
            merge_sort(vec_merge[i], 0, dim-1);           
        }
        double t_merge=tc.toc()/100;

        //misuro il tempo di quicksort
        tc.tic();
        for (int i=0; i<100; i++){
            quicksort(vec_quick[i], 0, dim-1);
        }
        double t_quick=tc.toc()/100;
        
        cout << "Dimensione vettore: "<< dim << "\n";
        cout << "Tempo bubble: " << t_bubble << "\n";
        cout << "Tempo insertion: " << t_ins << "\n";
        cout << "Tempo selection: " << t_sel << "\n";
        cout << "Tempo sort: " << t_sort << "\n" ;
        cout << "Tempo merge: " << t_merge << "\n" ;
        cout << "Tempo quick: " << t_quick << "\n\n" ;
    }
}
