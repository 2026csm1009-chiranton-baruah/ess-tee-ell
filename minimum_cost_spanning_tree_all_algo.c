#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ============================================================
   MINIMUM COST SPANNING TREE
   Algorithms:
       1. Kruskal
       2. Prim (Adjacency Matrix)
       3. Prim (Min Heap + Adjacency List)
       4. Boruvka
       5. Reverse Delete
   ============================================================ */


/* ============================================================
   EDGE REPRESENTATION
   ============================================================ */

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int V, E;
    Edge *edges;
} Graph;


/* ============================================================
   UNION-FIND / DISJOINT SET
   ============================================================ */

typedef struct {
    int *parent;
    int *rank;
    int n;
} DSU;

DSU *createDSU(int n)
{
    DSU *dsu = (DSU *)malloc(sizeof(DSU));

    dsu->n = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
        dsu->parent[i] = i;

    return dsu;
}

int find(DSU *dsu, int x)
{
    if (dsu->parent[x] != x)
        dsu->parent[x] = find(dsu, dsu->parent[x]);

    return dsu->parent[x];
}

void unionSets(DSU *dsu, int a, int b)
{
    a = find(dsu, a);
    b = find(dsu, b);

    if (a == b)
        return;

    if (dsu->rank[a] < dsu->rank[b])
        dsu->parent[a] = b;

    else if (dsu->rank[a] > dsu->rank[b])
        dsu->parent[b] = a;

    else {
        dsu->parent[b] = a;
        dsu->rank[a]++;
    }
}

void freeDSU(DSU *dsu)
{
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}


/* ============================================================
   UTILITY: SORT EDGES BY WEIGHT
   ============================================================ */

int compareEdges(const void *a, const void *b)
{
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;

    return e1->w - e2->w;
}


/* ============================================================
   PRINT MST
   ============================================================ */

void printMST(Edge *mst, int count, int cost)
{
    printf("\nEdges in MST:\n");

    for (int i = 0; i < count; i++)
        printf("%d -- %d   weight = %d\n",
               mst[i].u, mst[i].v, mst[i].w);

    printf("Minimum Cost = %d\n", cost);
}


/* ============================================================
   1. KRUSKAL'S ALGORITHM
   ============================================================ */

void kruskal(Graph *g)
{
    printf("\n========== KRUSKAL ==========\n");

    Edge *sorted = (Edge *)malloc(g->E * sizeof(Edge));

    for (int i = 0; i < g->E; i++)
        sorted[i] = g->edges[i];

    qsort(sorted, g->E, sizeof(Edge), compareEdges);

    Edge *mst = (Edge *)malloc((g->V - 1) * sizeof(Edge));

    DSU *dsu = createDSU(g->V);

    int count = 0;
    int cost = 0;

    for (int i = 0; i < g->E && count < g->V - 1; i++) {

        int u = sorted[i].u;
        int v = sorted[i].v;

        if (find(dsu, u) != find(dsu, v)) {

            mst[count++] = sorted[i];
            cost += sorted[i].w;

            unionSets(dsu, u, v);
        }
    }

    if (count != g->V - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printMST(mst, count, cost);

    free(mst);
    free(sorted);
    freeDSU(dsu);
}


/* ============================================================
   2. PRIM'S ALGORITHM
      Using Adjacency Matrix
   ============================================================ */

void primMatrix(Graph *g)
{
    printf("\n========== PRIM (MATRIX) ==========\n");

    int V = g->V;

    int **matrix = (int **)malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++) {
        matrix[i] = (int *)calloc(V, sizeof(int));
    }

    for (int i = 0; i < g->E; i++) {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int w = g->edges[i].w;

        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    int *key = (int *)malloc(V * sizeof(int));
    int *parent = (int *)malloc(V * sizeof(int));
    int *visited = (int *)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[0] = 0;

    int cost = 0;

    for (int count = 0; count < V; count++) {

        int u = -1;
        int min = INT_MAX;

        /* Find minimum key vertex */
        for (int v = 0; v < V; v++) {

            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        if (parent[u] != -1)
            cost += matrix[parent[u]][u];

        /* Update adjacent vertices */
        for (int v = 0; v < V; v++) {

            if (matrix[u][v] != 0 &&
                !visited[v] &&
                matrix[u][v] < key[v]) {

                key[v] = matrix[u][v];
                parent[v] = u;
            }
        }
    }

    Edge *mst = (Edge *)malloc((V - 1) * sizeof(Edge));
    int count = 0;

    for (int v = 1; v < V; v++) {

        if (parent[v] != -1) {

            mst[count].u = parent[v];
            mst[count].v = v;
            mst[count].w = matrix[parent[v]][v];

            count++;
        }
    }

    if (count != V - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printMST(mst, count, cost);

    free(mst);
    free(key);
    free(parent);
    free(visited);

    for (int i = 0; i < V; i++)
        free(matrix[i]);

    free(matrix);
}


/* ============================================================
   MIN HEAP FOR PRIM
   ============================================================ */

typedef struct {
    int vertex;
    int key;
} HeapNode;

typedef struct {
    int size;
    int capacity;
    int *position;
    HeapNode *array;
} MinHeap;

void swapHeapNode(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));

    heap->size = 0;
    heap->capacity = capacity;

    heap->position =
        (int *)malloc(capacity * sizeof(int));

    heap->array =
        (HeapNode *)malloc(capacity * sizeof(HeapNode));

    return heap;
}

void minHeapify(MinHeap *heap, int index)
{
    int smallest = index;

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size &&
        heap->array[left].key <
        heap->array[smallest].key)

        smallest = left;

    if (right < heap->size &&
        heap->array[right].key <
        heap->array[smallest].key)

        smallest = right;

    if (smallest != index) {

        HeapNode smallestNode = heap->array[smallest];
        HeapNode indexNode = heap->array[index];

        heap->position[smallestNode.vertex] = index;
        heap->position[indexNode.vertex] = smallest;

        swapHeapNode(
            &heap->array[smallest],
            &heap->array[index]
        );

        minHeapify(heap, smallest);
    }
}

HeapNode extractMin(MinHeap *heap)
{
    HeapNode root = heap->array[0];

    HeapNode lastNode =
        heap->array[heap->size - 1];

    heap->array[0] = lastNode;

    heap->position[root.vertex] = heap->size - 1;
    heap->position[lastNode.vertex] = 0;

    heap->size--;

    minHeapify(heap, 0);

    return root;
}

void decreaseKey(MinHeap *heap, int vertex, int key)
{
    int i = heap->position[vertex];

    heap->array[i].key = key;

    while (i &&
           heap->array[i].key <
           heap->array[(i - 1) / 2].key) {

        heap->position[
            heap->array[i].vertex
        ] = (i - 1) / 2;

        heap->position[
            heap->array[(i - 1) / 2].vertex
        ] = i;

        swapHeapNode(
            &heap->array[i],
            &heap->array[(i - 1) / 2]
        );

        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *heap, int vertex)
{
    return heap->position[vertex] < heap->size;
}


/* ============================================================
   3. PRIM'S ALGORITHM
      Using Min Heap
   ============================================================ */

void primHeap(Graph *g)
{
    printf("\n========== PRIM (MIN HEAP) ==========\n");

    int V = g->V;

    /*
       Build adjacency matrix for simplicity.
       The heap handles the priority queue.
    */

    int **matrix = (int **)malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
        matrix[i] = (int *)calloc(V, sizeof(int));

    for (int i = 0; i < g->E; i++) {

        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int w = g->edges[i].w;

        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    int *parent = (int *)malloc(V * sizeof(int));
    int *key = (int *)malloc(V * sizeof(int));

    MinHeap *heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {

        parent[v] = -1;
        key[v] = INT_MAX;

        heap->array[v].vertex = v;
        heap->array[v].key = INT_MAX;

        heap->position[v] = v;
    }

    heap->size = V;

    key[0] = 0;
    heap->array[0].key = 0;

    int cost = 0;

    while (heap->size > 0) {

        HeapNode minNode = extractMin(heap);

        int u = minNode.vertex;

        if (parent[u] != -1)
            cost += key[u];

        for (int v = 0; v < V; v++) {

            if (matrix[u][v] != 0 &&
                isInMinHeap(heap, v) &&
                matrix[u][v] < key[v]) {

                key[v] = matrix[u][v];
                parent[v] = u;

                decreaseKey(heap, v, key[v]);
            }
        }
    }

    Edge *mst = (Edge *)malloc((V - 1) * sizeof(Edge));

    int count = 0;

    for (int v = 1; v < V; v++) {

        if (parent[v] != -1) {

            mst[count].u = parent[v];
            mst[count].v = v;
            mst[count].w = key[v];

            count++;
        }
    }

    if (count != V - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printMST(mst, count, cost);

    free(mst);
    free(parent);
    free(key);

    free(heap->position);
    free(heap->array);
    free(heap);

    for (int i = 0; i < V; i++)
        free(matrix[i]);

    free(matrix);
}


/* ============================================================
   4. BORUVKA'S ALGORITHM
   ============================================================ */

void boruvka(Graph *g)
{
    printf("\n========== BORUVKA ==========\n");

    int V = g->V;

    DSU *dsu = createDSU(V);

    Edge *mst = (Edge *)malloc((V - 1) * sizeof(Edge));

    int components = V;
    int count = 0;
    int cost = 0;

    while (components > 1) {

        int *cheapest =
            (int *)malloc(V * sizeof(int));

        for (int i = 0; i < V; i++)
            cheapest[i] = -1;

        /* Find cheapest outgoing edge
           for every component */
        for (int i = 0; i < g->E; i++) {

            int u = g->edges[i].u;
            int v = g->edges[i].v;

            int setU = find(dsu, u);
            int setV = find(dsu, v);

            if (setU == setV)
                continue;

            if (cheapest[setU] == -1 ||
                g->edges[i].w <
                g->edges[cheapest[setU]].w)

                cheapest[setU] = i;

            if (cheapest[setV] == -1 ||
                g->edges[i].w <
                g->edges[cheapest[setV]].w)

                cheapest[setV] = i;
        }

        /* Add cheapest edges */
        for (int i = 0; i < V; i++) {

            if (cheapest[i] == -1)
                continue;

            Edge e = g->edges[cheapest[i]];

            int setU = find(dsu, e.u);
            int setV = find(dsu, e.v);

            if (setU == setV)
                continue;

            mst[count++] = e;
            cost += e.w;

            unionSets(dsu, setU, setV);

            components--;
        }

        free(cheapest);

        /* Disconnected graph */
        if (count == 0 && components > 1)
            break;
    }

    if (count != V - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printMST(mst, count, cost);

    free(mst);
    freeDSU(dsu);
}


/* ============================================================
   CHECK IF GRAPH IS CONNECTED
   After temporarily deleting an edge
   ============================================================ */

void dfs(int u, Graph *g, int *visited,
         int skipEdge)
{
    visited[u] = 1;

    for (int i = 0; i < g->E; i++) {

        if (i == skipEdge)
            continue;

        int a = g->edges[i].u;
        int b = g->edges[i].v;

        if (a == u && !visited[b])
            dfs(b, g, visited, skipEdge);

        if (b == u && !visited[a])
            dfs(a, g, visited, skipEdge);
    }
}

int isConnected(Graph *g, int skipEdge)
{
    int *visited =
        (int *)calloc(g->V, sizeof(int));

    dfs(0, g, visited, skipEdge);

    int connected = 1;

    for (int i = 0; i < g->V; i++) {

        if (!visited[i]) {
            connected = 0;
            break;
        }
    }

    free(visited);

    return connected;
}


/* ============================================================
   5. REVERSE-DELETE ALGORITHM
   ============================================================ */

void reverseDelete(Graph *g)
{
    printf("\n========== REVERSE DELETE ==========\n");

    int E = g->E;

    Edge *edges =
        (Edge *)malloc(E * sizeof(Edge));

    for (int i = 0; i < E; i++)
        edges[i] = g->edges[i];

    /*
       Sort in descending order.
    */

    for (int i = 0; i < E - 1; i++) {

        for (int j = i + 1; j < E; j++) {

            if (edges[i].w < edges[j].w) {

                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    /*
       active[i] = 1 means edge is currently present.
       We implement this by creating a temporary graph
       whenever an edge is considered for deletion.
    */

    int *active = (int *)malloc(E * sizeof(int));

    for (int i = 0; i < E; i++)
        active[i] = 1;

    for (int i = 0; i < E; i++) {

        /*
           Find original edge index corresponding
           to this edge.
        */

        int original = -1;

        for (int j = 0; j < E; j++) {

            if (active[j] &&
                g->edges[j].u == edges[i].u &&
                g->edges[j].v == edges[i].v &&
                g->edges[j].w == edges[i].w) {

                original = j;
                break;
            }
        }

        if (original == -1)
            continue;

        active[original] = 0;

        /*
           Build temporary graph.
        */

        Graph temp;

        temp.V = g->V;
        temp.E = 0;

        temp.edges =
            (Edge *)malloc(E * sizeof(Edge));

        for (int j = 0; j < E; j++) {

            if (active[j])
                temp.edges[temp.E++] = g->edges[j];
        }

        /*
           If removing the edge disconnects the graph,
           put it back.
        */

        if (!isConnected(&temp))
            active[original] = 1;

        free(temp.edges);
    }

    Edge *mst =
        (Edge *)malloc((g->V - 1) * sizeof(Edge));

    int count = 0;
    int cost = 0;

    for (int i = 0; i < E; i++) {

        if (active[i]) {

            mst[count++] = g->edges[i];
            cost += g->edges[i].w;
        }
    }

    if (count != g->V - 1)
        printf("Graph is disconnected. MST does not exist.\n");
    else
        printMST(mst, count, cost);

    free(mst);
    free(active);
    free(edges);
}


/* ============================================================
   MAIN
   ============================================================ */

int main()
{
    Graph g;

    printf("Enter number of vertices: ");
    scanf("%d", &g.V);

    printf("Enter number of edges: ");
    scanf("%d", &g.E);

    g.edges =
        (Edge *)malloc(g.E * sizeof(Edge));

    printf("\nEnter edges as:\n");
    printf("u v weight\n\n");

    for (int i = 0; i < g.E; i++) {

        scanf("%d %d %d",
              &g.edges[i].u,
              &g.edges[i].v,
              &g.edges[i].w);
    }

    /*
       Vertices are numbered:
       0, 1, 2, ..., V-1
    */

    kruskal(&g);

    primMatrix(&g);

    primHeap(&g);

    boruvka(&g);

    reverseDelete(&g);

    free(g.edges);

    return 0;
}
