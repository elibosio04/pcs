#include <optional>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
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