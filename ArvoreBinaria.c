#include <stdio.h>
#include <stdlib.h>

// estrututa n�
typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} No;

// estrutura �rvore com um ponteiro para um n�
typedef struct {
    No *raiz;
    int tam;
} ArvB;

/*
    Procedimento para inserir um elemento na �rvore,
    inserindo � esquerda ou � direita
    nova vers�o para a inser��o, mais resumida
    perceba que agora � uma fun��o
*/
No* inserirNovaVersao(No *raiz, int valor) {
    if(raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        if(valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor);
        if(valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita, valor);
        return raiz;
    }
}

// fun��o que retorna a quantidade de elemento em uma �rvore
int tamanho(No *raiz) {
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

// fun��o para buscar um elemento na �rvore
int buscar(No *raiz, int chave) {
    if(raiz == NULL) {
        return 0;
    } else {
        if(raiz->conteudo == chave)
            return 1;
        else {
            if(chave < raiz->conteudo)
                return buscar(raiz->esquerda, chave);
            else
                return buscar(raiz->direita, chave);
        }
    }
}
/*  faz a impress�o da �rvore em ordem crescente
    esquerda - raiz - direita
*/
void imprimir(No *raiz) {
    if(raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

int maior(No *raiz){
    No *navegacao = raiz;
    while(navegacao->direita != NULL){
        navegacao = navegacao->direita;
    }
    return navegacao->conteudo;
}




// fun��o para a remo��o de um n�
No* remover(No *raiz, int chave) {
    if(raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if(raiz->conteudo == chave) {
            // remove n�s folhas (n�s sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            }
            else{
                // remover n�s que possuem apenas 1 filho
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
                else{
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        } else {
            if(chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
}

