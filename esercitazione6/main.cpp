#include <iostream>
#include "edge.hpp"
#include "graph.hpp"

int main(void){
    cout<< "--Test sulla classe degli archi--" << "\n";
    unidirected_edge<int> arco1(10, 5);  //Verifico mi stampi l'arco con i nodi nell'ordine giusto
    unidirected_edge<int> arco2(3, 1);
    unidirected_edge<int> arco3 (5,10);
    cout << boolalpha; // Aggiungo questo in modo che stampi True/Falso al posto 1/0
    cout << "Verifica stampa arco: " << arco1 << "\n";
    cout << "L'arco (5-10) è minore dell'arco (1-3)? "<< (arco1<arco2) << "\n";
    cout << "L'arco (10-5) è uguale all'arco (5-10)? "<< (arco1==arco3) << "\n\n";
    cout << "--Test sulla classe dei grafi--" << "\n";
    unidirected_graph<int> G1;
    G1.add_edge(1, 5);
    G1.add_edge(6, 3);
    G1.add_edge(3, 4);
    G1.add_edge(4, 5);
    cout<< "Grafo G1:"<< "\n";
    for (const auto& arco : G1.all_edges()) {
        cout << "Arco: " << arco << endl;
    }
    unidirected_graph<int> G2;
    G2.add_edge(3, 4);
    G2.add_edge(4, 5);
    cout<< "\nGrafo G2:"<< "\n";
    for (const auto& arco : G2.all_edges()) {
        cout << "Arco: " << arco << endl;
    }
    
    cout<< "\nVerifica sottrazioni G1-G2:" << "\n";
    cout<< "Grafo differenza:"<< "\n";
    unidirected_graph<int> G_diff = G1 - G2;
    // Verifico che rimangono solo (1-5) e (3-6)
    for (const auto& arco : G_diff.all_edges()) {
        cout << "Arco: " << arco << endl;
    }

    cout<< "\nVerifica vicini di 3 in G1:" << "\n";
    set<int> vicini = G1.neighbours(3);
    cout << "I vicini di 3 sono: ";
    for (int n : vicini) {
        cout << n << " ";   //Verifico che sono 4 e 6
    }

    cout<< "\n\nAggiungiamo un arco a G1:"<<"\n";
    G1.add_edge(5, 1); //Verifico che se aggiungo un arco già presente, non cambia nulla nel mio grafo
    G1.add_edge(8, 6);
    cout<< "Grafo G1:"<< "\n";
    for (const auto& arco : G1.all_edges()) {
        cout << "Arco: " << arco << endl;
    }

    set<unidirected_edge<int>> set_archi = G1.all_edges();
    cout << "\nNumero totale di archi in G1: " << set_archi.size() << "\n"; //Verifico mi dia 5

    set<int> set_nodi = G1.all_nodes();
    cout << "Numero totale di nodi in G1: " << set_nodi.size() << "\n"; //Verifico mi dia 6

    cout << "\nVerifica posizione archi:"<< "\n";
    unidirected_edge<int> arco_ricerca(6, 3);
    int pos = G1.edge_number(arco_ricerca);
    cout << "L'arco (6-3) si trova alla posizione: " << pos << "\n";
    cout << "\nVerifico che con edge_at mi restituisca lo stesso arco: \n";
    cout << "L'arco alla posizione " << pos << " e': " << G1.edge_at(pos) << "\n";
}