#include <iostream>

struct Item {
  int value, priority;
  long long sum;
  int amount;
  Item *l, *r;

  Item(int Value) : value(Value), priority(rand()), sum(Value), amount(1), l(nullptr), r(nullptr) {
  }
};

int count(Item* t) {
  return t ? t->amount : 0;
}

long long getSum(Item* t) {
  return t ? t->sum : 0;
}

void update(Item* t) {
  if (t) {
    t->amount = 1 + count(t->l) + count(t->r);
    t->sum = t->value + getSum(t->l) + getSum(t->r);
  }
}

void merge(Item* l, Item* r, Item*& t) {
  if (!l || !r) t = l ? l : r;
  else if (l->priority > r->priority) merge(l->r, r, l->r), t = l;
  else merge(l, r->l, r->l), t = r;
  update(t);
}

void split(Item* t, Item*& l, Item*& r, int pos) {
  if (!t) return void(l = r = nullptr);
  if (pos <= count(t->l)) split(t->l, l, t->l, pos), r = t;
  else split(t->r, t->r, r, pos - 1 - count(t->l)), l = t;
  update(t);
}

long long sum(int l, int r, Item*& t1, Item*& t2) {
  if (l > r) return 0;

  int L1 = (l + 1) / 2, R1 = r / 2;
  int L2 = l / 2, R2 = (r + 1) / 2 - 1;

  Item *a1, *b1, *c1, *a2, *b2, *c2;

  split(t1, a1, b1, L1);
  split(b1, b1, c1, R1 - L1 + 1);
  split(t2, a2, b2, L2);
  split(b2, b2, c2, R2 - L2 + 1);

  long long res = getSum(b1) + getSum(b2);

  merge(a1, b1, b1);
  merge(b1, c1, t1);
  merge(a2, b2, b2);
  merge(b2, c2, t2);

  return res;
}

void swap(int l, int r, Item*& t1, Item*& t2) {
  int L1 = (l + 1) / 2, R1 = r / 2;
  int L2 = l / 2, R2 = (r + 1) / 2 - 1;

  Item *a1, *b1, *c1, *a2, *b2, *c2;

  split(t1, a1, b1, L1);
  split(b1, b1, c1, R1 - L1 + 1);
  split(t2, a2, b2, L2);
  split(b2, b2, c2, R2 - L2 + 1);

  merge(a1, b2, b2);
  merge(b2, c1, t1);
  merge(a2, b1, b1);
  merge(b1, c2, t2);
}

int main() {
  int test = 1;
  int n, m, num, type, a, b;

  while (true) {
    std::cin >> n >> m;
    if (!n && !m) break;

    Item *t1 = nullptr, *t2 = nullptr;
    std::cout << "Swapper " << test++ << ":\n";

    for (int i = 0; i < n; i++) {
      std::cin >> num;
      if (i & 1) merge(t2, new Item(num), t2);
      else merge(t1, new Item(num), t1);
    }

    for (int i = 0; i < m; i++) {
      std::cin >> type >> a >> b;
      if (type == 1) swap(a - 1, b - 1, t1, t2);
      else std::cout << sum(a - 1, b - 1, t1, t2) << '\n';
    }

    std::cout << '\n';
  }

  return 0;
}
