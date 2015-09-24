#include <iostream>
#include <chrono>

#include <unordered_map>
#include <vector>
#include <functional>
#include <math.h>
#include <stdio.h>
#include <utility>
#include <bitset>

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
/*
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
};*/


void BitToString(bitset<N> b)
{
  string BitString = b.to_string<char,string::traits_type,string::allocator_type>();
  BitString = string (BitString.rbegin(), BitString.rend());
  //string BitString = b.to_string;
  cout << BitString << " " << BitString.length() << endl;
  Key pass = {{0}};
  for ( int i = {0}; i < C; ++i)
    {
      string asdf = BitString.substr(i*5, 5);
      bitset<5> temp (asdf);
      //cout << temp.to_ulong() << endl;
      //cout << ALPHABET[temp.to_ulong()] << endl;
      pass.digit[ i ] = temp.to_ulong();
    }
  cout << pass << endl;
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



unordered_map < Key, vector< vector< int > >, key_hash > getMap(Key T[], int range, int indexToAdd) {

  int mask[range];
  for (int i = 0; i < range; ++i)
    mask[i] = 0;
  
  vector< vector <int> > permutations;

  while (next(mask, range))
  {
    vector<int> v;
    for (int i = 0; i < range; ++i)
      if (mask[i])
      {
	v.push_back(i + indexToAdd);
      }
    permutations.push_back(v);
  }

 
  unordered_map < Key, vector< vector< int > >, key_hash > temp;

  //Populate one half of the hash table
  for( int i = {0}; i < permutations.size(); ++i)
    {
      Key subSet{{0}};
      for( int j = {0}; j < permutations[i].size(); ++j)
	{
	  subSet = subSet + T[ permutations[i][j] ];
	 
	}
      unordered_map < Key, vector< vector< int > >, key_hash >::iterator it = temp.find(subSet);
      if( it != temp.end())
	{
	  temp[subSet].push_back( permutations[i] );
	  cout << "We here 2222" << endl;
	}
      else {
	vector < vector < int > > temp_vec = { permutations[i] };
	temp.insert(make_pair(subSet, temp_vec));
      }     
    }

  return temp;

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

   unordered_map < Key, vector< vector< int > >, key_hash > first_half;
   unordered_map < Key, vector< vector< int > >, key_hash > second_half;

   cout << "C: " << C << ", N: " << N << endl;


   int n = 0;
   int m = 0;

   if (N%2 != 0)
     {
       n = N/2;
       m=N/2+1;
     }
   else
     {
       n=N/2;
       m=N/2;
     }

  first_half = getMap(T, n, 0);
  second_half = getMap(T, m, m);

  cout << first_half.size() << endl;
  cout << second_half.size() << endl;

  /*for ( auto ff = first_half.begin(); ff != first_half.end(); ++ff )
    {
      cout << ff->second.size() << " ";
    }
    cout << endl;*/
  
  /*for ( auto ff = first_half.begin(); ff != first_half.end(); ++ff )
    {
       if ( ff->first == encrypted )
	    {
	      
	    }
    }
  for ( auto ff = second_half.begin(); ff != second_half.end(); ++ff )
    {
       if ( ff->first == encrypted )
	    {
	      
	    }
	    }*/

  
   for ( auto ff = first_half.begin(); ff != first_half.end(); ++ff )
    {

      Key temp = encrypted - ff->first;
      if ( second_half.count(temp) == 1 )
	{
	  bitset<N> b;
	  //b.set(ff->first + (encrypted - ff->first));
	  for(int fi = 0; fi < ff->second.size(); fi++)
	    {
	      bitset<N> b;
	      cout << "Indexes for a possible password" << endl;
	      
	      for(int fj = 0; fj < ff->second[fi].size(); fj++)
		{
		  b.set(ff->second[fi][fj]);
		  cout << ff->second[fi][fj] << " ";
		}

	      for( int si = {0}; si < second_half[temp].size(); ++si)
		{
		  bitset<N> first_part = b;
		  for(int sj = {0}; sj < second_half[temp][si].size(); ++sj)
		    {
		      first_part.set(second_half[ temp ][si][sj] );
		      cout << second_half[ temp ][si][sj] << " ";
		    }
		  cout << "----------------------" << endl;
		  BitToString(first_part);
		}

	    }
	}

    }

  auto end = chrono::high_resolution_clock::now();
  cout << "Decryption took "
       << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
       << " seconds." << endl;
  
  return 0;
}



