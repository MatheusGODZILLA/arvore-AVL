#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

// Funções modificadas/criadas para AVL
int max(int a, int b) {
 if (a > b) return a;
 return b;
}

PONT criaNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    novoNo->h = 0; // A altura de um nó folha é 0
    return novoNo;
}

PONT direita(PONT r) { // Rotação simples à direita
    PONT aux = r->esq;
    r->esq = aux->dir;
    aux->dir = r;
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;
    return aux;
}

PONT esquerda(PONT r) { // Rotação simples à esquerda
    PONT aux = r->dir;
    r->dir = aux->esq;
    aux->esq = r;
    r->h = max(altura(r->dir), altura(r->esq)) + 1;
    aux->h = max(altura(aux->esq), r->h) + 1;
    return aux;
}

PONT esquerdaDireita(PONT r) {  
    r->esq = esquerda(r->esq); 
    return direita(r); 
}

PONT direitaEsquerda(PONT r) {
    r->dir = direita(r->dir);
    return esquerda(r);
}

int altura(PONT raiz) { 
    if (!raiz) return -1; // A altura de um nó nulo é -1
    return raiz->h; // A altura de um nó é o valor de h
}

PONT insere(PONT raiz, TIPOCHAVE ch) {
    if (!raiz)
        return criaNovoNo(ch);

    if (ch < raiz->chave) {
        raiz->esq = insere(raiz->esq, ch);
        if (altura(raiz->esq) - altura(raiz->dir) == 2) {
            if (ch < raiz->esq->chave)
                raiz = direita(raiz);
            else
                raiz = esquerdaDireita(raiz);
        }
    }
    else if (ch > raiz->chave) {
        raiz->dir = insere(raiz->dir, ch);
        if (altura(raiz->dir) - altura(raiz->esq) == 2) {
            if (ch > raiz->dir->chave)
                raiz = esquerda(raiz);
            else
                raiz = direitaEsquerda(raiz);
        }
    }
    raiz->h = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    return raiz;
}

// Função que remove um nó
PONT removeNo(PONT raiz, TIPOCHAVE ch) {
  if (raiz == NULL)
    return raiz;

  if (ch < raiz->chave)
    raiz->esq = removeNo(raiz->esq, ch);
  else if (ch > raiz->chave)
    raiz->dir = removeNo(raiz->dir, ch);
  else {
    // Nó com apenas um filho ou sem filhos
    if (raiz->esq == NULL || raiz->dir == NULL) {
      PONT temp = raiz;
      if (raiz->esq)
        raiz = raiz->esq;
      else
        raiz = raiz->dir;

    } else {
      // Nó com dois filhos: encontrar o sucessor em ordem
      PONT temp = raiz->esq;
      while (temp->dir != NULL)
          temp = temp->dir;

      // Copiar o sucessor em ordem para este nó
      raiz->chave = temp->chave;

      // Remover o sucessor em ordem da subárvore direita
      raiz->esq = removeNo(raiz->esq, temp->chave);

      free(temp);
    }
  }

  // Se a árvore tinha apenas um nó, então a atualização da altura não é
  // necessária
  if (raiz == NULL)
    return raiz;

  // Atualizar a altura deste nó
  raiz->h = 1 + max(altura(raiz->esq), altura(raiz->dir));

  return balanceamento(raiz);
}

PONT balanceamento(PONT p) {
  int fatorBalanceamento = altura(p->dir) - altura(p->esq);
  if (fatorBalanceamento == 2) {
    int fatorBalanceamentoFilho = altura(p->dir->dir) - altura(p->dir->esq);
    if (fatorBalanceamentoFilho == -1)
      p = direitaEsquerda(p);
    else
      p = esquerda(p);
  } else if (fatorBalanceamento == -2) {
    int fatorBalanceamentoFilho = altura(p->esq->dir) - altura(p->esq->esq);
    if (fatorBalanceamentoFilho == 1)
      p = esquerdaDireita(p);
    else
      p = direita(p);
  }
  return p;
}

// Funções já existentes:
PONT inicializa() {
    return NULL;
}

// Função que adiciona um nó (não será usada mais)
PONT adiciona(PONT raiz, PONT no) {
    if (raiz == NULL)
        return no;
    if (no->chave < raiz->chave)
        raiz->esq = adiciona(raiz->esq, no);
    else
        raiz->dir = adiciona(raiz->dir, no);
    /* Ignora chave igual */
    return raiz;
}

// Função que verifica se um nó consta da árvore
PONT contem(TIPOCHAVE ch, PONT raiz) {
    if (raiz == NULL) 
        return NULL;
    if (raiz->chave == ch) 
        return raiz;
    if (raiz->chave > ch)
        return contem(ch, raiz->esq);
    return contem(ch, raiz->dir);
}

// Função que conta o número de nós da árvore
int numeroNos(PONT raiz) {
    if (!raiz) 
        return 0;
    return numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir);
}

// Função que imprime a árvore
void exibirArvore(PONT raiz) {
    if (raiz != NULL)
    {
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

// Função que busca um nó e atribui o filho ao pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai) {
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if (atual->chave == ch) 
            return atual;
        *pai = atual;
        if (ch < atual->chave) 
            atual = atual->esq;
        else 
            atual = atual->dir;
    }
    return NULL;
}