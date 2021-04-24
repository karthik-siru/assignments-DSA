#include <stdio.h>
#include <stdlib.h>

struct node {
    int key ;
    int d ;
};

struct edge{
  int src, dest , weight ;
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

void Detect_Negative_Cycle (struct graph*G[] , int n){
  int i , j , flag = 0;
  struct l_node *temp , *u;

  for ( i=1;i<n;i++){
    G[i]->head->node->d = 9999 ;
  }
  G[0]->head->node->d = 0 ;

  for (i=0;i<n-1;i++){
    for (j = 0 ;j<n;j++){
      temp = G[j]->head->next ;
      u = G[j]->head ;
      while (temp){
        if (u->node->d + temp->weight < temp->node->d ){
          temp->node->d = u->node->d + temp->weight ;
        }
        temp = temp->next ;
      }
    }
  }

    for (j = 0 ;j<n;j++){
      temp = G[j]->head->next ;
      u = G[j]->head ;
      while (temp){
        if (u->node->d + temp->weight < temp->node->d ){
          flag = 1 ;
          break ;
        }
        temp = temp->next ;
      }
      if (flag)
        break ;
    }

    if (flag)
      printf("1\n");
    else
      printf("-1\n");

}

int main(){
    int n ,m, i,w,val,key ,source;
    scanf("%d %d",&n, &m);

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
    for (i=0;i<m;i++){

        scanf("%d %d %d",&val,&key, &w);
        Insert(a[val],Create_l_node(nodes[key],w));
    }

    Detect_Negative_Cycle(a,n);
    return 0 ;
}
