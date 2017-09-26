Goldbach Conjecture Tester
==========================

29 February 2016

I first wrote this program in the late 1990's after reading ["Fermat's Last Theorem" by Simon Singh](https://en.wikipedia.org/wiki/Fermat%27s_Last_Theorem_%28book%29) (published in 1997).  At the end of the book, it states:

> [Andrew] Wiles realises that in order to give mathematics one of its greatest proofs, he has had to deprive it of its greatests riddle: `People have told me that I've taken away their problem, and asked if I could give them something else ...'

> [snip]

> Goldbach asked Euler if he could prove that every even number could be split into two primes.  Despite years of effort, the man known as `analysis incarnate' was confounded by Goldbach's challenge.  In today's computer age, the Goldbach conjecture, as it has become known, has been tested and found to be correct for every even number up to 100,000,000 but still nobody has been able to prove that the conjecture holds true for every even number up to infinity.

When I read this, I thought that testing the [Goldback Conjecture](https://en.wikipedia.org/wiki/Goldbach%27s_conjecture) up to 100,000,000 didn't sound like a big number and I wondered if I could extend it - and this is my attempt.

The program uses the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) to find the prime numbers up to 1,000,000,000 (using ~32MB of storage which was a fair amount at the time) and then does the addition of all the primes through a mixture of Shift's and Or's.  I was quite pleased with the result since it was able to get to the result in a matter of minutes.

Since then, I've uses the program to test the performance of my computers.  My current computer runs the program in 8.5 seconds.

By-the-way, the conjecture was [verified on 4 April 2012](http://sweet.ua.pt/tos/goldbach.html) up to 4 × 10^18, so rather more than my measly 10^9.

Steve Palmer

