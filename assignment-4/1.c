#include <stdio.h>
#include <stdlib.h>

struct node {
    int key ;
};

struct l_node {
    struct node *node ;
    struct l_node *next ;
};

struct linked_list{
    struct l_node *head ;
    struct l_node *last ;
};

struct l_node * Create_l_node (struct node *node){
    struct l_node *l = (struct l_node*)malloc(sizeof(struct l_node));
    l->node =  node ;
    l->next =  NULL ;
}

struct linked_list * Create_List (struct l_node * l_node){
    struct linked_list *l = (struct linked_list*)malloc(sizeof(struct linked_list));
    l->head = l->last = l_node ;
    return l ;
}

struct node *Create_node (int key)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->key = key ;
    return p ;
}

void Insert(struct linked_list *l , struct l_node * p){
   l->last->next = p ;
   l->last = p ;
}

int main(){
    int n ,i,j,key ;
    scanf("%d",&n);

    struct linked_list *a[n];
    struct node *nodes[n];

    for (i= 0;i<n ; i++){
       nodes[i] = Create_node(i) ;
    }
    i = 0;

    struct l_node *temp ;

//    Initialisation of the adj lists .  
    while (i<n){
        a[i] = Create_List(Create_l_node(nodes[i]));
        i++ ;
    }
    
// Marking -Edges 
    for (i=0;i<n;i++){

        for (j = 0 ;j<n;j++)
        {
            scanf("%d",&key);
            if (key == 1)
               Insert(a[i],Create_l_node(nodes[j]));
        }
    }

    for (i=0;i<n;i++){
        
        temp =  a[i]->head ;

        while (temp){
            printf("%d ",temp->node->key);
            temp = temp->next ;
        }
        printf("\n");
    }

    return 0 ;
}
