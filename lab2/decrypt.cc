#include <iostream>
#include <chrono>

#include <unordered_map>
#include <vector>
#include <functional>
#include <math.h>
#include <stdio.h>

#include "Key.h"

using namespace std;

class key_hash
{
  public:
    long operator()(const Key& x) const
    {
      long hash = 0;

      for (int i{N - 1}; i >= 0; i--)
	{
	  hash +=  KEYbit(x, i) * pow(2.0, i);
	}
      return hash;
    }
};

class key_equal_to
{
  public:
     bool operator()(const Key& a, const Key& b) const
     {
       for( int i{0}; i < C; ++i)
	 {
	   if( a.digit[i] != b.digit[i] )
	     return false;
	 }
        return true;
     }
};

unordered_map < Key, int, key_hash, key_equal_to > calcIt(const Key T[], int i1, int i2)
{
  unordered_map < Key, int, key_hash, key_equal_to > temp;
  
  return temp;
}
/*Applies the mask to a set like {1, 2, ..., n} and prints it */ 
void printv(int mask[], int n) {
    int i;
    printf("{ ");
    for (i = 0; i < n; ++i)
        if (mask[i])
	  printf("%d ", i + 1); //i+1 is part of the subset
    printf("\\b }\\n");
}

void add()
{
 
}

/* Generates the next mask*/
int next(int mask[], int n) {
    int i;
    for (i = 0; (i < n) && mask[i]; ++i)
        mask[i] = 0;
 
    if (i < n) {
        mask[i] = 1;
        return 1;
    }
    return 0;
}
 
int
main(int argc, char* argv[])
{
  unsigned char buffer[C+1];     // temporary string buffer
  Key candidate = {{0}};         // a password candidate
  Key encrypted;                 // the encrypted password
  Key candenc;                   // the encrypted password candidate
  Key zero = {{0}};              // the all zero key
  Key T[N];                      // the table T

  if (argc != 2)
    {
      cout << "Usage:" << endl << argv[0] << " password < rand8.txt" << endl;

      return 1;
    }

  encrypted = KEYinit((unsigned char *) argv[1]);

  // read in table T
  for (int i{0}; i < N; ++i)
    {
      scanf("%s", buffer);
      T[i] = KEYinit(buffer);
    }

  auto begin = chrono::high_resolution_clock::now();
  unordered_map < Key, int, key_hash, key_equal_to > first_half = calcIt(T, 0, 11);
  unordered_map < Key, int, key_hash, key_equal_to > second_half = calcIt(T, 12, 25);
  //unordered_map < Key, int > second_halv;
  
  cout << "C: " << C << ", N: " << N << endl;

  // try all possible subsets of T
  /*do
    {
      candenc = KEYsubsetsum(candidate, T);
      if (candenc == encrypted)
	cout << candidate << endl;
      ++candidate;
    } while (candidate != zero);
  */

  candenc = KEYsubsetsum(candidate, T);
  cout << "A Key?? " << candenc << endl;

  /*
  // temp code
  long hash = 0;
  for (int i{N - 1}; i >= 0; i--)
    hash += KEYbit(candidate, i) * pow(2.0, i);
  cout << "Hash value for " << candidate << ":   " << hash << endl;
  hash = 0;
  ++candidate;
  for (int i{N - 1}; i >= 0; i--)
    hash +=  KEYbit(candidate, i) * pow(2.0, i);
  cout << "Hash value for " << candidate << ":   " << hash << endl;
  hash = 0;
  ++candidate;
  for (int i{N - 1}; i >= 0; i--)
    {
      hash +=  KEYbit(candidate, i) * pow(2.0, i);
    }
  cout << "Hash value for " << candidate << ":   " << hash << endl;
  */
  
  auto end = chrono::high_resolution_clock::now();
  cout << "Decryption took "
       << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
       << " seconds." << endl;

  cout << "\n" << "Testing printv" << endl;
  int n = 12;
  int m = 13;

  int nask[12];
  int mask[13]; /* Guess what this is */
  
  
  int i;
  for (i = 0; i < n; ++i)
    nask[i] = 0;
  
  for (i = 0; i < m; ++i)
    mask[i] = 0;

  /* Print the first set */
//  printv(mask, n);
  vector< vector<int> > in;
  vector< vector<int> > im;
  /* Print all the others */
  while (next(mask, m))
    //  printv(mask, n);
  {
    vector<int> v;
    for (i = 0; i < m; ++i)
      if (mask[i])
      {
	v.push_back(i);
      }
    im.push_back(v);
  }

  while (next(nask, n))
    //  printv(mask, n);
  {
    vector<int> v;
    for (i = 0; i < n; ++i)
      if (nask[i])
      {
	v.push_back(i+13);
      }
    in.push_back(v);
  }
    
  cout << in.size() << endl;
  cout << im.size() << endl;

  return 0;
}



