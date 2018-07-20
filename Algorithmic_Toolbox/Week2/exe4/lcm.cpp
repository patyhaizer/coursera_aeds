#include <iostream>
#include <cassert>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {
    long long ret = a/gcd(a, b);
    ret = ret * b;
    return ret;
}

void test_solution() {
    for (int i = 0; i < 10000; ++ i) {
        int a = (rand() % 10000) + 1;
        int b = (rand() % 10000) + 1;
        if (b > a) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        std::cout << "LCM(" << a << ", " << b << ")" << std::endl;
        int naive = lcm_naive(a,b);
        std::cout << "naive: " << naive << std::endl;
        int fast = lcm_fast(a,b);
        std::cout << "fast: " << fast << std::endl;
        assert (fast == naive);
    }
}

int main() {
  int a, b;
  std::cin >> a >> b;
  if (b > a) {
      int tmp = a;
      a = b;
      b = tmp;
  }
  //test_solution();
  //std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
