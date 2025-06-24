#include <iostream>
#include <vector>
#include <algorithm> // 用于 swap
using namespace std;

class Matrix
{
private:
    vector<int> data; // 线性化的矩阵数据
    int n; // 当前矩阵的行数
    int m; // 当前矩阵的列数
    bool is_transposed; // 标记当前是否处于转置视图

public:
    Matrix(int initial_n, int initial_m) : n(initial_n), m(initial_m), is_transposed(false)
    {
        data.reserve(initial_n * initial_m);
    }

    void read_initial_data()
    {
        int total_elements = n * m;
        for (int i = 0; i < total_elements; ++i)
        {
            int element;
            cin >> element;
            data.push_back(element);
        }
    }

    void reshape(int p, int q)
    {
        if (is_transposed)
        {
            // “烘焙”转置：创建一个新的数据向量，其顺序与当前转置视图匹配。
            vector<int> temp_data;
            temp_data.reserve(data.size());
            // 遍历转置后的视图（n x m）
            for (int i = 0; i < n; ++i)
            {
                // 新的行 (旧的列)
                for (int j = 0; j < m; ++j)
                {
                    // 新的列 (旧的行)
                    // 从原始数据布局中获取元素。
                    // 视图中的 (i, j) 对应物理数据中的 (j, i)。
                    // 物理数据的维度是 m x n（在转置之前）。
                    temp_data.push_back(data[j * n + i]);
                }
            }
            data = temp_data;
            is_transposed = false; // 重置转置标志
        }
        // 更新维度以匹配新的形状
        n = p;
        m = q;
    }

    //对矩阵执行转置操作。

    void transpose()
    {
        swap(n, m);
        is_transposed = !is_transposed;
    }


    //查询并返回位于 (r, c) 的元素。
    int query(int r, int c)
    {
        int index;
        if (!is_transposed)
        {
            // 标准行优先布局
            index = r * m + c;
        } else
        {
            // 转置视图：视图中的 (r, c) 对应物理数据中的 (c, r)。
            // 物理数据的维度是 m x n，因此有 n 列。
            index = c * n + r;
        }
        return data[index];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, t;
    cin >> n >> m >> t;

    // 创建并初始化矩阵
    Matrix matrix(n, m);
    matrix.read_initial_data();

    // 处理 t 个操作
    for (int k = 0; k < t; ++k)
    {
        int op, a, b;
        cin >> op >> a >> b;
        switch (op)
        {
            case 1: // 重塑
                matrix.reshape(a, b);
                break;
            case 2: // 转置
                matrix.transpose();
                break;
            case 3: // 查询
                cout << matrix.query(a, b) << "\n";
                break;
        }
    }
    return 0;
}

/*
3 2 3
1 2
3 4
5 6
3 0 1
1 2 3
3 1 2
 */
/*
3 2 5
1 2
3 4
5 6
3 1 0
2 0 0
3 1 0
1 3 2
3 1 0
 */
