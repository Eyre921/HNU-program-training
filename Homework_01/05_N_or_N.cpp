#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 检查数字num是否包含数字n
bool containsDigit(int num, int n)
{
    string numStr = to_string(num);
    string nStr = to_string(n);
    return numStr.find(nStr) != string::npos;
}

int main()
{
    int m, n;
    cin >> m >> n;

    vector<int> result;

    // 遍历从1到m的所有数
    for (int i = 1; i <= m; i++)
    {
        // 检查是否是n的倍数或包含数字n
        if (i % n == 0 || containsDigit(i, n))
        {
            result.push_back(i);
        }
    }

    // 输出结果
    for (int i = 0; i < int(result.size()); i++)
    {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}
