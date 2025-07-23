#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define size 30
typedef struct{
	float doDai;
	int dau, cuoi;
}canh;
void readFile(canh dsc[], int *n){
	FILE *f=fopen("TSP.txt", "r");
	if(f!=NULL){
		fscanf(f, "%d", n);
		int i, j, t, k=0;
		float temp;
		while(!feof(f)){
			for(i=0;i<*n;i++){
				for(j=i;j<*n;j++){
					if(i==j) for(t=0;t<=j;t++) fscanf(f, "%f", &temp);
					else{
						fscanf(f, "%f", &dsc[k].doDai);
						dsc[k].dau=i;
						dsc[k].cuoi=j;
						k++;
					}
				}
			}
		}
	}
	fclose(f);
}
void swap(canh *a, canh *b){
	canh temp=*a;
	*a=*b;
	*b=temp;
}
void bubbleSort(canh dsc[], int n){
	int i, j;
	for(i=0;i<n-1;i++){
		for(j=n-1;j>i;j--){
			if(dsc[j].doDai<dsc[j-1].doDai) swap(&dsc[j], &dsc[j-1]);
		}
	}
}
void init_foreign(int parent[], int n){
	int i;
	for(i=0;i<n;i++) parent[i]=i;
}
int find_root(int parent[], int u){
	while(parent[u]!=u) u=parent[u];
	return u;
}
int chutrinh(int r_dau, int r_cuoi){
	return r_dau==r_cuoi;
}
void update_foreign(int parent[], int r1, int r2){
	parent[r2]=r1;
}
int dinh_cap3(canh dspa[], int k, canh canhmoi){
	int i, dem;
	i=0;
	dem=1;
	while(i<k && dem<3){
		if(canhmoi.dau==dspa[i].dau || canhmoi.dau==dspa[i].cuoi) dem++;
		i++;
	}
	if(dem==3) return 1;
	i=0;
	dem=1;
	while(i<k && dem<3){
		if(canhmoi.cuoi==dspa[i].dau || canhmoi.cuoi==dspa[i].cuoi) dem++;
		i++;
	}
	return dem==3;
}
void greedy(canh dsc[], canh PA[], int n){
	int i, j;
	int parent[n];
	init_foreign(parent, n);
	int r_dau, r_cuoi;
	j=0;
	for(i=0;i<n*(n-1)/2 && j<n-1;i++){
		r_dau=find_root(parent, dsc[i].dau);
		r_cuoi=find_root(parent, dsc[i].cuoi);
		if(!chutrinh(r_dau, r_cuoi) && !dinh_cap3(PA, j, dsc[i])){
			PA[j++]=dsc[i];
			update_foreign(parent, r_dau, r_cuoi);
		}
	}
	for(;i<n*(n-1);i++){
		r_dau=find_root(parent, dsc[i].dau);
		r_cuoi=find_root(parent, dsc[i].cuoi);
		if(chutrinh(r_dau, r_cuoi) && !dinh_cap3(PA, n-1, dsc[i])){
			PA[n-1]=dsc[i];
			break;
		}
	}
}
void inDSC(canh dsc[], int n, int la_PA){
	int i;
	float tong=0.0;
	for(i=0;i<n;i++){
		printf("%d. %c%c = %.2f\n", i+1, dsc[i].dau+97, dsc[i].cuoi+97, dsc[i].doDai);
		if(la_PA) tong+=dsc[i].doDai;
	}
	if(la_PA) printf("Tong do dai duong di = %.2f", tong);
}
int main(){
	int n;
	canh dsc[size];
	readFile(dsc, &n);
	printf("Phuong an TSP dung thuat toan THAM AN:\n");
	printf("Cac canh truoc khi sap xep:\n");
	inDSC(dsc, n*(n-1)/2, 0);
	bubbleSort(dsc, n*(n-1)/2);
	printf("Cac canh sau khi sap xep:\n");
	inDSC(dsc, n*(n-1)/2, 0);
	canh PA[n];
	greedy(dsc, PA, n);
	printf("PHUONG AN:\n");
	inDSC(PA, n, 1);
	return 0;
}
