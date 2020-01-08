给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

class Solution {
public:
    bool isMatch(string s, string p) {
        int n,m =0;
        while ( s[m] ){
            if (s[m] == p[n] || p[n] == '.' ){
                m++;
                n++;
            }
            else if  ( p[n] == '*' ){
                m++;
                if( m >=2 ){
                    if ( s[m-2] != s[m-1] ){
                    n++;
                    }
                }
            }
            else { n++; }
            
        }
    if ( !p[n] ){ return true; }    
    return false;
    }
};

这给了我们一个至关重要的启示—— f[n]只与 f[n-1]相关
这就是DP（动态规划，dynamic programming）.
将一个问题拆成几个子问题，分别求解这些子问题，即可推断出大问题的解。
状态
首先状态 dp 一定能自己想出来。
dp[i][j] 表示 s 的前 i个是否能被 p 的前 j个匹配

#include <vector>
#include <string>
#include <iostream>
using namespace std;

void print(vector<vector<bool>> store);

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int sSize = int(s.size());
        int pSize = int(p.size());
        if (p.empty())
        {
            return s.empty();
        }
        vector<bool> tmpVec(pSize + 1, false);//dp大小应该比s，p的size大1
        vector<vector<bool>> dp(sSize + 1, tmpVec); //dp[i][j] 表示 s 的前 i 个是否能被 p 的前 j 个匹配
        dp[0][0] = true;
        if (sSize != 0 && (p[0] == s[0] || p[0] == '.'))
        {
            dp[1][1] = true;
        }
        if (p[0] == '*')
        {
            dp[0][1] = true;
        }
        //初始化情况：s为空，p为.*.*的情况
        for (int i = 1; i < pSize; i++)
        {
            if (p[i] == '*' && dp[0][i - 1] == true)
            {
                dp[0][i + 1] = true;
            }
        }

        for (int i = 0; i < sSize; i++)
        {
            for (int j = 1; j < pSize; j++)
            {
                if (p[j] == '.' || p[j] == s[i])
                { //如果是任意元素 或者是对于元素匹配
                    dp[i + 1][j + 1] = dp[i][j];
                }
                if (p[j] == '*')
                {
                    //caa cb* -> caa c
                    if (p[j - 1] != s[i] && p[j - 1] != '.')
                    { //如果前一个元素不匹配 且不为任意元素
                        dp[i + 1][j + 1] = dp[i + 1][j - 1];
                    }
                    else
                    {
                        //caa c.* -> ca c.*
                        //caa ca* -> ca ca*
                        //ca ca* -> ca ca / c ca*
                        //ca ca*a* -> ca ca*
                        dp[i + 1][j + 1] = (dp[i][j + 1] || dp[i + 1][j - 1]);// || dp[i + 1][j]不需要
                    }
                }
            }
        }
        //print(dp);
        return dp[sSize][pSize];
    }
};
