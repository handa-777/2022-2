#include<stdio.h>
#include<time.h>

int insert(int* nums, int size);
int main() {
	FILE* data;
	int n;
	int size = 10;
	int* nums = (int*)malloc(size * sizeof(int));

	clock_t total_start = clock();
	data = fopen("lab1.data", "r");

	int i = 0;
	while (!feof(data)) {
		i++;
		n = fgetc(data);
		if (i % 2 == 1 && i/2<=9) {
			nums[i / 2] = n-'0';
		}
	}

	printf("Input : ");
	for (int j = 0; j < size; j++) {
		printf("%d ", nums[j]);
	}
	printf("\n");
	
	nums = insert(nums, size);

	printf("Sorted : ");
	for (int j = 0; j < size; j++) {
		printf("%d ", nums[j]);
	}
	printf("\n");
	free(nums);

	printf("    n    repetitions time\n");
	for (int k = 0; k <= 100; k += 10) {
		double duration;
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			int* arr = (int*)malloc(k * sizeof(int));
			for (int r = 0; r < k; r++) {
				arr[r] = k - r;
			}
			arr = insert(arr, k);
			free(arr);
		} while (clock() - start < 10);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d   %9d   %f\n", k, repetitions, duration);
	}

	double total_time;
	total_time = ((double)(clock() - total_start)) / CLOCKS_PER_SEC;
	printf("[Finished in %.1fs]\n", total_time);
	fclose(data);
	
	return 0;
}
int insert(int* nums, int size) {
	int p, q, key, i;
	int* U = (int*)malloc(size * sizeof(int));
	int* S = (int*)malloc(size * sizeof(int));

	S[0] = nums[0];
	for (i = 0; i < size-1; i++) {
		U[i] = nums[i + 1];
	}

	for (p = 1; p < size; p++) {
		key = U[0];
		for (q = p - 1; q >= 0 && S[q] > key; q--) {
			S[q + 1] = S[q];
		}
		S[q + 1] = key;
		for (i = 0; i < size - p -1; i++) {
			U[i] = U[i + 1];
		}
	}
	return S;
}