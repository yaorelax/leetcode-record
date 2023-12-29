#define MAX_N 100000

typedef struct
{
    long long fuel;
    int num_people;
}data_t;

typedef struct node_t
{
    int data;
    struct node_t *next;
}node_t;

void append(node_t *map[MAX_N], int id, int data)
{
    node_t *tmp = NULL;
    if (map[id] == NULL)
    {
        map[id] = (node_t*)malloc(sizeof(node_t));
    }
    else
    {
        tmp = map[id];
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = (node_t*)malloc(sizeof(node_t));
        tmp->next->data = data;
        tmp->next->next = NULL;
    }
}

int exist(node_t *map[MAX_N], int id, int data)
{
    node_t *tmp = NULL;
    if (map[id] == NULL)
    {
        return 0;
    }
    else
    {
        tmp = map[id];
        while (tmp != NULL)
        {
            if (tmp->data == data)
            {
                return 1;
            }
            tmp = tmp->next;
        }
    }
    return 0;
}

data_t get_fuel(node_t *map[MAX_N], int n, int is_visited[MAX_N], int id, int seats)
{
    int i = 0;
    data_t res = {0};
    data_t data = {0};
    for (i = 0; i < n; i++)
    {
        if (i == id || is_visited[i] || !exist(map, id, i))
        {
            continue;
        }
        is_visited[i] = 1;
        data = get_fuel(map, n, is_visited, i, seats);
        res.num_people += data.num_people;
        res.fuel += data.fuel + (data.num_people - 1) / seats + 1;
    }
    res.num_people += 1;
    return res;
}

long long minimumFuelCost(int** roads, int roadsSize, int* roadsColSize, int seats) {
    node_t *map[MAX_N] = {0};
    int is_visited[MAX_N] = {0};
    int i = 0;
    data_t data = {0};
    for (i = 0; i < roadsSize; i++)
    {
        append(map, roads[i][0], roads[i][1]);
        append(map, roads[i][1], roads[i][0]);
    }
    data = get_fuel(map, *roadsColSize, is_visited, 0, seats);
    return data.fuel;
}