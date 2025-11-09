#include <stdlib.h>
#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int contarNos(struct TreeNode* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarNos(raiz->left) + contarNos(raiz->right);
}

void percursoEmOrdem(struct TreeNode* no, int* valoresOrdenados, int* indice) {
    if (no == NULL) {
        return;
    }
    
    percursoEmOrdem(no->left, valoresOrdenados, indice);
    
    valoresOrdenados[*indice] = no->val;
    (*indice)++;
    
    percursoEmOrdem(no->right, valoresOrdenados, indice);
}

struct TreeNode* construirArvoreBalanceada(int* valoresOrdenados, int inicio, int fim) {
    if (inicio > fim) {
        return NULL;
    }
    
    int meio = inicio + (fim - inicio) / 2;
    
    struct TreeNode* novaRaiz = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    novaRaiz->val = valoresOrdenados[meio];
    novaRaiz->left = NULL;
    novaRaiz->right = NULL;
    
    novaRaiz->left = construirArvoreBalanceada(valoresOrdenados, inicio, meio - 1);
    novaRaiz->right = construirArvoreBalanceada(valoresOrdenados, meio + 1, fim);
    
    return novaRaiz;
}

struct TreeNode* balanceBST(struct TreeNode* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    
    int totalNos = contarNos(raiz);
    
    int* valoresOrdenados = (int*)malloc(totalNos * sizeof(int));
    
    int indice = 0; 
    
    percursoEmOrdem(raiz, valoresOrdenados, &indice);
    
    struct TreeNode* novaRaizBalanceada = construirArvoreBalanceada(valoresOrdenados, 0, totalNos - 1);
    
    free(valoresOrdenados);
    
    return novaRaizBalanceada;
}
