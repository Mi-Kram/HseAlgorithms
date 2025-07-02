#include <iostream>

const unsigned long long BASE_NUM = 4'294'967'295;
const size_t BASE_NUM_LENGTH = 10;                

std::string multiply(std::string a, std::string b);
void addTo(std::string& a, const std::string& b);
void subtractTo(std::string& a, const std::string& b);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr); 
  
  std::string a, b;
  std::cin >> a >> b;

  std::cout << multiply(a, b) << '\n';  
  return 0;
}

std::string multiply(std::string a, std::string b) {
  size_t len = std::max(a.size(), b.size());

  if (len < BASE_NUM_LENGTH) {
    unsigned long long x = std::stoull(a);
    unsigned long long y = std::stoull(b);
    return std::to_string(x * y);
  }

  if (a.size() != len) a = std::string(len - a.size(), '0') + a;
  else if (b.size() != len) b = std::string(len - b.size(), '0') + b;
  size_t half = len / 2;

  std::string s10k(len - half, '0');
  std::string a1 = a.substr(0, half), a2 = a.substr(half);
  std::string b1 = b.substr(0, half), b2 = b.substr(half);

  // 100^k*A*B + 10^k*((A+Ar) * (B+Br) - A*B - Ar*Br) + Ar*Br

  std::string a_b = multiply(a1, b1);
  std::string ar_br = multiply(a2, b2);
  addTo(a1, a2);
  addTo(b1, b2);
  
  std::string mdl = multiply(a1, b1);
  subtractTo(mdl, a_b);
  subtractTo(mdl, ar_br);

  if (a_b != "0") a_b += s10k + s10k;
  if (mdl != "0") mdl += s10k;
  
  addTo(a_b, mdl);
  addTo(a_b, ar_br);
  return a_b;
}

void addTo(std::string& a, const std::string& b) {
  if (a.size() < b.size()) a = std::string(b.size() - a.size(), '0') + a;
  bool remember = false;

  int i = a.size() - 1;
  for (int j = b.size() - 1; j >= 0; --i, --j) {
    a[i] += b[j] - '0';
    if (remember) ++a[i];
    if (remember = a[i] > '9'; remember) a[i] -= 10;
  }

  if (!remember) return;

  for (; i >= 0; --i) {
    if (a[i] < '9') {
      ++a[i];
      return;
    }
    a[i] = '0';
  }
  a = "1" + a;
}

void subtractTo(std::string& a, const std::string& b) {
  bool remember = false;

  int i = a.size() - 1;
  for (int j = b.size() - 1; j >= 0; --i, --j) {
    a[i] -= b[j] - '0';
    if (remember) --a[i];
    if (remember = a[i] < '0'; remember) a[i] += 10;
  }

  if (remember) {
    for (; i >= 0; --i) {
      if (a[i] > '0') {
        --a[i];
        break;
      }
      a[i] = '9';
    }
  }
  
  size_t idx = 0;
  while (idx < a.size() && a[idx] == '0') ++idx;

  if (idx == a.size()) a = "0";
  else if (idx) a = a.substr(idx);
}
