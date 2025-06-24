#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;
// 定义一个结构体来存储每个单词的信息，
// 包括其词汇序列和出现频率。
struct Word
{
    vector<int> tokens; // 单词被表示为一串词汇ID
    int frequency;
};

// 定义一个结构体来存储合并候选对的信息，
// 用于根据题目的优先级规则找到最佳合并对。
struct CandidatePair
{
    long long frequency = -1; // 出现频率
    int merged_length = -1; // 合并后字符串的长度
    int first_token_length = -1; // 对中第一个词汇的长度
    string merged_string; // 合并后的字符串
    pair<int, int> token_ids; // 对的词汇ID
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // 输入单词的数量
    int m; // 期望的词汇表长度
    cin >> n >> m;

    vector<pair<string, int> > initial_input(n);
    set<char> char_set;

    // 读取所有输入单词及其频率，并收集所有出现过的唯一字符。
    for (int i = 0; i < n; ++i)
    {
        cin >> initial_input[i].first >> initial_input[i].second;
        for (char c: initial_input[i].first)
        {
            char_set.insert(c);
        }
    }

    // --- 1. 初始化词汇表和单词序列 ---
    vector<string> vocabulary;
    map<string, int> token_to_id;

    // 将排序后的唯一字符作为初始词汇加入词汇表。
    for (char c: char_set)
    {
        string s(1, c);
        token_to_id[s] = vocabulary.size();
        vocabulary.push_back(s);
    }

    vector<Word> word_data(n);
    // 将输入的每个单词字符串转换为其对应的初始词汇ID序列。
    for (int i = 0; i < n; ++i)
    {
        word_data[i].frequency = initial_input[i].second;
        for (char c: initial_input[i].first)
        {
            word_data[i].tokens.push_back(token_to_id[string(1, c)]);
        }
    }

    // final_vocabulary 用于存储按顺序生成的所有词汇，以备最后输出。
    vector<string> final_vocabulary = vocabulary;

    // --- 2. 主合并循环 ---
    // 循环直到词汇表达到目标大小 m，或无法再进行合并。
    while (final_vocabulary.size() < m)
    {
        // --- 2a. 统计所有相邻词汇对的出现频率 ---
        map<pair<int, int>, long long> pair_counts;
        for (const auto &word: word_data)
        {
            if (word.tokens.size() < 2) continue;
            for (size_t i = 0; i < word.tokens.size() - 1; ++i)
            {
                pair_counts[{word.tokens[i], word.tokens[i + 1]}] += word.frequency;
            }
        }

        // 如果没有可以合并的词汇对，则提前终止循环。
        if (pair_counts.empty())
        {
            break;
        }

        // --- 2b. 根据优先级规则寻找最佳合并对 ---
        CandidatePair best_candidate;
        for (const auto &entry: pair_counts)
        {
            const auto &current_pair_ids = entry.first;
            long long current_freq = entry.second;

            const string &first_token_str = vocabulary[current_pair_ids.first];
            const string &second_token_str = vocabulary[current_pair_ids.second];
            string merged_str = first_token_str + second_token_str;

            bool is_better = false;
            // 按照题目描述的优先级顺序进行比较和选择
            if (best_candidate.frequency == -1)
            {
                // 如果是第一个候选
                is_better = true;
            } else if (current_freq > best_candidate.frequency)
            {
                // 1. 频率更高
                is_better = true;
            } else if (current_freq == best_candidate.frequency)
            {
                if (merged_str.length() < best_candidate.merged_length)
                {
                    // 2. 合并后长度更短
                    is_better = true;
                } else if (merged_str.length() == best_candidate.merged_length)
                {
                    if (first_token_str.length() < best_candidate.first_token_length)
                    {
                        // 3. 第一个词汇长度更短
                        is_better = true;
                    } else if (first_token_str.length() == best_candidate.first_token_length)
                    {
                        if (merged_str < best_candidate.merged_string)
                        {
                            // 4. 字典序更小
                            is_better = true;
                        }
                    }
                }
            }

            // 如果当前候选对更优，则更新最佳候选
            if (is_better)
            {
                best_candidate.frequency = current_freq;
                best_candidate.merged_length = merged_str.length();
                best_candidate.first_token_length = first_token_str.length();
                best_candidate.merged_string = merged_str;
                best_candidate.token_ids = current_pair_ids;
            }
        }

        // --- 2c. 执行合并并更新数据 ---
        // 将新生成的词汇添加到词汇表中
        int new_token_id = vocabulary.size();
        vocabulary.push_back(best_candidate.merged_string);
        final_vocabulary.push_back(best_candidate.merged_string);

        // 使用新的合并规则更新所有单词的词汇序列
        int token1_id = best_candidate.token_ids.first;
        int token2_id = best_candidate.token_ids.second;

        for (auto &word: word_data)
        {
            if (word.tokens.size() < 2) continue;
            vector<int> new_tokens;
            new_tokens.reserve(word.tokens.size()); // 预分配内存以提高效率
            // 从左到右遍历词汇序列，应用合并规则
            for (size_t i = 0; i < word.tokens.size();)
            {
                if (i + 1 < word.tokens.size() &&
                    word.tokens[i] == token1_id &&
                    word.tokens[i + 1] == token2_id)
                {
                    new_tokens.push_back(new_token_id);
                    i += 2; // 跳过被合并的两个词汇
                } else
                {
                    new_tokens.push_back(word.tokens[i]);
                    i += 1;
                }
            }
            word.tokens = new_tokens; // 用新的序列替换旧的序列
        }
    }

    // --- 3. 输出结果 ---
    // 按顺序打印最终词汇表中的所有词汇
    for (const auto &token: final_vocabulary)
    {
        cout << token << "\n";
    }

    return 0;
}

/*
 *
】
4 8
cut 15
cute 10
but 6
execute 3
 */
