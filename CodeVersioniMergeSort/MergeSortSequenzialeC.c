/* Merge sort in C */
#include<stdio.h>
#include<stdlib.h>

#include <papi.h>


// Function to Merge Arrays L and R into A. 
// lefCount = number of elements in L
// rightCount = number of elements in R. 
void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers. 
void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing. 

	mid = n/2;  // find the mid index. 

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array 
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}

int main(int argc, char *argv[]) {
	/* Code to test the MergeSort function. */
	
	int n=atoi(argv[1]); //numero elementi array
    	//int A = (int *)malloc(n*sizeof(int));
	int A[n];
	int i;
	int numberOfElements;
	int EventSet = PAPI_NULL;
	long_long countCacheMiss;

	//crea un array randomico con un numero di elementi pari al parametro passato
	for(i=0; i<n; i++){
		A[i] = random() % n;	
	}
	
	
//	int A[] = {6,2,3,1,9,10,15,13,12,17}; // creating an array of integers. 
	

	// printf("papi init\n");
 	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
    
    	/*Create an EventSet */
    	if (PAPI_create_eventset(&EventSet) != PAPI_OK)  exit(1);
    
    	if (PAPI_add_event(EventSet,PAPI_L1_TCM) != PAPI_OK){
            printf("Errore nell'aggiunta dell'evento cache miss level 1\n");
            exit(1);
    	}


	// finding number of elements in array as size of complete array in bytes divided by size of integer in bytes. 
	// This won't work if array is passed to the function because array
	// is always passed by reference through a pointer. So sizeOf function will give size of pointer and not the array.
	// Watch this video to understand this concept - http://www.youtube.com/watch?v=CpjVucvAc3g  
	numberOfElements = sizeof(A)/sizeof(A[0]); 

	//inizio conteggio cache miss 
    	if(PAPI_start(EventSet) != PAPI_OK){
    		printf("Errore nell'avvio del conteggio \n");
    		exit(1);    
    	}

	long_long startT = PAPI_get_real_usec(); //prelevo il tempo 
	printf("startT: %lld   ",  startT);

	// Calling merge sort to sort the array. 
	MergeSort(A,numberOfElements);

	long_long stopT=PAPI_get_real_usec(); //fine tempo
	printf("totalT: %lld ",  stopT-startT);

	//stop dei contatori e inserimento dei risultati in countCacheMiss
	if(PAPI_stop(EventSet, &countCacheMiss) != PAPI_OK){
	  	printf("Errore in stop e store del contatore \n");
	   	exit(1);
	}
	   
	printf ("Cache miss=%lld\n", countCacheMiss);

	//printing all elements in the array once its sorted.
//	for(i = 0;i < numberOfElements;i++) 
//		printf("%d ",A[i]);
	
	printf("\n");
	
	return 0;
}
