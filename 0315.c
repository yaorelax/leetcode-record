/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    int *dp = NULL;
    int i = 0, j = 0;
    * returnSize = numsSize;
    dp = (int*)malloc(numsSize * 4);
    memset(dp, 0, numsSize * 4);
    dp[numsSize - 1] = 0;
    for (i = numsSize - 2; i >= 0; i--)
    {
        for (j = i + 1; j < numsSize; j++)
        {
            if (nums[j] == nums[i])
            {
                dp[i] += dp[j];
                break;
            }
            else if (nums[j] < nums[i])
            {
                dp[i] += 1;
                continue;
            }
            else if (dp[j] == 0)
            {
                break;
            }
        }
    }
    return dp;
}