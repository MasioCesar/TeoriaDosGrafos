#include <bits/stdc++.h>
using namespace std;

// Função para encontrar o pai de um vértice
int find(vector<int> &pai, int u)
{
    if (pai[u] != u)
    {
        pai[u] = find(pai, pai[u]);
    }
    return pai[u];
}

// Função para unir dois conjuntos disjuntos
void unir(vector<int> &pai, vector<int> &rank, int u, int v)
{
    u = find(pai, u);
    v = find(pai, v);

    if (rank[u] < rank[v])
    {
        pai[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        pai[v] = u;
    }
    else
    {
        pai[v] = u;
        rank[u]++;
    }
}

// Algoritmo de Kruskal para encontrar a árvore geradora mínima
vector<pair<int, int>> kruskal(vector<vector<pair<int, int>>> &grafo, int V, int &menor_caminho)
{
    vector<pair<int, pair<int, int>>> arestas;
    vector<pair<int, int>> resultado;

    for (int u = 0; u < V; u++)
    {
        for (auto &vizinho : grafo[u])
        {
            int v = vizinho.first;
            int peso = vizinho.second;
            arestas.push_back({peso, {u, v}});
        }
    }

    sort(arestas.begin(), arestas.end());

    vector<int> pai(V + 1);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
    {
        pai[i] = i;
    }

    for (auto &aresta : arestas)
    {
        int peso = aresta.first;
        int u = aresta.second.first;
        int v = aresta.second.second;

        if (find(pai, u) != find(pai, v))
        {
            resultado.push_back({u, v});
            menor_caminho += peso;
            unir(pai, rank, u, v);
        }
    }

    return resultado;
}

int main(int argc, char *argv[])
{
    string input = "";
    string output = "";

    int V, E;
    bool mostra_resultado = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução" << endl;

            return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            mostra_resultado = true;
        }
    }

    if (input == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input);

    if (!fin)
    {
        cerr << "Could not open input file: " << input << endl;
        return 1;
    }

    fin >> V >> E;

    vector<vector<pair<int, int>>> grafo(V + 1);

    int u, v, peso;

    for (int i = 0; i < E; i++)
    {
        fin >> u >> v >> peso;
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso}); // Para grafos não direcionados
    }

    fin.close();

    int menor_caminho = 0;
    vector<pair<int, int>> resultado = kruskal(grafo, V, menor_caminho);

    int tamanho = resultado.size();

    if (mostra_resultado)
    {
        for (int i = 0; i < tamanho; i++)
        {
            cout << "(" << resultado[i].first << "," << resultado[i].second << ")" << endl;
        }
    }
    else
    {
        cout << menor_caminho << endl;
    }

    return 0;
}