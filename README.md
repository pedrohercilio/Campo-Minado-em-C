# 💣 Campo Minado em C

Implementação do clássico jogo **Campo Minado** desenvolvida em linguagem C para execução via terminal.

O projeto foi desenvolvido com foco na prática de programação estruturada, algoritmos, recursão e manipulação de matrizes bidimensionais, reproduzindo as principais mecânicas do jogo original.

---

## 📌 Funcionalidades

- Geração automática de um tabuleiro 9x9.
- Distribuição aleatória de 10 bombas.
- Cálculo automático das bombas adjacentes.
- Interface interativa no terminal.
- Revelação de células escolhidas pelo jogador.
- Abertura automática de áreas vazias utilizando recursão.
- Sistema de marcação e desmarcação de bombas.
- Verificação de vitória e derrota.
- Exibição colorida do tabuleiro para facilitar a visualização.

---

## 🛠 Tecnologias

- Linguagem C
- GCC
- Bibliotecas padrão:
  - stdio.h
  - stdlib.h
  - time.h

---

## 📚 Conceitos aplicados

- Programação Estruturada
- Modularização utilizando funções
- Matrizes bidimensionais
- Recursão
- Algoritmos de busca em vizinhança (8 direções)
- Geração de números aleatórios
- Estruturas de decisão e repetição
- Manipulação do estado do jogo
- Validação de entradas do usuário

---

## ▶️ Como executar

Compile o projeto:

```bash
gcc campo_minado.c -o campo_minado
