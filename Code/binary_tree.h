

enum ns { nfree=1, noccupied=2};
int COUNT=3;
typedef struct node{
int size;
struct node* left;
struct node * right;
struct node * m_parent;
enum ns node_state; //1 is free, 2 is occupied
int start, end;
} node;

void insert(node ** tree, int val) {
   printf("\n --------------- inserted in tree --------------------\n");
node *temp = NULL;
if(!(*tree)) {
temp = (node *)malloc(sizeof(node));
temp->left = temp->right = NULL;
temp->size = val;
temp->node_state=nfree;
*tree = temp;
printf("\n --------------- inserted bta3 el null in tree --------------------\n");
return;
}

//if(val < (*tree)->data) {
(*tree)->node_state=noccupied;
insert(&(*tree)->left, val);
(*tree)->left->start=(*tree)->start;
int s=(*tree)->start;
int e=(*tree)->end;
int t=((e-s)/2)+s;
(*tree)->left->end=t;
(*tree)->left->m_parent= *tree;
printf("\nparent with size %d",(*tree)->size);
//} else if(val > (*tree)->data) {
insert(&(*tree)->right, val);
(*tree)->right->start=t+1;
(*tree)->right->end=(*tree)->end;
(*tree)->right->m_parent= *tree;
printf("\n ---------------inserted msh null in tree --------------------\n");
}

void deletechild(node * parent)
{ if(parent->left)
   free(parent->left);
   parent->left=NULL;
if(parent->right)
   free(parent->right);
   parent->right=NULL;

}



void deltree(node * tree) {
if (tree) {
deltree(tree->left);
deltree(tree->right);
free(tree);
}
}

void printTree(node *root, int space){
   if (root == NULL)
      return;
   space += COUNT;
   printTree(root->right, space);
   for (int i = COUNT; i < space; i++)
      printf("\t");
   printf("%d , %d , %d , %d \n",root->size,root->node_state,root->start,root->end);
   printTree(root->left, space);
}
