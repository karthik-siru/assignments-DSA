#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int  a ;
    struct node * left ;
    struct node * right ;
};

//creating a bst 

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

struct node * SEARCH (struct node * root , int k )
{
   struct node * temp = root ; 
   
   while (temp)
   {
      if (temp->a <  k )
      {
         temp = temp->right ;
      }
      else if ( temp->a ==  k )
      {
         return  temp ;
      }
      else
      {
         temp = temp->left ;
      }
   }

}
int max_value (struct node * root , int l , int r )
{
     struct node * temp =  root , *temp1 , *temp2 ;     
     int a, b , m  ; 
     
     temp1 = SEARCH(root,r) ;
     temp2 = SEARCH (root , l);
     
     if (found (temp1->left , l) )
     {
         temp1 = temp1->left ;
         
         while (temp1 != temp2 )
         {
             if (temp1->a > temp2->a )
                 return temp1->a ;
             else 
             {   
                 m =  temp1->a ;
                 temp1 =  temp1->right ; 
             }
         }
         
         return m ;
     }
   
     while ( temp )
     {   
        a = found (temp->left , l) ;
        b = found (temp->right , r);
        
        if (!(a) && b )
            temp = temp->right ;

        else if (a && !(b))
            temp = temp->left ;
 
        else
            break ;          
     }
     
     
     while (temp )
     {
        if (temp->a < r)
        {
            m  = temp->a ;
            temp = temp->right ;
        }
        else 
             break ;
     }
     
     if (temp->a ==  r )
       return m;  
       
     else 
       return temp->a  ;  
}

int main()
{
   
   char ch ;
   
   int  k , l, r , max , i ,temp;
   
   struct bst * t ; 
   
   t = (struct bst *)malloc(sizeof(struct bst));
   
   t->root =  NULL ;
   
   do
   {  
      scanf("%d%c",&k,&ch);
      insert (t,create_node (k));
   }
   while (ch != '\n');

   scanf("%d%d",&l,&r);
   
   if (l > r)
   {
      temp =  l ;
      l =  r;
      r = temp ;
   }

   max = max_value (t->root , l ,r );
 
   printf("%d\n",max);
   
   return 0 ;  
}
