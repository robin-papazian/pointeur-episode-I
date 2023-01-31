# Les pointeurs en C - Episode I

1. [Introduction](#introduction)
2. [Les variables & la mémoire](#variable)
3. [La portée des variables](#porte)
4. [L'opérateur d'adresse](#adresse)
5. [La base des pointeurs](#pointeur)
6. [Exercice](#exercice)

<a name="introduction"></a>

## Introduction

Cette documentation a pour objectif d'aborder de façon simple et compréhensible la notion des pointeurs dans le langage C.

L'épisode I couvrira [Les variables & la mémoire](#variable), [La portée des variables](#porte), [L'opérateur d'adresse](#adresse) dans le but d'aborder [La base des pointeurs](#pointeur) ce qui permettra d'aller plus loin dans les futurs épisodes ; - )

Cloner le dépot:

> git clone nom_du_depot

Compiler les sources avec gcc:

> gcc fichier_source.c -o fichier_source

<a name="variable"></a>

## La mémoire et les variables

- La mémoire est constituée d'octets pour y stocker de la donnée.
- 1 octet = 8 bits pouvant prendre deux valeurs distinctes 0 ou 1
- Chaque octet de la mémoire est identifié par une adresse
- Il existe differents types de variable et certaine recouvre plusieurs octets

> 1 octet = 00000000

> 4 octets = 00000000 00000000 00000000 0000000

```C
#include <stdio.h>

int main(void)
{
   printf("taille d'une variable de type char = %zu octet\n",sizeof(char));
   printf("taille d'une variable de type entier = %zu octets\n",sizeof(int));

   return 0;
}
```

Le programme ci-dessus affiche :

> taille d'une variable de type char = 1 octet

> taille d'une variable de type entier = 4 octets

<a name="lvalue"></a>

On appelle Lvalue (left value) tout objet pouvant être placé à gauche d'un opérateur d'affectation. Une Lvalue est caractérisée par :

- Son adresse, c'est-à-dire l'adresse-mémoire à partir de laquelle l'objet est stocké
- Sa valeur, c'est-à-dire ce qui est stocké à cette adresse.

On désigne souvent une variable par un identifiant (nom de variable), le compilateur ensuite fait le lien entre le nom de la variable et son adresse en mémoire.
Il est cependant possible de manipuler une variable par son adresse en mémoire.

```C
#include <stdio.h>

int main(void)
{
   //Entier => 4 octets
   int i = 32;

   return 0;
}
```

> Représentation de la variable **i** en mémoire ci-dessous

| Adresse  | Contenue | Nom | Valeur |
| -------- | -------- | --- | ------ |
| 90000000 | 00000000 | i   |        |
| 90000001 | 00000000 | i   |        |
| 90000002 | 00000000 | i   |        |
| 90000003 | 00100000 | i   | 32     |

> La zone mémoire de cette variable (4 octets) est fixés par son type (int). Les octets étant contigus, il suffit de connaître l'adresse du premier octet de la variable **i** pour récupérer sa valeur.

> 00000000 00000000 00000000 00100000 = 32

<a name="porte"></a>

## La portée des varibales

- Une **instruction composée** ou **bloc** est une suite d'instructions et/ou de **déclarations** délimitées par des accolades
- Toute **déclaration** (variable) a une durée de vie bornée au bloc où elle
  est déclarée. Elles sont automatiquement allouées à l'entrée d'une instruction composée, et libérées lors de la sortie de l'instruction composée
- Le **bloc** définit la portée de la variable
- Les variables déclarées hors de tout bloc sont appelées globales et utilisables dans tout le fichier. Elles sont allouées au début de l'exécution du programme, et ne sont libérées qu'à la fin de l'exécution du programme
- Il est possible de données à une variable qui est locale à une instruction composée, une durée de vie supérieure à celle de la procédure concernée en utilisant le mot-clé **static**.
  Cependant cette variable sera privée à la procédure, aucune autre procédure ne pourra en modifier la valeur

```C
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
```

Le programme ci-dessus affiche:

> Incrementation possible 0

> Incrementation possible 1

> Incrementation pas possible 0

> Incrementation pas possible 0

<a name="adresse"></a>

## L'opérateur d'adresse

L'opérateur d'adresse (&) appliqué à une variable **renvoi** l'adresse-mémoire de celle-ci.

```C
#include <stdio.h>

int main(void)
{
   int i = 32;

   printf("La variable i = %d\n",i);
   printf("Adresse de la variable i = %p\n",&i);

   return 0;
}
```

> La variable i = 32

> Adresse de la variable i = 0x7fffc26257dc

## La base des pointeurs

Un pointeur est un objet [(Lvalue)](#lvalue) dont la **valeur** est égale à l'adresse mémoire d'un autre objet. Pour déclarer un pointeur il faut:

- Le **type** de l'objet pointé (int, char ...)
- L'opérateur (\*)
- Un identificateur (nom_du_pointeur)

Ensuite il suffit d'affecter l'adresse de l'objet pointé au pointeur grace à [l'opérateur d'adresse](#adresse) **(&)** appliqué à un objet.

```C
#include <stdio.h>

int main(void)
{
   // Déclaration d'un pointeur qui pointera sur un entier
   int *pointeur;

   // Déclaration d'une variable de type entier
   int i = 32;

   // Afféctation de l'adresse de i vers pointeur
   pointeur = &i;

   return 0;
}
```

> **IMPORTANT** </br>
> Le type d'un pointeur dépend du type de l'objet vers lequel il pointe. Le pointeur sur un objet de type char aura la valeur de l'adresse de l'octet où cet objet est stocké. Par contre, pour un pointeur sur un objet de type int, la valeur donne l'adresse du premier des 4 octets où l'objet est stocké.

| Adresse  | Contenue | Nom      | Valeur   |
| -------- | -------- | -------- | -------- |
| 90000000 | 00000000 | i        |          |
| 90000001 | 00000000 | i        |          |
| 90000002 | 00000000 | i        |          |
| 90000003 | 00100000 | i        | 32       |
| 90000004 | ...      | pointeur | 90000000 |

Un pointeur permet :

- D'accéder à la valeur de l'objet pointé
- D'accéder à l'adresse de l'objet pointé
- De modifier la valeur de l'objet

On manipulera le pointeur avec :

- Son identificateur (nom) qui retourne l'adresse de l'objet pointé
- L'opérateur **(\*)** rattaché à son identificateur qui retourne la valeur de l'objet pointé

```C
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
```

Le programme ci-dessus affiche :

> La variable i = 32

> L'adresse de i = 0x7ffef58cb67c

> La valeur de la variable pointé = 32

> La variable i = 42

<a name="exercice"></a>

## Exercice

Ecrivez une fonction qui échange les valeurs des variables nbrA et nbrB du programme ci-dessous:

```C
#include <stdio.h>

int main(void)
{
   int nbrA = 5, nbrB = 10;

   printf("nbrA: %d\nnbrB: %d\n", nbrA, nbrB);

   return 0;
}
```

Resulta attendu :

> nbrA: 10

> nbrB: 5
