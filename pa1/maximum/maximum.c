#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  //size: the size of the list
  //num_of_elements: The number of elements to be returned
  //temp: store the current largest number
  int size = 0, num_of_elements = 0, temp;
  fscanf(fp, "%d", &size);
  fscanf(fp, "%d", &num_of_elements);

  // num[ ]: The array that holds the numbers to be returned
  // Initialize all its elements to INT_MIN
  int num [num_of_elements]; 
  for(int i=0; i<num_of_elements; i++)
  {
    num[i] = INT32_MIN;
  }


  //The algorithm: whenever a number larger than the elements in the return array is found, insert that number into the array and push back all the elements of larger index one index.
  //To form a sorted descending array.
  for(int i=0; i<size; i++)
  {
    fscanf(fp, "%d", &temp);
    for(int j=0; j<num_of_elements; j++)
    {
      if(temp > num[j])
      {
        for(int k=num_of_elements-1; k>j; k--)
        {
          num[k] = num[k-1];
        }
        num[j] = temp;
        break;
      }
    }
  }



  //Print the array to the command line
  for(int i=0; i<num_of_elements; i++)
  {
    printf("%d ", num[i]);
  }
  printf("\n");

  fclose(fp);
  return 0;

}
