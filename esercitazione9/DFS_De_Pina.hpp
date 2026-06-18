#pragma once
#include "contenitori.hpp"
#include "graph.hpp"
#include "visita_grafi.hpp"
#include <limits>
#include <concepts>
#include <set>
#include <map>
#include <vector>
#include <Eigen/Dense>

using namespace std;


//dfs per cicli
template<typename I>
bool findpath(const unidirected_graph<I>& T, const I& u, const I& v, set<I>& visited, vector<I>& path){
    visited.insert(u);  //considero visitato il nodo corrente
    path.push_back(u);
    if (u==v){
        return true;
    }
    for (const I& n: T.neighbours(u)){  //controllo i vicini non ancora visitati
        if (visited.count(n)==0){ //controllo che il vicino non sia ancora stato visitato
            if (findpath(T, n, v , visited, path)){
                return true;
            }
        }
    }
    path.pop_back();
    return false; 
}

template<typename I> requires integral<I>
vector<vector<I>> cicli_dfs(const unidirected_graph<I>& G){
    vector<vector<I>> cicli; // inizializzo un vettore di vettori che conterrà tutti i cicli
    I nodo_sorgente = *G.all_nodes().begin(); //costruiamo l'albero DFS
    lifo<I> pila; 
    unidirected_graph<I> T = graph_visit(G, nodo_sorgente, pila);
    unidirected_graph<I> C= G-T; //troviamo il coalbero
    set<unidirected_edge<I>> archi_coalbero=C.all_edges(); //salviamo in un set gli archi del coalbero per poterci ciclare sopra
    
    for (const auto& arco : archi_coalbero){
        I u=arco.from();
        I v=arco.to();

        set<I> visited;
        vector<I> path;

        if (findpath(T, u, v, visited, path)){  //trovo il cammino da u a v
            path.push_back(u); //aggiungo u al cammino per formare il ciclo
            cicli.push_back(path);
        }
    }
    return cicli;
}

//algoritmo de pina

//prodotto scalare
bool prodotto_scalare(const vector<bool>& S, const vector<bool>& P){
    if (S.size() != P.size()) {
        cerr << "Errore: vettore di dimensioni diverse" << endl;
        return false; 
    }
    int count=0; //qua conto il numero di 1 in posizioni corrispondenti
    for (size_t i=0; i <S.size(); i++){
        if (S[i] && P[i]){
           count++; 
        }
    }
    return (count%2)!=0; //restituisce true se il numero di 1 è dispari, 0 se è pari
}

//differenza simmetrica
vector<bool> differenza_simmetrica(const vector<bool>& S, const vector<bool>& P) {
    if (S.size() != P.size()) {
        cerr << "Errore: vettori di dimensioni diverse" << endl;
    }
    vector<bool> risultato(S.size());
    for (size_t i=0; i < S.size(); i++){
        risultato[i]=S[i]^P[i];
    }
    return risultato;
}

template<typename I>
vector<bool> cicli_minimi(const unidirected_graph<I>& G, const vector<bool>& S_i, const Eigen::MatrixXi& pesi){
    set<unidirected_edge<I>> archi=G.all_edges();
    int N=G.all_nodes().size(); //numero di nodi del grafo originale
    int m=archi.size(); //numero totale di archi

    //definisco la matrice dei pesi di G primo
    Eigen::MatrixXi pesi_G_primo=Eigen:: MatrixXi::Constant(2*N,2*N, INF ); 
    for (const auto& arco: archi){
        int u= arco.from();
        int v=arco.to();

        int u_pos=u;     //associo ai nodi positivi una posizione da 0 a N e a quelli negativi da N a 2N, dato che il mio algoritmo dijkstra usa solo distanze positive
        int v_pos=v;
        int u_neg=u+N;
        int v_neg= v+N;

        int peso_arco=pesi(u,v);
        int i=G.edge_number(arco);
        if (i !=-1){ 
            if (S_i[i]){ 
                pesi_G_primo(u_pos, v_neg)=peso_arco;
                pesi_G_primo(u_neg, v_pos)=peso_arco;
                pesi_G_primo(v_pos, u_neg)=peso_arco;
                pesi_G_primo(v_neg, u_pos)=peso_arco;
            }
            else {
                pesi_G_primo(u_pos, v_pos)=peso_arco;
                pesi_G_primo(v_pos, u_pos)=peso_arco;
                pesi_G_primo(v_neg, u_neg)=peso_arco;
                pesi_G_primo(u_neg, v_neg)=peso_arco;
            }
        }
    }

    //ricerca cammino minimo
    vector<bool> C_i(m, false);
    int min_elementi=INF;

    for (int v=0; v<N; v++){
        int sorgente_pos=v;
        int destinazione_neg=v+N;

        vector<int> distanze;
        vector<int> predecessori;

        dijkstra(2*N, pesi_G_primo, sorgente_pos, distanze, predecessori);
        if (distanze[destinazione_neg]!=INF){
            vector<bool> C_mu(m, false); //creiamo un vettore booleano per il cammino corrente
            int corrente= destinazione_neg;
            bool cammino_valido=true;
            while(corrente!= sorgente_pos){
                int pred=predecessori[corrente];
                if (pred==-1){
                    cammino_valido=false;
                    break;
                }
                int u_orig=pred % N;  //mi ritrovo i nodi originali
                int v_orig=corrente % N;

                unidirected_edge<I> arco_corrente(u_orig, v_orig);
                int indice=G.edge_number(arco_corrente);
                if (indice!=-1){
                    C_mu[indice]=!C_mu[indice];
                }
                corrente=pred;
            }

            if (cammino_valido){
                int conto=0; //per contare quanti true ho
                for (int k=0; k<m; k++){
                    if (C_mu[k]){
                        conto++;
                    }
                }
                if (conto<min_elementi){
                    min_elementi=conto;
                    C_i=C_mu;
                }
            }
        }
    }
    return C_i;
}

template<typename I> requires integral<I>
vector<vector<bool>> algoritmo_de_pina(const unidirected_graph<I>& G, const Eigen::MatrixXi& pesi) { 
    set<unidirected_edge<I>> archi=G.all_edges();
    int m=archi.size();
    I nodo_sorgente = *G.all_nodes().begin();
    lifo<I> pila; 
    unidirected_graph<I> T = graph_visit(G, nodo_sorgente, pila);
    unidirected_graph<I> C=G-T;
    set<unidirected_edge<I>> archi_coalbero=C.all_edges();
    int k=archi_coalbero.size();
    //inizializziamo la matrice di supporto S
    vector<vector<bool>> S(k, vector<bool>(m, false));
    int i=0; //contatore per indentificare la riga di S_i
    for (const auto& arco: archi_coalbero){
        int indice=G.edge_number(arco);
        if (indice!=-1){
            S[i][indice]= true;
        }
        i++;
    }
    //inizializzo il vettore contenente tutti i C_i
    vector<vector<bool>> B(k); 
    for (int riga=0; riga <k; riga++){
        B[riga]=cicli_minimi(G, S[riga], pesi);
        for (int j=riga +1; j<k; j++){
            if (prodotto_scalare(S[j], B[riga])){
                S[j]=differenza_simmetrica(S[j],S[riga]);
            }
        }
    }
    return B;
}
