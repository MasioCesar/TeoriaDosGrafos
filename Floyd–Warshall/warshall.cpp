#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX

vector<vector<int>> warshall(int vertice_inicial, int V, vector<vector<int>> &matriz)
{
  vector<vector<int>> dist = matriz;

  for (int k = 1; k <= V; k++)
  {
    for (int i = 1; i <= V; i++)
    {
      for (int j = 1; j <= V; j++)
      {
        if (dist[i][k] != INF && dist[k][j] != INF && i != j)
        {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  if (vertice_inicial == 0)
  {
    for (int z = 1; z <= V; z++)
    {
      dist[z][z] = 0;
    }
  }
  else
  {
    dist[vertice_inicial][vertice_inicial] = 0;
  }

  return dist;
}

int main(int argc, char *argv[])
{
  string input = "";
  string output = "";
  int vertice_inicial = 0;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0)
    {
      cout << "Help:" << endl;
      cout << "-h: mostra o help" << endl;
      cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
      cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada"
           << endl;
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

  if (not fin)
  {
    cerr << "Could not open input file: " << input << endl;
    return 1;
  }

  int V, E;
  fin >> V >> E;

  int u, v, peso;
  vector<vector<int>> matriz(V + 1, vector<int>(V + 1, INF));

  for (int i = 0; i < E; i++)
  {
    fin >> u >> v >> peso;
    matriz[u][v] = peso;
    matriz[v][u] = peso;
  }

  vector<vector<int>> distancia = warshall(vertice_inicial, V, matriz);

  fin.close();

  if (!(output == ""))
  {
    ofstream fout(output);
    if (!fout)
    {
      cerr << "Could not open output file: " << output << endl;
      return 1;
    }
    if (vertice_inicial == 0)
    {
      for (int i = 1; i <= V; i++)
      {
        for (int j = 1; j <= V; j++)
        {
          fout << j << ":" << distancia[i][j] << " ";
        }
        fout << endl;
      }
    }
    else
    {
      for (int i = 1; i <= V; i++)
      {
        fout << i << ":" << distancia[vertice_inicial][i] << " ";
      }
      fout << endl;
    }
    fout << endl;
    fout.close();
  }

  if (vertice_inicial == 0)
  {
    for (int i = 1; i <= V; i++)
    {
      for (int j = 1; j <= V; j++)
      {
        cout << j << ":" << distancia[i][j] << " ";
      }
      cout << endl;
    }
  }
  else
  {
    for (int i = 1; i <= V; i++)
    {
      cout << i << ":" << distancia[vertice_inicial][i] << " ";
    }
    cout << endl;
  }

  return 0;
}
