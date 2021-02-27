#include <stdio.h>
#include <stdlib.h>

struct node 
{
   int a ; 
   struct node *left ;
   struct node * right ; 
};

struct tree  
{
   struct node *root ;
};

struct node * create_node (int k )
{
    struct node * p ;
    
    p = (struct node *) malloc(sizeof(struct node )) ;
    
    p->a = k ;
    p->left = NULL ;
    p->right = NULL ;
    
    return p ;
}

void INORDER (struct node * node )
{
   if ( node != NULL )
   {
       INORDER (node->left);
       printf("%d ",node->a);
       INORDER (node->right);
   }
}
int SEARCH (struct node * root , int k )
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
         return 1;
      }
      else
      {
         temp = temp->left ;
      }
   }
   
   return 0 ;
}


struct node * SUCCESSOR(struct node *root , int k )
{
   struct node * curr = root ; 
   struct node * suc = NULL ; 
   
   if (SEARCH (root , k))
   {
   
   while (curr)
   {
      if (curr->a > k)
      {
         suc =  curr ; 
         curr = curr->left ;
      }
      else
      { 
        curr =  curr->right ;
      }
   }
   }
   
   return suc ;
}


struct node * PREDECESSOR (struct node * root , int k )
{
   struct node * curr = root ; 
   struct node * pre = NULL ;
   
   if (SEARCH (root , k ))
   { 
   
   while (curr)
   {
      if ( curr->a < k )
      {
         pre = curr ; 
         curr =  curr->right ; 
      }
      else
      {  
         curr = curr->left  ;
      }
   }
   }
   return pre ; 
}

struct node * min_value (struct node * root )
{
    struct node *  temp =  root ; 
    
    while (temp->left )
    {
        temp =  temp->left ;
    }
    
    return temp  ;
}

struct node * max_value (struct node * root )
{
    struct node *  temp =  root ; 
    
    while (temp->right )
    {
        temp =  temp->right ;
    }
    
    return temp  ;
}

int KLARGEST (struct node * root , int k )
{   
    struct node * temp = max_value (root);
    int p;
    
    while (k>1 && temp )
    {   
        p = temp->a ;
        
        temp =  PREDECESSOR (root , p );
        
        k--;
    }
    
    if (temp !=  NULL )
    {
        return temp->a ;
    }
    
    return -1 ;
    
}

int KSMALLEST (struct node * root , int k )
{   
    struct node * temp = min_value (root);
    int p;
    
    while (k>1 && temp )
    {   
        p = temp->a ;
        
        temp =  SUCCESSOR (root , p );
        
        k--;
    }
    
    if (temp !=  NULL )
    {
        return temp->a ;
    }
    
    return -1 ;      
}



//  tree from string -- code from here 

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

int number (char s[200],int *i )
{
  int num = 0 ;
  
  if (isnumber (s[*i]) == 0)
  {
      return -1; 
  }
  
  while (isnumber(s[*i]))
  { 
    num = num*10 + (int)s[*i]-'0';
    *i += 1 ; 
  } 
  
  *i = *i -1 ;
  
  return num ;
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
       
       t->right = build_tree (s,index+2,end-1);
       
   }
   
   return t ;
 
}


int main()
{
  char a[300] , s[200] , ch;
 
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
  
  struct node * temp ; 
  
  while (1)
  {
      scanf("%c",&ch );
      
      switch (ch )
      {
         case 'r':
         scanf ("%d",&end);
         temp = PREDECESSOR(t->root , end );
         if (temp)
         {
             printf("%d\n",temp->a);
         }
         else
         {
            printf("-1\n");
         }
         break ;
         
         case 'u':
         scanf ("%d",&end);
         temp = SUCCESSOR(t->root , end );
         if (temp)
         {
             printf("%d\n",temp->a);
         }
         else
         {
            printf("-1\n");
         }
         break ;
         
         case 'i':
         INORDER (t->root);
         printf("\n");
         break ;
         
         case 'l':
         scanf("%d",&end);
         printf("%d\n",KLARGEST (t->root , end));
         break ;
         
         case 's':
         scanf("%d",&end );
         printf("%d\n",KSMALLEST (t->root , end ));
         break ;
         
         case 'e':
         exit(1);
      }
  }
  
}

