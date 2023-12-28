#define MAX_NODES 100
#define INF 1e9

typedef struct
{
    int is_connect;
    int cost;
}graph_node_t;

int all_visited(int *visited, int n)
{
    int i = 0;
    for (i = 1; i <= n; i++)
    {
        if (visited[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){
    graph_node_t graph[MAX_NODES + 1][MAX_NODES + 1] = {0};
    int distance[MAX_NODES + 1] = {0};
    int visited[MAX_NODES + 1] = {0};
    int i = 0, j = 0;
    int has_changed = 1;
    int idx_min_distance = 0;
    int min_distance = INF;
    int tmp_dis = 0;
    int idx_max_distance = 0;
    int max_distance = 0;
    for (i = 0; i < timesSize; i++)
    {
        graph[times[i][0]][times[i][1]].is_connect = 1;
        graph[times[i][0]][times[i][1]].cost = times[i][2];
    }
    for (i = 1; i <= n; i++)
    {
        if (i == k)
        {
            continue;
        }
        distance[i] = graph[k][i].is_connect ? graph[k][i].cost : INF;
    }
    visited[k] = 1;
    distance[k] = 0;
    while (!all_visited(visited, n) || has_changed)
    {
        has_changed = 0;
        min_distance = INF;
        for (i = 1; i <= n; i++)
        {
            if (visited[i])
            {
                continue;
            }
            if (distance[i] < min_distance)
            {
                idx_min_distance = i;
                min_distance = distance[i];
            }
        }
        if (min_distance == INF)
        {
            break;
        }
        visited[idx_min_distance] = 1;
        for (i = 1; i <= n; i++)
        {
            if (visited[i] || !graph[idx_min_distance][i].is_connect)
            {
                continue;
            }
            tmp_dis = distance[idx_min_distance] + graph[idx_min_distance][i].cost;
            if (tmp_dis < distance[i])
            {
                distance[i] = tmp_dis;
                has_changed = 1;
            }
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (distance[i] > max_distance)
        {
            idx_max_distance = i;
            max_distance = distance[i];
        }
    }
    if (max_distance == INF)
    {
        return -1;
    }
    else
    {
        return max_distance;
    }
}