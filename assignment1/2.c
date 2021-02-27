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


// queue things required for level-order traversal 

struct queue 
{
   int head ;
   int tail ;
   struct node * a[100];
   int size ;
};

int isqempty(struct queue*s)
{
   return (s->head == -1 && s->tail == -1 ) ;
}


struct node *  Dequeue(struct queue *s)
{
   if (isqempty(s) )
   {  
      return NULL ; 
   }
   
   struct node *k =  s->a[s->head];
   
   if (s->tail == s->head )
   {
      s->tail = s->head = -1 ;
      return k ;
   }
     
   else
   {       
       s->head =  (s->head+1)%s->size;
       return k ;
   }  
}


void Enqueue(struct queue *s,struct  node * k)
{   
   if (s->tail == -1 && s->head == -1)
   {
       s->tail = s->head = 0;
       
       s->a[s->head] = k ;
   }
   
   else
   {
       s->tail =  ((s->tail+1) % s->size);
       
       s->a[s->tail] = k ;
   }
}



void cousins (struct node *t , int k )
{  
   if (t== NULL || t->a == k )
   {
      printf("-1\n");
      return ;
   }
   
   struct queue *q ;
 
   q = (struct queue *)malloc(sizeof(struct queue));
   
   q->head = -1 ;
   
   q->tail =  -1 ;
   
   q->size = 100;
   
   struct node *root =  t ;
   struct node *null =  NULL ;
   
   struct node *temp , * req;
   
   int found = 0 ;
   
   Enqueue(q,root);
   Enqueue(q,null);

   while (!(isqempty(q)) && (found != 1))
   { 
     temp = Dequeue(q);
     

    while (temp != NULL )
    { 

      if (temp->left != NULL )
      {
          if (temp->left->a == k)
          {
               found = 1 ;
               
               req = temp->left ;
          }
          else
          {
               Enqueue(q,temp->left);
          }
      }
      
      if (temp->right != NULL )
      {
          if(temp->right->a == k )
          {
                found =  1 ;
                req =  temp->right ;
          }
          
          else 
          {
              Enqueue(q,temp->right);
          }
      }

      temp = Dequeue(q);
      
    }
    
    if (found != 1 && (q->tail != -1))
        Enqueue(q,null);
    
   }
   
   if (found == 1)
   {  
      if(isqempty(q))
      {
          printf("-1\n");
          free(q);
          return ;
      }
      if ( q->head == q->tail  )
      {
         if (q->a[q->head]->p == req->p)
         {
              printf("-1\n");
              free(q);
              return ;
         } 
      }
      
      Enqueue(q,null);
      
      temp = Dequeue(q);
      
      while (temp != NULL )
      {   
          if (!(temp->p == req->p))
             printf("%d ",temp->a);
                 
          temp = Dequeue(q);
      }
      
      printf("\n");
      
      free(q);
      return ;
   }
   
   else
   {
      printf("-1\n");
      free(q);
      return;
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


int main()
{
  char s[200] , a[300];
  
  int i = 1, num ,end ;
  
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
  
  scanf("%d",&num);
  
  cousins(t->root,num);
  
  return 0 ;
}
