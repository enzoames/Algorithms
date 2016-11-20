int main(void)
{  int a[20],b[20],c[20];
   int i;
   for( i=0; i<10; i++)
   {  a[i] = (((7*i)%10)+10); 
      b[i] = (((7*i)%10)-20);
      c[i] =  (((7*i)%10)+10)*(((7*i)%10)-20); 
   }
   for( i=0; i<10; i++)
   {  a[i+10] = -1*(((7*i)%10)+10); 
      b[i+10] = (((7*i)%10)-20);
      c[i+10] = (((7*i)%10)+10)*(((7*i)%10)-20); 
   }
   printf("calling longest_path()\n");
   longest_path(20, &(a[0]), &(b[0]), &(c[0]));
   printf(" longest path should start intersection line 0 and 3, then continue\n");
   printf(("line 3,6,9,2,5,8,1,4,7,17,14,11,18,15,12,19,16,13.\n");
   printf("End Test\n");
}
