#include <stdio.h>

int withStatic()
{
   static int nb = 0;
   return nb++;
}

int withOutStatic()
{
   int nb = 0;
   return nb++;
}

int main(void)
{
   printf("Incrementation possible %d\n",withStatic());
   printf("Incrementation possible %d\n",withStatic());

   printf("Incrementation pas possible %d\n",withOutStatic());
   printf("Incrementation pas possible %d\n",withOutStatic());

   return 0;
}