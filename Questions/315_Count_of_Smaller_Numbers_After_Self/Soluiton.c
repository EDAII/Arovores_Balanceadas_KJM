#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct NoArvoreAVL {
    int valor;
    struct NoArvoreAVL* esquerda;
    struct NoArvoreAVL* direita;
    int altura;
    int tamanhoSubarvore;
    int contagemPropria;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obterAltura(struct NoArvoreAVL* no) {
    if (no == NULL) return 0;
    return no->altura;
}

int obterTamanho(struct NoArvoreAVL* no) {
    if (no == NULL) return 0;
    return no->tamanhoSubarvore;
}

void atualizarNo(struct NoArvoreAVL* no) {
    if (no == NULL) return;
    no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));
    no->tamanhoSubarvore = no->contagemPropria + obterTamanho(no->esquerda) + obterTamanho(no->direita);
}

struct NoArvoreAVL* criarNo(int valor) {
    struct NoArvoreAVL* no = (struct NoArvoreAVL*)malloc(sizeof(struct NoArvoreAVL));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    no->contagemPropria = 1;
    no->tamanhoSubarvore = 1;
    return no;
}

struct NoArvoreAVL* rotacaoDireita(struct NoArvoreAVL* y) {
    struct NoArvoreAVL* x = y->esquerda;
    struct NoArvoreAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizarNo(y);
    atualizarNo(x);

    return x;
}

struct NoArvoreAVL* rotacaoEsquerda(struct NoArvoreAVL* x) {
    struct NoArvoreAVL* y = x->direita;
    struct NoArvoreAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizarNo(x);
    atualizarNo(y);

    return y;
}

int obterFatorBalanceamento(struct NoArvoreAVL* no) {
    if (no == NULL) return 0;
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

struct NoArvoreAVL* inserirNo(struct NoArvoreAVL* no, int valor, int* contadorMenores) {
    
    if (no == NULL) {
        return criarNo(valor);
    }

    if (valor < no->valor) {
        no->esquerda = inserirNo(no->esquerda, valor, contadorMenores);
        
    } else if (valor > no->valor) {
        *contadorMenores += no->contagemPropria + obterTamanho(no->esquerda);
        no->direita = inserirNo(no->direita, valor, contadorMenores);
        
    } else {
        *contadorMenores += obterTamanho(no->esquerda);
        no->contagemPropria++;
    }

    atualizarNo(no);

    int fatorBalanceamento = obterFatorBalanceamento(no);

    if (fatorBalanceamento > 1 && valor < no->esquerda->valor) {
        return rotacaoDireita(no);
    }

    if (fatorBalanceamento < -1 && valor > no->direita->valor) {
        return rotacaoEsquerda(no);
    }

    if (fatorBalanceamento > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (fatorBalanceamento < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void liberarArvore(struct NoArvoreAVL* no) {
    if (no == NULL) return;
    liberarArvore(no->esquerda);
    liberarArvore(no->direita);
    free(no);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    
    *returnSize = numsSize;
    if (numsSize == 0) {
        return NULL;
    }

    int* contagens = (int*)calloc(numsSize, sizeof(int));
    
    struct NoArvoreAVL* raiz = NULL;
    
    for (int i = numsSize - 1; i >= 0; i--) {
        int contadorMenores = 0;
        
        raiz = inserirNo(raiz, nums[i], &contadorMenores);
        
        contagens[i] = contadorMenores;
    }
    
    liberarArvore(raiz);
    
    return contagens;
}
