/* Gabriela Akemi Shima RA135819
 * EA876 - Lab04
 *
 * Este programa recebera uma serie de inteiros em sua entrada. Ao receber
 * um caractere fim de linha ('\n'), deve imprimir na tela a quantidade de
 * números primos da lista da entrada utilizando multiprocessos
 *
 */

 #include <stdio.h>

int calculaPrimo(int numero);

 int main() {
 int num;

   do {
     scanf("%d", &num);
     //printf("var = %d\n", var);
     if( calculaPrimo(num) ){
        printf("%d é primo!\n", num);
     }
     else {
        printf("%d não é primo!\n",num );
     }
   } while(getchar() != '\n');
   return 0;

 }

 int calculaPrimo(int numero) {
    int divisoes = 0;
    for(int i = 1; i <= numero; ++i){
       if(numero%i == 0) {
          divisoes++;
       }
    }
    if(divisoes == 2){
       return 1;
    }
    else {
       return 0;
    }
}
