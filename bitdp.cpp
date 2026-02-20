#include <bits/stdc++.h>
using namespace std;

int minCostAssignment(vector<vector<int>>& cost) {
    int n = cost.size();
    int totalMasks = 1 << n;

    vector<int> dp(totalMasks, INT_MAX);
    dp[0] = 0;  // no workers assigned

    for(int mask = 0; mask < totalMasks; mask++) {

        int task = __builtin_popcount(mask);  // how many tasks done

        for(int worker = 0; worker < n; worker++) {

            if((mask & (1 << worker)) == 0) {  // worker free

                int newMask = mask | (1 << worker);

                dp[newMask] = min(dp[newMask],
                                  dp[mask] + cost[worker][task]);
            }
        }
    }

    return dp[totalMasks - 1];
}
