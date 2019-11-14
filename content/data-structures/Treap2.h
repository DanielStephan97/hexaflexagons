/**
 * Author: HPI programming club
 * Date: 2019
 * Source: 
 * Description: alternative basic implicit Treap implementation
 * Time: $O(\log N)$
 */
mt19937 rnd(random_device{}());

struct Node {
    Node *left = nullptr, *right = nullptr;
    int x;
    uint32_t y;
    int size = 1;
    int64_t sum;

    Node(int x) : x(x), y(rnd()), sum(x) {}
};

int INF = 1'000'000'000;
int size(Node* v) { return v ? v->size : 0; }
int64_t sum(Node* v) { return v ? v->sum : 0; }

void recalc(Node* v) {
    v->size = size(v->left) + 1 + size(v->right);
    v->sum = sum(v->left) + v->x + sum(v->right);
}

void apply_trans(Node* v) {}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y >= r->y) {
        apply_trans(l);
        l->right = merge(l->right, r);
        recalc(l);
        return l;
    } else {
        apply_trans(r);
        r->left = merge(l, r->left);
        recalc(r);
        return r;
    }
}

pair<Node*, Node*> split_k(Node* v, int k) {
    if (!v) return {nullptr, nullptr};
    apply_trans(v);
    if (k < size(v->left) + 1) {
        auto [ll, lr] = split_k(v->left, k);
        v->left = lr;
        recalc(v);
        return {ll, v};
    } else {
        auto [rl, rr] = split_k(v->right, k - 1 - size(v->left));
        v->right = rl;
        recalc(v);
        return {v, rr};
    }
}
