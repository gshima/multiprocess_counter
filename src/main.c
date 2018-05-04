
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>

#define TAMANHO_VETOR 30

void sigquit() {
  /* Funcao que trata o sinal SIG_QUIT */
  printf("Recebi sinalizacao para terminar!\n");
  sleep(1);
  exit(0);
}

int calculaPrimo(long unsigned int numero);

int main() {
  pid_t filho;
  long unsigned int num;
  int a;
  a = 5;
  int qtde = 0;



  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */
  int *forks;
  forks = (int*) mmap(NULL, sizeof(int)*4, protection, visibility, 0, 0);
  if ((int)forks==-1) printf("Erro de alocacao!\n");
  for(int i = 0; i < 4; ++i){
    (*forks) = 0;
  }

  int *qtde_forks;
  qtde_forks = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
  if ((int)qtde_forks==-1) printf("Erro de alocacao!\n");
  (*qtde_forks) = 4;

  int *primos; //
  primos = (int*) mmap(NULL, sizeof(int)*10, protection, visibility, 0, 0);
  if ((int)primos==-1) printf("Erro de alocacao!\n");
  (*primos)=0;

  long unsigned int *numeros; //vetor que guarda os números da entrada
  numeros = (long unsigned int*) mmap(NULL, sizeof(long unsigned int)*TAMANHO_VETOR, protection, visibility, 0, 0);
  if ((long unsigned int)numeros==-1) printf("Erro de alocacao!\n");

  do {
    scanf("%lu", &num);
    *numeros = num;
    //printf("Número do vetor: %lu\n", *numeros);
    numeros++;
    qtde++;
  } while(getchar() != '\n');

  numeros = numeros - (qtde);

  int j = 0;
  while(j < qtde){
    if(*qtde_forks > 0) {
      filho = fork();
      (*qtde_forks)++;
      if (filho == 0) {
        /* Esta parte do codigo executa no processo filho */
        //signal(SIGQUIT, sigquit); /* Associa sinal SIGQUIT a funcao sigquit */
        if(calculaPrimo(numeros[j]))
          (*primos)++;
          //printf("Processo filho: qtde_primos= %d\n", *primos);
          //sleep(1);
        (*qtde_forks)--;
        exit(0);
      }
    }
    j++;
  }


 printf("%d\n", *primos);
}

int calculaPrimo(long unsigned int numero) {
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
