#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfields;
} recordtype;

void Swap(recordtype *x, recordtype *y) {
	recordtype temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void SelectionSort(recordtype a[], int n) {
	int i, j, lowindex;
	keytype lowkey;
	for (i = 0; i < n - 1; i++) {
		lowkey = a[i].key;
		lowindex = i;
		for (j = i + 1; j < n; j++) {
			if (lowkey > a[j].key) {
				lowkey = a[j].key;
				lowindex = j;
			}
		}
		Swap(&a[i], &a[lowindex]);
	}
}

void InsertionSort(recordtype a[], int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		j = i;
		while (j > 0 && a[j].key < a[j - 1].key) {
			Swap(&a[j], &a[j - 1]);
			j--;
		}
	}
}

void BubbleSort(recordtype a[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = n - 1; j > i; j--) {
			if (a[j].key < a[j - 1].key) {
				Swap(&a[j], &a[j - 1]);
			}
		}
	}
}

//O(n)
int FindPivot(recordtype a[], int i, int j) {
	keytype firstkey;
	int k;
	k = i + 1;
	firstkey = a[i].key;
	while (k <= j && a[k].key == firstkey) k++;
	if (k > j) return -1;
	if (a[k].key > firstkey) return k;
	return i;
}

//O(n)
int Partition(recordtype a[], int i, int j, keytype pivot) {
	int L, R;
	L = i;
	R = j;
	while (L <= R) {
		while (a[L].key < pivot) L++;
		while (a[R].key >= pivot) R--;
		if (L < R) Swap(&a[L], &a[R]);
	}
	return L;
}

//O(nlogn), TH xau nhat la O(n^2)
void QuickSort(recordtype a[], int i, int j) {
	keytype pivot;
	int pivotindex, k;
	pivotindex = FindPivot(a, i, j);
	if (pivotindex != -1) {
		pivot = a[pivotindex].key;
		k = Partition(a, i, j, pivot);
		QuickSort(a, i, k - 1);
		QuickSort(a, k, j);
	}
}

//O(logn)
//Thiet ke ham PushDown cho thuat toan HeapSort
void PushDown(recordtype a[], int first, int last) {
	int r = first;
	while (r <= (last - 1) / 2) {
		if (last == 2 * r + 1) { //r chỉ có con trái
			if (a[r].key < a[last].key) Swap(&a[r], &a[last]);
			r = last;
		}
		else 
			if ((a[r].key < a[2 * r + 1].key) && (a[2 * r + 1].key >= a[2 * r + 2].key)) {
				Swap(&a[r], &a[2 * r + 1]);
				r = 2 * r + 1;
			}
			else
				if (a[r].key < a[2 * r + 2].key) {
					Swap(&a[r], &a[2 * r + 2]);
					r = 2 * r + 2;
				}
				else r = last;
	}
}

//O(nlogn)
void HeapSort(recordtype a[], int n) {
	int i;
	for (i = (n - 2) / 2; i >= 0; i--) {
		PushDown(a, i, n - 1);
	}
	for (i = n - 1; i >= 2; i--) {
		Swap(&a[0], &a[i]);
		PushDown(a, 0, i - 1);
	}
	Swap(&a[0], &a[1]);
}

void Read_Data(recordtype a[], int *n) {
	FILE *f;
	f = fopen("data1.txt", "r");
	int i = 0;
	if (f != NULL)
		while (!feof(f)) {
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		} else printf("\nLoi mo file...");
	fclose(f);
	*n = i;
}

void Print_Data(recordtype a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%3d %5d %8.2f\n", i + 1, a[i].key, a[i].otherfields);
	}
}

recordtype a[100005];
int main() {
	int n;
	Read_Data(a, &n);
	printf("Du lieu ban dau:\n");
	Print_Data(a, n);
	long long begin = GetTickCount();
//	SelectionSort(a. n);
//	InsertionSort(a, n);
//	BubbleSort(a, n);
//	QuickSort(a, 0, n - 1);
	HeapSort(a, n);
	printf("Ket qua sap xep:\n");
	Print_Data(a, n);
	long long end = GetTickCount();
	double usedtime = (end - begin)*1e-3;
	printf("Thoi gian chay cua chuong trinh la: %.2lf", usedtime);
	
	return 0;
}