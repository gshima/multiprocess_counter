
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
  int qtde = 0, qtde_primos = 0, k = 0, qtde_forks = 4;

  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */

  long unsigned int *numeros; //vetor que guarda os números da entrada
  numeros = (long unsigned int*) mmap(NULL, sizeof(long unsigned int)*TAMANHO, protection, visibility, 0, 0);
  if ((long unsigned int)numeros==-1) printf("Erro de alocacao!\n");

  int *primos; //vetor que guarda quais numeros sao primos
  primos = (int*) mmap(NULL, sizeof(int)*TAMANHO, protection, visibility, 0, 0);
  if ((int)primos==-1) printf("Erro de alocacao!\n");
  (*primos)=0;

  // int *forks; // vetor guarda quais o filhos ativos
  // forks = (int*) mmap(NULL, sizeof(int)*4, protection, visibility, 0, 0);
  // if ((int)forks==-1) printf("Erro de alocacao!\n");
  // for(int i = 0; i < 4; ++i){
  //   (*forks) = 0;
  // }

  // int *qtde_forks; //guarda a quantidade de filhos
  // qtde_forks = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  // if ((int)qtde_forks==-1) printf("Erro de alocacao!\n");
  // (*qtde_forks) = 4;

  int *i; //índice
  i = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if ((int)i==-1) printf("Erro de alocacao!\n");
  (*i) = 0;


  do { // pega as entradas guarda em numeros na memória compartilhada
    scanf("%lu", &num);
    *numeros = num;
    numeros++;
    qtde++;
  } while(getchar() != '\n');

  numeros = numeros - (qtde);

  while ( (*i) < qtde) {
    printf("Olar\n");
    if( (qtde_forks) < 4 ) {
      qtde_forks ++;
      filho[qtde_forks-1] = fork();
      //printf("Entrei no fork?\n");
      if(filho[qtde_forks-1] == 0) {
        k = (*i);
        printf("Entrei no fork? -- Processo Filho: numero = %lu\n", numeros[k]);
        primos[k] = verificaPrimo(numeros[k]);
        exit(0);
      }
      else {
        qtde_forks ++;
        (*i) ++;
      }
    }
    else{
      /* Espera todos os filhos processarem */
      for(int j = 0; j < qtde_forks; ++j) {
        waitpid(filho[j],NULL, 0);
      }
      qtde_forks = 0;
      filho[qtde_forks] = fork();
      if(filho[qtde_forks] == 0) {
        k = (*i);
        printf("Entrei no fork? -- Processo Filho: numero = %lu\n", numeros[k]);
        primos[k] = verificaPrimo(numeros[k]);
        exit(0);
      }
      else {
        qtde_forks ++;
        (*i) ++;
      }
    }
  }

  /* Espera todos os filhos processarem */
  for(int j = 0; j < qtde_forks; ++j) {
    waitpid(filho[j],NULL, 0);
  }

  /* Soma quantidade de filhos */
  for(int j = 0; j < qtde ; ++j){
    if(numeros[j] == 1) qtde_primos++;
  }
 //(*qtde_primos) += verificaPrimo(num);
 printf("%d\n", *primos);
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
