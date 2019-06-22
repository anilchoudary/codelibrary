#include <bits/stdc++.h>

using namespace std;

// https://cp-algorithms.com/data_structures/treap.html

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int key, prio, size;
    Node *l, *r;

    Node(int key) : key(key), prio(rng()), size(1), l(nullptr), r(nullptr) {}

    void update() {
        size = 1 + get_size(l) + get_size(r);
    }

    static int get_size(Node *node) {
        return node == nullptr ? 0 : node->size;
    }
};

using pNode = Node *;

void split(pNode t, int key, pNode &l, pNode &r) {
    if (!t)
        l = r = nullptr;
    else if (key < t->key)
        split(t->l, key, l, t->l), r = t, t->update();
    else
        split(t->r, key, t->r, r), l = t, t->update();
}

void merge(pNode &t, pNode l, pNode r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prio > r->prio)
        merge(l->r, l->r, r), t = l, t->update();
    else
        merge(r->l, l, r->l), t = r, t->update();
}

void insert(pNode &t, pNode it) {
    if (!t)
        t = it;
    else if (it->prio > t->prio)
        split(t, it->key, it->l, it->r), t = it, t->update();
    else
        insert(it->key < t->key ? t->l : t->r, it), t->update();
}

void erase(pNode &t, int key) {
    if (t->key == key)
        merge(t, t->l, t->r);
    else
        erase(key < t->key ? t->l : t->r, key), t->update();
}

int kth(pNode root, int k) {
    if (k < Node::get_size(root->l))
        return kth(root->l, k);
    else if (k > Node::get_size(root->l))
        return kth(root->r, k - Node::get_size(root->l) - 1);
    return root->key;
}

void print(pNode t) {
    if (!t)
        return;
    print(t->l);
    cout << t->key << endl;
    print(t->r);
}

// usage example
int main() {
    pNode t1 = nullptr;
    int a1[] = {1, 2};
    for (int x: a1)
        insert(t1, new Node(x));

    pNode t2 = nullptr;
    int a2[] = {7, 4, 5};
    for (int x: a2)
        insert(t2, new Node(x));

    pNode t = nullptr;
    merge(t, t1, t2);

    for (int i = 0; i < t->size; ++i) {
        cout << kth(t, i) << endl;
    }
}
