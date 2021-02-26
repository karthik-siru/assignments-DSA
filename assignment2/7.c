#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int a ;
    
    struct node *p ;
    struct node * left ;
    struct node * right ;
};

struct tree
{
    struct node * root ;
};

struct node * CREATE_NODE (int num )
{
    struct node * k ;
    
    k = (struct node *)malloc(sizeof(struct node));
    
    k->a  =  num ;
    k->p  = NULL ;
    k->left =  NULL ;
    k->right =  NULL ;
    
    return k ;
}

struct node * build_tree (int left , int right , int *arr ,struct node * temp)
{
   if (left >= right )
      return NULL ;
      
   int mid =  (left+right )/2 ;
   
   temp = CREATE_NODE(arr[mid]);
   
   temp->left = build_tree (left , mid ,arr , temp->left);
   
   if (temp->left != NULL )
   {
        temp->left->p = temp ;
   }
   
   
   temp->right = build_tree ( mid+1, right ,arr , temp->right );
   
   if (temp->right != NULL )
   {
        temp->right->p = temp ;
   }
   
   return temp ;
}

// queue things from here 

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



void sum_of_levels (struct node *t )
{  
   if (t== NULL  )
   {
      return ;
   }
   
   struct queue *q ;
 
   q = (struct queue *)malloc(sizeof(struct queue));
   
   q->head = -1 ;
   
   q->tail =  -1 ;
   
   q->size = 100;
   
   struct node *root =  t ;
   struct node *null =  NULL ;
   
   struct node *temp ;
   
   int sum = 0 ;
   
   Enqueue(q,root);
   Enqueue(q,null);

   while (!(isqempty(q)))
   { 
       sum = 0;
       
       temp = Dequeue(q);
       
       while ( temp !=  NULL )
       {   
           sum += temp->a ;
           
           if (temp->left !=  NULL )
           {    
                Enqueue(q,temp->left );
           }
           
           if (temp->right != NULL )
           {
               Enqueue(q,temp->right); 
           }
           
           temp = Dequeue(q);
       }
       
       printf("%d ",sum);
       
              
      if (!(isqempty(q)))
         Enqueue(q,null);
   }
   
   return ;  
}


void PRINT(struct node *root)
{    
     struct node * temp = root ;
     
     printf("( ");
     
     if (temp == NULL )
     {
        printf(") ");
     }
     
     else
     {
        printf("%d ",temp->a);
        
        PRINT(temp->left);
        
        PRINT(temp->right);
        
        printf(") ");
     }
}


int main()
{
   int n  ;
   
   scanf ("%d",&n);
   
   int a[n] , i;
   
   for(i=0;i<n;i++)
   {
       scanf("%d",&a[i]);
   }
   
   struct tree *t ;
   
   t = (struct tree *)malloc(sizeof(struct tree));
   
   t->root =  NULL ;
   
   t->root = build_tree(0,n,a,t->root);
   
   PRINT(t->root); 
   printf("\n");
   
   sum_of_levels(t->root); 
   printf("\n");
}
