/* Gabriela Akemi Shima RA135819
 * EA876 - Lab04
 *
 * Este programa recebera uma serie de inteiros em sua entrada. Ao receber
 * um caractere fim de linha ('\n'), deve imprimir na tela a quantidade de
 * números primos da lista da entrada.
 *
 */

 #include <stdio.h>

 int main() {
 int var;

   do {
     scanf("%d", &var);
     printf("var = %d\n", var);
     
   } while(getchar() != '\n');
   return 0;

 }
