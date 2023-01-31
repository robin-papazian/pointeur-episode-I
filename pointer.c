#include <stdio.h>

int main(void)
{
   int i = 32;
   int *pointeur;
   pointeur = &i;

   printf("La variable i = %d\n",i);
   printf("L'adresse de i = %p\n",pointeur);
   printf("La valeur de la variable pointé = %d\n",*pointeur);
   *pointeur = 42;
   printf("La variable i = %d\n",i);

   return 0;
}