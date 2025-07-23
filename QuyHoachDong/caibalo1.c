#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
	char tenDV[25];
	int TL, GT, PA;
}DoVat;
typedef int bang[50][100];
DoVat *readFile(int *n, int *W){
	FILE *f=fopen("caibalo13.txt", "r");
	fscanf(f, "%d", W);
	DoVat *dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		dsdv[i].PA=0;
		i++;
		dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}
void inDSDV(DoVat *dsdv, int n, int W){
	int tongTL=0, tongGT=0;
	printf("Phuong an cai ba lo 1 dung thuat toan QUY HOACH DONG nhu sau:\n");
	printf("|---|------------------|------------|---------|-----------|\n");
	printf("|STT|    Ten do vat    | Trong luong| Gia tri | Phuong an |\n");
	printf("|---|------------------|------------|---------|-----------|\n");
	for(int i=0;i<n;i++){
		tongTL+=dsdv[i].PA*dsdv[i].TL;
		tongGT+=dsdv[i].PA*dsdv[i].GT;
		printf("|%-3d|%-18s|%-12d|%-9d|%-11d|\n", i+1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].PA);
	}
	printf("|---|------------------|------------|---------|-----------|\n");
	printf("Trong luong cua ba lo = %d\n", W);
	printf("Tong trong luong = %d\n", tongTL);
	printf("Tong gia tri = %d", tongGT);
}
void taoBang(DoVat *dsdv, int n, int W, bang F, bang X){
	int xk, yk, Fmax, Xmax, V, k;
	for(V=0;V<=W;V++){
		X[0][V]=V/dsdv[0].TL;
		F[0][V]=X[0][V]*dsdv[0].GT;
	}
	for(k=1;k<n;k++){
		for(V=0;V<=W;V++){
			Fmax=F[k-1][V];
			Xmax=0;
			yk=V/dsdv[k].TL;
			for(xk=1;xk<=yk;xk++){
				if(Fmax<F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT){
					Fmax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
					Xmax=xk;
				}
			}
			F[k][V]=Fmax;
			X[k][V]=Xmax;
		}
	}
}
void inBang(int n, int W, bang F, bang X){
	for(int k=0;k<n;k++){
		for(int V=0;V<=W;V++){
			printf("|%4d%2d", F[k][V], X[k][V]);
		}
		printf("\n");
	}
}
void traBang(DoVat *dsdv, int n, int W, bang X){
	int V=W;
	for(int k=n-1;k>=0;k--){
		dsdv[k].PA=X[k][V];
		V-=X[k][V]*dsdv[k].TL;
	}
}
int main(){
	int n, W;
	DoVat *dsdv=readFile(&n, &W);
	bang F, X;
	taoBang(dsdv, n, W, F, X);
	inBang(n, W, F, X);
	traBang(dsdv, n, W, X);
	inDSDV(dsdv, n, W);
	free(dsdv);
	return 0;
}
