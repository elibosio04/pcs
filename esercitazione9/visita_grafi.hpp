#pragma once
#include "contenitori.hpp"
#include "graph.hpp"
#include <limits>
#include <concepts>
#include <set>
#include <map>
#include <vector>
#include <Eigen/Dense>
using namespace std;

//metodo BFS e DFS
template <typename I, typename Contenitore>
unidirected_graph<I> graph_visit(const unidirected_graph<I>& G, I sorgente, Contenitore& lista) {
    // inizializzo il grafo che sarà l'albero di visita
    unidirected_graph<I> albero; 
    int n=G.all_nodes().size();
    // creo un vettore di booleani per tenere traccia dei nodi visitati
    vector<bool> reached(n+1,false);
    // aggiungo al contenitore (fifo o lifo) il nodo sorgente
    lista.put(sorgente);
    
    while (!lista.empty()) {
       I u=lista.get();
       reached[u]=true;
       
       for (const I& v: G.neighbours(u)) {
            if (!reached[v]) {
                lista.put(v);
                reached[v]=true;
                albero.add_edge(u,v);
            }
       }
    }
    return albero;
}

//helper: serve per eseguire il passo ricorsivo della DFS
template <typename I>
void recursive_dfs_passo(const unidirected_graph<I>& G, I u, vector<bool>& reached, unidirected_graph<I>& albero) {
    //segniamo il nodo u come visitato
    reached[u] = true;
    
    //esploriamo tutti i suoi vicini
    for (const I& v : G.neighbours(u)) {
        if (!reached[v]) {
            albero.add_edge(u, v); 
            recursive_dfs_passo(G, v, reached, albero);  //chiamata ricorsiva
        }
    }
}

//funzione principale:prende il grafo e la sorgente, inizializza i dati e fa partire la ricorsione
template <typename I>
unidirected_graph<I> recursive_dfs(const unidirected_graph<I>& G, I sorgente) {
    //inizializziamo l'albero
    unidirected_graph<I> albero;
    //troviamo il nodo con l'indice massimo
    I max_node = 0;
    for (const I& nodo : G.all_nodes()) {
        if (nodo > max_node) max_node = nodo;
    }    
    //vettore booleano per tenere traccia dei nodi visitati
    vector<bool> reached(max_node + 1, false);   
    //avviamo la ricorsione usando la funzione precedente
    recursive_dfs_passo(G, sorgente, reached, albero);

    return albero;
}

//modifico il mio metodo dijkstra rispetto la scorsa volta per poterlo usare in depina
const int INF = numeric_limits<int>::max();
template<typename I>
void dijkstra(int n,  const Eigen::MatrixXi&  pesi, I sorgente, vector<int>& distanze, vector<I>& pred) {
    distanze.assign(n,INF);
    pred.assign(n,-1);

    pred[sorgente]=sorgente;
    distanze[sorgente]=0;
    set<pair<int,I>> priority_queue;

    for(int i=0;i<n;i++) {
        priority_queue.insert({distanze[i],i});
    }

    while (!priority_queue.empty()) {
        auto [p, u] = *priority_queue.begin(); 
        priority_queue.erase(priority_queue.begin());
        
        if (p == INF) break;
        
        for (int v=0; v<n; v++) {            
            int peso_uv=pesi(u,v);
            if (peso_uv!=INF){
                if (distanze[u]+peso_uv< distanze[v]) {
                    priority_queue.erase({distanze[v],v});
                    distanze[v]= distanze[u]+peso_uv;
                    pred[v]=u;
                    priority_queue.insert({distanze[v],v});
                }
            }
        }
    }
}


