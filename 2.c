#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node 
{
   char * word ;
   struct node * next ;
};

struct linkedlist 
{
   struct node * head ;
};

struct node * create_node (char s[])
{
   struct node * p ;
   
   p = (struct node *)malloc(sizeof(struct node));
   
   int a = strlen(s);
   
   p->word = (char *)malloc(sizeof(char)*(a+1));
   
   strcpy(p->word , s) ;
   p->next  = NULL ;
   
   return p ;
}

void insert_node (struct node * l , struct node * p)
{
   struct node * temp = l, *a ; 
   
   printf("string in the node :: %s \n", p->word);
   
   if (temp ==  NULL )
   {
       temp =  p ;
       
       printf("string stored in the head :: %s \n",temp->word );
       return ;
   }
   
   else
   {
      while (temp != NULL )
      {   
          a = temp ;
          if (strcmp(temp->word , p->word) == 0)
             return ;
          
          temp =temp->next ;
      }
      
      a->next =  p ;
          
   }
}

int idx( int l , int k)
{
    return (l*l)%k ;
}

int main()
{
   int k , index ,i ;
   scanf("%d",&k);
   
   struct linkedlist* a[k] ;
   
   struct node * temp ;
   
   for (i=0;i<k ;i++)
   {   
       a[i] = (struct linkedlist *)malloc(sizeof(struct linkedlist));
       a[i]->head = (struct node *)malloc(sizeof(struct node));
       a[i]->head = NULL ;
   }
   
   char s[200] , ch ;
   
   do 
   {
      scanf("%s%c",s,&ch);
      
      index = idx(strlen(s),k);
      
      printf("index :: %d \n",index);
      
      insert_node (a[index]->head ,create_node (s));
      
      
   }while (ch != '\n');
   
   for(i =0 ; i< k;i++)
   {
      printf("%d:",i);
      
      if (a[i]->head ==  NULL )
      {
          printf("null\n");
      }
      
      else 
      {
          temp = a[i]->head ; 
          
          while (temp->next != NULL )
          {
             printf("%s-",temp->word);
             temp = temp->next ;
          }
          
          printf("%s\n",temp->word );
      }
   }
   
   
}
