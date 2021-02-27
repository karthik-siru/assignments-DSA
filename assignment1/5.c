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
   
   for (j= i ;j<= end ; j ++)
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


struct node * MIN_VALUE (struct node * a)
{
   struct node *temp =  a  ; 
   
   while (temp->left != NULL )
   {
      temp =  temp->left ;
   }
   
   return temp ;
}

struct node * MAX_VALUE (struct node * a)
{
   struct node *temp =  a  ; 
   
   while (temp->right != NULL )
   {
      temp =  temp->right ;
   }
   
   return temp ;
}


struct node * SUCCESSOR(struct node * a)
{
   if (a == NULL )
    return NULL ;
   
   if (a->right !=  NULL )
   {
       return MIN_VALUE(a->right);
   }
   
   struct node *t ;
   
   t =  a->p ;
   
   while(t != NULL && t->right == a)
   {
        a  = t ;
        t  = a->p ;
   }
   
   return t ;
    
}


int main()
{
  char s[200] , a[300];
  
  int i = 1, num ,end , k ;
  
  struct tree *t ;
  
  t = (struct tree *)malloc(sizeof(struct tree));
  
  t->root =  NULL ; 
  
 scanf("%[^\n]%*c",a);
  
  k =0 ;
  int j = 0;
  
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
  
  scanf("%d",&num);

  struct node *l = MIN_VALUE (t->root); 
  struct node *b = MAX_VALUE (t->root);

  while (num > 1 )
  {   
      if (b == l)
      {
          break ;
      }      
      l =  SUCCESSOR(l);

      num-- ;
  }
  
  printf("%d\n",l->a);
}
