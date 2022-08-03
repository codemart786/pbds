//Date: 03-08-22 //Author: Rishabh Paul
//Problem Link: https://leetcode.com/problems/merge-intervals/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& a) {
        vector<pair<int, int>> intervals;
        for (vector<int> x: a) {
            intervals.push_back({x[0], x[1]});
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;
        int n = intervals.size();
        for (int i = 0; i < n;) {
            int j = i + 1;
            int R = intervals[i].second;
            while(j < n && intervals[j].first <= R) {
                R = max(R, intervals[j].second);
                j++;   
            }
            ans.push_back(vector<int>{ intervals[i].first, R });
            i = j;
        }
        return ans;
    }
};
