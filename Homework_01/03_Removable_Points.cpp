// Original Filename: 03.可删除的点.cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int positive_count = 0; // x坐标为正的点的个数
    int negative_count = 0; // x坐标为负的点的个数
    
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        
        if (x > 0) {
            positive_count++;
        } else {
            negative_count++;
        }
    }
    
    // 如果正数或负数的点最多只有1个，就可以删除使得剩余点在同一边
    if (positive_count <= 1 || negative_count <= 1) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}
