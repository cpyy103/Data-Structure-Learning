#ifndef SORT_H
#define SORT_H

void SortTest(void);

void swap(int *a, int *b);
void InsertSort(int A[], int n);
void InsertSort_2(int A[], int n);
void ShellSort(int A[], int n);
void ShellSort_2(int A[], int n);
void BubbleSort(int A[], int n);
void BubbleSort_2(int A[], int n);
void QuickSort(int A[], int left, int right);
int partition(int A[], int left, int right);
void QuickSort_2(int A[], int left, int right);
int K_Elem(int A[], int left, int right, int k);
void SelectSort(int A[], int n);
void SelectSort_2(int A[], int n);
void BuildMaxHeap(int A[], int n);
void AdjustHeap(int A[], int k, int n);
void HeapSort(int A[], int n);
bool isMaxHeap(int A[], int n);
void merge(int A[], int left, int mid, int right);
void MergeSort_1(int A[], int left, int right);
void MergeSort_2(int A[], int n);
void CountSort(int A[], int n);

void Sort_2(void);



#endif

