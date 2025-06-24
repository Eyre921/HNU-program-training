// Original Filename: 06.字符串排序.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 计算字符串的无序度
int calculateDisorder(const string& str) {
    int disorder = 0;
    int n = str.length();
    
    for (int i = 0; i < n; i++) {
        // 统计位置i后面有多少个字符比str[i]小
        for (int j = i + 1; j < n; j++) {
            if (str[j] < str[i]) {
                disorder++;
            }
        }
    }
    
    return disorder;
}

// 用于存储字符串及其相关信息的结构体
struct StringInfo {
    string str;
    int disorder;
    int originalIndex; // 原始输入顺序
    
    StringInfo(const string& s, int d, int idx) : str(s), disorder(d), originalIndex(idx) {}
};

// 比较函数：按无序度升序排序，无序度相同时按原始顺序排序
bool compare(const StringInfo& a, const StringInfo& b) {
    if (a.disorder != b.disorder) {
        return a.disorder < b.disorder; // 无序度小的在前
    }
    return a.originalIndex < b.originalIndex; // 保持原始相对顺序
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<StringInfo> strings;
    
    // 读取字符串并计算无序度
    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;
        int disorder = calculateDisorder(str);
        strings.emplace_back(str, disorder, i);
    }
    
    // 按无序度排序（稳定排序）
    stable_sort(strings.begin(), strings.end(), compare);
    
    // 输出排序后的结果
    for (const auto& info : strings) {
        cout << info.str << endl;
    }
    
    return 0;
}
