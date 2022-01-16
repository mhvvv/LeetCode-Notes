// KMP模板    
// 王道讲的挺好
// https://leetcode-cn.com/problems/repeated-substring-pattern/solution/zhong-fu-de-zi-zi-fu-chuan-by-leetcode-solution/

#include <iostream>
#include <vector>
using namespace std;

void get_next(vector<int> &next, const string &T) {
    // google
    int i=0, j=-1;
    next[0] = -1;
    while(i < T.size()) {
        if(j == -1 || T[i] == T[j]) {
            ++j;
            ++i;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return ;
}
int index_kmp(const string &S, const string &T) {
    // googlugoogleabc
    // google
    // 012345
        vector<int>next(T.size()+1);   // 这里一定要+1 
        /*
         * +1 原因:
         * 首先要明确, 我们的字符串下标是从0开始
         * next[i] 记录的是前i-1个字符组成的字符串 的 最长相同前后缀长度 (也即匹配失败后j指针要指向的位置); 
         * 前T.size()的结果 存到next[T.size()]
         */
        get_next(next, T);
        int i=0, j=0; 
        while(i < S.size() && j < int(T.size())) {   // T.size()为一种无符号数，与负数相比可能会有意想不到的错误
            if(j == -1 || S[i] == T[j]) {
                ++i;
                ++j;
            } else {
                j = next[j];
            }
        }
        if(j == T.size())
            return i-T.size();
        return -111;
}


int main()
{
    int index = index_kmp("hello", "ll");
    cout << index << endl;
    
    getchar();
    return 0;
}
