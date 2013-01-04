#include "lottery.h"


int main()
{
  int m,n,t,p;
  
  cin>> m >> n >> t >> p;
  
  if( 0 < m && m <= 1000 &&			\
      0 < n && n <= m    &&			\
      0 < t && t <= 100  &&			\
      0 < p && p <= m ) 
    
    probability(m,n,t,p); 
  
  return 0;
}
