#include <stdlib.h>
#include <stdio.h>
//#include <limits.h>
int partition (int [], int, int);
void quicksort(int[], int, int, int);
int main(int argc, char* argv[]) {
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  //size: the size of the list
  //num_of_elements: The number of elements to be returned
  //temp: store the current largest number
  int size = 0, num_of_elements = 0;
  fscanf(fp, "%d", &size);
  fscanf(fp, "%d", &num_of_elements);

  // read in all elements
  int num [size] ; 
  for(int i=0; i<size; i++)
  {
    fscanf(fp, "%d", &num[i]);
    //printf("%d ", num[i]);
  }

  quicksort(num, 0, size-1, num_of_elements);
  for(int i=size-num_of_elements; i<size; i++)
  {
    printf("%d ", num[i]);
  }
  fclose(fp);
  return 0;

}
int partition(int num[], int indx_low, int indx_high)
{
  int pivot = num[indx_high];
  int i = indx_low-1;
  int temp;
  for(int j=indx_low; j<indx_high; j++)
  {
    if(num[j] < pivot)
    {
      i++;
      temp = num[i];
      num[i] = num[j];
      num[j] = temp;
    }
  }
  temp = num[i+1];
  num[i+1] = num[indx_high];
  num[indx_high] = temp;
  return i+1;
}
void quicksort(int num[], int indx_low, int indx_high, int return_size)
{
  //int piv_indx = 0;
  if( indx_low < indx_high)
  {
    //printf("indx_high is %d\n", indx_high);
    //printf("indx_low is %d\n", indx_low);
    int piv_indx = partition(num, indx_low, indx_high);
    quicksort(num, indx_low, piv_indx-1, return_size);
    quicksort(num, piv_indx+1, indx_high, return_size);
  }
  
}