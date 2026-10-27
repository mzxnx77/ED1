# Exercício 9 — TAD: Inventário Opaco

**Universidade Federal Rural do Semi-Árido (UFERSA)**  
**Disciplina:** Algoritmo e Estrutura de Dados I  
**Semestre:** 2026.2  
**Professora:** Rosana Rego

## Objetivo

Demonstrar o conceito de Tipo Abstrato de Dados (TAD) em C, usando a biblioteca Raylib para uma demonstração visual.

O projeto aborda:

- Tipo opaco: `Inventario` é declarado em `inventario.h`, mas sua estrutura interna é definida somente em `inventario.c`.
- Encapsulamento: `atividade9.c` manipula o inventário exclusivamente por funções públicas.
- Ponteiros e alocação dinâmica com `malloc` e `free`.
- Structs, enums e vetor de ponteiros para entidades.
- Contagem de entidades por tipo.

## Exercícios implementados

### Exercício 1 — Verificar se o inventário está cheio

A função `inventarioEstaCheio` compara `total` e `capacidade` dentro de `inventario.c`. O programa principal usa essa função para mostrar um aviso na tela.

### Exercício 2 — Contar entidades por tipo

A função `inventarioContarPorTipo` percorre o vetor interno e conta as entidades do tipo solicitado. A tela mostra quantos itens (`ENTIDADE_ITEM`) ainda restam.

## Arquivos

- `atividade9.c`: programa principal e demonstração com Raylib.
- `entidade.h` / `entidade.c`: estrutura pública e funções das entidades.
- `inventario.h`: interface pública do TAD opaco.
- `inventario.c`: estrutura interna e implementação do inventário.
- `Makefile`: comandos básicos de compilação.

## Controles

- `W`, `A`, `S`, `D` ou setas: mover o jogador.
- Colete os itens dourados para somar pontos.
- Colidir com inimigos reduz as vidas.

## Compilação no Linux

Instale o compilador C, o `make`, o `pkg-config` e a Raylib. Depois, na pasta do projeto:

```bash
make
./atividade9
```

Se o seu ambiente não disponibilizar `pkg-config`, compile manualmente usando as opções de link da Raylib instaladas no sistema.

## Compilação no Windows

Instale a Raylib e configure o compilador para encontrá-la. As opções de compilação e link dependem de como a Raylib foi instalada (por exemplo, MSYS2/MinGW ou instalador próprio).

## Observação

Este projeto é uma implementação independente baseada no enunciado fornecido. Compare com os arquivos das atividades anteriores e ajuste eventuais nomes de campos, funções ou configurações exigidos pela versão da professora.
