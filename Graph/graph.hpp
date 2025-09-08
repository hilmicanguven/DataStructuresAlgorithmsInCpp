/*

Graph

birbiirlerine bağlı farklı datalardan oluşan veri yapısıdır.
(Node/Vertex  --- Edge/Conneciton --- Node/Vertex)
Bir node'dan birden fazla node'a bağlı olabilir, conneciton sayısında bir limit bulunmaz.
her edge farklı bir değere (Cost) sahip olabilir.
ayrıca bu edge'ler bi-directional yani çift yönlü de olabilir.

Graph'i represente etmek için iki yöntem vardır

- Adjacency Matrix
    Matrix formunda, 0(connection yok) ve 1 (connection var) değerlerden oluşur.
    eğer edge'lerin bir weight'i varsa 0 ve weight olarak değerler alır

     This 2D matrix represents the connections between nodes in a graph.
    Let 'graph[i][j]' be the cell at row i and column j.

    - If graph[i][j] == 1, there is an edge from node i to node j.
    - If graph[i][j] == 0, there is no edge between node i and node j.

    For undirected graphs:
        graph[i][j] == graph[j][i]

    For weighted graphs:
        graph[i][j] = weight of edge from i to j

    Example:
        Nodes: 0, 1, 2
        Edges: (0 → 1), (1 → 2)

        Adjacency Matrix:
            0 1 2
        0 [0 1 0]
        1 [0 0 1]
        2 [0 0 0]
    
- Adjacency List

    Example (Directed Weighted Graph):
        Nodes: 0, 1, 2, 3
        Edges:
            0 → 1 (weight 5)
            0 → 2 (weight 3)
            1 → 2 (weight 2)
            2 → 3 (weight 4)
            3 → 1 (weight 1)
            3 → 3 (self-loop, weight 7)

        Adjacency List:
            0: [(1, 5), (2, 3)]
            1: [(2, 2)]
            2: [(3, 4)]
            3: [(1, 1), (3, 7)]

Burada key-value kullanımını unordered-map ile yapabiliriz.
conneciton'ları ise Unordered Set : un-ordered map ile benzerdir. ancak bir "key" yalnızca bir tane olur (no duplicates)
ve "value" ya sahip değildir.


- Big O
    Space Complexity
        Adj Matrix -> O(V^2)    Adj List -> (O(V)+O(E))
    Time Complexity
        Add Vertex
            Adj Matrix -> O(V^2)    Adj List -> O(1)
        Add Edge
            Adj Matrix -> O(1)    Adj List -> O(1)
        Remove Edge
            Adj Matrix -> O(1)    Adj List -> O(1)
        Remove Vertex
            Adj Matrix -> O(V^2)    Adj List -> O(V)

    To sum op, Adjacency List > better than > Adjacency List    in general

*/


#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Graph
{
    private:
        /*
        {
            "A" : [B, ... ,Z]
        }
        */
        unordered_map<string, unordered_set<string>> adjList;

    public:
        void printGraph() 
        {
            unordered_map<string, unordered_set<string>>::iterator kvPair = adjList.begin();
            while (kvPair != adjList.end()) {
                cout  << kvPair->first << ": [ ";  // this prints out the vertex
                unordered_set<string>::iterator edge = kvPair->second.begin();
                while (edge != kvPair->second.end()) {
                    cout  << edge->data() << " ";  // this prints out edges
                    edge++;
                }
                cout << "]" << endl;
                kvPair++;
            }
        }

        bool addVertex(string vertex)
        {
            if(adjList.count(vertex) == 0)
            {
                adjList[vertex].insert({});
                // adjList[vertex];
                return true;
            }
            return false;
        }

        bool addEdge(string vertex1, string vertex2)
        {
            // if both vertexes exist!!!
            if(adjList.count(vertex1) != 0 && adjList.count(vertex2) != 0)
            {
                // adjList.at(vertex1)-> return unordered set
                adjList.at(vertex1).insert(vertex2);
                adjList.at(vertex2).insert(vertex1);

                return true;
            }
            return false;
        }

        bool removeEdge(string vertex1, string vertex2)
        {
            // if both vertexes exist!!!
            if(adjList.count(vertex1) != 0 && adjList.count(vertex2) != 0)
            {
                adjList.at(vertex1).erase(vertex2);
                adjList.at(vertex2).erase(vertex1);

                return true;
            }
            return false;
        }

        /**
         * @brief if graph is bi-directional, then find removedVertex edges using its unordered set
         * and iterate them and remove removedVertex from their edges
         * 
         * Example
         * 
         * A : B, C, D
         * B : A, D
         * C : A, D
         * D : A, B, C
         */
        bool removeVertex(string vertex)
        {
            if(adjList.count(vertex) != 0)
            {
                // to remove connection of D's, lets iterate A,B and C since graph is bidirectional
                // and remove D from them.
                // at the end, remove D itself
                for(auto e : adjList.at(vertex))
                {
                    adjList.at(e).erase(vertex);
                }
                
                adjList.erase(vertex);
                
                return true;
            }

            return false;
        }
};




int graph_main()
{

    Graph* my_graph = new Graph();
    my_graph->addVertex("H");
    my_graph->addVertex("I");
    my_graph->addVertex("L");

    my_graph->addEdge("H","I");
    my_graph->addEdge("H","L");
    my_graph->printGraph();

    cout << "----AFTER DELETING VERTEX 'L'---- \n";
    my_graph->removeVertex("L");

    my_graph->printGraph();
    return 0;
}