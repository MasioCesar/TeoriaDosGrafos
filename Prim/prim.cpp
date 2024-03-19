#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

vector<pair<int, int>> prim(vector<vector<pair<int, int>>> &grafo, int V, int vertice_inicial, int &soma)
{
    vector<int> menor_caminho(V + 1, INF);
    vector<int> pai(V + 1, -1);
    vector<bool> visitado(V + 1, false);
    vector<pair<int, int>> resultado;

    menor_caminho[vertice_inicial] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_prioridade;

    fila_prioridade.push({0, vertice_inicial});

    while (!fila_prioridade.empty())
    {
        int u = fila_prioridade.top().second;
        fila_prioridade.pop();
        visitado[u] = true;

        for (auto vizinho : grafo[u])
        {
            int v = vizinho.first;
            int peso = vizinho.second;

            if (!visitado[v] && menor_caminho[v] > peso)
            {
                menor_caminho[v] = peso;
                pai[v] = u;
                fila_prioridade.push({menor_caminho[v], v});
            }
        }
    }

    for (int i = 2; i <= V; i++)
    {
        resultado.push_back({i, pai[i]});
        soma += menor_caminho[i];
    }

    return resultado;
}

int main(int argc, char *argv[])
{
    string input = "";
    string output = "";

    int V, E, vertice_inicial = 1, soma = 0;
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
            cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;

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
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            vertice_inicial = atoi(argv[++i]);
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

    vector<pair<int, int>> resultado = prim(grafo, V, vertice_inicial, soma);

    if (!(output == ""))
    {
        ofstream fout(output);
        if (!fout)
        {
            cerr << "Could not open output file: " << output << endl;
            return 1;
        }
        if (mostra_resultado)
        {
            for (auto result : resultado)
                fout << "(" << result.second << "," << result.first << ") ";
        }
        else
        {
            fout << soma << endl;
        }
        fout.close();
    }

    if (mostra_resultado)
    {
        for (auto result : resultado)
            cout << "(" << result.second << "," << result.first << ") ";
    }
    else
    {
        cout << soma << endl;
    }

    return 0;
}