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

void Swap(recordtype *a, recordtype *b) {
	recordtype temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void SelectionSort(recordtype a[], int n) {
	int i, j, lowindex;
	keytype lowkey;
	for (i = 0; i < n - 1; i++) {
		lowkey = a[i].key;
		lowindex = i;
		for (j = i + 1; j < n; j++) {
			if (a[j].key < lowkey) {
				lowkey = a[j].key;
				lowindex = j;
			}
		}
		Swap(&a[i], &a[lowindex]);
	}
}

void Read_Data(recordtype a[], int *n) {
	int i = 0;
	FILE *f;
	f = fopen("data1.txt", "r");
	if (f == NULL) printf("\nLoi! Khong the mo file...\n");
	else {
		while (!feof(f)) {
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	}
	fclose(f);
	*n = i;
}

void Print_Data(recordtype a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%3d %5d %8.2f\n", i + 1, a[i].key, a[i].otherfields);
//		if (i % 10000 == 0) {
//			getch();
//		}
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
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j].key < a[j - 1].key) Swap(&a[j], &a[j - 1]);
		}
	}
}

int FindPivot(recordtype a[], int i, int j) {
	keytype firstkey;
	int k = i + 1;
	firstkey = a[i].key;
	while (k <= j && a[k].key == firstkey) k++;
	if (k > j) return -1;
	if (a[k].key > firstkey) return k;
	return i;
}

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


void PushDown(recordtype a[], int first, int last) {
	int r = first;
	while (r <= (last - 1) / 2)
		if (last == 2 * r + 1) {
			if (a[r].key < a[last].key) Swap(&a[r], &a[last]);
			r = last;
		} else 
			if (a[r].key < a[2 * r + 1].key && a[2 * r + 1].key >= a[2 * r + 2].key) {
				Swap(&a[r], &a[2 * r + 1]);
				r = 2 * r + 1;
			} else
				if (a[r].key < a[2 * r + 2].key) {
					Swap(&a[r], &a[2 * r + 2]);
					r = 2 * r + 2;
				}
				else r = last;
}

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

void Merge(recordtype a[], int begin, int middle, int end, recordtype b[]) {
	int i = begin, j = middle, k = begin;
	while (i < middle && j < end)
		if (a[i].key < a[j].key) {
			b[k++] = a[i++];
		}
		else b[k++] = a[j++];
	while (i < middle) b[k++] = a[i++];
	while (j < end) b[k++] = a[j++];
}

void SplitMerge(recordtype b[], int begin, int end, recordtype a[]) {
	if (end - begin == 1) return;
	int middle = (begin + end) / 2;
	SplitMerge(a, begin, middle, b);
	SplitMerge(a, middle, end, b);
	Merge(b, begin, middle, end, a);
}

void CopyArray(recordtype a[], int n, recordtype b[]) {
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

void MergeSort(recordtype a[], int n) {
	recordtype b[n];
	CopyArray(a, n, b);
	SplitMerge(b, 0, n, a);
}

int getInterval(int n) {
	int k;
	while (k < n / 3) k = k * 3 + 1;
	return k;
}

void ShellSort(recordtype a[], int n) {
	int i, j;
	int k = getInterval(n);
	while (k >= 1) {
		for (i = k; i < n; i++) {
			j = i;
			while (j >= k && a[j].key < a[j - k].key) {
				Swap(&a[j], &a[j - k]);
				j = j - k;
			}
		}
		k = (k - 1) / 3;
	}
}

recordtype a[1000001];
int main() {
	int n;
	Read_Data(a, &n);
	printf("Du lieu ban dau:\n");
	Print_Data(a, n);
	long long begin = GetTickCount();
	SelectionSort(a, n);
//	InsertionSort(a, n);
//	BubbleSort(a, n);
	QuickSort(a, 0, n - 1);
//	HeapSort(a, n);
//	MergeSort(a, n);
//	ShellSort(a, n);
	printf("Ket qua sap xep:\n");
	Print_Data(a, n);
	long long end = GetTickCount();
	double usedtime = (end - begin)*1e-3;
	printf("Thoi gian chay cua chuong trinh la: %.2lfs", usedtime);
	return 0;
}
