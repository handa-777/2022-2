#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int row, column, value;
}Term;

#define MAX_TERMS 1024
int n, m;
int cCount = 0;

void readMatrix(FILE* fp, Term a[]);
void printMatrix(Term a[]);
void matrixAdd(Term a[], Term b[], Term c[]);

int main(void) {
	Term a[MAX_TERMS], b[MAX_TERMS], c[MAX_TERMS];
	FILE* fp = fopen("A.txt", "r");
	readMatrix(fp, a);
	fclose(fp);

	fp = fopen("B.txt", "r");
	readMatrix(fp, b);
	fclose(fp);

	matrixAdd(a, b, c);
	printMatrix(c);
	return 0;
}
void readMatrix(FILE* fp, Term a[]) {
	int i, j;
	int num;
	int count = 0;
	fscanf(fp, "%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fscanf(fp, "%d", &num);
			a[count].value = num;
			a[count].column = j;
			a[count].row = i;
			count++;
		}
	}
}
void matrixAdd(Term a[], Term b[], Term c[]) {
	int i, j;
	int count = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (a[count].value + b[count].value != 0) {
				c[cCount].value = a[count].value + b[count].value;
				c[cCount].column = j;
				c[cCount].row = i;
				cCount++;
			}
			count++;
		}
	}
}
void printMatrix(Term a[]) {
	printf("%d %d %d\n", n, m, cCount);
	for (int i = 0; i < cCount; i++) {
		printf("%d %d %d\n", a[i].row, a[i].column, a[i].value);
	}
}