#include <stdio.h>
int main()
{
  int casas;
  scanf("%d", &casas);

  int arr[casas];

  //  take 5 number
  for(int i=0;i<casas;i++)
  {
    arr[i]=0;
  }

  for(int i=0;i<casas;i++)
  {
    if(i%2){
      arr[i]=0;
    }else{
      arr[i]=1;
    }
    
  }
  // display array
  printf("The Array elements are:\n");
  for(int i=0; i<casas; i++) {
     printf("%d ", arr[i]);
  }


  printf("\n");
  return 0;
}