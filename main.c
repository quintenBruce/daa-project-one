#include <stdio.h>

const int FILE_SIZE = 10000;
const int NUM_FILES = 5;
const char * FILE_NAMES[] = { //manually change file names to match files in current working directory if needed
    "source1.txt",
    "source2.txt",
    "source3.txt",
    "source4.txt",
    "source5.txt"
};
const char * SORT_NAMES[] = {
    "Merge Sort",
    "Quick Sort",
    "Bubble Sort"
};

void Swap(int * a, int * b); //function declaration






// Program preconditions
/*
        - each source file specified in FILE_NAMES[] constant must
	      exist in working directory in order for the program to function correctly.
*/







int MergeSort(int arr[], int start, int end) {
    int inversion_MergeSort = 0;

    if (start < end){

      int mid = start+(end-start)/2;

      int pointer_left = start;
      int pointer_right = mid+1;

      inversion_MergeSort += MergeSort(arr, pointer_left, mid);
      inversion_MergeSort += MergeSort(arr, pointer_right, end);

      int length_left = mid-start+1;
      int length_right =  end-mid;
      int length = length_left+length_right;

      int temp[length];

      int i=0;
      int j=0;

      for( int k = 0; k<length; k++){


        if (j>=length_right || (i<length_left && arr[pointer_left]<=arr[pointer_right])){
          temp[k] = arr[pointer_left++];
          i++;
        }
        else{
          temp[k] = arr[pointer_right++];
          j++;
          inversion_MergeSort += (length_left-i);
        }
      }

      for(int i = 0;i<length;i++){
        arr[start+i] = temp[i];
      }

    }

    return inversion_MergeSort;
}
// postcondition: arr parameter will be sorted and # of inversions will be returned

int QuickSort(int arr[], int size) {
    //temp arrays for less, equal, and greater
    int less[size], equal[size], greater[size];

    //make pivot element start
    int pivot = arr[0];

    //inversions count
    int inversions = 0;

    //indexes for less, equal, and greater arrays
    int l, e, g = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] <= pivot) {
            int greater_count = 0;
            less[l] = arr[i];
            for (int j = 0; j < i; j++) {
                if (arr[j] > less[l]) {
                    greater_count++;
                }
            }
            inversions += greater_count;
            l++;

        } else if (arr[i] > pivot) {
            int lesser_count = 0;
            greater[g] = arr[i];
            for (int j = 0; j < i; j++) {
                if (arr[j] > greater[g])
                    lesser_count++;
            }
            inversions += lesser_count;
            l++;
        }
    }
    fflush(stdout);
    return inversions;
}
// postcondition: arr parameter will be sorted and # of inversions will be returned

int BubbleSort(int arr[]) {
    int i, j, inversions = 0;
    for (i = 0; i < FILE_SIZE - 1; i++)
        for (j = 0; j < FILE_SIZE - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                inversions++;
                Swap( & arr[j], & arr[j + 1]);
            }

    return inversions;
}
// postcondition: arr parameter will be sorted and # of inversions will be returned

void Swap(int * a, int * b) {
    int temp = * a;
    * a = * b;
    * b = temp;
}

void FillArrays(int sourceArrays[NUM_FILES][FILE_SIZE]) {
    for (int i = 0; i < NUM_FILES; i++) {
        FILE * file;
        file = fopen(FILE_NAMES[i], "r");

        for (int j = 0; j < FILE_SIZE; j++)
            fscanf(file, "%d", & sourceArrays[i][j]);
        fclose(file);
    }
}
// postcondition: two-dimensional array paramater 'arrays' will contain data
// from files in directory

int SumArrays(int sourceArrays[NUM_FILES][FILE_SIZE], int j) {
    int sum = 0;
    for (int i = 0; i < NUM_FILES; i++)
        sum += sourceArrays[i][j];
    return sum;
}
// postcondition: the function will return the sum of the 'i'th value of each
// source array

void ComputeStandardArray(int sourceArrays[NUM_FILES][FILE_SIZE],
    int standardArray[FILE_SIZE]) {
    for (int i = 0; i < FILE_SIZE; i++)
        standardArray[i] = SumArrays(sourceArrays, i);
}
// postcondition: sourceArrays will be unmodified. Each 'i'th array element will
// equal the sum of the 'i'th value of each source array

void SwapHelper(int sourceArrays[NUM_FILES][FILE_SIZE], int a, int b) {
    for (int i = 0; i < NUM_FILES; i++)
        Swap( & sourceArrays[i][a], & sourceArrays[i][b]);
}
// postcondition: For each source array, the 'a'th element will be swapped with
// the 'b'th element.

void BubbleSortStandardArray(int standardArray[], int sourceArrays[NUM_FILES][FILE_SIZE]) {
    int i, j;
    for (i = 0; i < FILE_SIZE - 1; i++)
        for (j = 0; j < FILE_SIZE - i - 1; j++)
            if (standardArray[j] > standardArray[j + 1]) {
                Swap( & standardArray[j], & standardArray[j + 1]);
                SwapHelper(sourceArrays, j, j + 1);
            }
}
// postcondition: every swap applied to the standard array will also be applied
// to each of the source arrays.


void InversionsHelper(int sortMethod, int sourceArrays[NUM_FILES][FILE_SIZE],
    int inversionsArray[]) {
    switch (sortMethod) {
    case 1:
        for (int i = 0; i < NUM_FILES; i++)
            inversionsArray[i] = MergeSort(sourceArrays[i], 0, FILE_SIZE - 1);
        break;
    case 2:
        for (int i = 0; i < NUM_FILES; i++)
            inversionsArray[i] = QuickSort(sourceArrays[i], FILE_SIZE);
        break;
    case 3:
        for (int i = 0; i < NUM_FILES; i++)
            inversionsArray[i] = BubbleSort(sourceArrays[i]);
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
    FillArrays(sourceArrays); //read data from source_.txt into sourceArrays[_]
    ComputeStandardArray(sourceArrays, standardArray);

    BubbleSortStandardArray(standardArray, sourceArrays); //sort source arrays sccording to sorted standard array

    int sortMethod;

    do {
        printf("Enter 1 for %s, 2 for %s, or 3 for %s: ", SORT_NAMES[0],
            SORT_NAMES[1], SORT_NAMES[2]);
        scanf("%d", & sortMethod);
    } while (sortMethod < 1 || sortMethod > 3);

    InversionsHelper(sortMethod, sourceArrays, inversionsArray);

    PrintResults(inversionsArray, sortMethod);

    return 0;
}
//postcondition: # of inversions of each source will computed and be printed to console

/*
	Program Written by:
		Quinten Bruce
		Qiang Chen
		Josh Badrina
		Rory Campbell
*/
