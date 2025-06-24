#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 快速输入输出设置
void setup_fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

// 定义更新操作的结构体
// 一次操作会将 (startX, startY) 到 (endX, endY) 的矩形区域内的值更新为 max(原值, value)
struct UpdateOperation
{
    int startX, endX, startY, endY;
    int value;
};

// 自定义比较函数，按 value 值降序对更新操作进行排序
// 这是离线算法的关键，我们希望优先检查 value 值最高的更新
bool compareOperations(const UpdateOperation &a, const UpdateOperation &b)
{
    return a.value > b.value;
}

int main()
{
    // 设置快速输入输出
    setup_fast_io();

    // n: 更新操作的数量
    // m: 查询操作的数量
    int n, m;
    cin >> n >> m;

    // 离线存储所有更新操作
    vector<UpdateOperation> updates;
    updates.reserve(n); // 预分配内存，提高效率

    for (int i = 0; i < n; ++i)
    {
        UpdateOperation op;
        cin >> op.startX >> op.endX >> op.startY >> op.endY >> op.value;
        updates.push_back(op);
    }

    // 按 value 值对所有更新操作进行降序排序
    // 题目的核心逻辑是 V(x,y) 变为 max(V(x,y), v)。
    // 通过降序排序，第一个与查询矩形相交的更新操作，其 value 值就是该区域的最大值。
    sort(updates.begin(), updates.end(), compareOperations);

    // 处理每次查询
    for (int i = 0; i < m; ++i)
    {
        int queryStartX, queryEndX, queryStartY, queryEndY;
        cin >> queryStartX >> queryEndX >> queryStartY >> queryEndY;

        int max_val = 0; // 矩阵的默认初始值为 0

        // 遍历排序后的更新操作
        for (const auto &op: updates)
        {
            // 检查矩形是否相交
            // 两个矩形不相交的条件是：一个完全在另一个的左侧、右侧、上方或下方。
            // 如果不满足“不相交”的条件，那么它们就是相交的。
            bool no_intersect = op.startX > queryEndX || op.endX < queryStartX || op.startY > queryEndY || op.endY <
                                queryStartY;

            if (!no_intersect)
            {
                // 因为更新操作已经按 value 值降序排序，第一个相交的操作即为最大值
                max_val = op.value;
                break; // 找到最大值，无需再检查更小的值，直接跳出循环
            }
        }
        cout << max_val << "\n";
    }

    return 0;
}

/*
5 5
1 3 2 3 3
4 5 2 5 1
3 5 1 2 1
2 5 3 4 4
1 4 3 4 2
1 5 2 5
1 5 2 5
1 5 1 5
1 4 1 5
2 5 1 3
 */

/*
10 10
3 10 7 7 10
1 10 9 9 3
4 6 7 7 7
1 8 5 5 1
6 8 1 1 1
1 3 8 8 2
2 10 10 10 9
1 10 6 6 4
1 8 9 9 4
5 9 9 9 2
1 9 2 2
2 10 1 10
2 10 6 9
2 2 1 4
2 10 8 10
7 10 1 10
1 8 1 9
1 8 5 7
3 7 5 8
2 10 1 7
 */
