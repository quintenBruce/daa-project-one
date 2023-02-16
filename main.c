#include <stdio.h>

const int FILE_SIZE = 10000;
const int NUM_FILES = 5;
const char *FILE_NAMES[] = {"source1.txt", "source2.txt", "source3.txt",
                            "source4.txt", "source5.txt"};
const char *SORT_NAMES[] = {"Merge Sort", "Quick Sort", "Bucket Sort"};

// Program preconditions
/*
        - files must exist in working directory.
*/

// insert mergesort code below. The function should sort a one-dimensonal array
// and return the number of inversions. Uncomment case 1 in InversionsHelper
// function to test code. Compare your algorithms output to the correct # of
// inversions
 int MergeSort(int arr[], int start, int end) {
   
    int inversion_MergeSort = 0;

    if (start < end){

      int mid = start+(end-start)/2;

      int pointer_left = start;
      int pointer_right = mid+1;

      inversion_MergeSort += MergeSortAndCount(a, pointer_left, mid);
      inversion_MergeSort += MergeSortAndCount(a, pointer_right, end);

      int length_left = mid-start+1;
      int length_right =  end-mid;
      int length = length_left+length_right;

      int temp[length];

      int i=0;
      int j=0;

      for( int k = 0; k<length; k++){


        if (j>=length_right || (i<length_left && a[pointer_left]<=a[pointer_right])){	
          temp[k] = a[pointer_left++];
          i++;
        }
        else{
          temp[k] = a[pointer_right++];
          j++;
          inversion_MergeSort += (length_left-i);
        }	
      }

      for(int i = 0;i<length;i++){
        a[start+i] = temp[i];	
      }

    }

    return inversion_MergeSort;
}

// insert QuickSort code below. The function should sort a one-dimensonal array
// and return the number of inversions. Uncomment case 2 in InversionsHelper
// function to test code.  Compare your algorithms output to the correct # of
// inversions
//  int QuickSort(int arr[]) {

// }

// insert BucketSort code below. The function should sort a one-dimensonal array
// and return the number of inversions. Uncomment case 3 in InversionsHelper
// function to test code.  Compare your algorithms output to the correct # of
// inversions
//  int BucketSort(int arr[]) {

// }

void FillArrays(int sourceArrays[NUM_FILES][FILE_SIZE]) {
  for (int i = 0; i < NUM_FILES; i++) {
    FILE *file;
    file = fopen(FILE_NAMES[i], "r");

    for (int j = 0; j < FILE_SIZE; j++)
      fscanf(file, "%d", &sourceArrays[i][j]);
    fclose(file);
  }
}
// postcondition: two-dimensional array paramater 'arrays' will contain data
// from files in directory

int SumArrays(int sourceArrays[NUM_FILES][FILE_SIZE], int j) {
  int sum = 0;
  for (int i = 0; i < NUM_FILES; i++) {
    sum += sourceArrays[i][j];
  }
  return sum;
}
// postcondition: the function will return the sum of the 'i'th value of each
// source array

void ComputeStandardArray(int sourceArrays[NUM_FILES][FILE_SIZE],
                          int standardArray[FILE_SIZE]) {
  for (int i = 0; i < FILE_SIZE; i++) {
    standardArray[i] = SumArrays(sourceArrays, i);
  }
}
// postcondition: sourceArrays will be unmodified. Each 'i'th array element will
// equal the sum of the 'i'th value of each source array

void Swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
// postcondition:

void SwapHelper(int sourceArrays[NUM_FILES][FILE_SIZE], int a, int b) {
  for (int i = 0; i < NUM_FILES; i++) {
    Swap(&sourceArrays[i][a], &sourceArrays[i][b]);
  }
}
// postcondition: For each source array, the 'a'th element will be swapped with
// the 'b'th element.

void BubbleSort(int standardArray[], int sourceArrays[NUM_FILES][FILE_SIZE]) {
  int i, j;
  for (i = 0; i < FILE_SIZE - 1; i++)
    for (j = 0; j < FILE_SIZE - i - 1; j++)
      if (standardArray[j] > standardArray[j + 1]) {
        Swap(&standardArray[j], &standardArray[j + 1]);
        SwapHelper(sourceArrays, j, j + 1);
      }
}
// postcondition: every swap applied to the standard array will also be applied
// to each of the source arrays.

// this function is not permanent. will be deleted
void WriteStandardArray(int arr[]) {
  FILE *fp;
  fp = fopen("standard.txt", "w+");
  for (int i = 0; i < FILE_SIZE; i++) {

    fprintf(fp, "%d\n", arr[i]);
  }
  fclose(fp);
}

// this temporary function computes the number of inversions in the given array
// as a reference for our other algorithms. Will be deleted
int CountInversions(int arr[]) {
  int inv_count = 0;
  for (int i = 0; i < FILE_SIZE - 1; i++)
    for (int j = i + 1; j < FILE_SIZE; j++)
      if (arr[i] > arr[j])
        inv_count++;

  return inv_count;
}

void InversionsHelper(int sortMethod, int sourceArrays[NUM_FILES][FILE_SIZE],
                      int inversionsArray[]) {
  switch (sortMethod) {
  case 0: // this case will be deleted once we have verified all of our
          // algorithms.
    for (int i = 0; i < NUM_FILES; i++)
      inversionsArray[i] = CountInversions(sourceArrays[i]);
    break;
  case 1:
    for (int i = 0; i < NUM_FILES; i++)
        inversionsArray[i] = MergeSort(sourceArrays[i],0,FILE_SIZE-1);
    break;
  case 2:
    // for (int i = 0; i < NUM_FILES; i++)
    // 	inversionsArray[i] = QuickSort(sourceArrays[i]);
    break;
  case 3:
    // for (int i = 0; i < NUM_FILES; i++)
    //     inversionsArray[i] = BucketSort(sourceArrays[i]);
    break;
  }
}
// postcondition: each source array will be sorted by the algorithm indicated by
// the 'sortMethod' parameter.  each 'i'th element of 'inversionsArray' will
// equal the number of inversions calculated by the chosen
// algorithm for the 'i'th source.

void PrintResults(int inversionsArray[], int sortMethod) {
  printf("\n# inversions computed using %s:\n", SORT_NAMES[sortMethod - 1]);
  printf("  source1: %d\n  source2: %d\n  source3: %d\n  source4: %d\n  "
         "source5: %d\n",
         inversionsArray[0], inversionsArray[1], inversionsArray[2],
         inversionsArray[3], inversionsArray[4]);
}
// postcondition: the number of inversions computed for each source by the
// chosen algorithm will be printed to the console.

int main(void) {

  int sourceArrays[NUM_FILES][FILE_SIZE];
  int standardArray[FILE_SIZE];
  int inversionsArray[NUM_FILES];
  FillArrays(sourceArrays);
  ComputeStandardArray(sourceArrays, standardArray);

  // WriteStandardArray(standard); ////you may use this function to write the
  // standard array to the output directory. Will be deleted.

  BubbleSort(standardArray, sourceArrays);

  InversionsHelper(
      0, sourceArrays,
      inversionsArray); // will compute the correct number of inversions for
                        // each source. will be deleted
  printf("Correct # Inversions:\n");
  printf("  source1: %d\n  source2: %d\n  source3: %d\n  source4: %d\n  "
         "source5: %d\n\n",
         inversionsArray[0], inversionsArray[1], inversionsArray[2],
         inversionsArray[3], inversionsArray[4]); // will be deleted.

  for (int i = 0; i < 5; i++)      // resets inversion array. will be deleted
    inversionsArray[i] = -9999999; // will be deleted

  int sortMethod;

  do {
    printf("Enter 1 for %s, 2 for %s, or 3 for %s: ", SORT_NAMES[0],
           SORT_NAMES[1], SORT_NAMES[2]);
    scanf("%d", &sortMethod);
  } while (sortMethod < 1 || sortMethod > 3);

  InversionsHelper(sortMethod, sourceArrays, inversionsArray);

  PrintResults(inversionsArray, sortMethod);

  return 0;
}
