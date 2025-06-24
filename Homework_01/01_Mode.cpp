// Original Filename: 01.众数.cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        vector<int> data(n);
        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
        }
        int mode = data[0]; // 当前众数
        int max_count = 1; // 最大出现次数
        int current_count = 1; // 当前数字的出现次数
        // 遍历数组，统计每个数字的连续出现次数
        for (int i = 1; i < n; i++)
        {
            if (data[i] == data[i - 1])
            {
                // 如果当前数字与前一个相同，增加计数
                current_count++;
            } else
            {
                // 如果当前数字与前一个不同，检查是否需要更新众数

                if (current_count > max_count)
                {
                    max_count = current_count;
                    mode = data[i - 1];
                }
                current_count = 1; // 重置计数
            }
        }
        // 检查最后一组数字
        if (current_count > max_count)
        {
            mode = data[n - 1];
        }
        cout << mode << endl;
    }
    return 0;
}
