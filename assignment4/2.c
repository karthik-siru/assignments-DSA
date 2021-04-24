#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct node {
    int key ;
    int d  ;
};

struct l_node {
    struct node *node ;
    struct l_node *next ;
    int weight ;
};

struct graph{
    struct l_node *head ;
    struct l_node *last ;
};

struct l_node * Create_l_node (struct node *node , int w){
    struct l_node *l = (struct l_node*)malloc(sizeof(struct l_node));
    l->node =  node ;
    l->next =  NULL ;
    l->weight = w ;
    return l ;
}

struct graph * Create_List (struct l_node * l_node){
    struct graph *l = (struct graph*)malloc(sizeof(struct graph));
    l->head = l->last = l_node ;
    return l ;
}

struct node *Create_node (int key){
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->key = key ;
    return p ;
}

void Insert(struct graph *l , struct l_node * p){
   l->last->next = p ;
   l->last = p ;
}

struct l_node* min_adj_list(struct l_node *n , int m_set[]){

   struct l_node *temp = n ,*iter = n->next ;

   while(iter){
     if (m_set[temp->node->key]== 0 && iter->weight < temp->weight ){
       temp = iter ;
     }
     iter = iter->next ;
   }
   return temp ;
}

int all(int m_set[] , int n, int i){
   if (i == n)
   return 1 ;
   else
     return m_set[i] && all(m_set , n , i+1);
}

int minKey(int key[], bool mstSet[] , int n ){

    while(0){
      printf("it is here \n");
    }
    int min = INT_MAX, min_index;

    for (int v = 0; v < n ; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void Prims(struct graph *G[], int n){

  int key[n], i, j, m , sum = 0;
  bool mstSet[n];

  struct l_node *temp ;

  for (int i = 0; i < n; i++){
    key[i] = 99999;
    mstSet[i] = false;
  }

  key[0] = 0;

  for (int j = 0; j < n - 1; j++) {

      int u = minKey(key, mstSet , n);

      mstSet[u] = true;

      temp =  G[u]->head->next ;

      while (temp){

        if (mstSet[temp->node->key] == false && temp->weight < key[temp->node->key])
               key[temp->node->key] = temp->weight;

        temp = temp->next ;
      }

    }
   for (i=0;i<n;i++){
      sum += key[i] ;
   }

   printf("%d\n",sum );
}

int main(){
    int n ,m, i,w,val,key ,source;
    char c ;
    scanf("%c",&c);
    scanf("%d",&n);

    struct graph *a[n];
    struct node *nodes[n];

    for (i= 0;i<n ; i++){
       nodes[i] = Create_node(i) ;
    }
    i = 0;

    struct l_node *temp ;

//    Initialisation of the adj lists .
    while (i<n){
        a[i] = Create_List(Create_l_node(nodes[i], 0));
        i++ ;
    }

// Marking -Edges - weights
    for (i=0;i<n;i++){

       scanf("%d",&val);
       do {
         scanf("%d%c",&key , &c);
         Insert(a[val], Create_l_node(nodes[key], 0));

       }while(c != '\n');
    }

    for (i=0;i<n;i++){

        temp =  a[i]->head ;

        while (temp){
            printf("%d ",temp->node->key);
            temp = temp->next ;
        }
        printf("\n");
    }

    for(i=0;i<n;i++){

      scanf("%d",&val);
      temp = a[val]->head ;
      temp = temp->next ;
      while(temp){
        scanf("%d", &key);
        temp->weight =  key ;
        temp = temp->next ;
      }
    }
    Prims(a,n);
    return 0 ;
}
