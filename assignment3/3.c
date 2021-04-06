#include <stdio.h>
#include <stdlib.h>

struct node{
  int key ;
  struct node *left;
  struct node *right;
  char color ;
};

struct rbtree{
  struct node * root ;
};

struct node* create_node (int key){

  struct node *p = (struct node *)malloc(sizeof(struct node));
  p->key = key ;
  p->left = NULL;
  p->right = NULL ;
  p->color = 'R';
  return p ;
}

struct node * ll( struct node * x )
{

      struct node * y = x->right;
    	x->right = y->left;
    	y->left = x;
    	return y;

}

struct node * rr ( struct node * x)
{

      struct node * y = x->left;
    	x->left = y->right;
    	y->right = x;
    	return y;

}

char color(struct node *x)
{
  if ( x == NULL )
      return 'B';
  return x->color ;
}

struct node * rbtreeinsert( struct node *r , struct node * x )
{
  if (r == NULL )
    return x ;
  else if (r->key < x->key)
  {
        r->right = rbtreeinsert(r->right , x);

        if (color(r->right)== 'B')
           return r ;
           
        else 
        {
                if (color(r->right->left) == 'R' || color(r->right->right) == 'R')
                {
                        if(color(r->left )== 'R') // Case1 : Uncle is red - simply recolor
                        {
                                 r->right->color = 'B';
                                 r->left->color = 'B';
                                 r->color = 'R';
                                 return r ;
                        }

                        else  //  Case2 and Case3 -- Uncle is black
                        {
                          //So, let's convert Case3 into Case2

                                  if(color(r->right->left )== 'R')
                                     r->right = rr(r->right);

                                  struct node * y  = ll(r);
                                  y->left->color = 'R' ;
                                  y->color = 'B' ;
                                  return y ;
                        }

                }
                
                return r ;
         }
  }

  else
  {
          r->left = rbtreeinsert(r->left, x);

          if (color(r->left) == 'B')
               return r ;
                         
          else  
          {
                  if (color(r->left->left)== 'R' || color(r->left->right) == 'R')
                  {
                          if (color(r->right) == 'R') // Case1 : Uncle is Red , simply recolor
                          {
                                 r->right->color = 'B';
                                 r->left->color  = 'B';
                                 r->color = 'R';
                                 return r ;
                          }

                          else //Case2 and case3 :: Uncle is Black
                          {
                                  if (color(r->left->right) == 'R')
                                     r->left = ll(r->left);

                                  struct node *y = rr(r);
                                  y->right->color = 'R';
                                  y->color = 'B';
                                  return y ;
                          }
                  }
                  
                 return r ;
          }
  }

}

struct node * Insert(struct node * r , struct node * x)
{
   r =  rbtreeinsert(r,x);
   if(r->color == 'R')
        r->color = 'B';
   return r ;
}

void Print_Tree (struct node * root)
{
  printf("( ");
  if (root != NULL)
  {
    printf("%d %c ",root->key ,root->color);
    Print_Tree(root->left);
    Print_Tree(root->right);
  }
  printf(") ");
}

int main()
{
  int k ;

  struct rbtree * t = (struct rbtree*)malloc(sizeof(struct rbtree));
  t->root = (struct node *)malloc(sizeof(struct node)) ;
  t->root = NULL ;

  while (scanf("%d",&k) == 1)
  {
     struct node *a = create_node(k);
     t->root = Insert(t->root , a );
     Print_Tree(t->root);
     printf("\n");
  }

  return 0 ;
}
