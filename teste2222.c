#include "raylib.h"
#include <string.h>
#define LARGURA 800
#define ALTURA 800
#define LADO 20
#define MAX_INIMIGOS 20



//Estrutura dos inimigos

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;

} INIMIGOS;
//int moveInimigo(int *qxi, int *qyi)
//{
//int dxi = (rand() % 40) * 20;
//int dyi = (rand() % 40) * 20;

//if ((*qxi + LADO + dxi * 20) < LARGURA && (*qyi + LADO + dyi * 20) < ALTURA &&
//(*qxi + dxi * 20) > 0 && (*qyi + dyi * 20) > 0)
//{
//*qxi += dxi * 20;
//*qyi += dyi * 20;
//}
//return 0;
//}
int moveInimigo(int *qxi, int *qyi)
{


    if ((*qxi + LADO * 20) < LARGURA && (*qyi + LADO  * 20) < ALTURA &&
            (*qxi * 20) > 0 && (*qyi  * 20) > 0)
    {
        *qxi += dx * 20;
        *qyi += dy * 20;
    }
    return 0;
}

int deveMover(int qx, int qy, int dx, int dy)
{

    if (qx + (dx * 20) > 780)
    {
        return 0;
    }
    if (qy + (dy * 20) > 780)
    {
        return 0;
    }
    if (qx + (dx * 20)< 0)
    {
        return 0;
    }
    if (qy + (dy * 20) < 0)
    {
        return 0;
    }

    return 1;
}

int move(int dx, int dy, int *qx, int *qy)
{
    *qx += dx * 20;
    *qy += dy * 20;
}

int main(void)
{

    int qx = ((rand()% 40)*20);
    int qy = ((rand()% 40)*20);

//--------------------------------------------------------------------------------------
//Inicializacões
    InitWindow(LARGURA, ALTURA, "Jogo");//Inicializa janela, com certo tamanho e título
    SetTargetFPS(75);// Ajusta a execução do jogo para 60 frames por segundo
//--------------------------------------------------------------------------------------
    int dx = 0;
    int dy = 0;

    // Sobre os inimigos:
    INIMIGOS inimigo[MAX_INIMIGOS];

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigo[i].dx = 0;
        inimigo[i].dy = 0;
        inimigo[i].x = (rand() % 40) * 20;
        inimigo[i].y = (rand() % 40) * 20;
    }

    while (!WindowShouldClose())
    {
        // Verifica as entradas do teclado para mover o quadrado


        if (IsKeyDown(KEY_RIGHT))
        {
            dx = 1;
            dy = 0;
            if (deveMover(qx, qy, dx, dy))
            {
                move(dx, dy, &qx, &qy);
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            dx = -1;
            dy = 0;
            if (deveMover(qx, qy, dx, dy))
            {
                move(dx, dy, &qx, &qy);
            }
        }

        if (IsKeyDown(KEY_DOWN))
        {
            dy = 1;
            dx = 0;
            if (deveMover(qx, qy, dx, dy))
            {
                move(dx, dy, &qx, &qy);
            }
        }

        else if (IsKeyDown(KEY_UP))
        {
            dy = -1;
            dx = 0;
            if (deveMover(qx, qy, dx, dy))
            {
                move(dx, dy, &qx, &qy);
            }
        }

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {
            DrawRectangle(inimigo[i].x, inimigo[i].y, LADO, LADO, ORANGE);
            moveInimigo();
        }
//----------------------------------------------------------------------------------
// Atualiza a representacão visual a partir do estado do jogo
//----------------------------------------------------------------------------------
        BeginDrawing();//Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo
//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posi¸c~ao, tamanho e cor
        DrawRectangle(qx, qy, 20, 20, VIOLET);
        EndDrawing();//Finaliza o ambiente de desenho na tela


//----------------------------------------------------------------------------------
    }
    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;
}

