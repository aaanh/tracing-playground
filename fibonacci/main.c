#include<stdio.h>

int fib(int n) {
  if (n <= 1) return n;

  return fib(n - 1) + fib(n -2);
}

int main() {
  int a = 0, b = 1;
  int n = 30;
  printf("%d", fib(n));
  return 0;
}