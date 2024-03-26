#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int boolean;
typedef int TIPOCHAVE;

typedef struct aux{
    TIPOCHAVE chave;
    /* Dados armazenados vão aqui */
    struct aux *esq;
    struct aux *dir;
    int h;
} NO, *PONT;

PONT inicializa();
int max(int a, int b);
PONT criaNovoNo(TIPOCHAVE ch);
PONT insere(PONT raiz, TIPOCHAVE ch); // alteração p/ nova função de inserção
int altura(PONT raiz);
PONT contem(TIPOCHAVE ch, PONT raiz);
int numeroNos(PONT raiz);
void exibirArvore(PONT raiz);
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai);
PONT removeNo(PONT raiz, TIPOCHAVE ch);
PONT direita(PONT r);
PONT esquerda(PONT r);
PONT esquerdaDireita(PONT r);
PONT direitaEsquerda(PONT r);