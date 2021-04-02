#include<stdio.h>
#include<stdlib.h>

struct node{

    int key ;
    struct node *left ;
    struct node *right ;
    int height ;
};

struct avl_tree{

    struct node *root ;
};

struct node * create_node ( int k  )
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->key = k;
    p->left = NULL;
    p->right = NULL;
    p->height = 1 ;
    return p ;
}

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

struct node * search(struct avl_tree *t , int k)
{
   struct node *temp = t->root;

   while (temp)
   {
       if (temp->key == k )
          return temp ;
       else if ( temp->key < k )
          temp = temp->right;
       else
          temp = temp->left ;
   }
   return NULL ;
}

int get_balance(struct node *x){

    if (x == NULL)
       return 0;
    else
       return height(x->left) -height(x->right);
}

struct node * Maximum (struct node * x)
{
    struct node * temp = x ;

    while (temp->right)
        temp = temp->right ;
    return temp;
}

struct node *  Minimum (struct node * a)
{
    struct node *temp = a ;

    while (temp->left != NULL )
    {
        temp= temp->left ;
    }

    return temp;
}

int isbst (struct node * l )
{
    if (l == NULL )
         return 1 ;

    if ( l->left != NULL &&  l->key < Maximum(l->left)->key )
      return 0 ;

    if ( l->right != NULL &&  l->key > Minimum(l->right)->key)
      return 0 ;

    if (!isbst(l->left) || !isbst(l->right))
       return 0;


    return 1 ;
}

int isavl(struct node * a)
{
    if (a)
    {
        if( isbst(a))
        {
             int k = get_balance(a);

             if (isavl(a->left) && isavl(a->right))
             {
                if (k <= 1 && k >= -1)
                    return 1 ;
             }
        }
        else
            return 0 ;
    }
    else
       return 0 ;
}

struct node * left_rotate( struct node *x )
{
   struct node *y = x->right ;
   struct node *temp = y->left ;

   y->left   = x ;
   x->right  = temp ;

   //storing heights
   int h1 = height( x->right) , h2 = height(x->left);
   x->height = h1 > h2 ? h1+1 : h2+1 ;
   y->height = height(y->left) > height(y->right) ? height(y->left)+1 : height(y->right) +1 ;

   return y ;
}

struct node * right_rotate(struct node *y)
{
   struct node *x = y->left;
   struct node*temp = x->right ;

   x->right = y ;
   y->left = temp ;

   int h1 = height(y->left) , h2 = height(y->right) ;

   y->height = h1 > h2 ? h1+1 : h2 +1 ;
   x->height = height(x->left) > height(x->right) ? height(x->left)+1 : height(x->right) +1 ;

   return x;
}

struct node * insert( struct node *node , int k1 )
{
    if (node == NULL)
        return create_node(k1);

    else if( k1 < node->key )
        node->left  = insert(node->left ,k1);
    else
        node->right = insert(node->right ,k1);

    node->height = height(node->left) > height(node->right) ? height(node->left)+1 : height(node->right) + 1 ;

    int k = get_balance(node);

    if (k > 1 && get_balance(node->left)>=0) // left child
          return right_rotate(node);
    if (k > 1 && get_balance(node->left)< 0) // left right case
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (k < -1 && get_balance(node->right)<=0) // right child
          return left_rotate(node);
    if (k < -1 && get_balance(node->right)> 0) // right left  case
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node ;
}

struct node * delete( struct node*node, int key)
{
    if (!node)
       return node ;

    if (key  < node->key)
       node->left = delete(node->left , key);

    else if ( key > node->key )
       node->right = delete(node->right , key);

    else
    {

        if (node->left == NULL || node->right == NULL) // one child or no child case
        {
            struct node * temp =  node->left ? node->left : node->right ;

            if (temp  == NULL )
            {
                temp = node ;
                node = NULL ;
            }

            else
            {
              *node = *temp ;
            }

            free(temp);
        }

        else
        {
            struct node * temp = Minimum(node->right);

            node->key  = temp->key ;

            node->right = delete(node->right , temp->key);
        }
    }

    if (node == NULL)
       return node ;

    node->height = height(node->left) > height(node->right) ? height(node->left)+1 : height(node->right)+1 ;

    int b = get_balance(node);

    if (b > 1 && get_balance(node->left) >= 0)
        return right_rotate(node);

    // Left Right Case
    if (b > 1 && get_balance(node->left) < 0)
    {
        node->left =  left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Right Case
    if (b < -1 && get_balance(node->right) <= 0)
        return left_rotate(node);

    //
    if (b < -1 && get_balance(node->right) > 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;

}

void Print_Tree(struct node *root)
{
     printf("( ");

     if (root == NULL )
     {
        printf(") ");
     }

     else
     {
        printf("%d ",root->key);

        Print_Tree(root->left);

        Print_Tree(root->right);

        printf(") ");
     }
}

int main()
{
     char c ;
     int k , a = 0 ;

     struct node *temp ;
     struct avl_tree *t ;
     t = (struct avl_tree*) malloc(sizeof(struct avl_tree));
     t->root = NULL ;

    while (1)
    {
        scanf("%c",&c);
        switch(c)
        {
            case'i':
            scanf("%d",&k);
            t->root = insert(t->root ,k);
            break ;

            case'd':
            scanf("%d",&k);
            temp = search(t,k);
            if(temp)
            {
                printf("%d\n",temp->key);
                t->root = delete (t->root , temp->key);
            }
            else
                printf("FALSE\n");
            break ;

            case's':
            scanf("%d",&k);
            if(search(t , k ))
                printf("TRUE\n");
            else
                printf("FALSE\n");
            break;

            case 'b':
            scanf("%d",&k);
            temp = search(t , k );
            if(temp)
                printf("%d\n",get_balance(temp));
            else
                printf("FALSE\n");
            break ;

            case 'p':
            Print_Tree(t->root);
            printf("\n");
            break;

            case 'e':
            a = 1;
        }

        if (a == 1)
         break ;
    }
}
