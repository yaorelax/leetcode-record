int minimumDeleteSum(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[1001][1001] = {0};
    int i = 0, j = 0;
    dp[0][0] = 0;
    for (i = 1; i <= len1; i++)
    {
        dp[i][0] = dp[i - 1][0] + s1[i - 1];
    }
    for (j = 1; j <= len2; j++)
    {
        dp[0][j] = dp[0][j - 1] + s2[j - 1];
    }
    for (i = 1; i <= len1; i++)
    {
        for (j = 1; j <= len2; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = fmin(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
            }
        }
    }
    return dp[len1][len2];
}