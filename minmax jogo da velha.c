//LP1
//Algoritmo MimniMax
//Michelle Moura

#include <stdio.h>
#include <stdlib.h>

char jogo(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void mostrar(int velha[9]) {
    printf(" %c | %c | %c\n",jogo(velha[0]),jogo(velha[1]),jogo(velha[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",jogo(velha[3]),jogo(velha[4]),jogo(velha[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",jogo(velha[6]),jogo(velha[7]),jogo(velha[8]));
}

int ganhar(const int tabuleiro[9]) {
    //determina se um jogador ganhou, retorna 0 caso contrário.
    int ganhador[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}}; // toda as forma de vencer o jogo
    int i;
    for(i = 0; i < 8; ++i) { // percorre todo o tabuleiro
        if(tabuleiro[ganhador[i][0]] != 0 && // se o valor armazenado nessa posição for igual a zero significa que ninguem venceu nessa posição
           tabuleiro[ganhador[i][0]] == tabuleiro[ganhador[i][1]] && //verifica se a segunda posição tbm foi marcada pela mesma pessoa que a primeira
           tabuleiro[ganhador[i][0]] == tabuleiro[ganhador[i][2]]) //verifica se a terceira posição tbm foi marcada pela mesma pessoa que a segunda
            return tabuleiro[ganhador[i][2]]; //restorna o vecedor se houver
    }
    return 0; // Se não houver, retorna 0
}

int minimax(int tabuleiro[9], int player) {// recebe como args o tabuleiro e o jogador
    //Posição do jogador (sua vez) 
    int ganhador = ganhar(tabuleiro);
    if(ganhador != 0) return ganhador*player; //Aqui se alguém ganhar ele não precisa mais verificar

    int mover = -1;
    int cont = -2;//Os movimentos perdidos são preferidos a nenhum movimento
    int i;
    for(i = 0; i < 9; ++i) { //Para todos os movimentos,
        if(tabuleiro[i] == 0) {  // se o movimento for possivel
            tabuleiro[i] = player; //Experimenta o movimento
            int pontuacao = -minimax(tabuleiro, player*-1); 
			if(pontuacao > cont) {
                cont = pontuacao;
                mover = i;
            } //Escolhe o pior para o adversário
            tabuleiro[i] = 0; //Reinicia a placa depois de tentar
        }
    }
    if(mover == -1) return 0;
    return cont;
}

void moviCom(int tabuleiro[9]) {
    int mover = -1;
    int cont = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(tabuleiro[i] == 0) {
            tabuleiro[i] = 1;
            int pontTempo = -minimax(tabuleiro, -1);
            tabuleiro[i] = 0;
            if(pontTempo > cont) {
                cont = pontTempo;
                mover = i;
            }
        }
    }
    //retorna uma pontuação baseada na árvore minimax em um determinado nó.
    tabuleiro[mover] = 1;
}

void moviPlay(int tabuleiro[9]) {
    int mover = 0;
    do {
        printf("\nMovimento de entrada ([0..8]): ");
        scanf("%d", &mover);
        printf("\n");
    } while (mover >= 9 || mover < 0 && tabuleiro[mover] == 0);
    tabuleiro[mover] = -1;
}

int main() {
    int tabuleiro[9] = {0,0,0,0,0,0,0,0,0}; // representa os estados de cada posição do tabuleiro
    //Quadrados do computador são 1, quadrados do jogador são -1.
    
    printf("Computador: O, Voce: X\n");
	printf("Voce quer comecar o jogo? (1)Sim ou (2)Nao? ");
	int player = 0;
    scanf("%d", &player);
    printf("\n");
  
    int vez;
    for(vez = 0; vez < 9 && ganhar(tabuleiro) == 0; ++vez) {  // quanto o ganhador() retornar 0 significa que ninguem ganhou
        if((vez + player) % 2 == 0)  // verifica se é sua vez dependendo da sua decisão no inicio do jogo 
            moviCom(tabuleiro); // faz o movimento da maquina
        else{
            mostrar(tabuleiro); // desenha o estado do tabuleiro atualmente
           moviPlay(tabuleiro); // faz a joga do jogador
       }
   }
   if (vez == 9 ) mostrar(tabuleiro);
    switch(ganhar(tabuleiro)) {
    	  
        case 0:
            printf("Deu velha.\n");
            break;
            
        case 1:
            mostrar(tabuleiro);
            printf("Voce perdeu.\n");
            break;
        case -1:
            printf("Voce venceu!\n");
            break;
    }
    
    return 0;
    
}