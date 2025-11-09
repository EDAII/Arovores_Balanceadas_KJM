# 1382. Balancear uma Árvore de Busca Binária

Dada a `root` de uma árvore de busca binária, retorne uma árvore de busca binária **balanceada** com os mesmos valores dos nós. Se houver mais de uma resposta, retorne **qualquer uma delas**.

Uma árvore de busca binária é **balanceada** se a profundidade das duas subárvores de cada nó nunca difere em mais de `1`.

**Exemplo 1:**

```
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explicação: Esta não é a única resposta correta, [3,1,4,null,2] também está correta.
```

**Exemplo 2:**

```
Input: root = [2,1,3]
Output: [2,1,3]
```

**Restrições:**

* O número de nós na árvore está no intervalo `[1, 10^4]`.
* `1 <= Node.val <= 10^5`
