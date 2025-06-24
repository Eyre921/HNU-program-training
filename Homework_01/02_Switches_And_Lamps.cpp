// Original Filename: 02.开关与灯.cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<string> switches(n);
    for (int i = 0; i < n; i++) {
        cin >> switches[i];
    }
    
    // 统计每个灯有多少个开关可以打开它
    vector<int> light_count(m, 0);
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (switches[i][j] == '1') {
                light_count[j]++;
            }
        }
    }
    
    // 检查每个开关是否可以被忽略
    for (int i = 0; i < n; i++) {
        bool can_ignore = true;
        
        // 检查这个开关能打开的每个灯
        for (int j = 0; j < m; j++) {
            if (switches[i][j] == '1') {
                // 如果这个灯只有当前开关能打开，那么不能忽略这个开关
                if (light_count[j] == 1) {
                    can_ignore = false;
                    break;
                }
            }
        }
        
        if (can_ignore) {
            cout << "YES" << endl;
            return 0;
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
