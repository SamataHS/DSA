#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void build(vector<int>& arr, int node, int start, int end) {
        if(start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(arr, 2*node+1, start, mid);
        build(arr, 2*node+2, mid+1, end);

        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

    void update(int index, int value) {
        updateUtil(0, 0, n-1, index, value);
    }

    void updateUtil(int node, int start, int end, int index, int value) {
        if(start == end) {
            tree[node] = value;
            return;
        }

        int mid = (start + end) / 2;

        if(index <= mid)
            updateUtil(2*node+1, start, mid, index, value);
        else
            updateUtil(2*node+2, mid+1, end, index, value);

        tree[node] = max(tree[2*node+1], tree[2*node+2]);
    }

    int queryMax(int L, int R) {
        return queryUtil(0, 0, n-1, L, R);
    }

    int queryUtil(int node, int start, int end, int L, int R) {
        // No overlap
        if(R < start || end < L)
            return INT_MIN;

        // Complete overlap
        if(L <= start && end <= R)
            return tree[node];

        // Partial overlap
        int mid = (start + end) / 2;

        return max(
            queryUtil(2*node+1, start, mid, L, R),
            queryUtil(2*node+2, mid+1, end, L, R)
        );
    }
};
