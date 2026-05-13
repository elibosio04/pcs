#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include "edge.hpp"
#include <concepts>
using namespace std;

template<typename I> requires integral<I> 
class unidirected_graph{
    set<unidirected_edge<I>> archi;
    map<I, set<I>> lista_adj;

public:
   //costruttore di default
   unidirected_graph() {}

   //costruttore di copia
   unidirected_graph(const unidirected_graph& other){
    archi=other.archi;
    lista_adj=other.lista_adj;
   }

   //metodo neighbours()
   set<I> neighbours(const I& nodo) const{
    //cerco il nodo nella lista di adiacenza
    if (lista_adj.count(nodo)>0){
        return lista_adj.at(nodo);
    }
    return{}; //se non ha nodi vicini non restituisco niente
   }

   //metodo add_edge()
   //aggiunge un arco tra i due nodi u e v
   void add_edge(const I&u, const I&v){
    //creo il nuovo arco
    unidirected_edge<I> nuovo_arco(u,v);
    archi.insert(nuovo_arco);
    //aggiorno la lista di adiacenza
    lista_adj[u].insert(v);
    lista_adj[v].insert(u);
   }

   //metodo all_edges()
   set<unidirected_edge<I>> all_edges() const {
    return archi;
   }

   //metodo all_nodes()
   set<I> all_nodes() const{
    set<I> nodi;
    for (auto& [nodo, vicini]: lista_adj){
        nodi.insert(nodo);
    }
    return nodi;
   }

   //metodo edge_number()
   int edge_number(const unidirected_edge<I>& arco) const{
    int count=0;
    for (const auto& edge : archi) {
        if (edge==arco){
            return count; //ho trovato l'arco e restituisco la posizione
        }
        count++;
    }
    return -1; //uso -1 per segnalare che non ho trovato l'arco
   }

   //metodo edge_at()
   unidirected_edge<I> edge_at(const int& num) const{
   int count=0;
   for (const auto& edge : archi){
    if (count==num){
        return edge;
    }
    count++;
   }
   return unidirected_edge<I>(); //restituisco un arco vuoto se num>posizione ultimo arco
   }

   //operatore-() G-G'
   //creo un nuovo grafo con gli stessi nodi di G, ma solo gli archi che non compaiono in G'
   unidirected_graph<I> operator-(const unidirected_graph<I>& other) const{
    unidirected_graph<I> grafo_diff; //creo un grafo vuoto che sarà il risultato della differenza
    set<I> nodi=all_nodes(); //mi salvo i nodi di G
    for (const auto& u : nodi){
        set<I> vicini=neighbours(u); //mi salvo i vicini del nodo u
        for (const auto& v : vicini){
            unidirected_edge<I> arco(u,v);
            if (other.edge_number(arco)==-1){ //se non trovo l'arco in G'
                grafo_diff.add_edge(u,v);
            }
        }

    }
    return grafo_diff;
    }
};
