#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int num_cycles;
int *primes;
int primes_len = 1;
int capacity = 2048;

void findprimes(int limit) {
  primes_len = 1;
  primes[0] = 2;

  for (int i = 3; i < limit; i += 2) {
    int inner_limit = (int)sqrt(i);
    bool is_prime = true;

    int j = 0;
    int prime = 2;

    while (j < primes_len) {
      prime = primes[j];
      // printf("prime: %d\n", prime);
      if (prime > inner_limit) {
        break;
      }
      if (i % prime == 0) {
        // printf("%d is divisible by %d\n", i, prime);
        is_prime = false;
        break;
      }
      j++;
    }

    if (is_prime) {
      if (capacity == primes_len) {
        primes = (int *)realloc(primes, sizeof(int) * capacity * 2);
        capacity = capacity * 2;
      }

      // printf("Adding: %d , len: %d\n", i, primes_len);
      primes[primes_len] = i;
      primes_len += 1;
    }
  }
  // printf("Number of primes found: %d\n", primes_len);
  num_cycles += 1;
}

void siginthandler() {
  printf("%d - %d", num_cycles, primes_len);
  exit(1);
}

int main(int argc, char **argv) {
  primes = (int *)malloc(sizeof(int) * capacity);

  signal(SIGINT, (__sighandler_t)siginthandler);

  while (true) {
    findprimes(atoi(argv[1]));
  }

  return 0;
}
