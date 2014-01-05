/******************************************************************************
 * $Author: steve $
 * $Date: 2003/11/29 22:42:11 $
 * $Id: primes.c,v 1.1 2003/11/29 22:42:11 steve Exp $
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

typedef enum {false, true} bool;

const int    max_prime  = 1000000000;
const int    sieve_size = 15625001;        /* (max_prime >> 6) + 1 */
unsigned int sieve1[15625002];                       /* sieve_size */
unsigned int sieve_mask[64];
unsigned int *sieve;

unsigned int sieve2[15625002];

#define not_prime(n) sieve[(n)>>6] &= ~sieve_mask[(n)&0x3F]
#define is_prime(n) (sieve[(n)>>6] & sieve_mask[(n)&0x3F])


/******************************************************************************/
void finish (char *message)
/******************************************************************************/
{
  fprintf(stderr, "%s\n", message);
  fprintf(stderr, "Aborting.");
  fflush(stderr);
  exit(1);
}


/******************************************************************************/
void message (char *s)
/******************************************************************************/
{
  printf("%s\n", s);
  fflush(stdout);
}


/******************************************************************************/
void process_arguments (int argc, char *argv[])
/******************************************************************************/
{
  int i;
  message("process_arguments");
  for (i = 0; i < 64; i += 1)
    sieve_mask[i] = (1 << (i >> 1));
}


/******************************************************************************/
void print_sieve_mask (void)
/******************************************************************************/
{
  int i;
  message("print_sieve_mask");
  for (i = 0; i < 64; i += 1)
    printf("%3d %10X\n", i, sieve_mask[i]);
}


/******************************************************************************/
void init_sieve (void)
/******************************************************************************/
{
  int i;
  message("init_sieve");
  for (i = 0; i < sieve_size+1; i += 1) {
    sieve1[i] = ~0;
    sieve2[i] = 0;
  }
  sieve = sieve1 + 1;
}


/******************************************************************************/
void find_primes (void)
/******************************************************************************/
{
  int i, j, k;
  message("find_primes");
  i = 3;
  j = i * i;
  while (j < max_prime) {
    if (is_prime(i)) {
      k = i<<1;
      while (j < max_prime) {
        not_prime(j);
        j += k;
      }
    }
    i += 2;
    j = i * i;
  }
}


/******************************************************************************/
void print_primes (void)
/******************************************************************************/
{
  int i, j;
  message("print_primes");
  j = 0;
  if (is_prime(1)) {
    printf("%8d ", 1);
    j += 1;
  }
  printf("%8d ", 2);
  j += 1;
  for (i = 3; i < max_prime; i += 2) {
    if (is_prime(i)) {
      printf("%8d ", i);
      j += 1;
      if (j >= 8) {
        printf("\n");
        j = 0;
      }
    }
  }
  printf("\n");
}


/******************************************************************************/
bool add_sieves (int offset)
/******************************************************************************/
{
  int i, j, k;
  bool more;
  offset >>= 1;
  k = (offset & 0x1F);
  j = (offset >> 5);
  more = false;
  if (k) {
    int l = 32 - k;
    for (i = j, j <<= 1; j < sieve_size; i += 1, j += 1)
      if (sieve2[j] != ~0) {
        sieve2[j] |= (sieve[i-1] >> l) | (sieve[i] << k);
        more = true;
      }
  }
  else /* k == 0 */
    for (i = j, j <<= 1; j < sieve_size; i += 1, j += 1)
      if (sieve2[j] != ~0) {
        sieve2[j] |= sieve[i];
        more = true;
      }
  return more;
}


/******************************************************************************/
void find_sums (void)
/******************************************************************************/
{
  int i;
  /*    char buffer[40];*/
  bool more;
  message("find_sums");
  more = true;
  for (i = 1; more && (i < max_prime); i += 2)
    if (is_prime(i))
      more = add_sieves(i);
}


/******************************************************************************/
void print_non_sums (void)
/******************************************************************************/
{
  int i;
  message("print_non_sums");
  for (i = 2; i < max_prime; i += 2)
    if (!(sieve2[(i-1)>>6] & sieve_mask[(i-1)&0x3F]))
      printf("%d ", i);
}


/******************************************************************************/
int main (int argc, char *argv[])
/******************************************************************************/
{
  message("main");
  process_arguments(argc, argv);
  init_sieve();
  find_primes();
#if 0
  not_prime(97);
  not_prime(89);
  not_prime(83);
  not_prime(71);
  not_prime(59);
  not_prime(53);
#endif
  find_sums();
  print_non_sums();
  message("end");
  exit(0);
}


/******************************************************************************
 * $Log: primes.c,v $
 * Revision 1.1  2003/11/29 22:42:11  steve
 * Created
 *
 * Revision 1.4  2002/03/04 07:17:34  Steve Palmer
 * Possibly fixed a bug
 *
 * Revision 1.3  2002/02/23 18:24:04  Steve Palmer
 * Testing CVS
 *
 * Revision 1.2  2002/02/23 13:03:17  Steve Palmer
 * Added CVS Headers and Footers
 *
 ******************************************************************************/
