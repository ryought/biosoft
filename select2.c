// https://github.com/manishc1/Coding/blob/4f7195079f31e61dfe52644b849f3844fe3f3add/C/Search/Median_Of_Median.c
// 動かない？？
#include "sort.h"
#include <stdio.h>

// selects the median of medians in an array
int select_(int *a, int s, int e, int k){
    // if the partition length is less than or equal to 5
    // we can sort and find the kth element of it
    // this way we can find the median of n/5 partitions
    if(e-s+1 <= 5){
      insertionSort(a, s, e);
      return s+k-1;
    }

    int tmp;
    
    // if array is bigger 
    // we partition the array in subarrays of size 5
    // no. of partitions = n/5 = (e+1)/5
    // iterate through each partition
    // and recursively calculate the median of all of them
    // and keep putting the medians in the starting of the array
    for(int i=0; i<(e+1)/5; i++){
      int left = 5*i;
      int right = left + 4;
      if(right > e) right = e;
      int median = select_(a, 5*i, 5*i+4, 3);

      //swap(a[median], a[i]);
      tmp = a[median]; a[median] = a[i]; a[i] = tmp;
    }
    
    // now we have array 
    // a[0] = median of 1st 5 sized partition
    // a[1] = median of 2nd 5 sized partition
    // and so on till n/5
    // to find out the median of these n/5 medians
    // we need to select the n/10th element of this set (i.e. middle of it)
    return select_(a, 0, (e+1)/5, (e+1)/10);
}

int main(){
    int a[] = {6,7,8,1,2,3,4,5,9,10};
    int n = 10;
    
    int mom = select_(a, 0, n-1, 2);
    
    //cout<<"Median of Medians: " << a[mom] << endl;
    printf("median of medians: %d\n", a[mom]);
    return 0;
}
