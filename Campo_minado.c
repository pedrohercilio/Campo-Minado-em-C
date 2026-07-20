#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 9 // tamanho da matriz
#define BOMBAS 10 // quantidade de bombas

int tela[TAM][TAM]; // -> campo minado
int jogador[TAM][TAM]; // -> controla o que o usuário já digitou --  0 = fechado, 1 = aberto, 2 = marcada com bomba

void inicializaJogador() {
    // Procedimento que inicializa a matriz do jogador
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            jogador[i][j] = 0;
        }
    }
}

void inicializaTela() {
    // Distribui bombas e calcula os números

    // Zera a matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tela[i][j] = 0;
        }
    }

    // Coloca as bombas
    int bombasColocadas = 0;

    // rand() -> a partir da semente gerada no main(), calcula um valor aleatório
    while (bombasColocadas < BOMBAS) {
        int linha = rand() % TAM;
        int coluna = rand() % TAM;

        if (tela[linha][coluna] != -1) {
            tela[linha][coluna] = -1;
            bombasColocadas++;
        }
    }

    // Calcula os números
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tela[i][j] == -1)
                continue;

            int contador = 0;

            // verifica os 8 vizinhos
            for (int l = i - 1; l <= i + 1; l++) {
                // conta as bombas que existem ao redor
                for (int c = j - 1; c <= j + 1; c++) {

                    if (l >= 0 && l < TAM &&
                        c >= 0 && c < TAM &&
                        tela[l][c] == -1) {

                        contador++;
                    }
                }
            }

            tela[i][j] = contador;
        }
    }
}

void imprimeTelaOriginal() {
    // Mostra a tela verdadeira

    printf("\n==== Resultado ====\n");

    printf("  ");
    for(int j = 0; j < TAM; j++){
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tela[i][j] == -1)
                printf("* ");
            else{
                if (tela[i][j] == 1)
                    printf("\033[34m%d \033[0m", tela[i][j]);
                else if(tela[i][j] == 2)
                    printf("\033[33m%d \033[0m", tela[i][j]);
                else if(tela[i][j] >= 3)
                    printf("\033[31m%d \033[0m", tela[i][j]);
                else if(tela[i][j] == 0)
                    printf("\033[32m%d \033[0m", tela[i][j]);
            }
        }

        printf("\n");
    }
}

void imprimeTelaJogador() {
    // Mostra a tela vista pelo jogador / o que foi aberto pelo jogador

    printf("\n=== Campo Minado ===\n");

    printf("  ");
    for(int j = 0; j < TAM; j++){
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (jogador[i][j] == 0)
                printf("X ");
            else if (jogador[i][j] == 2){
                printf("\033[35mX \033[0m");
            }
            else{
                if (tela[i][j] == 1)
                    printf("\033[34m%d \033[0m", tela[i][j]);
                else if(tela[i][j] == 2)
                    printf("\033[33m%d \033[0m", tela[i][j]);
                else if(tela[i][j] >= 3)
                    printf("\033[31m%d \033[0m", tela[i][j]);
                else if(tela[i][j] == 0)
                    printf("\033[32m%d \033[0m", tela[i][j]);
            }
        }

        printf("\n");
    }
}

int venceu() {
    // Verifica vitória

    int abertas = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (jogador[i][j] == 1)
                abertas++;
        }
    }

    return (abertas == (TAM * TAM - BOMBAS));
}

void revelarVazios(int linha, int coluna) {

    // Verifica se está dentro da matriz
    if (linha < 0 || linha >= TAM ||
        coluna < 0 || coluna >= TAM) {
        return;
    }

    // Se já estiver aberta, não faz nada
    if (jogador[linha][coluna] != 0) {
        return;
    }

    // NÃO abre bombas
    if (tela[linha][coluna] == -1)
        return;


    jogador[linha][coluna] = 1;

        // Se for número, para a recursão
    if (tela[linha][coluna] != 0) {
        return;
    }
    
    // Explora os 8 vizinhos
    for (int l = linha - 1; l <= linha + 1; l++) {
        for (int c = coluna - 1; c <= coluna + 1; c++) {

            if (l == linha && c == coluna)
                continue;

            revelarVazios(l, c);
        }
    }
}

int posicaoEscolhida(int linha, int coluna) {
    // Trata a posição escolhida

    if (jogador[linha][coluna] == 1){
        printf("Posicao ja aberta!\n");
        return 1;
    }

    if (jogador[linha][coluna] == 2){
        printf("Posicao marcada como bomba!\n");
        return 1;
    }

    if (tela[linha][coluna] == -1){

        printf("\033[31m\nVOCE PERDEU!\nBOOM! Voce encontrou uma bomba!\n\033[0m");

        imprimeTelaOriginal();
        return 0;
    }

    if (tela[linha][coluna] == 0){
        revelarVazios(linha, coluna);
    }
    else{
        jogador[linha][coluna] = 1;
    }


    if (venceu()){
        printf("\033[36m\nPARABENS! VOCE VENCEU O JOGO!\n\033[0m");
        imprimeTelaOriginal();
        return 0;
    }

    return 1;
}

void marcarBomba(){
    int linha, coluna;
    char escolha;

    while(1){
        printf("Digite a linha que você deseja marcar como bomba: ");
        scanf("%d", &linha);
        printf("Digite a coluna que você deseja marcar como bomba: ");
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Posicao invalida!\n");
        }
        else
            break;
    }

    if (jogador[linha][coluna] == 0){
        jogador[linha][coluna] = 2;

    }
    else if (jogador[linha][coluna] == 2){
        printf("Posicao ja marcada!\nDeseja desmarca-la? (y/n): ");
        scanf(" %c", &escolha);
        if (escolha == 'y' || escolha == 'Y'){
            jogador[linha][coluna] = 0;
        }
    }
        
    else
        printf("A posição escolhida já foi aberta!\n");

    imprimeTelaJogador();
}

int main() {

    srand(time(NULL));
    // define que a semente (valor inicial) de rand() será time(NULL) = segundos desde 1970
    // sempre sendo um valor "aleatório" ao final dos cálculos

    inicializaTela();
    inicializaJogador();

    int linha, coluna;
    int jogando = 1;
    char bombas;

    while (jogando) {

        imprimeTelaJogador();

        printf("\nDeseja marcar algum lugar com bomba? (y/n): ");
        scanf(" %c", &bombas);

        if ((bombas == 'y') || (bombas == 'Y')){
            marcarBomba();
            continue;
        }

        printf("\nDigite a linha a ser jogada (0-8): ");
        scanf("%d", &linha);

        printf("Digite a coluna a ser jogada (0-8): ");
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAM ||
            coluna < 0 || coluna >= TAM) {

            printf("Posicao invalida!\n");
            continue;
        }

        jogando = posicaoEscolhida(linha, coluna);
    }

    return 0;
}