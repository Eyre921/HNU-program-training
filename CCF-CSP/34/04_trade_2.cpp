
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 常量
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int N = 1005;
const int M = N * 40;

// DP表: dp[i][j] 表示处理前i个仓库，花费为j时的最大净收益
int dp[N][M];

void work()
{
    int n, m, v;
    cin >> n >> m >> v;

    vector<int> b(n + 1);
    vector<int> c(n + 1);

    int max_C = 0; // 估算最大可能成本
    for (int i = 1; i <= n; ++i)
    {
        cin >> b[i] >> c[i];
        max_C += b[i];
    }

    vector<vector<int> > a(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int k_val, t_idx;
        cin >> k_val >> t_idx;
        t_idx++; // 题目仓库从0开始，我们按1开始处理
        max_C += c[t_idx];

        if (k_val > c[t_idx])
        {
            a[t_idx].push_back(k_val - c[t_idx]);
        }
    }

    // 对每个仓库的收益列表进行排序和前缀和计算
    for (int i = 1; i <= n; ++i)
    {
        sort(a[i].rbegin(), a[i].rend());
        for (size_t j = 1; j < a[i].size(); ++j)
        {
            a[i][j] += a[i][j - 1];
        }
    }

    // 全局DP表已自动初始化为0

    long long ans = INF;

    // 动态规划
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= max_C; ++j)
        {
            // 不选择第 i 个仓库
            dp[i][j] = dp[i - 1][j];

            // 选择第 i 个仓库，并运送 k+1 件物品
            for (size_t k = 0; k < a[i].size(); ++k)
            {
                int cost = b[i] + c[i] * (k + 1);
                if (j >= cost)
                {
                    int prev_profit = dp[i - 1][j - cost];
                    int current_profit = prev_profit + a[i][k] - b[i];
                    dp[i][j] = max(dp[i][j], current_profit);
                }
            }

            // 检查是否满足利润要求
            if (dp[i][j] >= v)
            {
                ans = min(ans, (long long) j);
            }
        }
    }

    if (ans == INF)
    {
        // 无法达到目标
        cout << -1 << endl;
    } else
    {
        cout << ans << endl;
    }
}

int main()
{
    // 提高IO效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    work();

    return 0;
}
