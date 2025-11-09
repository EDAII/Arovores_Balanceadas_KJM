# 315. Contagem de Números Menores Após Si Mesmo

Dado um array de inteiros `nums`, retorne um array de inteiros `counts` onde `counts[i]` é o número de elementos menores à direita de `nums[i]`.

**Exemplo 1:**

```
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explicação:
À direita de 5 existem 2 elementos menores (2 e 1).
À direita de 2 existe apenas 1 elemento menor (1).
À direita de 6 existe 1 elemento menor (1).
À direita de 1 existe 0 elemento menor.
```

**Exemplo 2:**

```
Input: nums = [-1]
Output: [0]
```

**Exemplo 3:**

```
Input: nums = [-1,-1]
Output: [0,0]
```

**Restrições:**

* `1 <= nums.length <= 10^5`
* `-10^4 <= nums[i] <= 10^4`
