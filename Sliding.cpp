#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // stores indices
    vector<int> result;

    for(int i = 0; i < nums.size(); i++) {

        // 1️⃣ Remove elements out of window
        if(!dq.empty() && dq.front() == i - k)
            dq.pop_front();

        // 2️⃣ Remove smaller elements from back
        while(!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();

        // 3️⃣ Insert current index
        dq.push_back(i);

        // 4️⃣ Add result after first window is complete
        if(i >= k - 1)
            result.push_back(nums[dq.front()]);
    }

    return result;
}
