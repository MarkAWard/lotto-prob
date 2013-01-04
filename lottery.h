#ifndef LOTTERY_H
#define LOTTERY_H

#include "hugeint.h"
#include <iostream>
using namespace std;

//calculate n! n factorial
HugeInt factorial(int n)
{

  HugeInt one(1);
  HugeInt result(1);
  HugeInt fac(2);  
  

  for(int i = 1; i < n; i++ )
    {
      result = result * fac;
      fac = fac + one;
    }
  
  return (result);

}

/*
  calculate nCk --> n choose k

         n!      ==     n*(n-1)*...*(k+1)
      (n-k)!k!               (n-k)!   

        
                 ==    n*(n-1)*...*(n-k+1)
		              k!

using formulae on right to reduce computation

*/
HugeInt choose(int n, int k)
{
  HugeInt result;

  if(n >= k) // otherwise return 0
    {
      int m = min(n-k, k);
      
      HugeInt numer(1);
      HugeInt denom;
      HugeInt one(1);
      HugeInt fac(n);
      
      for(int i = 0; i < m; i++ )
	{
	  numer = numer * fac;
	  fac = fac - one;
	}
      
      denom = factorial(m);
      
      result = numer.divide(denom); 
      
      // TEST numerator and denominator are small as possible
      // cout<<numer<<"\n\n"<<denom<<"\n\n";
      
    }
  
  return (result);

}

//Calculate the min num of people that need to win so whole group goes
int need_to_win(int t, int p)
{
  //t tickets each can buy
  //p people in group

  int winners=1;
  int i = 1;  
  
  do{
    winners = i;
  }while( t*i++ < p); 
  
  
  return (winners);

}



HugeInt possible(int m, int n, int t, int p)
{
  /*
    Winning possibilities for entire group p

    A: combinations of people that won lottery but not in your group
    B: combinations of those in your group that won the lottery

    only consider the cominations for which there are enough group winners in B
    so that your entire group can go based on "t", # tickets winners can buy
  */

  int x = need_to_win(t,p);
  HugeInt A, B, total, one(1);
  
  if( m == n ) //time saver
    total = one;
  else
    {
      for(int i = 0; (x + i) <= n &&  (x + i) <= p; i++)
	{

	  A = choose(m - p, n - (x + i));
	  if( A > 0 )  // if A == 0 waste of time to calc B
	    {
	      B = choose(p, (x + i));
	      
	      total = total + ( A * B );
	    }
	  
	  //TEST print combinations and the results for both
	  //	  cout<< m-p<<"\t"<<p<<"\t"<< A <<"\t"<< B <<endl
	  //<< n-(x+i)<<"\t"<<x+i<<"\n\n";
	}
    }
  


  return (total);

}


HugeInt all_possible(int m, int n)
{
  // Total number of ways that n winners can be choosen from a pool of m people


  HugeInt total = choose(m, n);
  return (total);
}


void probability( int m, int n, int t, int p)
{
  // divide winning combinations by all possible combinations to get probability

  HugeInt Num, Den;
  Num = possible(m,n,t,p);
  Den = all_possible(m,n);

  // .divide() integer division
  // .divide2() remainder division for decimal
  cout << Num.divide(Den) << "."; Num.divide2(Den).display2();

}

#endif
