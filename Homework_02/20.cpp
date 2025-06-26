#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, a, b;
    string s;
    cin >> n >> a >> b >> s;

    // dp[i] 表示压缩前i个字符的最小成本
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        // 选择1：将第i个字符作为单独字符编码
        if (dp[i - 1] != INT_MAX) {
            dp[i] = min(dp[i], dp[i - 1] + a);
        }

        // 选择2：尝试将s[j..i-1]作为子串编码
        for (int j = 0; j < i; j++) {
            // 检查s[j..i-1]是否在s[0..j-1]中出现过
            string current = s.substr(j, i - j);
            bool found = false;

            // 在前面的部分查找当前子串
            for (int k = 0; k <= j - (int)current.length(); k++) {
                if (s.substr(k, current.length()) == current) {
                    found = true;
                    break;
                }
            }

            if (found && dp[j] != INT_MAX) {
                dp[i] = min(dp[i], dp[j] + b);
            }
        }
    }

    cout << dp[n] << endl;
    return 0;
}