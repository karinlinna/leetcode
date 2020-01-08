给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：
输入: "cbbd"
输出: "bb"

解法 1：暴力法
菜鸡的我第一想法只能想到暴力法，遍历各种可能结果。

C++
class Solution {
public:
    string longestPalindrome(string s) {
        string res="";//存放结果
        string temp="";//存放子串
        for(int i=0;i<s.length();i++)
        {
            for(int j=i;j<s.length();j++)
            {
                temp=temp+s[j];
                string tem=temp;//tem存放子串反转结果
                std::reverse(tem.begin(),tem.end());//反转
                if(temp==tem)
                    res=res.length()>temp.length()?res:temp;
            }
            temp="";
        }
        return res;
    }
};

解法 2：//感觉和解法一没有什么区别
将字符串 s 反转得到字符串 rev，再求他们的最长公共子串，再判断该最长公共子串是否就是我们要找的最长回文子串。

C++
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.length()==1) return s;//大小为1的字符串必为回文串
        string rev=s;//rev存放s反转结果
        string res;//存放结果
        std::reverse(rev.begin(),rev.end());
        if(rev==s) return s;
        int len=0;//存放回文子串的长度
        for(int i=0;i<s.length();i++)//查找s与rev的最长公共子串
        {
            string temp;//存放待验证子串
            for(int j=i;j<s.length();j++)
            {
                temp=temp+s[j];
                if(len>=temp.length())
                    continue;
                else if(rev.find(temp)!=-1)//在rev中找到temp
                {
                    string q=temp;//q用来验证temp是否是回文子串
                    std::reverse(q.begin(),q.end());
                    if(q==temp)
                    {
                        len=temp.length();
                        res=temp;
                    }
                }
                else break;
            }
            temp="";
        }
        return res;
    }
};

解法 3：动态规划
初始状态：
dp[i][i]=1; //单个字符是回文串
dp[i][i+1]=1 if s[i]=s[i+1]; //连续两个相同字符是回文串
实现代码：
C++
class Solution {
public:
    string longestPalindrome(string s) {
        int len=s.size();
        if(len==0||len==1)
            return s;
        int start=0;//回文串起始位置
        int max=1;//回文串最大长度
        vector<vector<int>>  dp(len,vector<int>(len));//定义二维动态数组
        for(int i=0;i<len;i++)//初始化状态
        {
            dp[i][i]=1;
            if(i<len-1&&s[i]==s[i+1])
            {
                dp[i][i+1]=1;
                max=2;
                start=i;
            }
        }
        for(int l=3;l<=len;l++)//l表示检索的子串长度，等于3表示先检索长度为3的子串
        {
            for(int i=0;i+l-1<len;i++)
            {
                int j=l+i-1;//终止字符位置
                if(s[i]==s[j]&&dp[i+1][j-1]==1)//状态转移
                {
                    dp[i][j]=1;
                    start=i;
                    max=l;
                }
            }
        }
        return s.substr(start,max);//获取最长回文子串
    }
};
解法 4：中心扩展法

回文中心的两侧互为镜像。因此，回文可以从他的中心展开，并且只有 2n-1 个这样的中心（一个元素为中心的情况有 n 个，两个元素为中心的情况有 n-1 个）

实现代码：
C++
class Solution {
public:
    string longestPalindrome(string s) {
        int len=s.size();
        if(len==0||len==1)
            return s;
        int start=0;//记录回文子串起始位置
        int end=0;//记录回文子串终止位置
        int mlen=0;//记录最大回文子串的长度
        for(int i=0;i<len;i++)
        {
            int len1=expendaroundcenter(s,i,i);//一个元素为中心
            int len2=expendaroundcenter(s,i,i+1);//两个元素为中心
            mlen=max(max(len1,len2),mlen);
            if(mlen>end-start+1)
            {
                start=i-(mlen-1)/2;
                end=i+mlen/2;
            }
        }
        return s.substr(start,mlen);
        //该函数的意思是获取从start开始长度为mlen长度的字符串
    }
private:
    int expendaroundcenter(string s,int left,int right)
    //计算以left和right为中心的回文串长度
    {
        int L=left;
        int R=right;
        while(L>=0 && R<s.length() && s[R]==s[L])
        {
            L--;
            R++;
        }
        return R-L-1;
    }
};

作者：chenlele
链接：https://leetcode-cn.com/problems/longest-palindromic-substring/solution/zui-chang-hui-wen-zi-chuan-c-by-gpe3dbjds1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
