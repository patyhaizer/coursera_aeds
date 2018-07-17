#include <iostream>
#include <cassert>
#include <stdlib.h>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
    if (b == 0)
        return a;
    return gcd_fast(b, a % b);
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
        std::cout << "GCD(" << a << ", " << b << ")" << std::endl;
        int naive = gcd_naive(a,b);
        std::cout << "naive: " << naive << std::endl;
        int fast = gcd_fast(a,b);
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
  //std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_fast(a, b) << std::endl;
  //test_solution();
  return 0;
}
