// Original Filename: 08.循环数.cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isCycle(const string& str) {
    vector<int> num(str.length());
    // 将字符串转换为数字数组
    int length = str.length();
    for (int i = 0; i < length; i++) {
        num[i] = str[i] - '0';
    }
    
    // 创建双倍字符串用于循环检查
    string strCycle = str + str;
    vector<int> num2(num.size());
    
    // 对每个乘数从1到字符串长度进行测试
    for (int i = 1; i <= length; i++) {
        // 复制原数组
        for (int j = 0; j < length; j++) {
            num2[j] = num[j];
        }
        
        int carry = 0;
        string result = "";
        
        // 高精度乘法（从右到左）
        for (int j = length - 1; j >= 0; j--) {
            num2[j] = num2[j] * i + carry;
            carry = num2[j] / 10;
            num2[j] = num2[j] % 10;
            // 构建结果字符串（从左到右添加）
        }
        
        // 将结果数组转换为字符串
        for (int j = 0; j < length; j++) {
            result += (char)('0' + num2[j]);
        }
        
        // 检查结果是否在双倍字符串中（即是否为循环）
        if (strCycle.find(result) == string::npos) {
            return false;
        }
    }
    
    return true;
}

int main() {
    string str;
    cin >> str;
    
    if (isCycle(str)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}
