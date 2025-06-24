#include <iostream>
#include <vector>
#include <algorithm> // 用于 swap
using namespace std;
/**
 * @brief Matrix 类封装了矩阵的状态和操作。
 *
 * 该类将矩阵数据线性化存储在一维向量中，以实现高效的重塑和转置。
 * 它采用“懒惰转置”策略：转置操作仅切换一个标志位并交换维度，
 * 而不实际移动数据。数据的物理重新排列被推迟到下一次重塑操作之前，
 * 因为重塑需要一个标准的行优先布局。
 */
class Matrix
{
private:
    vector<int> data; // 线性化的矩阵数据
    int n; // 当前矩阵的行数
    int m; // 当前矩阵的列数
    bool is_transposed; // 标记当前是否处于转置视图

public:
    /**
     * @brief 构造函数，初始化矩阵的初始维度。
     * @param initial_n 初始行数。
     * @param initial_m 初始列数。
     */
    Matrix(int initial_n, int initial_m) : n(initial_n), m(initial_m), is_transposed(false)
    {
        data.reserve(initial_n * initial_m);
    }

    /**
     * @brief 从标准输入读取初始矩阵数据。
     */
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

    /**
     * @brief 将矩阵重塑为新的维度 p x q。
     *
     * 如果矩阵当前处于转置状态，会先物理上应用转置，
     * 使数据恢复到标准的行优先顺序，然后再进行重塑。
     * @param p 新的行数。
     * @param q 新的列数。
     */
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

    /**
     * @brief 对矩阵执行转置操作。
     * 这是一个 O(1) 操作，只交换维度并切换标志位。
     */
    void transpose()
    {
        swap(n, m);
        is_transposed = !is_transposed;
    }

    /**
     * @brief 查询并返回位于 (r, c) 的元素。
     * @param r 行索引。
     * @param c 列索引。
     * @return 位于 (r, c) 的元素值。
     */
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

/**
 * @brief 主函数，处理输入、执行操作并打印查询结果。
 */
int main()
{
    // 优化 C++ I/O 性能
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
