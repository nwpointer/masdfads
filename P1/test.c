/* Fibonacci Series c language */

#include <stdio.h>
#include <unistd.h>

 
int main()
{
   int n, first = 0, second = 1, next, c;
   for ( c = 0 ; c < 500000000 ; c++ )
   {
   	  if(c%100000000 == 0){
   	  	printf("%d is thinking\n", getpid());
   	  }
      if ( c <= 1 )
         next = c;
      else
      {
         next = first + second;
         first = second;
         second = next;
      }
      // printf("%d\n",next);
   }
 printf("%d: %d\n",next, getpid());
   return 0;
}