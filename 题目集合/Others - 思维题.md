[1996. 游戏中弱角色的数量](https://leetcode-cn.com/problems/the-number-of-weak-characters-in-the-game/)

按攻击力从高到底排序，然后从前往后枚举，记录防御力最大值，若当前枚举的角色防御力小于已知防御力最大值，则弱角色数+1.

攻击力相同的应将防御力小的排在前边.

```C++
class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        sort(properties.begin(), properties.end(), [](const vector<int> & a, const vector<int> & b) {
            return a[0] == b[0] ? (a[1] < b[1]) : (a[0] > b[0]);
        });

        int maxDefence = -1;
        int result = 0;
        for(auto p : properties) {
            if(p[1] < maxDefence) ++result;
            else maxDefence = p[1];
        }
        return result;
    }

    static bool cmp(vector<int> v1, vector<int> v2) {
        return v1[0] == v2[0] ? v1[1] < v2[1] : v1[0] > v2[0];
    }
};

O(nlogn), 
O(logn)，为排序时栈的递归深度 
```

还可以用单调栈求解.
