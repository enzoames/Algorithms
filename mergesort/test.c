#include <stdio.h>
#include <stdlib.h>

struct listnode { struct listnode * next;
                  long              key; } ;


int main(void)
{  
   long i; 
   struct listnode *node, *tmpnode, *space;
   space =  (struct listnode *) malloc( 500000*sizeof(struct listnode));
   for( i=0; i< 500000; i++ )
   {  (space + i)->key = 2*((17*i)%500000);
      (space + i)->next = space + (i+1);
   }
   (space+499999)->next = NULL;
   node = space;
   printf("\n prepared list, now starting sort\n");
   node = sort(node);
   printf("\n checking sorted list\n");
   for( i=0; i < 500000; i++)
   {  if( node == NULL )
      {  printf("List ended early\n"); exit(0);
      }
      if( node->key != 2*i )
      {  printf("Node contains wrong value\n"); exit(0);
      }
      node = node->next;
   }
   printf("Sort successful\n");
   exit(0);
}
