#define MAX_NODES 100
#define INF 1e9

typedef struct
{
    int is_connect;
    int cost;
}graph_node_t;

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    graph_node_t graph[MAX_NODES + 1][MAX_NODES + 1] = {0};
    int distance[MAX_NODES + 1] = {0};
    int i = 0, j = 0;
    int has_changed = 1;
    for (i = 1; i <= timesSize; i++)
    {
        graph[times[0]][times[1]].is_connect = 1;
        graph[times[0]][times[1]].cost = times[2];
    }
    for (i = 1; i <= timesSize; i++)
    {
        if (i == k)
        {
            continue;
        }
        distance[i] = graph[k][i].is_connect ? graph[k][i].cost : INF;
    }
    while (has_changed)
    {
        has_changed = 0;
    }
}