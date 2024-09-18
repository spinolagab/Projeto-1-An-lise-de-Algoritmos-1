/*
Nome: Gabriel Alves de Freitas Spinola Sucupira
TIA: 32339623 
RA: 10418133
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int contador_merge = 0, contador_insertion = 0;

// definir um tamanho limite de palavras e limite de tamanho por palavra
#define MAX_PALAVRAS 10000
// A maior palavra na lingua portuguesa tem 46 letras
#define MAX_CARACTERES 50



// Compara as palavras ignorando diferencas entre maiusculas e minusculas
bool menor(const char *palavra1, const char *palavra2) {
  return (strcasecmp(palavra1, palavra2) < 0);
}



void Insertion_Sort(char vetor_principal[][MAX_CARACTERES], int fim){
  for (int i = 1; i < fim; i++){
    int percorrer = i-1;
    char auxiliar[MAX_CARACTERES];
    // Auxiliar vai sempre ser a proxima string na sequencia
    strcpy(auxiliar, vetor_principal[i]);

    // Loop para trocas enquanto o auxiliar vier antes do principal nas posicoes percorridas
    while (menor(auxiliar, vetor_principal[percorrer]) && percorrer >= 0){
      strcpy(vetor_principal[percorrer+1], vetor_principal[percorrer]);
      percorrer--;
      contador_insertion++;
    }
    // Se a troca nao for necessaria coloca a auxiliar na posicao correta ate o momento atual
    strcpy(vetor_principal[percorrer+1], auxiliar);
  }
}



void merge(char vetor_principal[][MAX_CARACTERES], char **vetor_auxiliar, int inicio, int meio, int fim) {
  int percorrer = inicio, inicio_auxiliar = inicio, meio_auxiliar = meio + 1;

  // Copiar os valores do principal no auxiliar
  for (; percorrer <= fim; percorrer++) {
      strcpy(vetor_auxiliar[percorrer], vetor_principal[percorrer]);
  }

  // resetar para voltar a percorrer
  percorrer = inicio;

  // loop para conferir vetores para verificar se precisa fazer uma troca ou nao
  while (inicio_auxiliar <= meio && meio_auxiliar <= fim) {
    
    // Caso ja esteja ordenado no auxiliar so faz uma copia no principal
    if (menor(vetor_auxiliar[inicio_auxiliar], vetor_auxiliar[meio_auxiliar])) {
      
      strcpy(vetor_principal[percorrer], vetor_auxiliar[inicio_auxiliar]);
      percorrer++;
      inicio_auxiliar++;
    }
    
    // Caso a primeira string da segunda metade venha antes da primeira string da primeira metade faz a troca
    else {
      strcpy(vetor_principal[percorrer], vetor_auxiliar[meio_auxiliar]);
      percorrer++;
      meio_auxiliar++;
      
    }
    contador_merge++;
  }

  while (inicio_auxiliar <= meio) {
    strcpy(vetor_principal[percorrer], vetor_auxiliar[inicio_auxiliar]);
    inicio_auxiliar++;
    percorrer++;
  }

  while (meio_auxiliar <= fim) {
    strcpy(vetor_principal[percorrer], vetor_auxiliar[meio_auxiliar]);
    meio_auxiliar++;
    percorrer++;
  }
}



void sort_m(char vetor_principal[][MAX_CARACTERES], char **vetor_auxiliar, int inicio, int fim) {
  if (inicio >= fim) {
    return;
  }

  //Definir o meio do vetor considerando apenas o valor inteiro
  int meio = (inicio + fim) / 2;

  // Ordenar as metades do vetor
  sort_m(vetor_principal, vetor_auxiliar, inicio, meio);
  sort_m(vetor_principal, vetor_auxiliar, meio + 1, fim);

  // Caso esteja ordenado retorna
  if (menor(vetor_principal[meio], vetor_principal[meio + 1])) {
      return;
  }

  merge(vetor_principal, vetor_auxiliar, inicio, meio, fim);
}



// Funcao Merge_Sort
void Merge_Sort(char vetor[][MAX_CARACTERES], int tamanho) {
  
  // alocar espaco igual ao do vetor em um ponteiro
  char **auxiliar = malloc(sizeof(char*) * tamanho);
  
  for (int i = 0; i < tamanho; i++) {
    auxiliar[i] = malloc(MAX_CARACTERES * sizeof(char));
  }

  // chamada da função para ordenar
  sort_m(vetor, auxiliar, 0, tamanho - 1);

  // liberar o espaço alocado
  for (int i = 0; i < tamanho; i++) {
    free(auxiliar[i]);
  }
  free(auxiliar);
}



int main() {
  FILE *arquivo, *out1, *out2;
  char palavra[MAX_CARACTERES];
  char vetor_palavrasm[MAX_PALAVRAS][MAX_CARACTERES], vetor_palavrasi[MAX_PALAVRAS][MAX_CARACTERES];

  int contadorm = 0, contadori = 0, gravar = 0;

  // Abra o arquivo para leitura
  arquivo = fopen("in.txt", "r");

  // Verifique se o arquivo foi aberto corretamente
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return 1;
  }

  // Ler palavras do arquivo ate atingir o final do arquivo
  while (fscanf(arquivo, "%s", palavra) != EOF && contadorm < MAX_PALAVRAS) {
    strcpy(vetor_palavrasm[contadorm], palavra);
    strcpy(vetor_palavrasi[contadori], palavra);
    contadorm++;
    contadori++;
  }

  // fechar o arquivo
  fclose(arquivo);

  Merge_Sort(vetor_palavrasm, contadorm);
  Insertion_Sort(vetor_palavrasi, contadori);

  // Criar o arquivo de texto para os 2 métodos
  out1 = fopen("out1.txt", "w");
  out2 = fopen("out2.txt", "w");

  // Inserir o texto nos 2 arquivos
  while (gravar != contadorm){
    fputs(vetor_palavrasm[gravar], out1);
    fputs(" ", out1);
    fputs(vetor_palavrasm[gravar], out2);
    fputs(" ", out2);
    gravar++;
  }

  printf("Numero de passos usando insertion: %i\n", contador_insertion);
  printf("Numero de passos usando merge: %i\n", contador_merge);

  return 0;
}

// Link Replit: https://replit.com/@GabrielSpinola3/testes#Projeto.c
