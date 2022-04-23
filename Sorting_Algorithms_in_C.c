
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N1 100
#define N2 500
#define N3 10000
#define SWAP(x,y) {int t; t=x; x=y; y=t;}

void setDecresingInput(int arr[], int size) {
	for (int i = 0; i < size; i++)
		arr[i] = size - i;
	printf("■input: [%d %d %d ... %d %d %d]\n", arr[0], arr[1], arr[2], arr[size - 3], arr[size - 2], arr[size - 1]);
}

void checkCorrectAnswer(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] != i + 1) {
			printf("wrong answer, with size %d\n", size);
			return;
		}
	}
	printf("■output: [%d %d %d ... %d %d %d]\n", arr[0], arr[1], arr[2], arr[size - 3], arr[size - 2], arr[size - 1]);
	printf("correct answer, with size %d\n", size);
	return;
}

void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++)
		printf("%3d ", arr[i]);
	printf("\n");
}

// Assume that the size of all input arrays is greater than 1,
// and also there is no same value ////
void bubbleSort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) 
				SWAP(arr[i], arr[j]);
		}
	}
}
// 안에 반복문은 j=0부터 할 필요없이, i+1부터 하면된다. 왜냐하면 앞에서부터 1개씩은 정렬되기 때문.

void insertionSort(int arr[], int size) {
	int key, j;
	for (int i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
// while문안에서 shift 하는것이 swap보다 약간 더 빠를거라 기대함.

void mergeSort(int arr[], int size, int start, int end) {
	if (start == end) return;

	int mid = (start + end) / 2;
	mergeSort(arr, size, start, mid);
	mergeSort(arr, size, mid + 1, end);

	int* sortedArr = (int*)malloc(sizeof(int) * (end - start + 1));

	int l = start, r = mid + 1, s = 0;
	while (l <= mid && r <= end) {
		if (arr[l] < arr[r])
			sortedArr[s++] = arr[l++];
		else
			sortedArr[s++] = arr[r++];
	}
	while (l <= mid)
		sortedArr[s++] = arr[l++];

	while (r <= end)
		sortedArr[s++] = arr[r++];

	s = 0;
	for (int i = start; i <= end; i++, s++) {
		arr[i] = sortedArr[s];
	}

	free(sortedArr);

}
// 크기 1이면 그대로 리턴, 그외에는 절반씩 recursive 하고, 절반 sort 된 상태에서 각자 sorting

void quickSort(int arr[], int start, int end) {
	if (start >= end) return;

	int mid = (start + end) / 2;
	SWAP(arr[mid], arr[end]);

	int pivot = arr[end];
	int l = start, r = end - 1;
	while (l <= r) {
		while (arr[l] < pivot && l < end) // l can move start to end
			l++;
		while (arr[r] > pivot && r > start) // r can move end-1 to start
			r--;
		if (l < r) {
			SWAP(arr[l], arr[r]);
		}
		else if (l == r) {
			break;
		}
	}
	SWAP(arr[l], arr[end]);
	// now pivot index is 'l'

	quickSort(arr, start, l - 1);
	quickSort(arr, l + 1, end);
}

void radixSort(int arr[], int size) {
	int maxExp = 1;
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	while (max != 0) {
		max /= 10;
		maxExp *= 10;
	}
	maxExp /= 10;

	int nowExp = 1;
	int* nowArr = (int*)malloc(sizeof(int) * size);

	// using counting sort
	while (nowExp <= maxExp) {
		int bucket[10] = { 0,0,0,0,0,0,0,0,0,0 };
		for (int i = 0; i < size; i++)
			bucket[arr[i] / nowExp % 10]++;
		for (int i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (int i = size - 1; i >= 0; i--) //to stable
			nowArr[--bucket[arr[i] / nowExp % 10]] = arr[i];
		for (int i = 0; i < size; i++)
			arr[i] = nowArr[i];
		nowExp *= 10;
	}
	free(nowArr);
}

void bucketSort(int arr[], int size) {
	int bucketNum = size / 20;
	int** bucket = (int**)malloc(sizeof(int**) * bucketNum);
	for (int i = 0; i < bucketNum; i++)
		bucket[i] = (int*)malloc(sizeof(int*) * size);

	int* bucketSize = (int*)malloc(sizeof(int*) * bucketNum);
	for (int i = 0; i < bucketNum; i++) {
		bucketSize[i] = 0; //each bucket's element count
	}

	int min = arr[0], max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min)
			min = arr[i];
		else if (arr[i] > max)
			max = arr[i];
	}

	int place;
	for (int i = 0; i < size; i++) {
		place = (arr[i] - min) * bucketNum / (max - min);
		if (place == bucketNum) place--;

		bucket[place][bucketSize[place]++] = arr[i];
	}
	for (int i = 0; i < bucketNum; i++) {
		insertionSort(bucket[i], bucketSize[i]);
	}

	printf("%d\n", 2323);


	int idx = 0;
	for (int i = 0; i < bucketNum; i++) {
		for (int j = 0; j < bucketSize[i]; j++) {
			arr[idx++] = bucket[i][j];
		}
	}

	for (int i = 0; i < bucketNum; i++) {
		free(bucket[i]);
	}
	free(bucket);
}


int main() {
	int arr1[N1];
	int arr2[N2];
	int arr3[N3];

	clock_t start, end;
	
	setDecresingInput(arr3, N3);
	start = clock();
	bubbleSort(arr3, N3);
	end = clock();
	checkCorrectAnswer(arr3, N3);
	printf("시간: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n");

	setDecresingInput(arr3, N3);
	start = clock();
	insertionSort(arr3, 0, N3-1);
	end = clock();
	checkCorrectAnswer(arr3, N3);
	printf("시간: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n");

	setDecresingInput(arr3, N3);
	start = clock();
	mergeSort(arr3, N3, 0, N3-1);
	end = clock();
	checkCorrectAnswer(arr3, N3);
	printf("시간: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n");
}
