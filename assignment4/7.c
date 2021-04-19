#include <stdio.h>
#include <stdlib.h>

struct node {
    int key ,rank ;
    struct node *p ;
};

struct arr {
    struct node *a[1000];
    int count ;
};

struct node * Create_node (int key){
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->key = key ;
    p->rank = 0 ;
    p->p  = p ;
    return  p;
}

struct node * Make_Set(int key){
    struct node *h = Create_node(key);
    return h ;
}

struct node * Link (struct node *x, struct node *y){
    
    if (x == y )
      return x ;

    if(x->rank >= y->rank){
        y->p = x;
        if(x->rank == y->rank)
            x->rank += 1;
        return x;
	}
	else{
        x->p = y;
        return y;
	}
}

struct node * Find_Set (struct node *x , struct arr *a){
    
    a->count ++ ;
    if (x->p == x)
        return x ;
    return Find_Set(x->p , a);
}

struct node * Find_Set_Path_Com (struct node *x , struct arr *a){

    a->count ++ ;
    if(x->p != x)
       x->p = Find_Set_Path_Com(x->p,a);
    return x->p ;
}

struct node *Union_1(struct arr *a ,struct node *x, struct node *y)
{
	x = Find_Set(x,a);
	y = Find_Set(y,a);
	if(x == y)
		return x;
	else
	{
		y->p = x;
		return x;
	}
}

struct node *Union_2(struct arr *a, struct node *x, struct node *y)
{
	x = Find_Set(x,a);
	y = Find_Set(y,a);
    return Link (x,y);
}

struct node *Union_3(struct arr *a, struct node *x, struct node *y)
{
	x = Find_Set_Path_Com(x,a);
	y = Find_Set_Path_Com(y,a);
	if(x == y)
        return x;
    else{
        y->p = x;
        return x;
    }
}

struct node *Union_4(struct arr*a, struct node *x, struct node *y)
{
    x = Find_Set_Path_Com(x,a);
    y = Find_Set_Path_Com(y,a);
    return Link(x,y);
}

int main (){
    int a , x1, x2 ;
    char c ;

    struct arr *a1 = (struct arr *)malloc(sizeof(struct arr));
    a1->count = 0 ;
    struct arr *a2 = (struct arr *)malloc(sizeof(struct arr));
    a2->count = 0 ;
    struct arr *a3 = (struct arr *)malloc(sizeof(struct arr));
    a3->count = 0 ;
    struct arr *a4 = (struct arr *)malloc(sizeof(struct arr));
    a4->count = 0 ;

    for(int i= 0 ; i<1000; i++)
    {
        a1->a[i] = NULL ;
        a2->a[i] = NULL ;
        a3->a[i] = NULL ;
        a4->a[i] = NULL ;
    }

    struct node *b1, *b2 , *b3 , *b4 ;


    while (1){
        
        scanf("%c",&c);

        switch(c){

            case 'm':

                scanf("%d",&x1);

                if (a1->a[x1] == NULL){

                    a1->a[x1] =  Make_Set(x1);
                    a2->a[x1] =  Make_Set(x1);
                    a3->a[x1] =  Make_Set(x1);
                    a4->a[x1] =  Make_Set(x1);

                    printf("%d\n",x1);
                }
                else {
                    printf("-1\n");
                }

            break;

            case 'f':

                scanf("%d",&x1);
                if (a1->a[x1]!= NULL ){

                    b1 = Find_Set(a1->a[x1], a1);
                    b2 = Find_Set(a2->a[x1], a2); 
                    b3 = Find_Set_Path_Com(a3->a[x1], a3); 
                    b4 = Find_Set_Path_Com(a4->a[x1], a4); 

                    printf("%d %d %d %d\n",b1->key , b2->key , b3->key , b4->key);
                    
                }  

            break;

            case 'u':

                scanf("%d %d",&x1,&x2);

                if (a1->a[x1] != NULL && a1->a[x2]!= NULL ){

                    b1 = Union_1(a1,a1->a[x1],a1->a[x2]);
                    b2 = Union_2(a2,a2->a[x1],a2->a[x2]);
                    b3 = Union_3(a3,a3->a[x1],a3->a[x2]);
                    b4 = Union_4(a4,a4->a[x1],a4->a[x2]);

                    printf("%d %d %d %d\n",b1->key , b2->key , b3->key , b4->key);
                }

            break;

            case 's':

                a = 1;
                printf("%d %d %d %d\n",a1->count , a2->count , a3->count , a4->count);

            break;
        }

        if (a)
        break ;
    }

    return 0 ;
}
