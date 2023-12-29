#define MAX_STATE_NUM 65535
#define MAX_GRID_SIZE 30
#define GRID_WALL '#'
#define GRID_START_POINT '@'
#define GRID_SPACE '.'
#define GRID_KEY_1 'a'
#define GRID_KEY_2 'b'
#define GRID_KEY_3 'c'
#define GRID_KEY_4 'd'
#define GRID_KEY_5 'e'
#define GRID_KEY_6 'f'
#define GRID_LOCK_1 'A'
#define GRID_LOCK_2 'B'
#define GRID_LOCK_3 'C'
#define GRID_LOCK_4 'D'
#define GRID_LOCK_5 'E'
#define GRID_LOCK_6 'F'
#define UP  0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct
{
    unsigned char row : 5;
    unsigned char has_key_1 : 1;
    unsigned char has_key_2 : 1;
    unsigned char has_key_3 : 1;
    unsigned char col : 5;
    unsigned char has_key_4 : 1;
    unsigned char has_key_5 : 1;
    unsigned char has_key_6 : 1;
} state_bitset_t;

typedef union
{
    state_bitset_t bitset;
    unsigned short number;
} state_t;

typedef struct
{
    state_t state;
    unsigned int step;
} element_t;

typedef struct
{
    element_t data[MAX_STATE_NUM];
    unsigned int head;
    unsigned int tail;
} queue_t;

unsigned char queue_is_empty(queue_t* queue)
{
    return queue->head == queue->tail;
}

void queue_push(queue_t* queue, element_t element)
{
    if (queue->tail >= MAX_STATE_NUM) {
        printf("QUEUE FULL, CAN'T PUSH!\n");
        return;
    }
    queue->data[queue->tail] = element;
    queue->tail++;
}

void queue_pop(queue_t* queue)
{
    if (queue_is_empty(queue))
    {
        printf("QUEUE EMPTY, CAN'T POP!\n");
        return;
    }
    queue->head++;
}

element_t queue_top(queue_t* queue) {
    if (queue_is_empty(queue))
    {
        printf("QUEUE EMPTY, CAN'T GET TOP!\n");
        return (element_t){0};
    }
    return queue->data[queue->head];
}

unsigned char is_success(state_t state, unsigned char *key_state_aim)
{
    return key_state_aim[1] == state.bitset.has_key_1 &&
           key_state_aim[2] == state.bitset.has_key_2 &&
           key_state_aim[3] == state.bitset.has_key_3 &&
           key_state_aim[4] == state.bitset.has_key_4 &&
           key_state_aim[5] == state.bitset.has_key_5 &&
           key_state_aim[6] == state.bitset.has_key_6;
}

element_t get_next_element(unsigned char map[MAX_GRID_SIZE + 2][MAX_GRID_SIZE + 2], element_t present_element, unsigned int direction)
{
    unsigned char direction_pos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    element_t new_element = {0};
    unsigned char new_pos_x = 0, new_pos_y = 0;
    if (direction < UP || direction > RIGHT)
    {
        return new_element;
    }
    new_pos_x = present_element.state.bitset.row + direction_pos[direction][0];
    new_pos_y = present_element.state.bitset.col + direction_pos[direction][1];
    new_element = present_element;
    new_element.step++;
    new_element.state.bitset.row = new_pos_x;
    new_element.state.bitset.col = new_pos_y;
    switch (map[new_pos_x][new_pos_y])
    {
    case GRID_WALL:
        new_element.step = 0;
        return new_element;
    case GRID_KEY_1:
        new_element.state.bitset.has_key_1 = 1;
        break;
    case GRID_KEY_2:
        new_element.state.bitset.has_key_2 = 1;
        break;
    case GRID_KEY_3:
        new_element.state.bitset.has_key_3 = 1;
        break;
    case GRID_KEY_4:
        new_element.state.bitset.has_key_4 = 1;
        break;
    case GRID_KEY_5:
        new_element.state.bitset.has_key_5 = 1;
        break;
    case GRID_KEY_6:
        new_element.state.bitset.has_key_6 = 1;
        break;
    case GRID_LOCK_1:
        if (new_element.state.bitset.has_key_1 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    case GRID_LOCK_2:
        if (new_element.state.bitset.has_key_2 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    case GRID_LOCK_3:
        if (new_element.state.bitset.has_key_3 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    case GRID_LOCK_4:
        if (new_element.state.bitset.has_key_4 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    case GRID_LOCK_5:
        if (new_element.state.bitset.has_key_5 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    case GRID_LOCK_6:
        if (new_element.state.bitset.has_key_6 == 0)
        {
            new_element.step = 0;
            return new_element;
        }
        break;
    default:
        break;
    }
    return new_element;
}

int shortestPathAllKeys(char** grid, int gridSize) {
    unsigned char state_array[MAX_STATE_NUM] = {0};
    unsigned int i = 0, j = 0;
    unsigned char map[MAX_GRID_SIZE + 2][MAX_GRID_SIZE + 2] = {0};
    element_t start_element = {0};
    element_t present_element = {0};
    element_t next_element = {0};
    queue_t* queue = NULL;
    unsigned char key_state_aim[7] = {0};
    queue = (queue_t*)malloc(sizeof(queue_t));
    memset(queue, 0, sizeof(queue_t));
    memset(map, GRID_WALL, (MAX_GRID_SIZE + 2) * (MAX_GRID_SIZE + 2));
    for (i = 0; i < gridSize; i++)
    {
        for (j = 0; grid[i][j] != 0; j++)
        {
            map[i + 1][j + 1] = grid[i][j];
            switch (map[i + 1][j + 1])
            {
            case GRID_START_POINT:
                start_element.state.bitset.row = i + 1;
                start_element.state.bitset.col = j + 1;
                break;
            case GRID_KEY_1:
                key_state_aim[1] = 1;
                break;
            case GRID_KEY_2:
                key_state_aim[2] = 1;
                break;
            case GRID_KEY_3:
                key_state_aim[3] = 1;
                break;
            case GRID_KEY_4:
                key_state_aim[4] = 1;
                break;
            case GRID_KEY_5:
                key_state_aim[5] = 1;
                break;
            case GRID_KEY_6:
                key_state_aim[6] = 1;
                break;
            default:
                break;
            }
        }
    }
    queue_push(queue, start_element);
    state_array[start_element.state.number] = 1;
    while(1)
    {
        if (queue_is_empty(queue))
        {
            return -1;
        }
        present_element = queue_top(queue);
        queue_pop(queue);
        for (i = UP; i <= RIGHT; i++)
        {
            next_element = get_next_element(map, present_element, i);
            if (next_element.step == 0 || state_array[next_element.state.number] == 1)
            {
                continue;
            }
            if (is_success(next_element.state, key_state_aim))
            {
                return next_element.step;
            }
            else
            {
                queue_push(queue, next_element);
                state_array[next_element.state.number] = 1;
            }
        }
    }
}