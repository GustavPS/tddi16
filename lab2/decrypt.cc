#include <iostream>
#include <chrono>

#include <unordered_map>
#include <vector>
#include <functional>

#include "Key.h"

using namespace std;

class key_hash
{
  public:
    long operator()(const Key& x) const
    {
        hash<string> z;
        return 300;
    }
};

class key_equal_to
{
  public:
     bool operator()(const Key& a, const Key& b) const
     {
       for( int i = 0; i < C; ++i)
	 {
	   if( a.digit[i] != b.digit[i] )
	     return false;
	 }
        return true;
     }
};

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

  unordered_map < Key, int, key_hash, key_equal_to > first_halv;
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

  auto end = chrono::high_resolution_clock::now();
  cout << "Decryption took "
       << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
       << " seconds." << endl;

  return 0;
}
