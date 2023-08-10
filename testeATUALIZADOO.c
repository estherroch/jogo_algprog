#include "raylib.h"
#include <string.h>
#define LARGURA 800
#define ALTURA 800
#define LADO 20


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
    InitWindow(LARGURA, ALTURA, "Jogo");//Inicializa janela, com certo tamanho e t´ıtulo
    SetTargetFPS(75);// Ajusta a execução do jogo para 60 frames por segundo
//--------------------------------------------------------------------------------------
    int dx = 0;
    int dy = 0;
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

