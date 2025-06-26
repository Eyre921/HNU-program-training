#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 检查以(r,c)为左上角，尺寸为size的子矩阵是否为完整棋盘
bool isValidChessboard(const vector<string>& matrix, int r, int c, int size) {
    int n = matrix.size();
    
    // 检查边界
    if (r + size > n || c + size > n) {
        return false;
    }
    
    // 检查每个位置是否符合棋盘模式
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int expected = (i + j) % 2;  // 棋盘模式：行号+列号为偶数时为1
            int actual = matrix[r + i][c + j] - '0';
            
            if (actual != expected) {
                return false;
            }
        }
    }
    
    return true;
}

int main() {
    int n;
    cin >> n;
    
    vector<string> matrix(n);
    for (int i = 0; i < n; i++) {
        cin >> matrix[i];
    }
    
    int maxSize = 0;
    int count = 0;
    
    // 枚举所有可能的棋盘尺寸（从大到小）
    for (int size = n; size >= 1; size--) {
        int currentCount = 0;
        
        // 枚举所有可能的左上角位置
        for (int r = 0; r <= n - size; r++) {
            for (int c = 0; c <= n - size; c++) {
                if (isValidChessboard(matrix, r, c, size)) {
                    currentCount++;
                }
            }
        }
        
        if (currentCount > 0) {
            maxSize = size;
            count = currentCount;
            break;  // 找到最大尺寸就停止
        }
    }
    
    cout << maxSize << " " << count << endl;
    
    return 0;
}