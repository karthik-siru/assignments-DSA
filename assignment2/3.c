#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void insert_node (struct linkedlist * a[] , struct node * p , int index )
{  
   struct node * temp = a[index]->head , *temp1  ;

   if (a[index]->head  ==  NULL )
   {
       a[index]->head =  p ;
       return ;
   }
   
   else if (strcmp(temp->word , p->word )>0 )
   {   
       p->next =  temp ; 
       a[index]->head  =  p  ;
       return ;
   }

   else
   {  
       temp1 =  temp ; 

       temp = temp->next ;
     
      while (temp != NULL )
      {   
          if (strcmp(temp->word , p->word) > 0 )
            break ;

          temp1 =  temp ;
          temp = temp->next ;
      } 

      if (temp !=  NULL )
      {
          temp1->next = p ;
          p->next =  temp ;
          return ;
      }
      else
      {
          temp1->next =  p ;
          return ;
      }     
   }
}

int idx( char s[] )
{
   int a[8] , i , index = 0;

   for( i =0; i< 8 ;i++)
   {
       a[i] = 0; 
   }
   
   i = 0 ;

   while (s[i] != '\0')
   {
       switch(s[i])
       {
           case 'a':
            a[0] = 1 ; 
           break ;

           case 'b':
            a[1] = 1 ;
           break ;

           case 'c':
            a[2] =  1;
           break ;

           case 'd':
            a[3] = 1;
           break ;

           case 'e':
            a[4] = 1;
           break ;

           case 'f':
            a[5] =  1 ;
           break ;

           case 'g':
            a[6] = 1 ;
           break ;

           case 'h':
            a[7] =  1 ;
           break ;
       }

       i += 1;
   }

   for (i=0;i<8;i++)
   {
      index +=  pow(2,i) * a[i] ;
   }

   return index ;
}

int main()
{
   int k , index ,i ;

   scanf("%d",&k);

   struct linkedlist* a[255] ;
   
   struct node * temp ;
   
   for (i=0;i<255 ;i++)
   {   
       a[i] = (struct linkedlist *)malloc(sizeof(struct linkedlist));
       a[i]->head = (struct node *)malloc(sizeof(struct node));
       a[i]->head = NULL ;
   }

   char s[50] ;
   
   while(k > 0)
   {
      scanf("%s",s);
      
      index = idx(s);
      
      insert_node (a ,create_node (s), index );  

      k-- ; 
      
   }
   
   for(i =0 ; i< 255 ;i++)
   {

      if (a[i]->head !=  NULL )
      {
          temp = a[i]->head ; 
          
          while (temp->next != NULL )
          {
             printf("%s ",temp->word);
             temp = temp->next ;
          }
          
          printf("%s\n",temp->word );
      }
   }  
}
