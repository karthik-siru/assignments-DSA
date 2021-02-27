#include <stdio.h>
#include <stdlib.h>

struct node 
{
   int a ;
   struct node * p ;
   struct node * left ;
   struct node * right ;
};

struct bst 
{
   struct node * root ;
};

struct node * CREATE_NODE (int k )
{
   struct node *l ;
   
   l =  (struct node *)malloc(sizeof(struct node));
   
   l->a =  k ;
   
   l->p =  NULL ;
   
   l->left =  NULL ;
   
   l->right = NULL ;
   
   return l ;
}

struct node * SEARCH (struct bst *t , int k )
{
  struct node *temp = t->root ;
  
  while (temp != NULL )
  {
      if (temp->a == k )
        return temp ;
        
      else if (k < temp->a)
        temp =  temp->left ;
      
      else
        temp =  temp->right ;    
  }
  
  return NULL ;
}


int MIN_VALUE (struct node *t )
{
   struct node * temp =  t  ;
   
   while (temp->left!= NULL )
   {
      temp = temp->left ;
   }
   
   return temp->a ;
}

int MAX_VALUE (struct node *t )
{
   struct node * temp =  t ;
   
   while (temp->right!= NULL)
   {
      temp = temp->right ;
   }
   
   return temp->a ;
}

void INSERT (struct bst *t , struct node * k)
{
   struct node *temp =  t->root ;
   
   struct node *prt =  NULL ;
   
   while (temp != NULL )
   {
       prt  = temp ;
       
       if (k->a < temp->a )
       {
          temp =  temp->left ;
       }
       else 
       {
          temp = temp->right ;
       }
   }
   
   if ( prt ==  NULL )
   {
      t->root = k ;
      return ; 
   }
   
   if (k->a < prt->a )
   {
      prt->left =  k ;
      k->p =  prt ;
   }
     
   else 
   {
      prt->right =  k ;
      k->p = prt ;
   }
   
}



void TRANSPLANT (struct bst *t , struct node * u , struct node *v )
{
   if (u->p ==  NULL )
   {
       t->root = v ;
   }
   
   else if (u ==  u->p->left)
   {
       u->p->left =  v ;
   }
   
   else 
   {
       u->p->right =  v ;
   }
   
   if (v!= NULL )
       v->p =  u->p ;
}

void DELETE (struct bst *t , struct node * z)
{
    
    int a ;
    struct node * y;
   
   
   if (z->left ==  NULL )
       TRANSPLANT (t,z,z->right);
       
   else if (z->right ==  NULL )
       TRANSPLANT (t,z,z->right);
       
   else 
   {
      a =  MIN_VALUE (z->right) ;
      
      y =  SEARCH (t,a);
      
      if  (y->p != z )
      {
          TRANSPLANT(t,y,y->right);
          y->right =  z->right ;
          y->right->p =  y ;
      } 
      
      TRANSPLANT (t,z,y);
      
      y->left =  z->left ;
      y->left->p = y ;
   }
}



struct node * SUCCESSOR(struct bst *t , int k )
{
    int a ;
    if (k ==  MAX_VALUE (t->root))
    {   
        return NULL ;
    }
            
    struct node * x =  SEARCH(t,k);
    
    if ( x == NULL )
    {  
       return NULL ;
    }
    
    struct node *y ;


    if (x->right != NULL )
    {
        a =  MIN_VALUE(x->right);    
        y =  SEARCH (t,a);
        return y ;
    }
    
    else 
    {
       y  =  x->p ; 
       
       while (y != NULL  &&  x == y->right)
       {
           x = y ;
           
           y = y->p ;
       }
       return y ;
    }  
}

struct node * PREDECESSOR (struct bst *t, int k )
{
     int a ;
     if (k ==  MIN_VALUE (t->root))
        return NULL ;
    
    struct node *x  =  SEARCH(t,k);
    
    if (x == NULL )
       return NULL ;
    
    struct node *y ;
    
    if (x->left != NULL )
    {
        a =  MAX_VALUE(x->left);
        
        y =  SEARCH (t,a);
        
        return y;
    }
    
    else 
    {
        y  =  x->p ;
        
        while (y!= NULL && x == y->left)
        {
            x = y ;
            y = y-> p ;
        }
        
        return y ;
    }
}


int LEVEL (struct bst *t , int k)
{
   int level =  1 ;
   
   struct node * temp =  t->root ;
   
   while (temp != NULL )
   {
       if (temp->a ==  k )
       {
          return level ;
       }
       
       else if (k < temp->a)
       {
           temp = temp->left ;
           level ++;
       }
       else
       {
           temp = temp->right  ;
           level ++;
       }
   }
   
   return 0 ;
}



void INORDER (struct node *t )
{ 
   if (t != NULL )
   {
      INORDER (t->left);
      printf("%d ",t->a);
      INORDER (t->right);
   }
}

void PREORDER (struct node *t )
{ 
   if (t != NULL )
   {  
      printf("%d ",t->a);
      PREORDER (t->left);
      PREORDER (t->right);
   }
}

void POSTORDER (struct node *t )
{ 
   if (t != NULL )
   {    
      POSTORDER (t->left);
      POSTORDER (t->right);
      printf("%d ",t->a);
   }
}


int main()
{ 
   int n,te;
   char c ;
   
   struct node *temp ;
   
   struct bst t ;
   t.root = NULL ;
   
   while (1)
   {
       scanf ("%c",&c);
       
       switch(c)
       {
          case 'a':
            scanf("%d",&n);
            INSERT(&t,CREATE_NODE (n));
          break ;
          
          case 'd':
            scanf("%d",&n);
            temp =  SEARCH(&t,n) ;
            
            if ( temp  == NULL )
                 printf("-1\n");
            else 
            {
               printf("%d\n",temp->a);
               
               DELETE (&t,temp);
            }
          break ;
          
          case 's':
             scanf("%d",&n);
             temp =  SEARCH (&t,n);
             
             if (temp ==  NULL )
             {
                  printf("-1\n");
             }
             else 
             {
                 printf("1\n");
             }
          break ;
          
          case 'l':
             scanf("%d",&n);
             te =  LEVEL (&t,n);
             
             if (te == 0)
                printf("-1\n");
             else
                printf("%d\n",te);
          break ;
          
          case 'm':
             n =  MIN_VALUE(t.root);
             printf("%d\n",n);
          break;
          
          case 'x':
             n =  MAX_VALUE(t.root);
             printf("%d\n",n);     
          break ;
          
          case 'r':
             scanf("%d",&n);
             temp =  PREDECESSOR(&t,n);
             
             if (temp ==  NULL )
                printf("-1\n");
             else
                printf("%d\n",temp->a);
          break ;
          
          
          case 'u':
             scanf("%d",&n);
             temp =  SUCCESSOR(&t,n);
             
             if (temp ==  NULL )
                printf("-1\n");
             else
                printf("%d\n",temp->a);  
              
          break ;
          
          
          case 'i':
              INORDER (t.root);
              printf("\n");
          break ;
          
          case 'p':
              PREORDER(t.root);
              printf("\n");
          break ;
          
          case 't':
              POSTORDER(t.root);
              printf("\n");
          break ;
          
          case 'e':
            exit(1);
          
       }
   }

}

