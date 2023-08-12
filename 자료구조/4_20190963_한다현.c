#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100

int nfind(char string[], char pattern[]);
int pmatch(char string[], char pattern[]);
void fail(char pattern[]);
int failure[MAX_SIZE];
int kmp_count = 0;

int main() {
	char string[MAX_SIZE], pattern[MAX_SIZE];
	int result1, result2;
	scanf("%s", string);
	scanf("%s", pattern);

	result1 = nfind(string, pattern);
	fail(pattern);
	result2 = pmatch(string, pattern);

	if (result1 != -1) {
		printf("nfind:\tYES %d\n", result1);
	}
	else {
		printf("nfind:\tNO\n");
	}

	if (result2 != -1) {
		printf("kmp:\tYES %d\n", kmp_count);
	}
	else {
		printf("kmp:\tNO\n");
	}

	return 0;
}
int nfind(char string[], char pattern[]) {
	int i, j, start = 0, count = 0, k = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pattern) - 1; 
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		count++;
		if (string[endmatch] == pattern[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pattern[j]; i++, j++)
				count++, k++;
		}
		if (k == lastp) {
			return count;
		}
		else
			k = 0;
	}
	return -1;
}
int pmatch(char string[], char pattern[]) {
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pattern);
	while (i < lens && j < lenp) {
		kmp_count++;
		if (string[i] == pattern[j]) {
			i++;
			j++;
		}
		else if (j == 0) {
			i++;
		}
		else {
			j = failure[j - 1] + 1;
		}
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
void fail(char pattern[]) {
	int i, n = strlen(pattern);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		kmp_count++;
		i = failure[j - 1];
		while ((pattern[j] != pattern[i + 1]) && (i >= 0)) {
			kmp_count++;
			i = failure[i];
		}
		if (pattern[j] == pattern[i + 1]) {
			failure[j] = i + 1;
		}
		else {
			failure[j] = -1;
		}
	}
}