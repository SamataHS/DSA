#include <bits/stdc++.h>
using namespace std;

class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        vector<string> top5;

        TrieNode() {
            for(int i = 0; i < 26; i++)
                children[i] = NULL;
        }
    };

    TrieNode* root;
    unordered_map<string, int> freq;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert word
    void insert(string word) {
        freq[word]++;  // increase frequency
        TrieNode* node = root;

        for(char c : word) {
            int idx = c - 'a';

            if(node->children[idx] == NULL)
                node->children[idx] = new TrieNode();

            node = node->children[idx];

            updateTop5(node, word);
        }
    }

    // Maintain top 5 frequent words
    void updateTop5(TrieNode* node, string word) {

        // If not already present, add
        if(find(node->top5.begin(), node->top5.end(), word) == node->top5.end())
            node->top5.push_back(word);

        // Sort by frequency (descending)
        sort(node->top5.begin(), node->top5.end(), [&](string &a, string &b) {
            return freq[a] > freq[b];
        });

        // Keep only top 5
        if(node->top5.size() > 5)
            node->top5.pop_back();
    }

    // Get top 5 suggestions for prefix
    vector<string> getSuggestions(string prefix) {
        TrieNode* node = root;

        for(char c : prefix) {
            int idx = c - 'a';
            if(node->children[idx] == NULL)
                return {};   // no suggestions
            node = node->children[idx];
        }

        return node->top5;   // O(1) return after O(L) traversal
    }
};
