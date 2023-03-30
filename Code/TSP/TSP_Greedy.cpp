#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	float doDai;
	int dau, cuoi;
} canh;

void swap(canh *x, canh *y) {
	canh tmp = *x;
	*x = *y;
	*y = tmp;
}

void bubbleSort(canh a[], int n) {
	int i, j;
	for (i = 0; i <= n - 2; i++){
		for (j = n - 1; j >= i + 1; j--) {
			if (a[j].doDai < a[j - 1].doDai) {
				swap(&a[j], &a[j - 1]);
			}
		}
	}
}

void readFromFile(canh a[], int *n){
	int i, j, t;
	float temp;
	FILE* f = fopen("TSP.txt", "r");
	if (f) {
		fscanf(f, "%d", n);
		int k = 0;
		for (i = 0; i < *n; i++) {
			for (j = i; j < *n; j++) {
				if (i == j) {
					for (t = 0; t <= j; t++) fscanf(f, "%f", &temp);
				}
				else {
					fscanf(f, "%f", &a[k].doDai);
					a[k].dau = i;
					a[k].cuoi = j;
					k++;
				}
			}
		}
		fclose(f);
	}
	else {
		printf("Loi Mo File");		
	}
}

void inDSCanh(canh a[], int m, int laPA) {
	int i = 0;
	float tong = 0.0;
	for (i = 0 ; i < m; i++) {
		tong += a[i].doDai;
		printf("%3d %c%c = %8.2f\n", i + 1, a[i].dau + 65, a[i].cuoi + 65, a[i].doDai);
	}
	if (laPA == 1) {
		printf("Tong do dai cac canh la: %8.2f", tong);
	}
}

int laDinhCap3(canh PA[], int k, canh moi) {
	int i, dem;
	i = 0;
	dem = 1;
	while (i < k && dem < 3) {
		if (moi.dau == PA[i].cuoi || moi.dau == PA[i].dau) {
			dem++;
		}
		i++;
	}
	if (dem == 3) return 1;
	i = 0;
	dem = 1;
	while (i < k && dem < 3) {
		if (moi.cuoi == PA[i].cuoi || moi.cuoi == PA[i].dau) {
			dem++;
		}
		i++;
	}
	return dem == 3;
}

void initForest(int parent[], int n) {
	int i = 0;
	for (i = 0 ; i < n; i++) {
		parent[i] = i;
	}
}

int findRoot(int u, int parent[]) {
	while (u != parent[u]) {
		u = parent[u];
	}
	return u;
}

int laChuTrinh(int rDau, int rCuoi) {
	return rDau == rCuoi;
}

void updateForest(int parent[], int r1, int r2) {
	parent[r2] = r1;
}

void Greedy(canh dsCanh[], int n, canh PA[]) {
	int i, j;
	int parent[n];
	initForest(parent, n);
	int rDau, rCuoi;
	
	j = 0;
	for (i = 0; (i < n * (n - 1) / 2) && (j < n - 1); i++) {
		rDau = findRoot(dsCanh[i].dau, parent);
		rCuoi = findRoot(dsCanh[i].cuoi, parent);
		if (!laDinhCap3(PA, j, dsCanh[i]) && !laChuTrinh(rDau, rCuoi)) {
			PA[j] = dsCanh[i];
			j++;
			updateForest(parent, rDau, rCuoi);
		}
	}
	
	for (; i < n * (n - 1) / 2; i++) {
		rDau = findRoot(dsCanh[i].dau, parent);
		rCuoi = findRoot(dsCanh[i].cuoi, parent);
		if (!laDinhCap3(PA, n - 1, dsCanh[i]) && laChuTrinh(rDau, rCuoi)) {
			PA[n - 1] = dsCanh[i];
			break;
		}
	}
}

int main(){
	canh dsCanh[200];
	int n;
	readFromFile(dsCanh, &n);
	canh PA[n];
	bubbleSort(dsCanh, n * (n - 1) / 2);
	printf("Danh Sach Cac Canh Cua Do Thi Da Sap Xep:\n");
	inDSCanh(dsCanh, n * (n - 1) / 2, 0);
	Greedy(dsCanh, n, PA);
	printf("\nPHUONG AN:\n");
	inDSCanh(PA, n, 1);
	return 0;
}