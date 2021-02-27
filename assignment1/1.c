#include <stdio.h>
#include <stdlib.h>

// queue things from here 

struct queue {
  
   int tail;
   struct t_node *a[100] ;
   int size;
   int head;
};


int isempty(struct queue*s)
{
   return (s->head == -1 || s->head == s->tail) ;
}


struct t_node *  Dequeue(struct queue *s)
{
   if (isempty(s) )
   {  
      return NULL ; 
   }
     
   else
   {       
       s->head = (s->head+1)%s->size; 
       return s->a[s->head-1];
   }
   
}


void Enqueue(struct queue *s,struct t_node * k)
{   
   s->a[s->tail] = k ;   
   s->tail ++ ;
}


// tree_node from here . 

struct t_node
{
   int a ;
   struct t_node * p ;
   struct t_node *left ;
   struct t_node *right ;
};

struct tree
{
   struct t_node *root ;
};

struct t_node * create_node (int k )
{
   struct t_node *l ;
   
   l = (struct t_node *)malloc(sizeof(struct t_node ));
   
   l->a = k ;
   l->p = NULL ;
   l->left = NULL ;
   l->right = NULL ;
   
   
   return l ;
}



void INSERT (struct tree *t, struct t_node * k )
{
   if (t->root ==  NULL )
   {
        t->root =  k ;
        return ;
   }
   
   
   struct t_node * temp =  t->root ;
  
   struct queue *q ;
   
   q = (struct queue *)malloc(sizeof(struct queue));
   
   q->head = 0 ;
   
   q->tail = 0 ;
   
   q->size = 100;
   
   while (temp != NULL )
   {
        if (temp->left == NULL )
        {
            temp->left =  k ;
            k->p = temp->left;
            break ;
        }
        
        else if(temp->right == NULL )
        {
            temp->right = k ;
            k->p = temp->right ;
            break ;
        }
        
        else 
        {
            Enqueue(q,temp->left);
            Enqueue(q,temp->right);
        }
        
        temp =  Dequeue (q);
   }
   
   
   free(q);
}



void PRINT(struct t_node *root)
{    
     struct t_node * temp = root ;
     
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
    char c ;
    
    int n ;
    
    struct tree *t ;
    
    t = (struct tree *)malloc(sizeof(struct tree));
    
    t->root =  NULL ;
    
    while (1)
    {
        scanf("%c",&c);
        
        switch (c)
        {
           case 'i':
           scanf("%d",&n);
           INSERT(t,create_node(n));
           break ;
           
           case 'p':
           PRINT(t->root);
           printf("\n");
           break ;
           
           case 'e':
           exit(1);
           
        }
    }

}

