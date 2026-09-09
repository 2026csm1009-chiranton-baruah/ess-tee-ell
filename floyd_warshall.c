#include <stdio.h>

#define INF 99999

void floydWarshall(int graph[][100], int V)
{
    int dist[100][100];

    // Initialize distance matrix
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative-weight cycle
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
        {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    // Print result
    printf("All-Pairs Shortest Path Matrix:\n");

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int V;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int graph[100][100];

    printf("Enter adjacency matrix:\n");
    printf("Use %d for no edge.\n", INF);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, V);

    return 0;
}
