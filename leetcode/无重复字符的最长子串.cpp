给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

回到我们的问题，我们使用 HashSet 将字符存储在当前窗口 [i, j)（最初 j = i）中。 然后我们向右侧滑动索引 j，如果它不在 HashSet 中，我们会继续滑动 j。
直到 s[j] 已经存在于 HashSet 中。此时，我们找到的没有重复字符的最长子字符串将会以索引 i 开头。如果我们对所有的 i 这样做，就可以得到答案。




class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max ,sum = 0;//记录最大长度
        int length = 0;
	    int start = 0;//记录活动窗口起始点
	    int right = 1;//滑动窗口的宽度
	    int left = 0;//可变记录点
	    for (start = 0; start <= s.length(); start++)
	    {
		    
            for (left = start; left < right ; right++)
		    {//从窗口的起始点开始进行比对，若有相同的字符则将起始点重新设置
                
			    if (s[left] == s[right])
			        {
				        length = right - left ;
						max = (max > length) ? max : length;
                        break;
			        }
				
		    }
            sum = (sum > max) ? sum : max;
		    
	    }
	return sum;

    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0) return 0;
        unordered_set<char> lookup;
        int maxStr = 0;
        int left = 0;
        for(int i = 0; i < s.size(); i++){
            while (lookup.find(s[i]) != lookup.end()){
                lookup.erase(s[left]);
                left ++;
            }
            maxStr = max(maxStr,i-left+1);
            lookup.insert(s[i]);
    }
        return maxStr;
        
    }
};

作者：powcai
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/solution/hua-dong-chuang-kou-by-powcai/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



