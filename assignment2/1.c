#include <stdio.h>
#include <stdlib.h>

struct table 
{
   int *a ;
   int size ;
   int index ;
};


struct table * HASHTABLE (int m)
{
    struct table *p ;

    int i = 0 ;
    
    p = (struct table *)malloc(sizeof(struct table));
    
    p->a =  (int *)malloc(sizeof(int)*m);

    for(i=0 ; i<m ;i++ )
    {
       p->a[i] = 0 ;
    }
    p->size = m ;
    p->index =  0 ;
    
    return  p ;  
}

int near_prime (int m)
{   
    int count ; 
    for ( int i = m-1 ; i > 1; i -- )
    {
        count =  0 ;
        
        for (int j = 1  ; j < i ; j++)
        {
            if ( i%j == 0 )
            {
               count ++ ;
            }
        }
        
        if (count == 1)
        {
            return i ;
        }
    }
}

int hash_a (int k , int m , int c1 , int c2 , int i)
{
    return ( (k % m) + c1*i + c2*i*i ) % m ;
}

int hash_b ( int k , int m , int r , int i)
{
   int  a =  k % m  , b  =  k % r ;
   
   return ( a +  i* (r-b) ) % m ;
}


void  INSERT(struct table *t ,int k)
{
   t->a[t->index] = k ;
}

void SEARCH (struct table *t , int k )
{
  for (int i =0 ; i< t->size ; i++)
  {
     if (t->a[i] == k)
     {
         printf("1 \n");
         return ;
     }
  }
  
  printf("-1\n");
  return ; 

}

void DELETE (struct table * t , int k )
{
  for (int i =0 ; i< t->size ; i++)
  {
     if (t->a[i] == k)
     {
         t->a[i] = 0 ;
         return ;
     }
  }
  
}

void PRINT (struct table *t )
{
   for (int i =0; i< t->size ; i++)
   {
      printf("%d (",i);
      
      if (t->a[i] != 0 )
      {
         printf("%d",t->a[i]);
      }
      
      printf(")\n");   
   }
}

int main()
{
    char ch,c,gar ;
    
    scanf("%c",&ch);

    
    int m ,c1, c2 ,k , i , t_index ;
    
    if ( ch == 'a' )
    {
       scanf("%d",&m);
       
       struct table * T ;
       
       T = HASHTABLE(m);
       
       scanf("%d%d",&c1,&c2);
       
       while (1)
       {            
          scanf("%c",&c);
          
          switch (c)
          {
             
             case 'i':
                    scanf("%d",&k); 
          
                    if ( T->a[ k % m] == 0 )
                    { 
                       T->index =  k%m ;
                       INSERT(T,k);
                    }
                    
                    else
                    {  
                       i = 0 ;
                      do 
                      {  
                         t_index = hash_a(k,m,c1,c2,i) ;
                    
                         if ( T->a[t_index] ==  0 )
                         {   
                             T->index =  t_index ; 
                             INSERT(T ,k );
                             break ;
                         }
                       
                         i += 1 ;
                      }while (i<m);
                       
                    }
             break ;
             
             case 's':
                    scanf("%d",&k);
                    SEARCH(T,k);
             break ;
             
             case 'd':
                    scanf("%d",&k);
                    DELETE(T,k);
             break ;
             
             case 'p':
                    PRINT (T);
             break ;
             
             case 't':
             exit(1) ;
          }
       }
    }
    
    
    if ( ch == 'b' )
    {
       scanf("%d",&m);
       
       struct table * T1 ;
       
       T1 = HASHTABLE(m);
       
       while (1)
       {
          scanf("%c",&c);
          
          switch (c)
          {
             
             case 'i':
                    scanf("%d",&k);             
                    if ( T1->a[ k % m] == 0 )
                    { 
                       T1->index =  k%m ;
                       INSERT(T1,k);
                    }
                    
                    else
                    {  
                       i = 0 ;
                      do 
                      {  
                         t_index = hash_b(k,m,near_prime(m),i) ;
                    
                         if ( T1->a[t_index] ==  0 )
                         {   
                             T1->index =  t_index ; 
                             INSERT(T1 ,k );
                             break ;
                         }
                       
                         i += 1 ;
                      }while (i<m);
                       
                    }
             break ;
             
             case 's':
                    scanf("%d",&k);
                    SEARCH(T1,k);
             break ;
             
             case 'd':
                    scanf("%d",&k);
                    DELETE(T1,k);
             break ;
             
             case 'p':
                    PRINT (T1);
             break ;
             
             case 't':
             exit(1) ;
          }
       }
    }
}

