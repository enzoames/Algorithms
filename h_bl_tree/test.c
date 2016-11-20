#include <stdio.h>
#include <stdlib.h>

int main(void)
{  tree_node_t *tree1, *tree2;
   int i,j;
   int errors = 0;
   int objects[10000];
   tree1 = create_tree();
   tree2 = create_tree();
   for(i=0; i<10000; i++)
     objects[i] = i+1;
   for(i=0; i< 300000; i++)
   {  insert(tree1, i, &(objects[0]));
   }
   for(i=400000; i< 500000; i++)
   {  if( i%2==0 )
         insert(tree2, i, &(objects[0]));
      else
         insert(tree2, i, &(objects[1]));
   }
   for(i=0; i<300000; i++)
   {  if(i%10 !=5)
      {  delete(tree1, i);
      }
   }
   for(i=0; i<10000; i++)
   {  insert(tree1, 10*i+2, &(objects[i]));
   }

   printf("Prepared trees; now start test1\n");fflush(stdout);
   for(i=0; i<10000; i++)   
   {  j = *find_by_number(tree1, 2*i +1);
      if( j!= i+1)
	{   printf("the %dth leaf from left should carry number %d, instead has %d\n", 2*i+1, i+1, j);
	    errors +=1;
            if( errors > 4)
                 exit(0);
        }
   }
   printf("Start test2\n");fflush(stdout);
   for(i=0; i< 100000; i++)
   {  j = *find_by_number(tree2, i+1);
      if( j != (i%2)+1 )
	{   printf("the %dth leaf from left should carry number %d, instead has %d\n", i+1, (i%2)+1, j);
	    exit(0);
        }
   }
   if( errors == 0 )
      printf("Tree test successful\n");
   exit(0);
}
