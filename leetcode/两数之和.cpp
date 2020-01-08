题目：给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:
给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

方法一：用减法遍历 i = target - a[0]
方法二：暴力法
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i,j;
        for(i=0;i<nums.size()-1;i++)
        {
            for(j=i+1;j<nums.size();j++)
            {
                if(nums[i]+nums[j]==target)
                {
                   return {i,j};
                }
            }
        }
        return {i,j};
    };
};

方法三：两遍哈希表

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> a;//建立hash表存放数组元素
        vector<int> b(2,-1);//存放结果 元素个数为2 值为-1
        for(int i=0;i<nums.size();i++)
            a.insert(map<int,int>::value_type(nums[i],i));
        for(int i=0;i<nums.size();i++)
        {
            if(a.count(target-nums[i])>0&&(a[target-nums[i]]!=i))
            //判断是否找到目标元素且目标元素不能是本身
            {
                b[0]=i;
                b[1]=a[target-nums[i]];
                break;
            }
        }
        return b;
    };
};


