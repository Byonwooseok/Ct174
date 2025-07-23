#include<stdio.h>
typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;

void swap(recordtype *x, recordtype *y){
	recordtype temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

void readData(recordtype a[], int *n){
	FILE *f;
	f=fopen("data.txt", "r");
	int i=0;
	if(f!=NULL)
		while(!feof(f)){
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	else printf("Loi mo file\n");
	fclose(f);
	*n=i;
}

void printData(recordtype a[], int n){
	int i;
	for(i=0;i<n;i++){
		printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].otherfields);
	}
}

int findPivot(recordtype a[], int i, int j){
	int k=i+1;
	keytype firstkey=a[i].key;
	while(k<=j && a[k].key==firstkey) k++;
	if(k>j) return -1;
	else{
		if(a[k].key<firstkey) return k;
		return i;
	}
}

int partition(recordtype a[], int i, int j, keytype pivot){
	int L=i, R=j;
	while(L<=R){
		while(a[L].key<=pivot) L++;
		while(a[R].key>pivot) R--;
		if(L<R) swap(&a[L], &a[R]);
	}
	return L;
}

void quickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex, k;
	pivotindex=findPivot(a, i, j);
	if(pivotindex!=-1){
		pivot=a[pivotindex].key;
		k=partition(a, i, j, pivot);
		quickSort(a, i, k-1);
		quickSort(a, k, j);
	}
}

int main(){
	recordtype a[100];
	int n;
	printf("Thuat toan sap xep quickSort:\n");
	readData(a, &n);
	printf("Du lieu truoc khi sap xep:\n");
	printData(a, n);
	quickSort(a, 0, n-1);
	printf("Du lieu sau khi sap xep:\n");
	printData(a, n);
	return 0;
}
