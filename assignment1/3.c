#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack 
{
   int top;
   char a[30]; 
};

int isempty(struct stack *s)
{
   return (s->top == -1);
}

char pop(struct stack *s)
{
   s->top -= 1;
   return (s->a[s->top+1]);
}

void push(struct stack *s, char k )
{  
   s->top += 1 ;
   s->a[s->top] = k ;
}

int isnumber (char c )
{
  return (c>= '0' && c<= '9');
}


// binary tree  equipments from here 

struct node 
{
  int a ;
  struct node *p ;
  struct node *left ;
  struct node *right ; 
};


struct tree
{
  struct node * root ;
};

struct node * create_node (int k )
{
  struct node * l ;
  
  l = (struct node *)malloc(sizeof(struct node));
  
  l->a = k ;
  l->p = NULL ;
  l->left = NULL ;
  l->right = NULL ;
  
  return l ;
}


int number (char s[200],int *i )
{
  int num = 0 ;
  
  if (isnumber (s[*i]) == 0 && s[*i] != '-')
  {
      return -1; 
  }
  
  if (s[*i] == '-')
  { 
  
  *i = *i + 1 ; 
    
  while (isnumber(s[*i]))
  { 
    num = num*10 + (int)s[*i]-'0';
    *i += 1 ;
  } 
  
  *i = *i -1 ;

  return 0-num ;
 }
 
 else 
 {
    while (isnumber(s[*i]))
  { 
    num = num*10 + (int)s[*i]-'0';
    *i += 1 ;  
  } 
  
  *i = *i -1 ;
  
  return num ;
 }
}


int find_index(char s[200], int i , int end)
{

   if (i >end)
      return -1 ; 
   
   struct stack *st ;
   
   st =  (struct stack *)malloc(sizeof(struct stack)); 
   
   st->top = -1 ;
   
   int j ;
   
   char c ;
   
   for (j= i ;j<= end ; j++)
   {
      if (s[j] == '(')
       push(st,s[j]);
       
      else if ( s[j] == ')')
      {
         if (st->a[st->top] == '(')
         {
             c = pop(st);
             
             if (isempty(st))
                return j ;
         }
      }
   }
   
   return -1 ; 
}




struct node * build_tree (char s[200], int i , int end )
{
   if (i > end )
     return NULL ;
     
   int num ;
   
   num =  number (s,&i);
   
   struct node * t = create_node (num);
   
   int index = -1 ;
   
   if (i+1 <= end && s[i+1] == '(')
      index =  find_index(s,i+1,end);
      
   if (index !=  -1 )
   {
       t->left = build_tree (s,i+2,index-1);
       
       if (t->left != NULL )
       {
           t->left->p =  t ;
       }
       
       
       t->right = build_tree (s,index+2,end-1);
       
       if (t->right !=  NULL )
       {
            t->right->p = t ;
       }
   }
   
   return t ;
 
}


int  MAX_VALUE(struct node * a)
{
    struct node *temp = a ;
    
    while (temp->right != NULL )
    {
        temp->right ;
    }
    
    return temp->a ;
}

int  MIN_VALUE(struct node * a)
{
    struct node *temp = a ;
    
    while (temp->left != NULL )
    {
        temp->left ;
    }
    
    return temp->a ;
}

int isbst (struct node * l )
{
    if (l == NULL )
    {
         return 1 ;
    }
    
    if ( l->left != NULL &&  l->a < MAX_VALUE(l->left))
    {  
      return 0 ;
    }
      
    if ( l->right != NULL &&  l->a > MIN_VALUE(l->right))
    { 
      return 0 ;
    }
      
    if (!isbst(l->left) || !isbst(l->right))
    {
       return 0;
    }

      
    return 1 ;
}


int  SUBTREESUM (struct node *p  )
{  
   if (p == NULL )
   { 
     return 0 ;
   }
     
   int sum = 0; 
   
   sum += p->a ;
   
   if (p->left != NULL )
      sum += SUBTREESUM(p->left);
     
   if (p->right != NULL )
     sum +=  SUBTREESUM(p->right);
     
   return sum ;
}


int  sum_of_subtrees(struct node *l , int k )
{
    if ( l == NULL )
    { 
     return 0 ; 
    }
    
     
    int count = 0;
    
    if ((SUBTREESUM(l) == k ) && isbst(l))
    {
        count = 1 ;
    }
    
    
    return count + sum_of_subtrees(l->left, k) + sum_of_subtrees(l->right, k) ;
} 


int main()
{
  char s[200] , a[300];
  
  int i = 1,end ;
  
  struct tree *t ;
  
  t = (struct tree *)malloc(sizeof(struct tree));
  
  t->root =  NULL ; 
  
  scanf("%[^\n]%*c",a);
  
  int k =0 , j = 0;
  
  while (a[k] != '\0')
  {   
      if (a[k] != ' ')
      {
          s[j] = a[k];
          j ++ ;
      }
      
      k ++;
  }
  
  s[j+1] = '\0';
 
  end =  j-2;
  
  t->root =  build_tree(s,i,end);
  
  
  int count ,number ;
  
  scanf("%d",&number);
    
  count = sum_of_subtrees (t->root , number );
  
  
  if (count != 0)
    printf("%d\n",count );
    
  else
   printf("-1\n");
  
}
