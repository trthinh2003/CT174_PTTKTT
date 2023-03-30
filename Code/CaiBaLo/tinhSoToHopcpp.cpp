#include <stdio.h>
#include <conio.h>
#include <windows.h>

int DP_Comb(int n, int k) {
	int C[n + 1][n + 1], i, j;
	C[0][0] = 1;
	for (i = 1; i <= n; i++) {
		C[i][0] = 1;
		C[i][i] = 1;
		for (j = 1; j < i; j++) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
	return C[n][k];
}

int main() {
	int k, n;
	printf("---------CHUONG TRINH TINH SO TO HOP CHAP k cua n---------\n");
	printf("Nhap vao k: "); scanf("%d", &k);
	printf("Nhap vao n: "); scanf("%d", &n);
	if (k > n) {
		printf("\nLoi toan hoc (k <= n)...");
		exit(0);
	}
	printf("\n->Gia tri to hop chap %d cua %d la: %d", k, n, DP_Comb(n, k));
	return 0;
}