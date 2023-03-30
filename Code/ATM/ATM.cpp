#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char TenTien[25];
	int MG, PA;
} Tien;

void Swap(Tien *a, Tien *b) {
	Tien temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(Tien a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (a[j].MG > a[j - 1].MG) {
				Swap(&a[j], &a[j - 1]);
			}
		}
	}
}

void ReadFromFile(Tien dslt[], int *n) {
	FILE *f;
	f = fopen("ATM.txt", "r");
	int i = 0;
	if (f == NULL) {
		printf("Loi mo file!\n");
		return;
	}
	while (!feof(f)) {
		fscanf(f, "%d%[^\n]", &dslt[i].MG, &dslt[i].TenTien);
		dslt[i++].PA = 0;
	}
	*n = i;
	fclose(f);
}

void inPA(Tien dslt[], int n) {
	int i;
	printf("\nPhuong an cho bai toan tra tien cua may ATM theo thuat toan THAM AN nhu sau:\n");
	printf("STT      	Ten tien                Ten menh gia      Phuong an\n");
	for (i = 0; i < n; i++) {
		printf("%2d	       %-20s      %9d 	%9d\n", i + 1, dslt[i].TenTien, dslt[i].MG, dslt[i].PA);
	}                                 
	printf("Phuong an (Theo thu tu giam dan) la: X(");
	for (i = 0; i < n - 1; i++) {
		printf("%d,", dslt[i].PA);
	}
	printf("%d)", dslt[n - 1].PA);
}

void Greedy(Tien dslt[], int n, int TienCanRut) {
	int i = 0;
	BubbleSort(dslt, n);
	while (i < n && TienCanRut > 0) {
		dslt[i].PA = TienCanRut / dslt[i].MG;
		TienCanRut = TienCanRut - dslt[i].PA * dslt[i].MG;
		i++;
	}
}

Tien dslt[100];
int main() {
	int n;
	int TienCanRut;
	printf("So tien ban muon rut la: "); scanf("%d", &TienCanRut);
	ReadFromFile(dslt, &n);
	BubbleSort(dslt, n);
	Greedy(dslt, n, TienCanRut);
	inPA(dslt, n);
	
	return 0;
}