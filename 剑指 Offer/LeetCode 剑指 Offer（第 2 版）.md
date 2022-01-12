[题集](https://leetcode-cn.com/problem-list/xb9nqhhg/)

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



### 剑指 Offer 06. 从尾到头打印链表

[题目链接](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

逆序输出链表，reverse() 或 递归.

**reverse()**
```C++
vector<int> printListFromTailToHead(ListNode* head) {
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
vector<int> result;
void recursion(ListNode *head) {
    if(head == NULL) return;
    dfs(head->next);
    result.push_back(head->val);
}
vector<int> printListFromTailToHead(ListNode* head) {
    recursion(head);
    return result;
}
```

时间复杂度O(n).

空间复杂度O(n).

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
每个元素都只会被在两个栈间移动一次，每个元素时间O(1)，时间复杂度O(n).

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
