#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Function declerations
bool is_prime(int n);

int main(int argc, char* argv[]) {
  int number = atoi(argv[1]);//transform the first command line input to integer
  //printf("The string is %s and the int is %d\n", argv[1], argc);
  
  /**Transform the question into goldbach's conjecture: Any even number which is greater
   than 2 can be splitted into two prime numbers**/
  int sub_num = number-3; 
  //printf("test\n");
  for(int i=0;i<sub_num;i++) //iterate through all possible combinations of two prime numbers to
  {                                    //represent the sub_number
    if(is_prime(i)&&is_prime(sub_num-i))
    {
      printf("%d = 3 + %d + %d\n", number, sub_num-i, i);
      break;
    }
  }
  return 0;
}

bool is_prime(int n){
  if(n==1||n==0) //1 and 0 are not prime numbers
  {
    return false;
  }
  else if(n==2) //2 is a prime number
  {
    return true;
  }
  else //for number greater than 2, it cannot be divided other than 1 and itself, noted 3 is automatically categorized as a prime number
  {
    int m=n/2, i; 
    for (i=2; i<=m; i++)
    {
      if(n%i==0)
      {
        return false;
      }
    }
    return true;
  }
}
