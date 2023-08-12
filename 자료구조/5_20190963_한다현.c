#include<stdio.h>
#include<stdlib.h>

#define MAX_TERMS 100
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

void inorder(treePtr ptr);
void preorder(treePtr);
void insert(treePtr* node, int num);
treePtr modifiedSearch(treePtr tree, int num);

void main() {
	int i, n, A[MAX_TERMS], num, state;
	int j = 0;
	treePtr tree = NULL;

	FILE* fp;
	fp = fopen("input.txt", "r");
	state = fscanf(fp, "%d", &n);
	for (j = 0; j < n; j++) {
		state = fscanf(fp, "%d", &num);
		A[j] = num;
	}
	fclose(fp);

	for (i = 0; i < n; i++) {
		insert(&tree, A[i]);
	}

	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");
}

void inorder(treePtr ptr) {
	if (ptr) { //ptr != 0
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}
void preorder(treePtr ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void insert(treePtr* node, int num) {
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) { //temp != 0 or *node == 0
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if(*node){ // node != 0 , temp != 0 
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
	while (tree) { //tree != 0
		if (num == tree->data) {
			return NULL;
		}
		if (num < tree->data){
			if (tree->lchild == NULL) {
				return tree;
			}
			else {
				tree = tree->lchild;
			}
		}
		else {
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