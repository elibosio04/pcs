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
    for (int i=4; i<=8192; i=i*2){
        vector<int> vec_bubble(i);
        rf.fill(vec_bubble, -1000,1000);  
        vector<int> vec_sort=vec_bubble; //mi copio in un altro vettore lo stesso vettore per poter fare il confronto fra bubble e sort
        vector<int> vec_ins=vec_bubble;
        vector<int> vec_sel=vec_bubble;
        
        //misuro il tempo di bubble
        tc.tic();
        bubble_sort(vec_bubble);
        double t_bubble=tc.toc();

        //misuro il tempo di insertion
        tc.tic();
        insertion_sort(vec_ins);
        double t_ins=tc.toc();

        //misuro il tempo di selection
        tc.tic();
        selection_sort(vec_sel);
        double t_sel=tc.toc();

        //misuro il tempo di sort
        tc.tic();
        sort(vec_sort.begin(), vec_sort.end());
        double t_sort=tc.toc();

        cout << "Dimensione vettore: " << i << "\n";
        cout << "Tempo bubble: " << t_bubble << "\n";
        cout << "Tempo insertion: " << t_ins << "\n";
        cout << "Tempo selection: " << t_sel << "\n";
        cout << "Tempo sort: " << t_sort << "\n\n";
    }
}