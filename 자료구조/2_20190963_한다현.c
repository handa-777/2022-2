#include<stdio.h>
#include<time.h>

typedef struct {
	int coef;
	int expon;
} poly;
poly term[1001];
int avail = 0;

void readPoly(FILE *fp);
void padd(int starta, int finisha, int startb, int finishb, int startc, int finishc, int* startd, int* finishd);
void printPoly(int start, int end);
void attach(int coefficient, int exponent);

int main() {
	double duration;
	clock_t start = clock();

	FILE* fa, * fb, * fc;
	fa = fopen("A.txt", "r");
	fb = fopen("B.txt", "r");
	fc = fopen("c.txt", "r");
	int starta, startb, startc, startd, finishd;

	starta = avail;
	readPoly(fa);
	startb = avail;
	readPoly(fb);
	startc = avail;
	readPoly(fc);

	padd(starta, startb - 1, startb, startc - 1, startc, avail - 1, &startd, &finishd);

	printPoly(startd, finishd);

	fclose(fa);
	fclose(fb);
	fclose(fc);

	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	printf("[Finished in %.1fs]\n", duration);

	return 0;
}
void readPoly(FILE* fp) {
	int state;
	while (1) {
		state = fscanf(fp, "%d %d", &term[avail].coef, &term[avail].expon);
		if (state == EOF)
			break;
		avail++;
	}
}
void padd(int starta, int finisha, int startb, int finishb, int startc, int finishc, int* startd, int* finishd) {
	int coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb && startc <= finishc) {
		if (term[starta].expon > term[startb].expon && term[starta].expon > term[startc].expon) {
			attach(term[starta].coef, term[starta].expon);
			starta++;
		}
		else if (term[startb].expon > term[starta].expon && term[startb].expon > term[startc].expon) {
			attach(term[startb].coef, term[startb].expon);
			startb++;
		}
		else if (term[startc].expon > term[startb].expon && term[startc].expon > term[starta].expon) {
			attach(term[startb].coef, term[startb].expon);
			startb++;
		}
		else if (term[starta].expon == term[startb].expon && term[starta].expon > term[startc].expon) {
			coefficient = term[starta].coef + term[startb].coef;
			if (coefficient)
				attach(coefficient, term[starta].expon);
			starta++;
			startb++;
		}
		else if (term[starta].expon == term[startc].expon && term[starta].expon > term[startb].expon) {
			coefficient = term[starta].coef + term[startc].coef;
			if (coefficient)
				attach(coefficient, term[starta].expon);
			starta++;
			startc++;
		}
		else if (term[startc].expon == term[startb].expon && term[startc].expon > term[starta].expon) {
			coefficient = term[startc].coef + term[startb].coef;
			if (coefficient)
				attach(coefficient, term[startc].expon);
			startc++;
			startb++;
		}
		else if (term[starta].expon == term[startb].expon && term[startb].expon == term[startc].expon) {
			coefficient = term[starta].coef + term[startb].coef + term[startc].coef;
			if (coefficient)
				attach(coefficient, term[starta].expon);
			starta++;
			startb++;
			startc++;
		}
	}
	for (; starta <= finisha; starta++) {
		attach(term[starta].coef, term[starta].expon);
	}
	for (; startb <= finishb; startb++) {
		attach(term[startb].coef, term[startb].expon);
	}
	for (; startc <= finishc; startc++) {
		attach(term[startc].coef, term[startc].expon);
	}
	*finishd = avail - 1;
}
void attach(int coefficient, int exponent) {
	term[avail].coef = coefficient;
	term[avail++].expon = exponent;
}
void printPoly(int start, int end) {
	for (int i = start; i < end; i++) {
		printf("(%d,%d), ", term[i].coef, term[i].expon);
	}
	printf("(%d,%d)\n", term[end].coef, term[end].expon);
}
