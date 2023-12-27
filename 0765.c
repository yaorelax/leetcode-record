#define MAX_LENGTH 30

int find_root(int *joint_set, int member)
{
    int path_record[MAX_LENGTH];
    int num_path_record = 0;
    int i = 0;
    while (joint_set[member] >= 0)
    {
        path_record[num_path_record] = member;
        num_path_record++;
        member = joint_set[member];
    }
    for (i = 0; i < num_path_record; i++)
    {
        joint_set[path_record[i]] = member;
    }
    return member;
}

void merge(int *joint_set, int member1, int member2)
{
    int root1, root2;
    root1 = find_root(joint_set, member1);
    root2 = find_root(joint_set, member2);
    if (root1 != root2)
    {
        if (joint_set[root1] <= joint_set[root2])
        {
            joint_set[root1] += joint_set[root2];
            joint_set[root2] = root1;
        }
        else
        {
            joint_set[root2] += joint_set[root1];
            joint_set[root1] = root2;
        }
    }
}

int minSwapsCouples(int* row, int rowSize) {
    int joint_set[MAX_LENGTH];
    int i = 0;
    int result = 0;
    memset(joint_set, -1, rowSize * 2);
    for (i = 0; i < rowSize / 2; i++)
    {
        merge(joint_set, row[2 * i] / 2, row[2 * i + 1] / 2);
    }
    for (i = 0; i < rowSize / 2; i++)
    {
        if (joint_set[i] < 0)
        {
            result -= 1 +  joint_set[i];
        }
    }
    return result;
}