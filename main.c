#include<stdio.h>
#include<stdlib.h>
#include "AVL.h"

int main(int argc, char** argv) {
    PONT r;
    int v, b, n;
    int continuar = 1;

    do {
        printf("\n\tMenu de Opcao\n\n");
        printf("1. Inicializa a arvore \n");
        printf("2. Insere na arvore\n");
        printf("3. Buscar um valor na arvore\n");
        printf("4. Conta o numero de nos da arvore\n");
        printf("5. Imprime a arvore\n");
        printf("6. Remove um no da arvore\n");
        printf("0. Sair\n");

        scanf("%d", &continuar);
        system("cls || clear");

        switch (continuar) {
            case 1:
                r = inicializa();
                printf("Arvore criada com sucesso");
                break;

            case 2:
                printf("Digite um numero para inserir na arvore:");
                scanf("%d", &v);
                PONT no = criaNovoNo(v);
                r = insere(r, v); // Alteração aqui para chamar a nova função de inserção
                printf("No inserido com sucesso");
                break;
                
            case 3:
                printf("Digite um valor para pesquisar na arvore");
                scanf("%d", &b);
                PONT resultado = contem(b, r);
                if (resultado == NULL)
                    printf("O valor %d nao foi localizado\n", b);
                else
                    printf("O valor %d foi localizado na arvore\n", b);
                break;
                
            case 4:
                n = numeroNos(r);
                printf("A arvore possui: %d nos\n", n);
                break;
                
            case 5:
                exibirArvore(r);
                break;
            
            case 6:
                printf("Digite um valor para remover da arvore:");
                scanf("%d",&v);
                r = removeNo(r,v);
                printf("Valor removido com sucesso");
                break;

            case 0:
                break;
            default:
                printf("Digite uma opcao valida\n");
        }
    } while (continuar != 0);
    return 0;
}