# 🧩 Crakme — Brute Force / Engenharia Reversa

Este repositório documenta a engenharia reversa e a solução por *brute force* aplicada ao desafio **Crakme.exe**. O código presente implementa a função de hash replicada a partir da análise do binário e um brute-force que busca o inteiro de 4 bytes cuja aplicação da função produz a *hash* alvo.

> **Importante:** durante a análise o objetivo mudou: o crackme originalmente exigia uma chave de **6 bytes** (busca impraticável por força bruta no escopo do projeto). Por isso o objetivo foi alterado para encontrar a *hash* do valor **`1770989405`** que corresponde a uma verificação de **4 bytes**. Essa decisão permitiu validar a lógica do algoritmo e concluir a análise.

---

## 📄 Conteúdo do repositório

```
/
├─ Hash/                 # Código-fonte 
├─ x64/Debug/.           # Executavél
└─ Hash.Sln              # Solução
```

---

## 🔧 Código principal (resumo)

A função `hash` replicada encontrada no binário foi implementada em C/C++ assim:

```c
int __cdecl hash(int8_t* a1)
{
    signed char* v1;
    int v3;

    v3 = -1515870811;
    for (int i = 0; i < 4; i++)
    {
        v1 = a1++;
        v3 = 31 * v3 + *v1;
    }
    return v3;
}
```

* `v3` inicia com `-1515870811` (seed).
* Para cada um dos 4 bytes da entrada, `v3 = 31 * v3 + byte`.
* A função retorna um `int` de 4 bytes portanto testamos combinações de 32 bits (um `int`).

O brute-force itera sobre o espaço de inteiros (4 bytes) e constrói o vetor `s[4]` com os bytes de cada `i`:

```c
s[0] = (int8_t)((i >> 24) & 0xFF);
s[1] = (int8_t)((i >> 16) & 0xFF);
s[2] = (int8_t)((i >> 8) & 0xFF);
s[3] = (int8_t)(i & 0xFF);
```

Se `hash(s)` for igual ao valor alvo (`1770989405`), o programa imprime o resultado.

---

## 🛠 Requisitos e como compilar

Requisitos:

* Compilador C++ (g++, clang++ ou Visual Studio)
* Ambiente Windows / Linux conforme sua preferência

No Windows com Visual Studio, abra o projeto/arquivo e compile como console app (x86/x64 conforme desejado).

**Observação de performance:** o loop percorre até `INT_MAX`. Em máquinas comuns o brute-force pode levar um tempo considerável — otimizações possíveis incluem multithreading, reduzir prints durante o loop e usar bit-operations mais eficientes.

---

## ✅ Resultados e observações

* A análise estática (IDA) e dinâmica (x32dbg) permitiu identificar a função `hash` e a sequência de chamadas relevantes.
* A descoberta do *seed* e do algoritmo (multiplicação por 31 + adição do byte) foi suficiente para implementar a função de verificação.
* Como explicado, a exigência original de uma chave de **6 bytes** foi substituída por uma meta prática: confirmar a *hash* alvo **`1770989405`** (4 bytes).
* Ao executar o brute-force corretamente replicando o algoritmo do binário, o programa deverá encontrar o inteiro correspondente cuja representação em 4 bytes produz a *hash* desejada.

---

## 🔍 Como verificar / reproduzir a análise

1. Abra `Hash/brute_force.cpp` (ou o arquivo principal fornecido).
2. Compile com o seu compilador.
3. Execute o binário e aguarde o programa imprime uma mensagem de progresso e, ao encontrar a correspondência, imprime o inteiro correspondente e o hash encontrado.

---

## ⚠️ Avisos legais e éticos

* Este repositório e a documentação têm fins **educacionais**: estudar técnicas de engenharia reversa, depuração e análise de binários.
* Não utilize estes métodos para violar a segurança de software alheio sem autorização explícita. Sempre obtenha permissão antes de analisar software que você não possui ou que esteja protegido por lei.

---


## 🤝 Créditos / Agradecimentos

* **Daniel Zanata** — autor da análise e código presente no repositório (GitHub: `DevDanielZanata`).
* **Cestaro0** — instrução, mentoria e suporte técnico durante o desafio (GitHub: `Cestaro0`). 

  > Agradecimento especial: o *Cestaro0* forneceu o crackme que serviu de base para esta análise, e orientou grande parte do processo de engenharia reversa. Sem a ajuda e o material fornecido por ele, este trabalho não teria avançado como avançou.

---
