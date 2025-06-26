#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

struct Paper {
    string title;
    int citations;
    int order;  // 输入顺序
    
    Paper(string t, int c, int o) : title(t), citations(c), order(o) {}
};

// 将字符串转换为小写
string toLowerCase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// 将标题分割成单词
vector<string> splitTitle(const string& title) {
    vector<string> words;
    stringstream ss(title);
    string word;
    
    while (ss >> word) {
        words.push_back(toLowerCase(word));
    }
    
    return words;
}

// 检查论文标题是否包含所有关键词
bool containsAllKeywords(const string& title, const vector<string>& keywords) {
    vector<string> titleWords = splitTitle(title);
    
    for (const string& keyword : keywords) {
        bool found = false;
        for (const string& word : titleWords) {
            if (word == toLowerCase(keyword)) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    
    return true;
}

// 比较函数：按引用次数降序，相同时按输入顺序升序
bool comparePapers(const Paper& a, const Paper& b) {
    if (a.citations != b.citations) {
        return a.citations > b.citations;  // 引用次数降序
    }
    return a.order < b.order;  // 输入顺序升序
}

int main() {
    int n;
    
    while (cin >> n && n != 0) {
        cin.ignore();  // 忽略换行符
        
        vector<Paper> papers;
        
        // 读取论文信息
        for (int i = 0; i < n; i++) {
            string title;
            int citations;
            
            getline(cin, title);
            cin >> citations;
            cin.ignore();
            
            papers.emplace_back(title, citations, i);
        }
        
        int m;
        cin >> m;
        cin.ignore();
        
        // 处理查询
        for (int i = 0; i < m; i++) {
            string query;
            getline(cin, query);
            
            // 分割查询关键词
            vector<string> keywords;
            stringstream ss(query);
            string keyword;
            
            while (ss >> keyword) {
                keywords.push_back(keyword);
            }
            
            // 找到匹配的论文
            vector<Paper> matchedPapers;
            
            for (const Paper& paper : papers) {
                if (containsAllKeywords(paper.title, keywords)) {
                    matchedPapers.push_back(paper);
                }
            }
            
            // 排序
            sort(matchedPapers.begin(), matchedPapers.end(), comparePapers);
            
            // 输出结果
            for (const Paper& paper : matchedPapers) {
                cout << paper.title << endl;
            }
            
            cout << "***" << endl;
        }
        
        cout << "---" << endl;
    }
    
    return 0;
}