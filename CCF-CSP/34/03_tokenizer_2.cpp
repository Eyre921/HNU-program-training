#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct Word
{
    vector<string> tokens;
    int freq;
};

struct Pair
{
    string first, second;

    bool operator<(const Pair &other) const
    {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Word> words(n);
    set<char> chars;

    // 读入单词并收集所有字符
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s >> words[i].freq;

        // 将单词拆分为单字符
        for (char c: s)
        {
            chars.insert(c);
            words[i].tokens.push_back(string(1, c));
        }
    }

    // 初始词汇表：按字典序加入所有字符
    vector<string> vocab;
    for (char c: chars)
    {
        vocab.push_back(string(1, c));
    }

    // 输出初始词汇表
    for (const string &token: vocab)
    {
        cout << token << "\n";
        if (vocab.size() >= m) return 0;
    }

    // 迭代合并过程
    while (vocab.size() < m)
    {
        // 统计词汇对频率
        map<Pair, int> pair_freq;

        for (const Word &word: words)
        {
            for (int i = 0; i < word.tokens.size() - 1; i++)
            {
                Pair p = {word.tokens[i], word.tokens[i + 1]};
                pair_freq[p] += word.freq;
            }
        }

        if (pair_freq.empty()) break;

        // 找到最佳词汇对
        Pair best_pair;
        int max_freq = 0;

        for (const auto &[pair, freq]: pair_freq)
        {
            bool is_better = false;

            if (freq > max_freq)
            {
                is_better = true;
            } else if (freq == max_freq)
            {
                string new_token = pair.first + pair.second;
                string current_best = best_pair.first + best_pair.second;

                // 优先级比较
                if (new_token.length() < current_best.length())
                {
                    is_better = true;
                } else if (new_token.length() == current_best.length())
                {
                    if (pair.first.length() < best_pair.first.length())
                    {
                        is_better = true;
                    } else if (pair.first.length() == best_pair.first.length())
                    {
                        if (new_token < current_best)
                        {
                            is_better = true;
                        }
                    }
                }
            }

            if (is_better)
            {
                max_freq = freq;
                best_pair = pair;
            }
        }

        // 生成新词汇
        string new_token = best_pair.first + best_pair.second;
        vocab.push_back(new_token);
        cout << new_token << "\n";

        if (vocab.size() >= m) break;

        // 更新所有单词的词汇序列
        for (Word &word: words)
        {
            vector<string> new_tokens;
            int i = 0;

            while (i < word.tokens.size())
            {
                if (i < word.tokens.size() - 1 &&
                    word.tokens[i] == best_pair.first &&
                    word.tokens[i + 1] == best_pair.second)
                {
                    // 合并词汇对
                    new_tokens.push_back(new_token);
                    i += 2;
                } else
                {
                    new_tokens.push_back(word.tokens[i]);
                    i++;
                }
            }

            word.tokens = new_tokens;
        }
    }

    return 0;
}
