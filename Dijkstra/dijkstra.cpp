#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

// Algoritmo de Dijkstra para encontrar as menores distâncias de um vértice inicial para todos os outros vértices em um grafo ponderado
vector<int> dijkstra(vector<vector<pair<int, int>>> &grafo, int V, int vertice_inicial)
{
  vector<int> dist(V + 1, INF);
  dist[vertice_inicial] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_prioridade;

  fila_prioridade.push({0, vertice_inicial});

  while (!fila_prioridade.empty())
  {
    int u = fila_prioridade.top().second;
    fila_prioridade.pop();

    for (auto vizinho : grafo[u])
    {
      int v = vizinho.first;
      int peso = vizinho.second;

      if (dist[v] > dist[u] + peso)
      {
        dist[v] = dist[u] + peso;
        fila_prioridade.push({dist[v], v});
      }
    }
  }

  return dist;
}

int main(int argc, char *argv[])
{
  string input = "";
  string output = "";

  int V, E;
  int vertice_inicial = 1;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0)
    {
      cout << "Help:" << endl;
      cout << "-h: mostra o help" << endl;
      cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
      cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
      cout << "-i: vértice inicial" << endl;

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
    grafo[v].push_back({u, peso});
  }

  fin.close();

  vector<int> distancias = dijkstra(grafo, V, vertice_inicial);

  if (!(output == ""))
  {
    ofstream fout(output);
    if (!fout)
    {
      cerr << "Could not open output file: " << output << endl;
      return 1;
    }

    for (int i = 1; i <= V; i++)
    {
      if (distancias[i] != INF)
      {
        fout << i << ":" << distancias[i] << " ";
      }
      else
      {
        fout << i << ":" << -1 << " ";
      }
    }

    fout.close();
  }

  for (int i = 1; i <= V; i++)
  {
    if (distancias[i] != INF)
    {
      cout << i << ":" << distancias[i] << " ";
    }
    else
    {
      cout << i << ":" << -1 << " ";
    }
  }
  cout << endl;

  return 0;
}