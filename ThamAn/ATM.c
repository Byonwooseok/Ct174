#include<stdio.h>
#include<string.h>
#include<malloc.h>
typedef struct{
	char tenTien[25];
	int MG, PA;
}Tien;
Tien *readFile(int *n){
	FILE *f=fopen("ATM.txt", "r");
	int i=0;
	Tien *dslt=(Tien*)malloc(sizeof(Tien));
	while(!feof(f)){
		fscanf(f, "%d%[^\n]", &dslt[i].MG, &dslt[i].tenTien);
		dslt[i].PA=0;
		i++;
		dslt=(Tien*)realloc(dslt, sizeof(Tien)*(i+1));
	}
	fclose(f);
	*n=i;
	return dslt;
}
void swap(Tien *a, Tien *b){
	Tien temp=*a;
	*a=*b;
	*b=temp;
}
void bubbleSort(Tien *dslt, int n){
	int i, j;
	for(i=0;i<n-1;i++){
		for(j=n-1;j>i;j--){
			if(dslt[j].MG>dslt[j-1].MG) swap (&dslt[j], &dslt[j-1]);
		}
	}
}
void greedy(Tien *dslt, int n, int tienCanRut){
	int i=0;
	while(i<n && tienCanRut>0){
		dslt[i].PA=tienCanRut/dslt[i].MG;
		tienCanRut-=dslt[i].PA*dslt[i].MG;
		i++;
	}
}
void inDSLT(Tien *dslt, int n, int tienCanRut){
	int i;
	int tongTienTra=0;
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "Loai Tien", "Menh gia", "So to", "Thanh tien");
	printf("|---|-------------------------|---------|---------|----------|\n");
	for(i=0;i<n;i++){
		if(dslt[i].PA==0) printf("|%-3d|%-25s|%-9d|%-9s|%-10d|\n", i+1, dslt[i].tenTien, dslt[i].MG, "", dslt[i].PA*dslt[i].MG);
		else printf("|%-3d|%-25s|%-9d|%-9d|%-10d|\n", i+1, dslt[i].tenTien, dslt[i].MG, dslt[i].PA, dslt[i].PA*dslt[i].MG);
		tongTienTra+=dslt[i].PA*dslt[i].MG;
	}
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("Tien can rut = %-9d\n", tienCanRut);
	printf("Tong tien tra = %-9d\n", tongTienTra);
	printf("So tien khong rut duoc = %-9d", tienCanRut-tongTienTra);
}
int main(){
	int tienCanRut;
	printf("Nhap so tien can rut:");
	scanf("%d", &tienCanRut);
	int n;
	Tien *dslt=readFile(&n);
	bubbleSort(dslt, n);
	greedy(dslt, n, tienCanRut);
	inDSLT(dslt, n, tienCanRut);
	free(dslt);
	return 0;
}
