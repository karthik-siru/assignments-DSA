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
   
    printf("node created \n");
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

int  MAX_VALUE(struct node * a)
{
    struct node *temp = a ;
    
    while (temp->right != NULL )
    {
        temp->right ;
    }
    
    return temp->key ;
}

int  MIN_VALUE(struct node * a)
{
    struct node *temp = a ;
    
    while (temp->left != NULL )
    {
        temp->left ;
    }
    
    return temp->key ;
}

int isbst (struct node * l )
{
    if (l == NULL )
         return 1 ;
    
    printf("isbst function \n"); 

    if ( l->left != NULL &&  l->key < MAX_VALUE(l->left))
      return 0 ;
      
    if ( l->right != NULL &&  l->key > MIN_VALUE(l->right)) 
      return 0 ;
      
    if (!isbst(l->left) || !isbst(l->right))
       return 0;

    return 1 ;
}

int isavl(struct node *l){
    if (l == NULL)
       return 1 ;
    
    printf("isavl function \n");
    if(isbst(l))
    {
        if ( abs(get_balance(l) <= 1) && isavl(l->left) && isavl(l->right) )
            return 1;
    }

    return 0 ;
}

struct node * insert( struct node *node , int k )
{
    if (node == NULL)
    {   
        printf("firstcase \n");
        return(create_node(k));
    }

    if (node->key > k )
    {   
        printf("going-left\n");
        node->left = insert(node->left, k) ;
    }
    if (node->key < k )
    {   
        printf("going-right\n");
        node->right  = insert(node->right, k) ;
    }

    node->height = node->left->height > node->right->height ? node->left->height +1 : node->right->height+1 ;

    if (!isavl(node))
    {
        if( get_balance(node) > 1  )      // heavy on left side 
        { 
            if (get_balance(node->left) < -1 )  // zigzag heavy on left 
            {
                node->left  = left_rotate(node->left);
                node = right_rotate(node);
                printf("zigzag left\n");
                return node ; 
            } 

            else  // normal left heavy 
            {
               node = right_rotate(node);
               printf("setting left heavy\n"); 
               return node; 
            }
        }

        if (get_balance(node) < -1 ) //heavy on right side 
        {
            if(get_balance(node->right) > 1 ) // zigzag heavy on right
            {
                 node->right  = right_rotate(node->right);
                 node = left_rotate(node);
                 printf("zigzag right\n");
                 return node; 
            } 
            else  // normal right way 
            {
                node = left_rotate(node);
                printf("setting right heavy\n"); 
                return node ;
            }
        }
    }

    return node ;

}

struct node * delete( struct node*node , int k )
{
    
}

void Print_Tree(struct node *node){

    if(node!= NULL )
    {
        printf("( %d ",node->key);
        Print_Tree( node->left );
        Print_Tree( node->right );
        printf(")");
    }

    else {
        printf("( )");
    }
}

int main()
{
     char c ; 
     int k , a = 0 ;
     
     struct node *temp ; 
     struct avl_tree *t ;
     t = (struct avl_tree*) malloc(sizeof(struct avl_tree));
     t->root = NULL ;

    while (1)
    {   
        scanf("%c ",&c);
        switch(c)
        {
            case'i':
            scanf("%d",&k);
            t->root = insert(t->root ,k);
            break ;

            case'd':
            scanf("%d",&k);
            if(search(t , k ))
                delete (t->root , k);
            else
                printf("FALSE");
            break ;

            case's':
            scanf("%d",&k);
            if(search(t , k ))
                printf("TRUE");
            else
                printf("FALSE");
            break;

            case 'b':
            scanf("%d",&k);
            temp = search(t , k );
            if(temp)
                printf("%d\n",get_balance(temp));
            else
                printf("FALSE");
            break ;

            case 'p':
            Print_Tree(t->root);
            printf("\n");
            break;

            case 'e':
            exit(1);     
        }
    } 
}
