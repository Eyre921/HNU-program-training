// 新型冠状病毒（COVID19）传播
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// 题目的 N 最大值为 10^5，但这里开了 10^7+10，可能是模板习惯，够用即可
const int N = 1e7 + 10;
int n, k;
// ans 用来最终计数
int ans;
int s[N], v[N];

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> v[i];

    // --- 阶段一: 确定感染群体的速度边界 ---
    // 核心思想是，所有最终被感染的人会形成一个“感染群组”。
    // 这个群组有一个最快的领跑者和一个最慢的殿后者。
    // max_v: 用来记录感染群组中“最快”的速度。
    // min_v: 用来记录感染群组中“最慢”的速度。
    // 初始时，我们只知道病人k，所以速度边界就是v[k]。
    int max_v = v[k], min_v = v[k];

    // 第一次遍历：此循环的目的是找到所有能与初始病人k（或与k同起点的人）
    // 直接构成感染关系的人，并用他们的速度来更新整个感染群体的速度边界 (max_v, min_v)。
    for (int i = 1; i <= n; i++)
    {
        // 情况1: 跑者i在病人k前面 (s[i] > s[k])，但速度比k慢 (v[i] < v[k])。
        // 这意味着k迟早会追上i，从而直接感染i。
        // i的速度就可能成为感染群组里更慢的速度，所以我们更新min_v。
        if (s[i] > s[k] && v[i] < v[k])
        {
            min_v = min(min_v, v[i]);
        }
        // 情况2: 跑者i在病人k后面 (s[i] < s[k])，但速度比k快 (v[i] > v[k])。
        // 这意味着i迟早会追上k，从而直接感染i。
        // i的速度就可能成为感染群组里更快的速度，所以我们更新max_v。
        if (s[i] < s[k] && v[i] > v[k])
        {
            max_v = max(max_v, v[i]);
        }
        // 情况3: 跑者i和病人k在同一位置起跑 (s[i] == s[k])。
        // 他们在 t=0 时刻就相遇，所以i立即被感染。
        // 我们需要把这个人的速度也纳入考虑，来更新速度边界。
        if (s[i] == s[k])
        {
            // 注意：这里的ans计数方式比较特殊，它只先加上了和k同起点的人。
            // 最终结果还需要在下一轮循环中累加。病人k自己也会在这里被算进去一次。
            ans++;
            min_v = min(min_v, v[i]);
            max_v = max(max_v, v[i]);
        }
    }

    // --- 阶段二: 根据速度边界统计所有间接感染者 ---
    // 现在我们有了整个感染群体的最快速度max_v和最慢速度min_v。
    // 这两个速度定义了一个移动的“感染区间” [min_v, max_v]。
    // 任何跑者，只要其运动轨迹会进入这个由感染群体构成的“移动时空区域”，就会被感染。

    // 第二次遍历，统计所有会被这个“感染群组”追上或追上这个“感染群组”的人。
    // 注意：这里我们只考虑那些与k不同起点的人，因为同起点的已经在阶段一被ans统计过了。
    for (int i = 1; i <= n; i++)
    {
        // 情况A: 跑者i在病人k后面 (s[i] < s[k])。
        // 要想追上并被感染，他必须比感染群组中“最慢”的那个殿后者(min_v)还要快。
        // 只要 v[i] > min_v，他就总有一天能追上感染群组的“尾巴”。
        if (s[i] < s[k] && v[i] > min_v) ans++;

        // 情况B: 跑者i在病人k前面 (s[i] > s[k])。
        // 要想被追上并感染，他必须比感染群组中“最快”的那个领跑者(max_v)还要慢。
        // 只要 v[i] < max_v，感染群组的“排头兵”总有一天能追上他。
        if (s[i] > s[k] && v[i] < max_v) ans++;
    }

    // 输出最终统计的总人数。
    cout << ans << endl;
    return 0;
}
