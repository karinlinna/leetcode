给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

示例 1:

输入: 123
输出: 321
 示例 2:

输入: -123
输出: -321
示例 3:

输入: 120
输出: 21
注意:

假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−231,  231 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。

不会写的原因，想把它放在一个数组里，然后反转这个数组即可。但是，不会数组和指针。动态分配内存也不会。

class Solution {
public:
    int reverse(int x) {
        int *a;
        int num,t;
        if ( x>2147483647 || x< -2147483648){
            return 0 ;
        }
        t = x;
        while(t>0){
            t=t/10;
            num++;
        }
        a = new int[num];
        for( int i = 0;i<num ; i++){
            t = x%10;
            x = x/10;
            a[i] = t;
        }
        return a[num];
    }
};

class Solution {
    public int reverse(int x) {
        int ans = 0;
        while (x != 0) {
            int pop = x % 10;
            if (ans > Integer.MAX_VALUE / 10 || (ans == Integer.MAX_VALUE / 10 && pop > 7)) 
                return 0;
            if (ans < Integer.MIN_VALUE / 10 || (ans == Integer.MIN_VALUE / 10 && pop < -8)) 
                return 0;
            ans = ans * 10 + pop;
            x /= 10;
        }
        return ans;
    }
}

作者：guanpengchn
链接：https://leetcode-cn.com/problems/reverse-integer/solution/hua-jie-suan-fa-7-zheng-shu-fan-zhuan-by-guanpengc/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。