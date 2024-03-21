#include <bits/stdc++.h>
using namespace std;

// Função DFS para preencher a pilha com a pós-ordem dos vértices
void dfs(int cont, vector<vector<int>> &grafo, vector<bool> &visitado, stack<int> &pilha)
{
    visitado[cont] = true;
    for (int vizinho : grafo[cont])
    {
        if (!visitado[vizinho])
        {
            dfs(vizinho, grafo, visitado, pilha);
        }
    }
    pilha.push(cont);
}

// Função DFS no grafo reverso para encontrar componentes fortemente conexos
void dfs_reverse(int cont, vector<vector<int>> &grafo_reverso, vector<bool> &visitado, vector<int> &component, int comp_num)
{
    visitado[cont] = true;
    component[cont] = comp_num;
    for (int vizinho : grafo_reverso[cont])
    {
        if (!visitado[vizinho])
        {
            dfs_reverse(vizinho, grafo_reverso, visitado, component, comp_num);
        }
    }
}

// Algoritmo de Kosaraju para encontrar componentes fortemente conexos
vector<vector<int>> kosaraju(int V, vector<vector<int>> &grafo)
{
    vector<vector<int>> grafo_reverso(V + 1);
    // Cria o grafo reverso
    for (int i = 1; i <= V; i++)
    {
        for (int vizinho : grafo[i])
        {
            grafo_reverso[vizinho].push_back(i);
        }
    }

    vector<bool> visitado(V + 1, false);
    stack<int> pilha;

    // Preenche a pilha pós-ordem dos vértices
    for (int i = 1; i <= V; i++)
    {
        if (!visitado[i])
        {
            dfs(i, grafo_reverso, visitado, pilha);
        }
    }

    fill(visitado.begin(), visitado.end(), false);
    vector<vector<int>> components;

    // Encontra os componentes fortemente conexos ate esvaziar a pilha
    while (!pilha.empty())
    {
        int cont = pilha.top();
        pilha.pop();
        if (!visitado[cont])
        {
            vector<int> component(V + 1, -1);
            dfs_reverse(cont, grafo, visitado, component, components.size());
            components.push_back(component);
        }
    }

    return components;
}

int main(int argc, char *argv[])
{
    string input = "";
    string output = "";

    int V, E;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;

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

    vector<vector<int>> grafo(V + 1);

    int u, v;

    for (int i = 0; i < E; i++)
    {
        fin >> u >> v;
        grafo[u].push_back(v);
    }

    fin.close();

    vector<vector<int>> components = kosaraju(V, grafo);

    if (!(output == ""))
    {
        ofstream fout(output);
        if (!fout)
        {
            cerr << "Could not open output file: " << output << endl;
            return 1;
        }

        for (int i = 0; i < static_cast<int>(components.size()); i++)
        {
            for (int j = 1; j <= V; ++j)
            {
                if (components[i][j] == i)
                {
                    fout << j << " ";
                }
            }
            fout << endl;
        }

        fout.close();
    }
    for (int i = 0; i < static_cast<int>(components.size()); i++)
    {
        for (int j = 1; j <= V; ++j)
        {
            if (components[i][j] == i)
            {
                cout << j << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
