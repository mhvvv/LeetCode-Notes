[题集](https://leetcode-cn.com/problem-list/xb9nqhhg/)

[学习计划](https://leetcode-cn.com/study-plan/lcof/?progress=nwn96jd)

## 1. 栈与队列

### 剑指 Offer 09. 用两个栈实现队列

[题目链接](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

入队操作的时候，若出栈不为空，不需要将出栈中的元素全部移到入栈中.

对应的，只有出栈为且进行出队操作时，才需要将入栈中的元素全部移到出栈中.

这样做可以避免同一个元素在两个栈间反复移动，浪费资源.

```C++
class CQueue {
public:
    CQueue() {
    }
    
    void appendTail(int value) {
        s_in.push(value);
    }
    
    int deleteHead() {
        if(s_out.empty()) {
            while(!s_in.empty()) {
                s_out.push(s_in.top());
                s_in.pop();
            }
        }
        if(s_out.empty()) return -1;
        int theHead = s_out.top();
        s_out.pop();
        return theHead;
    }

private:
    stack<int> s_in, s_out;
};
```
每个元素都只会被在两个栈间移动一次，每个元素时间O(1)，总时间复杂度O(n).

空间复杂度O(n).

### 剑指 Offer 30. 包含min函数的栈

[题目链接](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/)

思路: 双栈实现MinStack

一个栈(s1)正常，另外保证一个栈(s2)的元素从栈底到栈顶单调不增，用于实现`min()`函数.

* `.min()`：只需返回`s2.top()`;
* `.push()`：是否加入s2根据s2能否维持单调性;
* `.pop()`：若`s2.top() == s1.top()`， s2才出栈;
* `.top()`：返回`s1.top()`.

```C++
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() { }
    
    void push(int x) {
        s1.push(x);
        if(s2.empty() || x <= s2.top()) s2.push(x);
    }
    
    void pop() {
        if(s1.top() == s2.top()) s2.pop();
        s1.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int min() {
        return s2.top();
    }

private:
    stack<int> s1;
    stack<int> s2;
};
```

所有操作时间复杂度O(1)

## 2. 链表

### 剑指 Offer 06. 从尾到头打印链表

[题目链接](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

逆序输出链表，reverse() 或 递归.

**reverse()**
```C++
vector<int> reversePrint(ListNode* head) {
    vector<int> result;
    while(head != NULL) {
        result.push_back(head->val);
        head  = head->next;
    }
    reverse(result.begin(), result.end());
    return result;
}
```
**递归**
```C++
class Solution {
public:
    vector<int> result;
    void recursion(ListNode *head) {
        if(head == NULL) return;
        recursion(head->next);
        result.push_back(head->val);
    }
    vector<int> reversePrint(ListNode* head) {
        recursion(head);
        return result;
    }
};
```

时间复杂度O(n).

空间复杂度O(n).

### 剑指 Offer 24. 反转链表

[题目链接](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/)

头插法原地反转链表

```C++
ListNode* reverseList(ListNode* head) {
    ListNode *vHead = new ListNode;
    while(head) {
        ListNode *t = head->next;
        head->next = vHead->next;
        vHead->next = head;
        head = t;
    }
    head = vHead->next;
    delete vHead;
    return head;
}
```
时间复杂度O(n), 空间复杂度O(1)

### 剑指 Offer 35. 复杂链表的复制

[题目链接](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/)



---

---

### 剑指 Offer 03. 数组中重复的数字

[题目链接](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

遍历

```C++
hash: (unordered_) set / map

bool[]
```

时间复杂度:  bool - O(n),   hash:  不小于O(n)，不大于O(nlogn).

空间复杂度:  O(n)

### 剑指 Offer 04. 二维数组中的查找

[题目链接](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/)

**评论区金手指:**

站在右上角看, 这个矩阵其实就像是一个`Binary Search Tree`。然后，聪明的大家应该知道怎么做了.

```C++
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if(matrix.size() == 0) return false;

    int x = matrix.size()-1, y = 0, m = matrix[0].size();
    while(x >= 0 && y < m) {
        int cur = matrix[x][y];
        if(cur == target) return true;
        else if(cur > target) --x;
        else ++y;
    }
    return false;
}
```

时间复杂度O(n).

空间复杂度O(1).

**常规想法:**

有序数组查找，必然`二分查找`. 即若target ∈ [matrix[x][0], matrix[x][m-1]] , 则对x行进行二分查找.

```C++
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
    if(matrix.size() == 0 || matrix[0].size() == 0) return false;

    int m = matrix[0].size() - 1;
    for(int i = 0; i < matrix.size(); ++i) {
        if(target < matrix[i][0] || target > matrix[i][m]) continue;
        int l = 0, r = m, mid;
        while(l <= r) {
            mid = l + (r-l)/2;
            if(matrix[i][mid] == target) return true;
            else if(matrix[i][mid] > target) r = mid - 1;
            else l = mid + 1;
        }
    }
    return false;
}
```

时间复杂度O(nlogm).

空间复杂度O(1).



### 剑指 Offer 07. 重建二叉树

[题目链接](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

经典数据结构问题，期末考试必考题.

前序: [根，[左子树], [右子树]]

中序: [[左子树], 根，[右子树]]

建树就是不断建根结点， 当前树的根结点必然为当前树前序遍历序列的第一个值，然后在其中序序列中找出这个值.

对左右子树，前序序列和后序序列的结点个数相同，又因为在中序序列中，找出当前树的根后，就可以得出左右子树的结点个数，前序序列中左子树的结点必然排在右子树结点的前边，因此可以用结点数来划分左右子树的前序遍历序列.

```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
vector<int> preorder, inorder;
unordered_map<int, int> umpVin;  // 将操作“查找val在vector中的位置”时间复杂度下降到O(1)
void cursion(TreeNode *&root, int lp, int rp, int li, int ri) {
    if(lp > rp) return;
    root = new TreeNode(preorder[lp]);
    int k = umpVin[preorder[lp]]; 
    cursion(root->left, lp+1, lp+(k-li), li, k-1);
    cursion(root->right, rp-(ri-k)+1, rp, k+1, ri);
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if(preorder.size() == 0) return nullptr;
    this->preorder = preorder;
    this->inorder = inorder;
    for(int i=0; i<preorder.size(); ++i) 
        umpVin[inorder[i]] = i;
    TreeNode *root;
    cursion(root, 0, preorder.size()-1, 0, inorder.size()-1);
    return root;
}
```

找n次根结点，时间复杂度O(n).

空间复杂度O(n).


### 剑指 Offer 10- I. 斐波那契数列

[题目链接](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)

`dp`, 没啥好说的. 来个滚动数组吧

```C++
int fib(int n) {
    int dp[] = {0, 1};
    constexpr int mod = 1e9 + 7;
    for(int i=2; i<=n; ++i)
        dp[i % 2] = (dp[0] + dp[1]) % mod;
    return dp[n % 2];
}
```

时间复杂度O(n).

空间复杂度O(1).

### 剑指 Offer 10- II. 青蛙跳台阶问题

[题目链接](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

`dp`， 和10- I. 斐波那契数列完全相同.

```C++
int numWays(int n) {
    if(n == 0) return 1;
    
    int dp[] = {1, 2};
    constexpr int mod = 1e9 + 7;
    for(int i=2; i<n; ++i)
        dp[i % 2] = (dp[0] + dp[1]) % mod;
    return dp[(n-1) % 2];
}
```

时间复杂度O(n).

空间复杂度O(1).

### 剑指 Offer 11. 旋转数组的最小数

[题目链接](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)

这必然是让你设计O(logn)时间复杂度的查找算法.   

`二分查找`

若数组中没有重复元素，则问题简化为：[153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

(以下，为了更形象的理解，可以画出折线图，参考官方题解中的图)

收先明确，最小值一定比其后边所有位置上的元素都小.

while(l <= r):
* 如果nums[mid] > nums[r]，又min_element < nums[r]，则最小值一定在mid的右边，更新 l = mid + 1；
* 如果nums[mid] < nums[r]，则说明最小值一定在mid左边，更新 r = mid - 1

这里需要考虑，最后应该如何返回最小值. 对于一般的二分查找，当nums[mid] == target时，只需要返回mid即可，但这里我们并不知道target是啥，所以不能使用 == 时返回。

考虑此种情况: l < mid < r, nums[mid] = min_element, nums[mid] < nums[r], 此时若更新r = mid - 1, 则永远找不到最小值.

对于二分查找解决target不具体给出的问题，往往采用以下方式:
```
while(l < r) {
    >： l = mid + 1
    else( <= ): r = mid 而非 mid - 1，这样可以保证要查找的位置不会被跳过  
}
return nums[r]
```
好好体会吧. 对于不那么聪明的选手，模拟是最好的学习方式.

**Solution：**

```C++
int findMin(vector<int>& nums) {
    int l = 0, r = nums.size() - 1, mid;
    while(l < r) {
        mid = l + (r-l)/2;
        if(nums[mid] > nums[r]) l = mid + 1;
        else r = mid;
    }
    return nums[r];
}
```

时/空: O(logn) / O(1)

**回到原题目：**

(这里仍建议画出折线图, 我知道聪明的你已经在脑里画好了)

与上面的153.题相比，数组中的数字允许重复.

多了numbers[mid] == numbers[r]的情况,

对于这种情况，我们不知道最小值到底就是numbers[mid]，还是在在mid的左边，还是在mid的右边. 即可能出现以下情况：
```txt
{3, 3, 1, 3}

l = 0, r = 3, mid = 1

nums[mid] = 3 = nums[r]. 
```
但我们可以肯定的是，最小值一定不会出现在r的后边，只能出现在r的左边且不会是当前r所在的位置(while(l<r)，在l < r的条件下，l+(r-l)/2 必定小于r)。在这种情况下我们只需要--r。

```C++
int minArray(vector<int>& numbers) {
    int l = 0, r = numbers.size() - 1, mid;
    while(l < r) {
        mid = l + (r-l)/2;
        if(numbers[mid] > numbers[r]) l = mid + 1;
        else if(numbers[mid] < numbers[r]) r = mid;
        // ==
        else r = mid;

    }
    return numbers[r];
}
```

时间复杂度：平均O(logn), 最差O(n)

空间复杂度：O(1)
