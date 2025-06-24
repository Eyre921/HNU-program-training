// 题目：求众数 更快更省空间，无需存储
#include <iostream>
using namespace std;

int main()
{
    // 提高cin/cout效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n && n != 0)
    {
        if (n == 0) continue;

        long long prev_num; // 使用 long long 防止整数溢出
        cin >> prev_num;

        long long mode = prev_num;
        int max_count = 1;
        int current_count = 1;

        // 读取并处理剩下的 n-1 个数
        for (int i = 1; i < n; ++i)
        {
            long long current_num;
            cin >> current_num;

            if (current_num == prev_num)
            {
                // 如果数字和前一个相同，增加当前计数
                current_count++;
            } else
            {
                // 如果数字不同，说明上一个数字的序列结束了
                // 检查是否需要更新众数
                // 注意：题目要求若有多个众数，取最先出现的。
                // > (严格大于)保证了只有次数更多时才更新，次数相同时保留前者。
                if (current_count > max_count)
                {
                    max_count = current_count;
                    mode = prev_num;
                }
                // 为新数字重置计数
                current_count = 1;
            }
            prev_num = current_num;
        }

        // 循环结束后，对最后一组数字进行最终检查
        if (current_count > max_count)
        {
            mode = prev_num;
        }

        cout << mode << endl;
    }
    return 0;
}
