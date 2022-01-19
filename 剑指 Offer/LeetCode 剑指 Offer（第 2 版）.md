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

**思路1：** 

先不考虑`random`指针重建一个链表，然后两层for同时遍历新旧链表的每个节点，根据在各自链表中的相同位次，在寻找旧链表每个节点的`random`指向时便可对应找到新链表每个节点的`random`指向.

时间复杂度O(n^2), 空间复杂度O(1)。 这里的的空间复杂度仅考虑辅助空间的消耗，下同

**思路2：**

仍然是先不考虑`random`指针建立一个新链表，但是在建立链表的过程中，用`map`记录下原链表每个节点与其对应的新链表的中的节点的对应关系。之后只需同时遍历一遍新旧链表，就可找到新链表每个节点的`random`指向.

```C++
Node* copyRandomList(Node* head) {
    Node *newHead = new Node(-1), *tail = newHead, *t = head;
    unordered_map<Node*, Node*> ump;
    while(t) {
        tail->next = new Node(t->val);
        tail = tail->next;
        ump[t] = tail;
        t = t->next;
    }
    tail = newHead->next, t = head;
    while(tail) {
        tail->random = ump[t->random];
        tail = tail->next;
        t = t->next;
    }
    tail = newHead->next;  // 此时tail指向真正的头节点, 逻辑上说不应该用`tail`表示
    delete newHead;
    return tail;
}
```
时间复杂度O(n), 空间复杂度O(n)

**思路3：**

交叉设置新旧节点，注意最终不能改变原链表.  

在每个旧节点后边插入其对应的新节点，即 `old_1 -> new_1 -> old_2 -> new_2 -> ... -> old_end -> new_end -> null`，则`new_k.random = old_k.random.next 或 nullptr`。 

最后再将`old_k`和`new_k`分开即可.

```C++
Node* copyRandomList(Node* head) {
    Node *t = head;
    while(t) {
        Node *theCopy = new Node(t->val);
        theCopy->next = t->next;
        t->next = theCopy;
        t = t->next->next;
    }
    t = head;
    while(t) {
        t->next->random = t->random == nullptr ? nullptr : t->random->next;
        t = t->next->next;
    }
    t = head;
    Node *vHead = new Node(-1), *newHead = vHead;
    while(t) {
        newHead->next = t->next;
        newHead = newHead->next;
        t->next = t->next->next;  // 最终不能改变原链表
        t = t->next;
    }
    newHead = vHead->next;
    delete vHead;
    return newHead;
}
```
时间复杂度O(n)，空间复杂度O(1)

## 3. 字符串

[../算法学习笔记/4. 字符串](https://github.com/mhvvv/Data_structures-and-algorithms/blob/main/%E7%AE%97%E6%B3%95%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/4.%20%E5%AD%97%E7%AC%A6%E4%B8%B2.md)

## 4. 查找算法

**有序数组上的查找一般都是二分查找**

### 剑指 Offer 03. 数组中重复的数字

[题目链接](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)

哈希

```C++
int findRepeatNumber(vector<int>& nums) {
    unordered_set<int> s;
    for(int num : nums) {
        if(s.find(num) != s.end())
            return num;
        s.insert(num);
    }
    return 0;
}
```
O(n), O(n)

### 剑指 Offer 53 - I. 在排序数组中查找数字 I

[题目链接](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/)

二分查找上下界.

```C++
int search(vector<int>& nums, int target) {
    //if(nums.size() == 0) return 0;
    int low = -1, high = -2;
    int l = 0, r = nums.size() - 1, mid;
    while(l <= r) {
        mid = l + (r-l)/2;
        if(nums[mid] == target) {
            low = mid;
            r = mid-1;
        }
        else if(nums[mid] > target) r = mid-1;
        else l = mid+1;
    }
    l = 0, r = nums.size() - 1;
    while(l <= r) {
        mid = l + (r-l)/2;
        if(nums[mid] == target) {
            high = mid;
            l = mid+1;
        }
        else if(nums[mid] > target) r = mid-1;
        else l = mid+1;
    }
    return high - low + 1;
}
```

O(nlogn), O(1)

### 剑指 Offer 53 - II. 0～n-1中缺失的数字

[题目链接](https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof/)

二分查找的具体思想都很简单,关键是如何设置边界，如何修改`l / r`指针，以及最后如何返回

**思想：**

数组长度为n，求0 -> n这n+1个数中缺少的那一个数。假设有指向数组中间位置的指针`mid = l + (r-l)/2`, 若数组中一个数字都不缺，则`nums[mid] = mid`.

即:

* 若 `nums[mid] > mid`, 则左边缺少数字, 
* 若 `n - nums[mid] > (n - 1)  - mid`, 则右边数字缺少数字. (不缺数字时, nums[n-1] = n, n - nums[mid] == (n-1) - mid) 
* 否则，不缺少数字

**具体实现：**

这里希望无论是何种情况退出二分，最后都可以只用`l`或`r`指针表示缺少的值.

(以下结论为我个人的写法总结, 实际上二分有很多种理解)

二分查找分两种情况:
* `while(l <= r); l = mid + 1, r = mid - 1`, 此种情况必然是左右闭区间，一般用于查找数组中存在的数返回mid，或确定数组中没有这个数.
* `while(l < r); l = mid + 1, r = mid`, 此种情况一般返回l或r相关的表达式，具体与谁相关，r初始为`size()`还是`size()-1`，一般是找两组不同退出方式(l右移导致/r左移导致)的样例模拟

实现二分时，首先判断应使用上述那种情况.

本题适用于第二种情况，初始化`l = 0, r = n = nums.size()`. 

最后返回的值直接就等于指针l的值.

```C++
int missingNumber(vector<int>& nums) {
    int l = 0, r = nums.size(), mid, n = nums.size();
    while(l < r) {
        mid = l + (r-l)/2;
        if(nums[mid] > mid) r = mid;
        else if(n - nums[mid] > n-1-mid) l = mid+1;
    }  
    return l;
}
```

O(logn)， O(1)

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

O(n)，O(1).


### 剑指 Offer 11. 旋转数组的最小数

[题目链接](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/)

这必然是让你设计O(logn)时间复杂度的查找算法.   

`二分查找`

若数组中没有重复元素，则问题简化为：[153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)

(以下，为了更形象的理解，可以画出折线图，参考官方题解中的图)

收先明确，最小值一定比其后边所有位置上的元素都小.

* 如果nums[mid] > nums[r]，又min_element < nums[r]，则最小值一定在mid的右边，更新 l = mid + 1；
* 如果nums[mid] < nums[r]，则说明最小值一定在mid左边或就是mid所在位置上的数，更新 r = mid

这里需要考虑，最后应该如何返回最小值. 对于一般的二分查找，当nums[mid] == target时，只需要返回mid即可，但这里我们并不知道target是啥，所以不能使用 == 时返回。

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
但我们可以肯定的是，无论numbers[r]是不是最小值，左边都有一个它的代替品numbers[mid]，这时我们可以大胆忽略右端点r.

```C++
int minArray(vector<int>& numbers) {
    int l = 0, r = numbers.size() - 1, mid;
    while(l < r) {
        mid = l + (r-l)/2;
        if(numbers[mid] > numbers[r]) l = mid + 1;
        else if(numbers[mid] < numbers[r]) r = mid;
        // ==
        else --r;

    }
    return numbers[r];
}
```

时间复杂度：平均O(logn), 最差O(n)

空间复杂度：O(1)

### 剑指 Offer 50. 第一个只出现一次的字符

[题目链接](https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/)

哈希, 一次遍历建立hash_map统计各字符出现次数, 一次遍历寻找只出现一次的字符.

```C++
char firstUniqChar(string s) {
    unordered_map<char, int> ump;
    for(char ch : s) 
        ++ump[ch];
    for(char ch : s) {
        if(ump[ch] == 1) 
            return ch;
    }
    return ' ';     
}
```

O(n), O(26)

弱弱的问一句：官方题解是在憋本科毕设么？















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

