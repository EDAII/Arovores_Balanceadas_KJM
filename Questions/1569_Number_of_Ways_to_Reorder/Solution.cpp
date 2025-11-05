#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 1e9 + 7;
enum Color { RED, BLACK };

struct Node {
    int val;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v) : val(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* gp = z->parent->parent;
            if (!gp) break;
            if (z->parent == gp->left) {
                Node* uncle = gp->right;
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateRight(gp);
                }
            } else {
                Node* uncle = gp->left;
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rotateLeft(gp);
                }
            }
        }
        if (root) root->color = BLACK;
    }

    void deleteSubtree(Node* node) {
        if (!node) return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() { deleteSubtree(root); }

    void insert(int val) {
        Node* z = new Node(val);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (z->val < x->val) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (!y) root = z;
        else if (z->val < y->val) y->left = z;
        else y->right = z;

        fixInsert(z);
    }
};

class Solution {
private:
    vector<long long> fact, invFact;

    long long modPow(long long a, long long e) {
        long long r = 1;
        while (e) {
            if (e & 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }

    void buildFactorials(int n) {
        fact.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
        invFact.assign(n + 1, 1);
        invFact[n] = modPow(fact[n], MOD - 2);
        for (int i = n - 1; i >= 0; --i) invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    inline long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return (((fact[n] * invFact[r]) % MOD) * invFact[n - r]) % MOD;
    }

    pair<long long,int> dfs(const vector<int>& nums) {
        int n = (int)nums.size();
        if (n <= 2) return {1LL, n};

        vector<int> left; left.reserve(n/2);
        vector<int> right; right.reserve(n/2);

        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[0]) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }

        auto L = dfs(left);
        auto R = dfs(right);

        long long ways = nCr((int)left.size() + (int)right.size(), (int)left.size());
        ways = ways * L.first % MOD;
        ways = ways * R.first % MOD;
        return {ways, n};
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return 0;

        buildFactorials(n);

        RedBlackTree rbt;
        for (int v : nums) rbt.insert(v);

        auto res = dfs(nums);
        return (int)((res.first - 1 + MOD) % MOD);
    }
};