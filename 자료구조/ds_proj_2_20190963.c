#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 1000001
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	int lvl;
	treePtr rchild;
}treeNode;
treeNode heap[MAX_TERMS];
int arr[MAX_TERMS];
int level;

void insert(treePtr* node, int num);
treePtr modifiedSearch(treePtr tree, int num);
void preorder(treePtr ptr);

void main() {
	int num, j;
	char enter;
	int i = 0;
	treePtr tree = NULL;

	do {
		scanf("%d", &num);
		arr[i] = num;
		i++;
		scanf("%c", &enter);
	} while (enter != '\n');

	for (j = i - 1; j >= 0; j--) {
		insert(&tree, arr[j]);
	}
	preorder(tree);
	printf("\n");
}
void insert(treePtr* node, int num) {
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) { //temp != 0 or *node == 0
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = num;
		ptr->lvl = level;
		ptr->lchild = ptr->rchild = NULL;
		if (*node) { // node != 0 , temp != 0 
			if (num < temp->data) {
				temp->lchild = ptr;
			}
			else {
				temp->rchild = ptr;
			}
		}
		else { // node == 0
			*node = ptr;
		}
	}
}
treePtr modifiedSearch(treePtr tree, int num) {
	level = 1;
	while (tree) { //tree != 0
		if (num < tree->data) {
			level += 1;
			if (tree->lchild == NULL) {
				return tree;
			}
			else {
				tree = tree->lchild;
			}
		}
		else {
			level += 1;
			if (tree->rchild == NULL) {
				return tree;
			}
			else {
				tree = tree->rchild;
			}
		}
	}
	return tree;
}
void preorder(treePtr ptr) {
	if (ptr) {
		printf("%d(%d) ", ptr->data, ptr->lvl);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}