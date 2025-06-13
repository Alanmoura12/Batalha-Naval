#include <stdio.h>
#include <stdbool.h>

// Tamanho do tabuleiro
#define TAMANHO 10

// Valores do tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Função para limpar o tabuleiro (preencher com água)
void limparTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se uma posição é válida
bool posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO;
}

// Função para posicionar um navio horizontalmente
bool posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    // Verifica se o navio cabe na posição
    if (!posicaoValida(linha, coluna)) return false;
    if (!posicaoValida(linha, coluna + tamanho - 1)) return false;
    
    // Verifica se não há navio nas posições
    for (int j = coluna; j < coluna + tamanho; j++) {
        if (tabuleiro[linha][j] != AGUA) return false;
    }
    
    // Posiciona o navio
    for (int j = coluna; j < coluna + tamanho; j++) {
        tabuleiro[linha][j] = NAVIO;
    }
    
    return true;
}

// Função para posicionar um navio verticalmente
bool posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    // Verifica se o navio cabe na posição
    if (!posicaoValida(linha, coluna)) return false;
    if (!posicaoValida(linha + tamanho - 1, coluna)) return false;
    
    // Verifica se não há navio nas posições
    for (int i = linha; i < linha + tamanho; i++) {
        if (tabuleiro[i][coluna] != AGUA) return false;
    }
    
    // Posiciona o navio
    for (int i = linha; i < linha + tamanho; i++) {
        tabuleiro[i][coluna] = NAVIO;
    }
    
    return true;
}

// Função para posicionar um navio na diagonal (direita para baixo)
bool posicionarNavioDiagonal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int tamanho) {
    // Verifica se o navio cabe na posição
    if (!posicaoValida(linha, coluna)) return false;
    if (!posicaoValida(linha + tamanho - 1, coluna + tamanho - 1)) return false;
    
    // Verifica se não há navio nas posições
    for (int i = 0; i < tamanho; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) return false;
    }
    
    // Posiciona o navio
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }
    
    return true;
}

// Função para criar matriz de habilidade em forma de cone
void criarCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i && i <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em forma de cruz
void criarCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar matriz de habilidade em forma de octaedro (losango)
void criarOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int distancia = abs(i - 2) + abs(j - 2);
            if (distancia <= 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[5][5], int linha, int coluna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int tabLinha = linha - 2 + i;
            int tabColuna = coluna - 2 + j;
            
            if (posicaoValida(tabLinha, tabColuna)) {
                if (habilidade[i][j] == 1) {
                    tabuleiro[tabLinha][tabColuna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    // 1. Inicializar o tabuleiro
    limparTabuleiro(tabuleiro);
    
    // 2. Posicionar navios (nível novato)
    printf("Posicionando navios...\n");
    posicionarNavioHorizontal(tabuleiro, 2, 2, 3);  // Navio horizontal
    posicionarNavioVertical(tabuleiro, 5, 5, 3);    // Navio vertical
    
    // Exibir tabuleiro após posicionar navios básicos
    exibirTabuleiro(tabuleiro);
    printf("\n");
    
    // 3. Posicionar navios diagonais (nível aventureiro)
    printf("Adicionando navios diagonais...\n");
    posicionarNavioDiagonal(tabuleiro, 1, 1, 3);    // Navio diagonal 1
    posicionarNavioDiagonal(tabuleiro, 6, 0, 3);    // Navio diagonal 2
    
    // Exibir tabuleiro após posicionar navios diagonais
    exibirTabuleiro(tabuleiro);
    printf("\n");
    
    // 4. Adicionar habilidades especiais (nível mestre)
    printf("Aplicando habilidades especiais...\n");
    
    // Criar matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);
    
    // Aplicar habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 4, 4);
    aplicarHabilidade(tabuleiro, cruz, 7, 7);
    aplicarHabilidade(tabuleiro, octaedro, 2, 7);
    
    // Exibir tabuleiro final com habilidades
    exibirTabuleiro(tabuleiro);
    
    return 0;
}