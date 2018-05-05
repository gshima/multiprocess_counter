
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <unistd.h>
#include <signal.h>

#define TAMANHO 30

void sigquit() {
  /* Funcao que trata o sinal SIG_QUIT */
  printf("Recebi sinalizacao para terminar!\n");
  sleep(1);
  exit(0);
}

int verificaPrimo(long unsigned int numero);

int main() {
  pid_t filho[3];
  long unsigned int num;
  int qtde_elementos = 0, qtde_primos = 0, qtde_forks = 0;

  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */

  long unsigned int *numeros; //vetor que guarda os números da entrada
  numeros = (long unsigned int*) mmap(NULL, sizeof(long unsigned int)*TAMANHO, protection, visibility, 0, 0);
  if ((long unsigned int)numeros==-1) printf("Erro de alocacao!\n");

  long unsigned int *primos; //vetor que guarda os números qtde_primos
  primos = (long unsigned int*) mmap(NULL, sizeof(long unsigned int)*TAMANHO, protection, visibility, 0, 0);
  if ((long unsigned int)primos==-1) printf("Erro de alocacao!\n");

  long unsigned int *forks; //vetor que guarda os forks ativos
  forks = (long unsigned int*) mmap(NULL, sizeof(long unsigned int)*4, protection, visibility, 0, 0);
  if ((long unsigned int)forks==-1) printf("Erro de alocacao!\n");
  for(int j = 0; j < 4; ++j) forks[j] = 0;

  int *i; //índice
  i = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if ((int)i==-1) printf("Erro de alocacao!\n");
  (*i) = 0;


  do { // pega as entradas guarda em numeros na memória compartilhada
    scanf("%lu", &num);
    //*numeros = num;

    // int achou = 0;
    // while (achou == 0){
    //   for(int j = 0; j < 4; ++j){
    //     if(forks[j] == 0 ) { //processo livre
    //       achou = 1;
    //       forks[j] = 1;
    //       filho[j] = fork(); //processo filho começa aqui
    //       if(filho[j] == 0) {
    //         primos[qtde_elementos] = verificaPrimo(num);
    //         printf("Numero %d é primo? %d\n", num, primos[qtde_elementos]);
    //         forks[j] = 0;
    //         exit(EXIT_SUCCESS);
    //       }
    //       //break;
    //     }
    //   }
    // }


    qtde_primos += verificaPrimo(num);
    qtde_elementos++;
  } while(getchar() != '\n' && qtde_elementos < TAMANHO);


  /* Espera todos os filhos processarem */
  for(int j = 0; j < 4; ++j) {
    waitpid(filho[j],NULL, 0);
  }

  /* Calcula a quantidade de números primos calculados */
  for(int j = 0; j < qtde_elementos; ++j){
    qtde_primos += primos[j];
  }

 printf("%d\n", qtde_primos);
 return 0;
}

int verificaPrimo(long unsigned int numero) {
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
