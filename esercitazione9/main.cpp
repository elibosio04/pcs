#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "graph.hpp"
#include "contenitori.hpp"
#include "visita_grafi.hpp"
#include "DFS_De_Pina.hpp" 

using namespace std;

int main() {

    // Creo il grafo
    unidirected_graph<int> G;

    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G.add_edge(2, 3);
    G.add_edge(3, 4);
    G.add_edge(4, 5);
    G.add_edge(5, 0); 
    G.add_edge(0, 2); 
    G.add_edge(2, 5); 

    int num_nodi = G.all_nodes().size();
    int num_archi = G.all_edges().size();
    
    cout << "Numero di nodi nel grafo: " << num_nodi << endl;
    cout << "Numero di archi nel grafo: " << num_archi << endl;

    // Diamo dei pesi agli archi del grafo
    Eigen::MatrixXi pesi = Eigen::MatrixXi::Constant(num_nodi, num_nodi, INF);
    pesi(0, 1) = 5;  pesi(1, 0) = 5;
    pesi(1, 2) = 5;  pesi(2, 1) = 5;
    pesi(2, 3) = 6;  pesi(3, 2) = 6;
    pesi(3, 4) = 6;  pesi(4, 3) = 6;
    pesi(4, 5) = 5;  pesi(5, 4) = 5;
    pesi(5, 0) = 10; pesi(0, 5) = 10;
    pesi(0, 2) = 1;  pesi(2, 0) = 1;
    pesi(2, 5) = 1;  pesi(5, 2) = 1;

    //DFS CICLI 
    cout << "--- CICLI DFS ---" << endl;
    vector<vector<int>> cicli = cicli_dfs(G); 
    for (size_t i = 0; i < cicli.size(); i++) {  //stampo i nodi del ciclo
        cout << "Ciclo DFS " << i + 1 << ": ";
        for (size_t j = 0; j < cicli[i].size(); j++) {
            cout << cicli[i][j] << " ";
        }
        cout << endl;
    }

    //DE PINA
    cout << "\n--- CICLI DE PINA ---" << endl;
    vector<vector<bool>> cicli_pina= algoritmo_de_pina(G, pesi);
    for (size_t i = 0; i < cicli_pina.size(); i++) {
        cout << "Ciclo De Pina " << i + 1 << ": ";
        for (size_t j = 0; j < cicli_pina[i].size(); j++) {
            if (cicli_pina[i][j]) {
                cout << G.edge_at(j) << " ";  //stampo gli archi del ciclo
            }
        }
        cout << endl;
    }

    return 0;
}