#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct stack* stack_pointer;
typedef struct stack {
	char par;
	stack_pointer link;
}stack;
stack_pointer top[30];

int result[16];
int pre[16];
int num;
int len = 0;
int i = 0;
int total = 0;

void add(stack_pointer *top, char item);
void pop(stack_pointer* top);
int maxi(int* lst);

int main() {
	int error = 0;
	char data[31];
	scanf("%s", data);
	for (int k = 0; k < strlen(data); k++) {
		char item = data[k];
		if (item == ')') {
			if (top[len-1]->par == '(') {
				pop(&top[len-1]);
			}
			else {
				error = 1;
				break;
			}
		}
		else if (item == ']') {
			if (top[len-1]->par == '[') {
				pop(&top[len-1]);
			}
			else {
				error = 1;
				break;
			}
		}
		else {
			add(&top[len], item);
		}
	}
	
	if (len != 0 || error == 1) {
		printf("%d\n", 0);
	}
	else {
		for (int r = 0; r < i; r++) {
			total += result[r];
		}
		printf("%d\n", total);
	}

	return 0;
}
void add(stack_pointer* top, char item) {
	stack* temp = (stack_pointer)malloc(sizeof(stack));
	temp->par = item;
	temp->link = *top;
	*top = temp;
	len++;
}
void pop(stack_pointer* top) {
	stack* temp = *top;
	char item;
	item = temp->par;
	*top = temp->link;
	free(temp);
	len--;
	if (item == '(') {
		num = 2;
	}
	else {
		num = 3;
	}
	result[i] = num;
	pre[i] = len + 1;
	i++;

	if (len == 0) {
		int p, q, mid;
		int ma = maxi(pre);

		while (ma != 1) {
			for (p = 0; p < i - 1; p++) {
				if (pre[p] == 0) {
					break;
				}
				else {
					if (pre[p] == ma && pre[p + 1] == ma) {
						mid = result[p] + result[p + 1];
						result[p] = mid;
						for (q = p + 1; q < i; q++) {
							pre[q] = pre[q + 1];
							result[q] = result[q + 1];
						}
						i--;
						p--;
					}
					else if (pre[p] == ma && pre[p + 1] == ma - 1) {
						mid = result[p] * result[p + 1];
						result[p] = mid;
						pre[p] -= 1;
						for (q = p + 1; q < i; q++) {
							pre[q] = pre[q + 1];
							result[q] = result[q + 1];
						}
						i--;
					}
				}
			}
			ma--;
		}
	}
}
int maxi(int* lst) {
	int temp = lst[0];
	for (int j = 1; j < i - 1; j++) {
		if (lst[j] > temp) {
			temp = lst[j];
		}
	}
	return temp;
}