#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int  a ;
    struct node * left ;
    struct node * right ;
};

struct bst 
{
  struct node * root ;
};

struct node * create_node (int k )
{
   struct node * p =  (struct node *)malloc(sizeof(struct node ));
   
   p->a = k ;
   p->left  =  NULL ;
   p->right =  NULL ;
   
   return p ;
}

void insert (struct bst * t , struct node *p)
{
   struct node * temp =  t->root ; 
   struct node * prev = NULL ;

   while (temp)
   {    
       prev =  temp ;
       if (temp->a > p->a )
       {
           temp = temp->left ;
       }
       else
       {
           temp = temp->right ;
       }     
   }
   
   if ( prev == NULL ) // tree is empty 
     { 
        t->root = p ;
        return ;
     }
       
   else if (prev->a >  p->a )
        prev->left =  p ;
   else
      prev->right =  p ;
}

int found (struct node * node , int l)
{
    struct node * temp =  node ; 
    
    while (temp )
    {   
        if (temp->a == l ) 
            return 1 ; 
        if (temp->a > l )
            temp = temp->left ;
        else if (temp->a < l )
            temp = temp->right ;
    }
    
    return (0);
}

int max_value (struct node * root , int l , int r , int k )
{
     struct node * temp =  root ;     
     int a, b , m  ; 
 
     m =  l > r ? l : r ;
     
     if (m ==  temp->a )
     {
         return temp->a ; 
     }
     
     while ( temp && k )
     {   
        a = found (temp->left , l) ;
        b = found (temp->right , r);
        
        if (!(a) && b )
            temp = temp->right ;

        if (a && !(b))
            temp = temp->left ;
 
        if ( a && b )
            break ;
            
        k--; 
     }
     
     while (temp )
     {
        if (temp->a < r)
            temp = temp->right ;
        else  
             break ;
     }
     
     return temp->a ;     
}

int main()
{
   
   char ch ;
   
   int  k , l, r , max , i , count = 0;
   
   struct bst * t ; 
   
   t = (struct bst *)malloc(sizeof(struct bst));
   
   t->root =  NULL ;
   
   do
   {  
      scanf("%d%c",&k,&ch);
      insert (t,create_node (k));
      count ++ ;
   }
   while (ch != '\n');

   scanf("%d%d",&l,&r);

   max = max_value (t->root , l ,r , count );
 
   printf("%d\n",max);
   
   return 0 ;  
}
