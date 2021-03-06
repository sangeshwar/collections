#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct bst_node bst_node;
typedef struct bst bst;

bst* bst_create(int, void*, void*, void*);
bst_node* bst_new_node(void*, int);
void bst_push_util(bst_node** ,void*, int, int (*lt)(void*, void*));
void bst_pop_util(bst_node**,void*, int (*lt)(void*, void*), int (*gt)(void*, void*), int (*et)(void*, void*));
void bst_print_preorder_util(bst_node*, void (*print_data)(void*));
void bst_print_postorder_util(bst_node*, void (*print_data)(void*));
void bst_print_inorder_util(bst_node*, void (*print_data)(void*));

void bst_push(bst*, void*);
void bst_pop(bst*, void*);
void bst_print_preorder(bst* ,void (*print_data)(void*));
void bst_print_postorder(bst* ,void (*print_data)(void*));
void bst_print_inorder(bst*, void (*print_data)(void*));

struct bst  {
    bst_node* root;
    int size;
    int (*gt)(void*, void*);
    int (*lt)(void*, void*);
    int (*et)(void*, void*);
};

struct bst_node{
	char* data;
	int height;
	bst_node* left;
	bst_node* right;
};


bst* bst_create(int size, void* gt, void* lt, void* et)  {
	bst* b = malloc(sizeof(bst));
    b->root = NULL;
    b->size = size;
    b->lt = lt;
    b->gt = gt;
    b->et = et;
	return b;
}

void bst_push(bst* b ,void* data)    {
    bst_push_util(&(b->root), data, b->size, b->lt);
}

void bst_pop(bst* b,void* data)  {
    bst_pop_util(&(b->root), data, b->lt, b->gt, b->et);
}

void bst_print_preorder(bst* b, void (*print_data)(void*))   {
    bst_print_preorder_util(b->root, print_data);
}

void bst_print_postorder(bst* b, void (*print_data)(void*))  {
    bst_print_postorder_util(b->root, print_data);
}

void bst_print_inorder(bst* b, void (*print_data)(void*))    {
    bst_print_inorder_util(b->root, print_data);
}

void bst_print_inorder_util(bst_node* root, void (*print_data)(void*))  {
	if(root!=NULL)  {
		bst_print_inorder_util(root->left, print_data);
		print_data(root->data);
		bst_print_inorder_util(root->right, print_data);
	}
}

bst_node* bst_new_node(void* data, int size)   {
	bst_node* temp=(bst_node*)malloc(sizeof(bst_node));
    temp->data = malloc(size);
	memcpy(temp->data, (char*)data, size);
	temp->left=NULL;
	temp->right=NULL;

	return temp;
}

void bst_print_postorder_util(bst_node* root, void (*print_data)(void*))    {
	if(root!=NULL)  {
		bst_print_postorder_util(root->left, print_data);
		bst_print_postorder_util(root->right, print_data);
		print_data(root->data);
	}
}

void bst_print_preorder_util(bst_node* root, void (*print_data)(void*))    {
	if(root!=NULL)   {
	print_data(root->data);
	bst_print_preorder_util(root->left, print_data);
	bst_print_preorder_util(root->right, print_data);
	}
}

void bst_push_util(bst_node** node,void* data, int size, int (*lt)(void*, void*))   {	
	if(*node==NULL)   {
		(*node)=bst_new_node(data, size);
	}
    else if(lt(data, (*node)->data))   {
		bst_push_util(&((*node)->left), data, size, lt);
    }
	else    {
		bst_push_util(&((*node)->right), data, size, lt);
    }
}


void bst_pop_util(bst_node** root, void* key, int (*lt)(void*, void*), int (*gt)(void*, void*), int (*et)(void*, void*)) 
{ 
	if ((*root) == NULL) return; 

	if (lt(key, (*root)->data)) 
		bst_pop_util(&((*root)->left), key, lt, gt, et); 

	else if (gt(key, (*root)->data)) 
		bst_pop_util(&((*root)->right), key, lt, gt, et); 

	else
	{ 
		if ((*root)->left == NULL) 
		{ 
			bst_node *temp = (*root)->right; 
			free((*root)); 
            (*root) = temp;
            return;
		} 
		else if ((*root)->right == NULL) 
		{ 
			bst_node *temp = (*root)->left; 
			free((*root)); 
            (*root) = temp;
            return;
		} 

        bst_node* current = (*root)->right; 

        while (current && current->left != NULL) 
            current = current->left; 

		bst_node* temp = current; 

		(*root)->data = temp->data; 

		bst_pop_util(&((*root)->right), temp->data, lt, gt, et); 
	} 
}