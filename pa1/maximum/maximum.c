#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }
  int size = 0, num_of_elements = 0, temp;
  //fscanf(fp, "%d", &size);
  fscanf(fp, "%d", &size);
  printf("the size of the list is %d\n", size);
  fscanf(fp, "%d", &num_of_elements);
  printf("you need output %d number\n", num_of_elements);
  int num [num_of_elements];
  int list [size];
  for(int i=0; i<num_of_elements; i++)
  {
    fscanf(fp, "%d", &num[i]);;
    //printf("%d ", num[i]);
  }
  //printf("\n");
  for(int i=0; i<size-num_of_elements; i++)
  {
    fscanf(fp, "%d", &temp);
    printf("temp is %d\n", temp);
    //int subtract = 0;
    for(int j=0; j<num_of_elements; j++)
    {
      //subtract = num[j]
      if(temp > num[j])
      {
        num[j]=temp;
        
      }
    }
  }
  for(int i=0; i<num_of_elements; i++)
  {
    //printf("%d", num[i]);
  }


  fclose(fp);
  return 0;

}
