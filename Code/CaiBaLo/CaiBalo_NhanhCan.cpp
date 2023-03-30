#include <stdio.h>
#include<string.h>
#include <malloc.h>

typedef struct {
	char TenDV[50];
	float TL, DG, GT;
	int PA;
} DoVat;

DoVat *readfile(float *W, int *n) {
	FILE *f;
	f = fopen ("CaiTui1.txt", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f)) {
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].TenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat) * (i + 1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void swap(DoVat *x, DoVat *y) {
	DoVat Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}

void BubbleSort(DoVat *dsdv, int n) {
	int i, j;
	for (i = 0; i <= n - 2; i++) {
		for (j = n - 1; j >= i + 1; j--) {
	   		if (dsdv[j].DG > dsdv[j - 1].DG) {
				swap(&dsdv[j], &dsdv[j - 1]);
			}
		}
	}
}

void InDSDV(DoVat *dsdv ,int n, float W) {
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri | Don gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");
	for (i = 0; i < n; i++) {
		printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n", i + 1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
		TongTL += dsdv[i].PA * dsdv[i].TL;
		TongGT += dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|--------------------|---------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9.2f\n", W);
	printf("Tong trong luong = %-9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

// Tinh cac dai luong tai nut goc
void Tao_Nut_Goc(float W, float *V, float *CT, float *GLNTT, float *TGT, float DG_Max) {
	*TGT = 0.0;
	*V = W;
	*CT = *V * DG_Max; 	// Can tren cua nut goc
	*GLNTT = 0.0;
} 

//Ghi nhan phuong an tot nhat tam thoi
void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int i;
	if (*GLNTT < TGT) {
		*GLNTT = TGT;
		for (i = 0; i < n; i++) dsdv[i].PA = x[i];
	}
}

int min(int a, int b) {
	return a < b ? a : b;
}

void Nhanh_Can(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int j; 	// j la so vat duoc chon
	int yk; 	// So do vat lon nhat co the chon
	yk = *V / dsdv[i].TL;	
	for (j = yk; j >= 0; j--) {			// Xet tat ca cac kha nang co the phan nhanh theo so luong do vat
	 									// Ung voi mot gia tri cua j la mot nut tren cay 
	 									// Tinh 3 dai luong cua mot nut trong		
		*TGT = *TGT + j * dsdv[i].GT;
		*V = *V - j * dsdv[i].TL;
		*CT = *TGT + *V * dsdv[i + 1].DG;	// dsdv[i+1].DG la DG vat ke tiep cua vat i (i + 1)
		
		if (*CT > *GLNTT) { 					// Truong hop Chua cat tia (Dieu kien Cat tia la khi CT <= GLNTT)
			x[i] = j;
		 	if ((i == n - 1) || (*V == 0)) 		// Da xet het tat ca cac do vat hoac ba lo da day
		 		Cap_Nhat_GLNTT(*TGT, GLNTT, x, dsdv, n);
		 	else
		 		Nhanh_Can(i + 1, TGT, CT, V, GLNTT, x, dsdv, n); //Xet nut con cua nut i
	 	}
	 // Quay lui xet nut khac
		x[i] = 0;
		*TGT = *TGT - j * dsdv[i].GT;	// Tra lai Tong gia tri cua nut cha
		*V = *V + j * dsdv[i].TL;		// Tra lai Trong luong con lai cua nut cha
	}
}
	
int main() {
	DoVat *dsdv;	
	int n; 			
	float W, CT, TGT, V, GLNTT ; 		

	dsdv = readfile(&W, &n);	
	int x[n];		
	BubbleSort(dsdv, n);
	Tao_Nut_Goc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	Nhanh_Can(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	InDSDV(dsdv, n, W);
	
	free(dsdv);
	return 0;
}