#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void merge(int a[], int p, int q, int r);

void mergeSort(int a[], int p, int r);

int max;
clock_t begin, end;


int main(int argc, char* argv[]) {

	int c;
	max = atoi(argv[1]);
    int *a = (int*)malloc(max * sizeof(int));
    double eltime;
  
   
    for(c = 0; c < max; c++) {
        
        a[c] = rand() % max;
       // printf("%d ", original_array[c]);
        
    }

  begin=clock();
  mergeSort(a, 0, max-1);
  end=clock();

  eltime=(double)(end-begin)/CLOCKS_PER_SEC;
  printf("Time:%.30f \n",eltime);
    
      // for(c = 0; c < max; c++)
       //printf("%d ", original_array[c]);
  

  return(0);
}

void merge(int a[], int p, int q, int r) {
  int i, j, k=0, b[max];
  i = p;
  j = q+1;

  while (i<=q && j<=r) {
    if (a[i]<a[j]) {
      b[k] = a[i];
      i++;
    } else {
      b[k] = a[j];
      j++;
    }
    k++;
  }
  while (i <= q) {
    b[k] = a[i];
    i++;
    k++;
  }
  while (j <= r) {
    b[k] = a[j];
    j++;
    k++;
  }
  for (k=p; k<=r; k++)
    a[k] = b[k-p];
  return;
}

void mergeSort(int a[], int p, int r) {
  int q;
  if (p < r) {
    q = (p+r)/2;
    mergeSort(a, p, q);
    mergeSort(a, q+1, r);
    merge(a, p, q, r);
  }
  return;
}
