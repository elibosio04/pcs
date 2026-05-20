#include "graph.hpp"
#include "visita_grafi.hpp" 
#include "contenitori.hpp"
#include <iostream>
using namespace std;

int main() {
    unidirected_graph<int> G;
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(2, 4);
    G.add_edge(3, 5);
    G.add_edge(2, 5);
    G.add_edge(5, 6);

    //visita DFS 
    lifo<int> s;
    auto dfsG = graph_visit(G, 1, s); 

    //visita BFS 
    fifo<int> q;
    auto bfsG = graph_visit(G, 1, q);

    //visita DFS ricorsiva
    auto dfsRicorsivaG = recursive_dfs(G, 1);

    //aggiungiamo i pesi al grafo per poter testare Dijkstra
    int n = G.all_nodes().size();
    Eigen::MatrixXi pesi = Eigen::MatrixXi::Zero(n+1, n+1);
    pesi(1, 2) = 1; pesi(2, 1) = 1;
    pesi(1, 3) = 4; pesi(3, 1) = 4;
    pesi(2, 4) = 7; pesi(4, 2) = 7;
    pesi(3, 5) = 2; pesi(5, 3) = 2;
    pesi(2, 5) = 1; pesi(5, 2) = 1;
    pesi(5, 6) = 3; pesi(6, 5) = 3;

    //visita Dijkstra
    vector<int> distanze;
    vector<int> predecessori;
    dijkstra(G, pesi, 1, distanze, predecessori);

    //stampa
    cout<< "Albero dfs iterativo:" <<"\n";
    for (const auto& arco: dfsG.all_edges()) {
        cout << arco << "\n";
    }
    cout<< "Albero bfs:" <<"\n";
    for (const auto& arco: bfsG.all_edges()) {
        cout << arco << "\n";
    }
    cout<< "Albero dfs ricorsiva:" <<"\n";
    for (const auto& arco: dfsRicorsivaG.all_edges()) {
        cout << arco << "\n";
    }
    cout<< "Albero dijkstra:" <<"\n";
     for (int i = 1; i <= n; ++i) {
        cout << "Nodo " << i << " Distanza minima da 1: "<< distanze[i]<< " predecessore: " << predecessori[i]<< "\n";    
    }
    return 0;
}