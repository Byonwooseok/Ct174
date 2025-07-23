#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
	char ten[25];
	float TL, GT, DG;
	int PA;
}DoVat;
DoVat *readFile(float *W, int *n){
	FILE *f=fopen("caibalo1.txt", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while(!feof(f)){
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].ten);
		dsdv[i].DG=dsdv[i].GT/dsdv[i].TL;
		dsdv[i].PA=0;
		i++;
		dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	fclose(f);
	*n=i;
	return dsdv;
}
void swap(DoVat *a, DoVat *b){
	DoVat temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void bubbleSort(DoVat *dsdv, int n){
	int i, j;
	for(i=0;i<n-1;i++){
		for(j=n-1;j>i;j--){
			if(dsdv[j].DG>dsdv[j-1].DG) swap(&dsdv[j], &dsdv[j-1]);
		}
	}
}
void greedy(DoVat *dsdv, float W, int n){
	int i;
	for(i=0;i<n;i++){
		dsdv[i].PA=W/dsdv[i].TL;
		W-=dsdv[i].PA*dsdv[i].TL;
	}
}
void inDSDV(DoVat *dsdv, int n, float W){
	int i;
	float tongTL=0, tongGT=0;
	printf("Phuong an cai ba lo 1 dung thuat toan THAM AN nhu sau:\n\n");
	printf("Trong luong cua ba lo = %-9.2f\n\n", W);
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("|STT|    Ten Do Vat    | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d     |\n", i+1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
		tongTL+=dsdv[i].PA*dsdv[i].TL;
		tongGT+=dsdv[i].PA*dsdv[i].GT;
	}
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for(i=0;i<n-1;i++){
		printf("%d, ", dsdv[i].PA);
	}
	printf("%d)\n", dsdv[n-1].PA);
	printf("Tong trong luong = %-9.2f\n", tongTL);
	printf("Tong gia tri = %-9.2f", tongGT);
}
int main(){
	int n;
	float W;
	DoVat *dsdv;
	dsdv=readFile(&W, &n);
	bubbleSort(dsdv, n);
	greedy(dsdv, W, n);
	inDSDV(dsdv, n, W);
	free(dsdv);
	return 0;
}
