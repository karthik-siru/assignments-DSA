#include<stdio.h>
#include<stdlib.h>

struct node{

    int key ;
    struct node *left ;
    struct node *right ;
    int height ;
    int count ;    
};

struct avl_tree{

    struct node *root ;
};

struct node * create_node ( int k  )
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->key = k;
    p->left = NULL;
    p->right = NULL;
    p->height = 1 ;
    p->count = 1;
    return p ;
}

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int get_balance(struct node *x){

    if (x == NULL)
       return 0;
    else 
       return height(x->left) -height(x->right);
}

struct node * left_rotate( struct node *x )
{  
   struct node *y = x->right ;
   struct node *temp = y->left ;

   y->left   = x ; 
   x->right  = temp ;

   //storing heights 
   int h1 = height( x->right) , h2 = height(x->left);
   x->height = h1 > h2 ? h1+1 : h2+1 ;
   y->height = height(y->left) > height(y->right) ? height(y->left)+1 : height(y->right) +1 ;
    
   return y ; 
}

struct node * right_rotate(struct node *y)
{
   struct node *x = y->left;
   struct node*temp = x->right ;

   x->right = y ;
   y->left = temp ;

   int h1 = height(y->left) , h2 = height(y->right) ;

   y->height = h1 > h2 ? h1+1 : h2 +1 ;
   x->height = height(x->left) > height(x->right) ? height(x->left)+1 : height(x->right) +1 ;

   return x;   
}

struct node * insert( struct node *node , int k1 )
{
    if (!node)
        return create_node(k1);
    
    else if ( node->key == k1 )
        node->count ++ ;

    else if( k1 < node->key )
        node->left  = insert(node->left ,k1);

    else 
        node->right = insert(node->right ,k1);

    node->height = height(node->left) > height(node->right) ? height(node->left)+1 : height(node->right) + 1 ; 

    int k = get_balance(node);

    if (k > 1 && get_balance(node->left)>=0) // left child
          return right_rotate(node);
    if (k > 1 && get_balance(node->left)< 0) // left right case
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (k < -1 && get_balance(node->right)<=0) // right child
          return left_rotate(node);
    if (k < -1 && get_balance(node->right)> 0) // right left  case
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node ; 
}

void Print_Tree(struct node *root)
{    
    if ( root )
    {
        Print_Tree(root->left);

        for (int i =0 ; i< root->count ;i++)
             printf("%d ",root->key);
        
        Print_Tree(root->right);
    }
}

int main()
{   
    int n , k  , i ;

    scanf("%d",&n);
    struct avl_tree *t ;
    t = (struct avl_tree*) malloc(sizeof(struct avl_tree));
    t->root = NULL ;

    for (i =0 ; i< n ;i++){
        scanf("%d",&k);
        t->root = insert(t->root ,k);
    }

    Print_Tree(t->root);
    printf("\n");
}