给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。
111111
示例 1:

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5

算法:

为了解决这个问题，我们需要理解 “中位数的作用是什么”。在统计中，中位数被用来：

将一个集合划分为两个长度相等的子集，其中一个子集中的元素总是大于另一个子集中的元素。

这其中又分为偶数组和奇数组：

奇数组: [2 3 5] 对应的中位数为3

偶数组: [1 4 7 9] 对应的中位数为 (4 + 7) /2 = 5.5

割和第k个元素
一个数组
对于一个有序数组，对于数组A,如果在k的位置割(Cut)一下（不是割(Cut)在两数中间），那么 LMax = RMin = A[k],

两个数组
也就是我们题目的状态，我们要求得两个数组合并成一个有序数组时，第k位的元素

我们设:
Ci为第i个数组的割。

LMaxi为第i个数组割后的左元素.

RMini为第i个数组割后的右元素

首先，LMax1<=RMin1，LMax2<=RMin2 这是肯定的，因为数组是有序的，左边肯定小于右边!，而如果割(Cut)在某个数上，
则左右相等。

其次，如果我们让LMax1<=RMin2，LMax2<=RMin1 呢

那么如果左半边全小于右半边，如果左边的元素个数相加刚好等于k, 那么第k个元素就是Max(LMax1, LMax2)，这个比较好理解的，
因为Max(LMax1, LMax2)肯定是左边k个元素的最大值，因为合并后的数组是有序，第k个元素肯定前面k个元素中最大的那个。

那么如果 LMax1>RMin2，说明数组1的左边元素太大（多），我们把C1减小，C2=k-C1也就相应的增大。LMax2>RMin1同理，
把C2减小，C1=k-C2也就相应的增大。

两个数组的最大问题是，它们合并后，m+n总数可能为奇, 也可能为偶，所以我们得想法让m+n总是为偶数

通过虚拟加入‘#’，我们让m转换成2m+1 ，n转换成2n+1, 两数之和就变成了2m+2n+2，恒为偶数。

注意是虚拟加，其实根本没这一步，通过下面的转换，我们可以保证虚拟加后每个元素跟原来的元素一一对应

例如：

割在3上，C = 3，LMax=a[(3-1)/2]=A[1]，RMin=a[3/2] =A[1]，刚好都是3的位置！

割在4/7之间‘#’，C = 4，LMax=A[(4-1)/2]=A[1]=4 ，RMin=A[4/2]=A[2]=7

剩下的事情就好办了，把2个数组看做一个虚拟的数组A，A有2m+2n+2个元素，割在m+n+1处，所以我们只需找到m+n+1位置的元素和m+n+2位置的元素就行了。

左边：A[m+n+1] = Max(LMax1,LMax2)

右边：A[m+n+2] = Min(RMin1,RMin2)

==>Mid = (A[m+n+1]+A[m+n+2])/2 = (Max(LMax1,LMax2) + Min(RMin1,RMin2) )/2

最快的割(Cut)是使用二分法，

有2个数组，我们对哪个做二分呢？
根据之前的分析，我们知道了，只要C1或C2确定，另外一个也就确定了。这里，为了效率，我们肯定是选长度较短的做二分，假设为C1。

LMax1>RMin2，把C1减小，C2增大。—> C1向左二分

LMax2>RMin1，把C1增大，C2减小。—> C1向右二分

如果C1或C2已经到头了怎么办？

这种情况出现在：如果有个数组完全小于或大于中值。假定n<m, 可能有4种情况：

C1 = 0 —— 数组1整体都在右边了，所以都比中值大，中值在数组2中，简单的说就是数组1割后的左边是空了，所以我们可以假定LMax1 = INT_MIN

C1 =2n —— 数组1整体都在左边了，所以都比中值小，中值在数组2中 ，简单的说就是数组1割后的右边是空了，所以我们可以假定RMin1= INT_MAX，来保证LMax2<RMin1恒成立

C2 = 0 —— 数组2整体在右边了，所以都比中值大，中值在数组1中 ，简单的说就是数组2割后的左边是空了，所以我们可以假定LMax2 = INT_MIN

C2 = 2m —— 数组2整体在左边了，所以都比中值小，中值在数组1中, 简单的说就是数组2割后的右边是空了，为了让LMax1 < RMin2 恒成立，我们可以假定RMin2 = INT_MAX

#include <stdio.h>
#include <vector>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b)) //max究竟应该怎么用

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int n = nums1.size();//取vector的大小用size函数。
		int m = nums2.size();

		if (n > m)  //保证数组1一定最短
		{
			return findMedianSortedArrays(nums2, nums1);
		}

		// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
		int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度 永远都是2n不管单数双数

		while (lo <= hi)   //二分
		{
			c1 = (lo + hi) / 2;  //c1是二分的结果
			c2 = m + n - c1;

			LMax1 = (c1 == 0) ? INT_MIN : nums1[(c1 - 1) / 2];
			RMin1 = (c1 == 2 * n) ? INT_MAX : nums1[c1 / 2];
			LMax2 = (c2 == 0) ? INT_MIN : nums2[(c2 - 1) / 2];
			RMin2 = (c2 == 2 * m) ? INT_MAX : nums2[c2 / 2];

			if (LMax1 > RMin2)
				hi = c1 - 1;
			else if (LMax2 > RMin1)
				lo = c1 + 1;
			else
				break;
		}
		return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
	}
};


int main(int argc, char *argv[])
{
	vector<int> nums1 = { 2,3, 5 };
	vector<int> nums2 = { 1,4,7, 9 };
	
	Solution solution;
	double ret = solution.findMedianSortedArrays(nums1, nums2);
	return 0;
}

作者：bian-bian-xiong
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/4-xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-shu/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

