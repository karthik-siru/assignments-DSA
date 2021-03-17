#include<stdio.h>
#include<stdlib.h>

struct node{

    int key ;
    struct node *left ;
    struct node *right ;
    int height ;    
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
    p->height = 0 ;

    return p ;
}

struct node * search(struct avl_tree *t , int k)
{
   struct node *temp = t->root;

   while (temp)
   {
       if (temp->key == k )
          return temp ;
       else if ( temp->key < k )
          temp = temp->left ;
       else 
          temp = temp->right ; 
   }
   return NULL ; 
}

int get_balance(struct node *x){
    return x->left->height - x->right->height ;
}

struct node * left_rotate( struct node *x )
{  
   struct node *y = x->right ;
   x->right  = y->left ;
   y->left   = x ; 

   //storing heights 
   int h1 = x->right->height , h2 = x->left->height;
   x->height = h1 > h2 ? h1+1 : h2+1 ;
   y->height = x->height > y->right->height ? x->height+1 : y->right->height +1 ;
    
   return y ; 
}

struct node * right_rotate(struct node *x )
{
   struct node *y = x->left;
   x->left = y->right ;
   y->right = x ;

   int h1 = x->left->height , h2 = x->right->height ;

   x->height = h1 > h2 ? h1+1 : h2 +1 ;
   y->height = x->height > y->right->height ? x->height+1 :y->right->height +1 ;

   return y;   
}

struct node * insert( struct node *node , int k )
{
    if (node == NULL)
    {
        node = create_node(k);
        return node;
    }


}