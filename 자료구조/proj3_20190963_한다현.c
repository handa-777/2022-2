#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct node* node_pointer;
typedef struct node {
	int data;
	node_pointer link;
}node;
node_pointer graph[50];

typedef struct stack* stack_pointer;
typedef struct stack {
	int data;
	stack_pointer link;
}stack;
node_pointer top[50];

int visit[50];

void add(stack_pointer* top, int data);
void delete(stack_pointer* top);
void dfs(int start);
void linksort(node_pointer* graph);

void main(void) {
	int n, src, dst, state, i, start;
	char dir;
	node_pointer x;
	FILE* fp;
	fp = fopen("graph.txt", "r");
	fscanf(fp, "%d", &n);

	for (i = 1; i < n+1; i++) {
		graph[i] = NULL;
		visit[i] = FALSE;
	} // graph initialization

	while(1) {
		state = fscanf(fp, "%d %d %c", &src, &dst, &dir);
		if (state == EOF) {
			break;
		}
		x = (node_pointer)malloc(sizeof(node));
		x->data = dst; x->link = graph[src]; graph[src] = x;
		if (dir == 'u') {
			x = (node_pointer)malloc(sizeof(node));
			x->data = src; x->link = graph[dst]; graph[dst] = x;
		}
	}
	fclose(fp);

	for (i = 1; i < n + 1; i++) {
		linksort(&graph[i]);
	}

	printf("> ");
	scanf("%d", &start);
	while (start != -1) {
		dfs(start);
		printf("\n");
		for (i = 1; i < n + 1; i++) {
			visit[i] = FALSE;
		}
		printf("> ");
		scanf("%d", &start);
	}
}
void linksort(node_pointer* graph) {
	node_pointer ptr1, ptr2;
	if (graph == NULL) {
		return;
	}
	ptr2 = NULL;
	while (1) {
		ptr1 = *graph;
		if (ptr2 == (*graph)) {
			break;
		}
		while (ptr1->link != ptr2) {
			if (ptr1->data > ptr1->link->data) {
				int temp = ptr1->data;
				ptr1->data = ptr1->link->data;
				ptr1->link->data = temp;
			}
			ptr1 = ptr1->link;
		}
		ptr2 = ptr1;
	}
}
void dfs(int start) {
	node_pointer w;
	visit[start] = TRUE;
	printf("%d ", start);
	int v = start;
	stack_pointer top = NULL;
	add(&top, start);
	while (top) {
		v = top->data;
		w = graph[v];
		while (1) {
			if (!w) {
				break;
			}
			if (!visit[w->data]) {
				visit[w->data] = TRUE;
				printf("%d ", w->data);
				add(&top, w->data);
				w = graph[w->data];
			}
			else {
				w = w->link;
			}
		}
		delete(&top);
	}
}
void add(stack_pointer* top, int data) {
	stack_pointer temp = (stack_pointer)malloc(sizeof(stack));
	temp->data = data;
	temp->link = *top;
	*top = temp;
}
void delete(stack_pointer* top) {
	stack_pointer temp = *top;
	int data;
	data = temp->data;
	*top = temp->link;
	free(temp);
}