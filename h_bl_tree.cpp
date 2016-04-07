//EDWARDS AMES CSC 220
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

#define BLOCKSIZE 256

typedef int object_t;
typedef int key_t;

typedef struct tr_n_t
{
    key_t key;
    struct tr_n_t *left;
    struct tr_n_t *right;
    int height;
    int leaves;
}tree_node_t;


tree_node_t *currentblock = NULL;
int size_left;
tree_node_t *free_list = NULL;


tree_node_t *get_node()
{
    tree_node_t *tmp;
    if( free_list != NULL )
    {
        tmp = free_list;
        free_list = free_list -> left;
    }
    else
    {
        if( currentblock == NULL || size_left == 0)
        {
            currentblock = (tree_node_t *) malloc( BLOCKSIZE * sizeof(tree_node_t) );
            size_left = BLOCKSIZE;
        }
        tmp = currentblock++;
        size_left -= 1;
    }
    return( tmp );
}


void return_node(tree_node_t *node)
{
    node->left = free_list;
    free_list = node;
}


tree_node_t *create_tree(void)
{
    tree_node_t *tmp_node;
    tmp_node = get_node();
    tmp_node->left = NULL;

    return( tmp_node );
}

void left_rotation(tree_node_t *n)
{
    tree_node_t *tmp_node;
    key_t tmp_key;

    tmp_node = n->left;
    tmp_key  = n->key;
    n->left  = n->right;
    n->key   = n->right->key;
    n->right = n->left->right;
    n->left->right = n->left->left;
    n->left->left  = tmp_node;
    n->left->key   = tmp_key;
}

void right_rotation(tree_node_t *n)
{
    tree_node_t *tmp_node;
    key_t tmp_key;

    tmp_node = n->right;
    tmp_key  = n->key;
    n->right = n->left;
    n->key   = n->left->key;
    n->left  = n->right->left;
    n->right->left = n->right->right;
    n->right->right  = tmp_node;
    n->right->key   = tmp_key;
}

object_t *find(tree_node_t *tree, key_t query_key)
{
    tree_node_t *tmp_node;

    if( tree->left == NULL )
        return(NULL);
    else
    {
        tmp_node = tree;
        while( tmp_node->right != NULL )
        {
            if( query_key < tmp_node->key )
                tmp_node = tmp_node->left;
            else
                tmp_node = tmp_node->right;
        }

        if( tmp_node->key == query_key )
            return( (object_t *) tmp_node->left );
        else
            return( NULL );
    }
}

int insert(tree_node_t *tree, key_t new_key, object_t *new_object)
{
    tree_node_t *tmp_node;

    tree_node_t *tmp_node2 =NULL;

    int finished;

    if( tree->left == NULL )
    {
        tree->left = (tree_node_t *) new_object;
        tree->key  = new_key;
        tree->height = 0;
        tree->right  = NULL;
        tree->leaves = 1;
    }
    else
    {
        tree_node_t * path_stack[100]; int path_st_p = 0;
        int path_st_p2;
        tmp_node = tree;

        while( tmp_node->right != NULL )
        {
            path_stack[path_st_p++] = tmp_node;

            if( new_key < tmp_node->key )
                tmp_node = tmp_node->left;
            else
                tmp_node = tmp_node->right;
        }

        if( tmp_node->key == new_key )
            return( -1 );

        /* key is distinct, now perform the insert */
        {
            tree_node_t *old_leaf, *new_leaf;
            old_leaf = get_node();
            old_leaf->left = tmp_node->left;
            old_leaf->key = tmp_node->key;
            old_leaf->right  = NULL;
            old_leaf->height = 0;

            old_leaf->leaves = 1;

            new_leaf = get_node();
            new_leaf->left = (tree_node_t *) new_object;
            new_leaf->key = new_key;
            new_leaf->right  = NULL;
            new_leaf->height = 0;

            new_leaf->leaves = 1;

            if( tmp_node->key < new_key )
            {
                tmp_node->left  = old_leaf;
                tmp_node->right = new_leaf;
                tmp_node->key = new_key;

                tmp_node->leaves = old_leaf->leaves + new_leaf->leaves;
            }
            else
            {
                tmp_node->left  = new_leaf;
                tmp_node->right = old_leaf;

                tmp_node->leaves = old_leaf->leaves + new_leaf->leaves; //

            }
            tmp_node->height = 1;
        }

        /* rebalance */
    finished = 0;
    path_st_p2 = path_st_p;

        while( path_st_p > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = path_stack[--path_st_p];
            old_height= tmp_node->height;

            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                    //update leaves count
                    tmp_node->right->leaves = tmp_node->right->leaves-1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    left_rotation( tmp_node->left );
                    //update leaves
                    tmp_node->left->leaves = tmp_node->left->right->leaves + tmp_node->left->left->leaves;

                    right_rotation( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                    //update leaves count
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;

                }
            }

            else if ( tmp_node->left->height - tmp_node->right->height == -2 )//-2
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation( tmp_node );
                    tmp_node->left->height = tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                    //update leaves count on first left branch, then update total
                    tmp_node->left->leaves = tmp_node->left->leaves - 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    right_rotation( tmp_node->right );
                    //update leaves count
                    tmp_node->right->leaves = tmp_node->right->left->leaves + tmp_node->right->right->leaves;

                    left_rotation( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                    //update leaves count
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
            }

            else /* update height even if there was no rotation */
            {
                if( tmp_node->left->height > tmp_node->right->height )
                {
                    tmp_node->height = tmp_node->left->height + 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    tmp_node->height = tmp_node->right->height + 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
            }


            if( tmp_node->height == old_height )
                finished = 1;
        }//while-loop end

        while(path_st_p2 > 0)
        {
            tmp_node2 = path_stack[--path_st_p2];
            tmp_node2->leaves = tmp_node2->left->leaves + tmp_node2->right->leaves;
        }

    }//else end

 return( 0 );
}//insert end


object_t * deletee (tree_node_t *tree, key_t delete_key)
{
    tree_node_t *tmp_node, *upper_node, *other_node;
    tree_node_t *tmp_node2 = NULL;
    object_t *deleted_object;
    int finished;

    if( tree->left == NULL )
        return( NULL );

    else if( tree->right == NULL )
    {
        if(  tree->key == delete_key )
        {
            deleted_object = (object_t *) tree->left;
            tree->left = NULL;

            tree->leaves -=1;

            return( deleted_object );
        }
        else
            return( NULL );
    }

    else
    {
        tree_node_t * path_stack[100]; int path_st_p = 0;
        int path_st_p2;
        tmp_node = tree;

        while( tmp_node->right != NULL )
        {
            path_stack[path_st_p++] = tmp_node;
            upper_node = tmp_node;

            if( delete_key < tmp_node->key )
            {
                tmp_node   = upper_node->left;
                other_node = upper_node->right;
            }
            else
            {
                tmp_node   = upper_node->right;
                other_node = upper_node->left;
            }
        }

        if( tmp_node->key != delete_key )
            deleted_object = NULL;

        else
        {
            upper_node->key   = other_node->key;
            upper_node->left  = other_node->left;
            upper_node->right = other_node->right;
            upper_node->height = other_node->height;
            deleted_object = (object_t *) tmp_node->left;
            //update leaves
            upper_node->leaves -= 1;

            return_node( tmp_node );
            return_node( other_node );
        }

        /*start rebalance*/
        finished = 0; path_st_p -= 1;
        path_st_p2 = path_st_p;

        while( path_st_p > 0 && !finished )
        {
            int tmp_height, old_height;
            tmp_node = path_stack[--path_st_p];
            old_height= tmp_node->height;

            if( tmp_node->left->height - tmp_node->right->height == 2 )
            {
                if( tmp_node->left->left->height - tmp_node->right->height == 1 )
                {
                    right_rotation( tmp_node );
                    tmp_node->right->height = tmp_node->right->left->height + 1;
                    tmp_node->height = tmp_node->right->height + 1;
                    //update leaves count
                    tmp_node->right->leaves = tmp_node->right->leaves-1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    left_rotation( tmp_node->left );
                    //update leaves
                    tmp_node->left->leaves = tmp_node->left->right->leaves + tmp_node->left->left->leaves;

                    right_rotation( tmp_node );
                    tmp_height = tmp_node->left->left->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                    //update leaves count
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;

                }
            }

            else if ( tmp_node->left->height - tmp_node->right->height == -2 )
            {
                if( tmp_node->right->right->height - tmp_node->left->height == 1 )
                {
                    left_rotation( tmp_node );
                    tmp_node->left->height =
                    tmp_node->left->right->height + 1;
                    tmp_node->height = tmp_node->left->height + 1;
                    //update leaves count on first left branch, then update total
                    tmp_node->left->leaves = tmp_node->left->leaves - 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    right_rotation( tmp_node->right );
                    //update leaves count
                    tmp_node->right->leaves = tmp_node->right->left->leaves + tmp_node->right->right->leaves;

                    left_rotation( tmp_node );
                    tmp_height = tmp_node->right->right->height;
                    tmp_node->left->height  = tmp_height + 1;
                    tmp_node->right->height = tmp_height + 1;
                    tmp_node->height = tmp_height + 2;
                    //update leaves count
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
            }

            else /* update height even if there was no rotation */
            {
                if( tmp_node->left->height > tmp_node->right->height )
                {
                    tmp_node->height = tmp_node->left->height + 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
                else
                {
                    tmp_node->height = tmp_node->right->height + 1;
                    tmp_node->leaves = tmp_node->left->leaves + tmp_node->right->leaves;
                }
            }

            if( tmp_node->height == old_height )
                finished = 1;

        }//while-loop end
    /*end rebalance*/
    while(path_st_p2 > 0)
    {
        tmp_node2 = path_stack[--path_st_p2];
        tmp_node2->leaves = tmp_node2->left->leaves + tmp_node2->right->leaves;
    }

    return( deleted_object );
    }//else end
}


void check_tree( tree_node_t *tr, int depth, int lower, int upper )
{
    if( tr->left == NULL )
    {
        printf("Tree Empty\n"); return; }
        if( tr->key < lower || tr->key >= upper )
            printf("Wrong Key Order \n");

        if( tr->right == NULL )
        {
            if( *( (int *) tr->left) == 10*tr->key + 2 )
                printf("%d(%d)  ", tr->key, depth );
            else
                printf("Wrong Object \n");
        }
        else
        {
            check_tree(tr->left, depth+1, lower, tr->key );
            check_tree(tr->right, depth+1, tr->key, upper );
        }
}


object_t *find_by_number(tree_node_t *tree, int k)
{
    if (k < 1 || k > tree->leaves )
    {
        return (NULL);
    }

    if (tree->left == NULL)
    {
        return (NULL);
    }

    tree_node_t *tmp_node = tree;

    while(tmp_node->right != NULL)
    {
        if (k > tmp_node->left->leaves)
        {
            k-=tmp_node->left->leaves;
            tmp_node=tmp_node->right;
        }
        else
            tmp_node = tmp_node->left;
    }
    return (object_t *) tmp_node->left;
}

int main(void)
{
    tree_node_t *tree1, *tree2;
    int i,j;
    int errors = 0;
    int objects[10000];

    tree1 = create_tree();
    tree2 = create_tree();

    for(i=0; i<10000; i++)
        objects[i] = i+1;

    for(i=0; i< 300000; i++)
    {
        insert(tree1, i, &(objects[0]));
    }

    for(i=400000; i< 500000; i++)
    {
        if( i%2==0 )
            insert(tree2, i, &(objects[0]));
        else
            insert(tree2, i, &(objects[1]));
    }

    for(i=0; i<300000; i++)
    {
        if(i%10 !=5)
        {
            deletee(tree1, i);
        }
    }

    for(i=0; i<10000; i++)
    {
        insert(tree1, 10*i+2, &(objects[i]));
    }

    printf("Prepared trees; now start test1\n");fflush(stdout);
    for(i=0; i<10000; i++)
    {
        j = *find_by_number(tree1, 2*i +1);
        if( j!= i+1)
        {
            printf("the %dth leaf from left should carry number %d, instead has %d\n", 2*i+1, i+1, j);
            errors +=1;
            if( errors > 4)
                exit(0);
        }
    }
    printf("Start test2\n");fflush(stdout);

    for(i=0; i< 100000; i++)
    {
        j = *find_by_number(tree2, i+1);

        if( j != (i%2)+1 )
        {
            printf("the %dth leaf from left should carry number %d, instead has %d\n", i+1, (i%2)+1, j);
            exit(0);
        }
    }
    if( errors == 0 )
        printf("Tree test successful\n");

    exit(0);
}
