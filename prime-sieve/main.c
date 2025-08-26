#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void sieve_iterative(int n)
{
  bool *prime = (bool *)malloc((n + 1) * sizeof(bool));
  memset(prime, true, (n + 1) * sizeof(bool));

  prime[0] = prime[1] = false; // 0 and 1 are not prime

  for (int p = 2; p * p <= n; p++)
  {
    if (prime[p])
    {
      // Mark all multiples of p as not prime
      for (int i = p * p; i <= n; i += p)
      {
        prime[i] = false;
      }
    }
  }

  printf("Primes up to %d (iterative): ", n);
  for (int i = 2; i <= n; i++)
  {
    if (prime[i])
    {
      printf("%d ", i);
    }
  }
  printf("\n");

  free(prime);
}

void mark_multiples_recursive(bool *prime, int p, int current, int n)
{
  if (current > n)
  {
    return;
  }

  prime[current] = false;
  mark_multiples_recursive(prime, p, current + p, n);
}

void sieve_recursive_helper(bool *prime, int p, int n)
{
  if (p * p > n)
  {
    return;
  }

  if (prime[p])
  {
    // Mark multiples of p starting from p*p
    mark_multiples_recursive(prime, p, p * p, n);
  }

  // Find next prime
  int next_p = p + 1;
  while (next_p * next_p <= n && !prime[next_p])
  {
    next_p++;
  }

  sieve_recursive_helper(prime, next_p, n);
}

void sieve_recursive(int n)
{
  bool *prime = (bool *)malloc((n + 1) * sizeof(bool));
  memset(prime, true, (n + 1) * sizeof(bool));

  prime[0] = prime[1] = false; // 0 and 1 are not prime

  sieve_recursive_helper(prime, 2, n);

  printf("Primes up to %d (recursive): ", n);
  for (int i = 2; i <= n; i++)
  {
    if (prime[i])
    {
      printf("%d ", i);
    }
  }
  printf("\n");

  free(prime);
}

void sieve_divide_conquer(bool *prime, int start, int end, int n)
{
  if (start > end)
  {
    return;
  }

  // Base case: process single number
  if (start == end)
  {
    if (start >= 2 && prime[start])
    {
      // Mark multiples of this prime
      for (int i = start * start; i <= n; i += start)
      {
        prime[i] = false;
      }
    }
    return;
  }

  int mid = start + (end - start) / 2;
  sieve_divide_conquer(prime, start, mid, n);
  sieve_divide_conquer(prime, mid + 1, end, n);
}

void sieve_recursive_divide_conquer(int n)
{
  bool *prime = (bool *)malloc((n + 1) * sizeof(bool));
  memset(prime, true, (n + 1) * sizeof(bool));

  prime[0] = prime[1] = false; // 0 and 1 are not prime

  int limit = (int)sqrt(n);
  sieve_divide_conquer(prime, 2, limit, n);

  printf("Primes up to %d (divide & conquer): ", n);
  for (int i = 2; i <= n; i++)
  {
    if (prime[i])
    {
      printf("%d ", i);
    }
  }
  printf("\n");

  free(prime);
}

int main()
{
  int n = 50;

  sieve_iterative(n);
  printf("\n");

  sieve_recursive(n);
  printf("\n");

  sieve_recursive_divide_conquer(n);

  return 0;
}
