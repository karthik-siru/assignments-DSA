#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node {
    int key ;
    struct node *left, *right ,*p , *child;
    int degree ;
    char mark , c ;
};

struct heap{
    struct node *head ;
    struct node *min ;
    int nodes ;
};

struct node* Create_Node(int key){
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->p = NULL ;
    p->child = NULL ;
    p->left = p;
    p->right = p ;
    p->key = key ;
    p->degree = 0;
    p->mark = 'W';
    p->c = 'N';

    return p ;
}

struct heap* Make_Heap (){
    struct heap *h = (struct heap*)malloc(sizeof(struct heap));
    h->head =  NULL ;
    h->min  =  NULL ;
    h->nodes = 0 ;
    return h ;
}

void Insert( struct heap*h , int key){
    struct node *new = Create_Node(key);

    if (h->min != NULL ){
        h->min->left->right =  new ;
        new->right = h->min  ;
        new->left  = h->min->left ;
        h->min->left  = new ;
        if (new->key < h->min->key)
            h->min = new ;
    }
    else {
        h->min = new ;
    }
    h->nodes += 1 ;
}

struct node * Minimum (struct heap *h){
    return h->min ;
}

void Cut(struct heap*h , struct node* found, struct node* temp)
{
    if (found == found->right)
        temp->child = NULL;
 
    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;
 
    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (h->min->left)->right = found;
    found->right = h->min;
    found->left = h->min->left;
    h->min->left = found;
    found->p = NULL;
    found->mark = 'B';
}
 
void Cascase_cut(struct heap *h  , struct node* temp)
{
    struct node* ptr = temp->p;
    if (ptr != NULL) {
        if (temp->mark == 'W') {
            temp->mark = 'B';
        }
        else {
            Cut(h ,temp, ptr);
            Cascase_cut(h,ptr);
        }
    }
}
 
struct node * Decrease_key(struct heap *h ,struct node* found, int val)
{
    found->key -= val;
 
    struct node* temp = found->p;
    if (temp != NULL && found->key < temp->key) {
        Cut(h,found, temp);
        Cascase_cut(h,temp);
    }
    if (found->key < h->min->key)
        h->min = found;

    return found ; 
}

int cal_degree(int n) {
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }
  return count;
}

void Fib_link(struct heap *H, struct node*y, struct node *x) {
  y->right->left = y->left;
  y->left->right = y->right;

  if (x->right == x)
    H->min = x;

  y->left = y;
  y->right = y;
  y->p = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right = x->child;
  y->left = x->child->left;
  x->child->left->right = y;
  x->child->left = y;
  if ((y->key) < (x->child->key))
    x->child = y;

  (x->degree)++;
}

void Consolidate(struct heap *H) {
  int degree, i, d;
  degree = cal_degree(H->nodes);
  struct node *A[degree], *x, *y, *z;
  for (i = 0; i <= degree; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->key > y->key) {
        struct node *exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min)
        H->min = x;
      Fib_link(H, y, x);
      if (y->right == x)
        H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < degree; i++) {
    if (A[i] != NULL) {
      A[i]->left = A[i];
      A[i]->right = A[i];
      if (H->min == NULL) {
        H->min = A[i];
      } else {
        H->min->left->right = A[i];
        A[i]->right = H->min;
        A[i]->left = H->min->left;
        H->min->left = A[i];
        if (A[i]->key < H->min->key) {
          H->min = A[i];
        }
      }
      if (H->min == NULL) {
        H->min = A[i];
      } else if (A[i]->key < H->min->key) {
        H->min = A[i];
      }
    }
  }
}
 
struct node  *Extract_min(struct heap *H) {

    struct node *temp = H->min;
    struct node *fin =  H->min ;
    struct node *pntr;
    pntr = temp;
    struct node *x = NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        pntr = x->right;
        (H->min->left)->right = x;
        x->right = H->min;
        x->left = H->min->left;
        H->min->left = x;
        if (x->key < H->min->key)
          H->min = x;
        x->p = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->left)->right = temp->right;
    (temp->right)->left = temp->left;
    H->min = temp->right;

    if (temp == temp->right && temp->child == NULL)
      H->min = NULL;
    else {
      H->min = temp->right;
      Consolidate(H);
    }
    H->nodes -= 1 ;
    return temp;
}

int Delete (struct heap *h , struct node *found ){
    if (h->min == NULL )
        return -1 ; 

    struct node *temp ;
    int res = found->key ;
    temp =  Decrease_key(h,found,99999);
    temp = Extract_min(h);

    return res ; 
}

void Print_Heap(struct node *n) {
  struct node *x;
  for (x = n;; x = x->right) {
    if (x->child == NULL) {
      printf("%d ", x->key);
    } else {
      printf("%d ",x->key);
      Print_Heap(x->child);
    }
    if (x->right == n) {
      break;
    }
  }
}

struct node * Search (struct node *n , int key){
    struct node *x;
  for (x = n;; x = x->right) {
    if (x->child == NULL) {
      if (x->key ==  key)
         return x ;
    } else {

      if (x->key ==  key)
         return x ;

      else 
         return Search(x->child,key); 
    }
    if (x->right == n) {
      break;
    }
  }
  return NULL ;    
}

int main(){

    struct heap *h = Make_Heap();
    struct node *temp ; 
    char c ;
    int a= 0 , key ,dec ;

    while(1){
        scanf("%c",&c);

        switch(c){

            case 'i':
                scanf("%d",&key);
                Insert(h,key);
            break ;

            case 'm':
                temp =  Minimum(h);
                if (temp)
                printf("%d\n",temp->key);
                else 
                printf("-1\n"); 
            break ;

            case 'x':
                temp =  Minimum(h);
                if (temp){
                    temp = Extract_min(h);
                    printf("%d\n",temp->key);
                }
                else 
                printf("-1\n");
            break ;

            case 'r':
                scanf("%d %d",&key ,&dec);
                temp =  Search(h->min,key);
                if (temp){
                     temp = Decrease_key(h,temp, dec);
                     printf("%d\n",temp->key);
                }
                else
                    printf("-1\n");
            break ;

            case 'd':
                scanf("%d",&key);
                temp =  Search(h->min,key);
                if (temp){
                      dec = Delete(h,temp);
                      printf("%d\n",dec);
                }
                else
                    printf("-1\n");
            break ;

            case 'p':
                Print_Heap(h->min);
                printf("\n");   
            break ;

            case 'e':
             a = 1 ;
            break ;
        }

        if (a)
          break ;
    }
}
