#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 600
#define ALTURA 600
#define LADO 20
#define MAX_INIMIGOS 10
#define PAREDE 3

// Defina o tamanho do mapa (número de células em largura e altura)
#define MAPA_LARGURA (LARGURA / LADO)
#define MAPA_ALTURA (ALTURA / LADO)


//////////////////////////////////////////////////////////////////////////////// INIMIGOS E PERSONAGENS
typedef struct
{
    int xi;
    int yi;
    int dxi;
    int dyi;
} INIMIGO;

int moveInimigo(INIMIGO *inimigo, int larg, int alt)
{

    if ((inimigo->xi + LADO) < LARGURA && (inimigo->yi + LADO) < ALTURA &&
            (inimigo->xi) > 0 && (inimigo->yi) > 0)
    {
        int dx = GetRandomValue(-1, 1); // Direção aleatória
        int dy = GetRandomValue(-1, 1); // Direção aleatória
        while (dx == 0 && dy == 0)
        {
            dx = GetRandomValue(-1, 1);
            dy = GetRandomValue(-1, 1);
        }
        inimigo->xi += dx * LADO;
        inimigo->yi += dy * LADO; //Atualiza posição

    }
    else
    {
        inimigo->dxi = -inimigo->dxi; // se bater na parede, reverte o movimento
        inimigo->dyi = -inimigo->dyi;

        if (inimigo->xi <= 0)
        {
            inimigo->xi = 1;
        }
        if ((inimigo->xi + LADO) >= LARGURA)
        {
            inimigo->xi = LARGURA - LADO - 1;
        }
        if (inimigo->yi <= 0)
        {
            inimigo->yi = 1;
        }
        if ((inimigo->yi + LADO) >= ALTURA)
        {
            inimigo->yi = ALTURA - LADO - 1;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void make_mapa(int mapa[MAPA_LARGURA][MAPA_ALTURA]) {
    for (int y = 0; y < MAPA_ALTURA; y++) {
        for (int x = 0; x < MAPA_LARGURA; x++) {
            Rectangle rect = { x * LADO, y * LADO, LADO, LADO };
            if (mapa[x][y] == 1) {
                DrawRectangleRec(rect, DARKGRAY);  // Wall
            } else {
                DrawRectangleRec(rect, RAYWHITE);  // Open path
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////



int deveMover(int x, int y, int dx, int dy, int alt, int larg)
{
    int posicao_x = x + (dx * LADO); //posição após o deslocamento, posição incial + deslocamento.
    int posicao_y = y + (dy * LADO);

    // se a posição calculada está dentro dos limites da tela, o quadrado pode se mover.

    if (posicao_x < 0 || posicao_x >= LARGURA || posicao_y < 0 || posicao_y >= ALTURA)
    {

        return 0;
    }

    return 1; //caso esteja fora dos limites.

}

int move(int dx, int dy, int *x, int *y)
{
    *x += dx * 20;
    *y += dy * 20;
}

///////////////////////////int main ()////////////////////////////////////////////////////////////////////////

int main(void){
///// MAPA
    int i=0, j=0;
    int mapa[MAPA_LARGURA][MAPA_ALTURA] = {0};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

srand(time(NULL));

    // Create walls along the borders
    for (int x = 0; x < MAPA_LARGURA; x++) {
        mapa[x][0] = 1;
        mapa[x][MAPA_ALTURA - 1] = 1;
    }
    for (int y = 0; y < MAPA_ALTURA; y++) {
        mapa[0][y] = 1;
        mapa[MAPA_LARGURA - 1][y] = 1;
    }

    // Create internal walls
    for (int x = 2; x < MAPA_LARGURA - 2; x += 2) {
        for (int y = 2; y < MAPA_ALTURA - 2; y += 2) {
            mapa[x][y] = 1;
    }
}



//return 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int x = ((rand()% 40)*LADO);
    int y = ((rand()% 40)*LADO);

//Inicializacões

    InitWindow(LARGURA, ALTURA, "Jogo");//Inicializa janela, com certo tamanho e tıtulo
    SetTargetFPS(30);// Ajusta a execução do jogo para 60 frames por segundo


    int dx = 0;

    int dy = 0;

////////////////////////////////////////////////////////////////////////////////////////////

    INIMIGO inimigo[MAX_INIMIGOS];

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigo[i].dxi = 0;
        inimigo[i].dyi = 0;
        inimigo[i].xi = (rand() % 40) * LADO;
        inimigo[i].yi = (rand() % 40) * LADO;
    }

    int frame_counter = 0;
    int enemy_update_freq = 4;


    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigo[i].dxi = GetRandomValue(-1, 1); // Random initial x direction (-1, 0, 1)
        inimigo[i].dyi = GetRandomValue(-1, 1); // Random initial y direction (-1, 0, 1)
        inimigo[i].xi = GetRandomValue(0, LARGURA); // Random initial x position
        inimigo[i].yi = GetRandomValue(0, ALTURA);   // Random initial y position
    }


    while (!WindowShouldClose())
    {
        // Verifica as entradas do teclado para mover o quadrado


        if (IsKeyDown(KEY_RIGHT))
        {
            dx = 1;
            dy = 0;
            if (deveMover(x, y, dx, dy, LARGURA, ALTURA))
            {
                move(dx, dy, &x, &y);
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            dx = -1;
            dy = 0;
            if (deveMover(x, y, dx, dy, LARGURA, ALTURA))
            {
                move(dx, dy, &x, &y);
            }

        }

        if (IsKeyDown(KEY_DOWN))
        {
            dy = 1;
            dx = 0;
            if (deveMover(x, y, dx, dy, ALTURA, LARGURA))
            {
                move(dx, dy, &x, &y);
            }
        }

        else if (IsKeyDown(KEY_UP))
        {
            dy = -1;
            dx = 0;
            if (deveMover(x, y, dx, dy, ALTURA, LARGURA))
            {
                move(dx, dy, &x, &y);
            }

        }


        if (frame_counter % enemy_update_freq == 0)
        {

            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                moveInimigo(&inimigo[i], LARGURA, ALTURA);
            }
        }


        frame_counter ++;



        if (frame_counter >= enemy_update_freq)
        {
            frame_counter = 0;
        }


// Atualiza a representacão visual a partir do estado do jogo

        BeginDrawing();//Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo

        make_mapa(mapa);

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {

            DrawRectangle(inimigo[i].xi, inimigo[i].yi, LADO, LADO, ORANGE);
        };



//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posi¸c~ao, tamanho e cor
        DrawRectangle(x, y, 20, 20, VIOLET);
        EndDrawing();//Finaliza o ambiente de desenho na tela

    }

    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;

}
