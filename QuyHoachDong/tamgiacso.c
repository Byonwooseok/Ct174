#include<stdio.h>
#define size 30
void readFile(int a[][size], int *n){
	FILE *f=fopen("tam_giac_so.txt", "r");
	if(f==NULL){
		printf("Loi mo file!!!");
		return;
	}
	int i=0;
	while(!feof(f)){
		for(int j=0;j<=i;j++){
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}
	*n=i;
	fclose(f);
}
void printTGS(int a[][size], int n){
	printf("Tam giac so:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
int CS_max(int F[][size], int i, int j){
	if(j==0) return (F[i-1][0]>F[i-1][1])?0:1;
	if(j==i) return i-1;
	if(j==i-1) return (F[i-1][j]>F[i-1][j-1])?j:j-1;
	if(F[i-1][j-1]>F[i-1][j] && F[i-1][j-1]>F[i-1][j+1]) return j-1;
	if(F[i-1][j]>F[i-1][j-1] && F[i-1][j]>F[i-1][j+1]) return j;
	if(F[i-1][j+1]>F[i-1][j] && F[i-1][j+1]>F[i-1][j-1]) return j+1;
}
void taoBang(int a[][size], int n, int F[][size]){
	F[0][0]=a[0][0];
	F[1][0]=F[0][0]+a[1][0];
	F[1][1]=F[0][0]+a[1][1];
	for(int i=2;i<n;i++){
		for(int j=0;j<=i;j++){
			int k=CS_max(F, i, j);
			F[i][j]=F[i-1][k]+a[i][j];
		}
	}
}
void inBang(int F[][size], int n){
	printf("Bang F:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			printf("%d ", F[i][j]);
		}
		printf("\n");
	}
}
int CS_max_dong_cuoi(int F[], int j){
	int max=F[0], maxindex=0;
	for(int k=1;k<=j;k++){
		if(F[k]>max){
			max=F[k];
			maxindex=k;
		}
	}
	return maxindex;
}
void traBang(int a[][size], int n, int F[][size], int PA[]){
	int j=CS_max_dong_cuoi(F[n-1], n-1);
	PA[n-1]=a[n-1][j];
	for(int i=n-1;i>=1;i--){
		j=CS_max(F, i, j);
		PA[i-1]=a[i-1][j];
	}
}
int giaPA(int PA[], int n){
	int sum=0;
	for(int i=0;i<n;i++) sum+=PA[i];
	return sum;
}
void printPA(int PA[], int n){
	printf("Phuong an la duong di qua cac so:\n");
	for(int i=0;i<n-1;i++){
		printf("%d => ", PA[i]);
	}
	printf("%d\n", PA[n-1]);
	printf("Tong duong di = %d\n", giaPA(PA, n));
}
int main(){
	int a[size][size];
	int n;
	printf("Bai toan tam giac so dung thuat toan QUY HOACH DONG:\n");
	readFile(a, &n);
	printTGS(a, n);
	int F[n][n], PA[n];
	taoBang(a, n, F);
	inBang(F, n);
	traBang(a, n, F, PA);
	printPA(PA, n);
	return 0;
}
