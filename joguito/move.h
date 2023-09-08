#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int moveInimigo(POSICAO *inimigo, int larg, int alt)
{

    if ((inimigo->x + LADO) < LARGURA && (inimigo->y + LADO) < ALTURA &&
            (inimigo->x) > 0 && (inimigo->y) > 0)
    {
        int dx = GetRandomValue(-1, 1); // Dire��o aleat�ria
        int dy = GetRandomValue(-1, 1); // Dire��o aleat�ria

        while (dx == 0 && dy == 0)
        {
            dx = GetRandomValue(-1, 1);
            dy = GetRandomValue(-1, 1);
        }
        inimigo->x += dx * LADO;
        inimigo->y += dy * LADO; //Atualiza posi��o

    }
    else
    {
        inimigo->dx = -inimigo->dx; // se bater na parede, reverte o movimento
        inimigo->dy = -inimigo->dy;

        if (inimigo->x <= 0)
        {
            inimigo->x = 1;
        }
        if ((inimigo->x + LADO) >= LARGURA)
        {
            inimigo->x = LARGURA - LADO - 1;
        }
        if (inimigo->y <= 0)
        {
            inimigo->y = 1;
        }
        if ((inimigo->y + LADO) >= ALTURA)
        {
            inimigo->y = ALTURA - LADO - 1;
        }
    }
}

//=======================================================================================================================================================//

// MOVIMENTO DO JOGADOR.

int deveMover(POSICAO *jogador, int alt, int larg, char mapa[MAPA_LINHA][MAPA_COLUNA])
{
    int posicao_x = jogador->x + (jogador->dx * LADO); // POSICAO APOS DESLOCAMENTO.
    int posicao_y = jogador->y + (jogador->dy * LADO);

    if (posicao_x < 0 || posicao_x >= LARGURA || posicao_y < 0 || posicao_y >= ALTURA) // VERIFICA SE A POSICAO CALCULADA ESTA DENTRO DOS LIMITES DA TELA.
    {

        return 0;
    }

    int mapa_x = posicao_x / LADO; // CALCULA AS COORDENADAS CORRESPONDENTES A NOVA POSICAO.
    int mapa_y = posicao_y / LADO;

    if (mapa[mapa_x][mapa_y] == '#')   // VERIFICA SE A NOVA POSICAO CORRESPONDE A UMA PAREDE.
    {
        return 0;
    }

    return 1; // CASO ESTEJA FORA DOS LIMITES OU SEJA UMA PAREDE.
}

//=======================================================================================================================================================//


void move(POSICAO *jogador)
{
    jogador->x += jogador->dx * LADO;
    jogador->y += jogador->dy * LADO;

}

//=======================================================================================================================================================//
void escreverMovimentoInimigo(FILE *arquivo, POSICAO *inimigo)
{
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita\n");
        return; // Saia da fun��o se o arquivo n�o puder ser aberto
    }

    // Registre a dire��o atual do movimento do inimigo no arquivo
    fprintf(arquivo, "Inimigo X: %d, Y: %d\n", inimigo->dx, inimigo->dy);


    // Feche o arquivo ap�s concluir a escrita
    fclose(arquivo);
}




