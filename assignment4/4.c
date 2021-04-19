#include <stdio.h>
#include <stdlib.h>

int time = 0;

struct node {
    int key , d, f ;
    struct node *pi;
    char color ;
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
    p->pi = NULL ;
    p->color = 'W';
    p->d = 0 ;
    p->f = 0;
    return p ;
}

void Insert(struct linked_list *l , struct l_node * p){
   l->last->next = p ;
   l->last = p ;
}

struct queue {

   int tail;
   struct l_node *a[100] ;
   int size;
   int head;
};

int isempty(struct queue*s){
   return (s->head == -1 || s->head == s->tail) ;
}

struct l_node *  Dequeue(struct queue *s){
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

void Enqueue(struct queue *s,struct l_node * k){
   s->a[s->tail] = k ;
   s->tail ++ ;
}

void BFS(struct linked_list *a[] , int s, int n ){
    int i = 0;
    struct l_node *temp ;

    for (i=0;i<n;i++){
        
        temp =  a[i]->head ;

        if ( s == i ){

            temp->node->color = 'G';
            temp->node->d  = 0 ;
            temp->node->pi = NULL ;
        }
        else{

            temp->node->color = 'W';
            temp->node->d  = 9999 ;
            temp->node->pi = NULL ;
        }

    }
    
    struct l_node *u , *v ;
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->head = q->tail = 0 ;
    q->size = 100 ;

    Enqueue(q,a[s]->head);

    while (!isempty(q)){
        u = Dequeue(q);
        printf("%d ",u->node->key);
        v = u->next ;
        
        while (v){
        
           if (v->node->color == 'W'){
               v->node->color = 'G';
               v->node->d ++ ;
               v->node->pi = u->node ;
               Enqueue(q,a[v->node->key]->head);           
           }
           v = v->next ;
        }
        u->node->color = 'B';
    }

    printf("\n");
}

void DFS_Visit (struct linked_list *a[] , struct l_node *u){
    time ++ ;
    u->node->d = time ;
    u->node->color = 'G' ;

    struct l_node *temp = u->next ;

    while (temp){

        if (temp->node->color == 'w'){
            temp->node->pi = u->node ;
            printf("%d ",temp->node->key);
            DFS_Visit(a,a[temp->node->key]->head);
        }
        temp = temp->next ;
    }

    u->node->color = 'B';
    time ++ ;
    u->node->f = time ;
}

void DFS (struct linked_list *a[] , int n ){
    int i = 0;
    struct l_node *temp ;

    for (i=0;i<n;i++){
        
        temp =  a[i]->head ;
        temp->node->color = 'w';
        temp->node->pi = NULL ;
    }
    
    printf("%d ",a[0]->head->node->key);
    for (i=0;i<n;i++){
        
        temp =  a[i]->head ;

        if ( temp->node->color = 'w')
           DFS_Visit(a,a[temp->node->key]->head);
    }
    printf("\n");
}

int main(){
    int n , m , n1 , key ,i=0 , source ;
    scanf("%d %d",&n,&m);

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
    while (m>0){
        scanf("%d %d ",&n1, &key);
        Insert(a[n1],Create_l_node(nodes[key]));
        m-- ;
    }
    scanf("%d",&source);

    BFS(a,source,n);
    DFS(a,n);
    return 0 ;
}
