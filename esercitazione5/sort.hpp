#include <optional>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// bubble-sort
template<typename T>
optional<vector<T>>
bubble_sort(vector<T>& vec)
{
    if (vec.size() ==0){
        return {};
    }
    else {
        int n=vec.size(); //mi salvo la lunghezza del vettore
        for (int i=0; i<n-1; i++){
            for (int j=n-1; j>i; j--){
                if (vec[j]<vec[j-1]) {
                    swap(vec[j], vec[j-1]);
                }
            }
        }
    }
    return vec;
}

// insertion-sort
template<typename T>
optional<vector<T>>
insertion_sort(vector<T>& vec){
    if (vec.size() ==0){
        return {};
    }
    else {
        int n=vec.size();
        for (int i=1; i<=n-1; i++){
            T value=vec[i];
            int j=i-1;
            while(j>=0 && vec[j]>value){
                swap (vec[j+1], vec[j]);
                j=j-1;
            }
            vec[j+1]=value;
        }
    }
    return vec;
}

// selection-sort
template<typename T>
optional<vector<T>>
selection_sort(vector<T>& vec){
    if (vec.size() ==0){
        return {};
    }
    else {
        int n=vec.size();
        for (int i=0; i<=n-2; i++){
            int min_index=i;
            for (int j=i+1; j<=n-1; j++){
                if (vec[j]<vec[min_index]){
                    min_index=j;
                }
            }
            if (min_index!=i){
                swap(vec[i], vec[min_index]);
            }
        }               
    }
    return vec;    
}

//merge
template<typename T>
optional<vector<T>>
merge(vector<T>& vec, int p, int q, int r){
    //calcolo lunghezze dei due vettori divisi
    int n1=q-p+1;
    int n2=r-q;
    //creo vettori temporanei
    vector<T> L(n1);
    vector<T> R(n2);
    //copio i dati
    for (int i=0; i<n1; i++){
        L[i]=vec[p+i];
    }
    for (int j=0; j<n2; j++){
        R[j]=vec[q+j+1];
    }

    int i=0;
    int j=0;
    //unione
    for (int k=p; k<=r; k++){
        if (i<n1 && (j>=n2 || L[i]<=R[j])){  //avevo dei problemi ad usare l'infinito con le stringhe allora ho cambiato la condizione dell'if
            vec[k]=L[i];
            i++;       
        }
        else{
            vec[k]=R[j];
            j++;
        }
    }
    return vec;
}

// merge-sort
template<typename T>
optional<vector<T>>
merge_sort(vector<T>& vec, int p, int r){
    if (vec.size()==0){
        return {};
    }
    else {
        if (p<r){
            int q=(p+r)/2;
            merge_sort(vec, p, q);
            merge_sort(vec, q+1,r);
            merge(vec, p, q,r);
        }
    }   
    return vec;    
}

//partition
template<typename T>
int partition(vector<T>&vec, int p, int r){
    T x=vec[r];
    int i= p-1;
    for (int j=p; j<=r-1; j++) {
        if (vec[j]<=x){
            i++;
            swap(vec[i], vec[j]);
        } 
    }
    swap(vec[i+1], vec[r]);
    return i+1;
}

// quicksort
template<typename T>
optional<vector<T>>
quicksort(vector<T>& vec, int p, int r){
    if (vec.size() ==0){
        return {};
    }
    else {
        if (p<r){
            int q=partition(vec, p, r);
            quicksort(vec, p, q-1);
            quicksort(vec, q+1,r);
        }
    }   
    return vec;    
}

//quicksort ibrido
//il mio quicksort modificato sotto la soglia di 70 (che ho trovato guardando il mio grafico) usa l'insertion sort e sopra il quicksort
template<typename T>
optional<std::vector<T>>
quicksort_ibrido(vector<T>& vec, int p, int r, int soglia = 70) 
{
    if (vec.size()==0) {
        return {};
    }

    if (p < r){
        if ((r - p + 1) < soglia) {
            insertion_sort(vec);
        } 
        else {
            int q = partition(vec, p, r);
            quicksort_ibrido(vec, p, q - 1, soglia);
            quicksort_ibrido(vec, q + 1, r, soglia);
        }
    }
    return vec;
}

//funzione per vedere se il vettore e' gia' ordinato
template<typename T>
bool is_sorted(const vector<T>& vec){
    if (vec.size() ==0){
        return true;
    }
    
    int n=vec.size();
    for (int i=0; i<n-1; i++){
        if (vec[i]>vec[i+1]){
            return false;
        }           
    }
    return true;
    
}