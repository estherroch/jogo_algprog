#include "raylib.h"
#include <string.h>
#include <stdlib.h>

#define LARGURA 700
#define ALTURA 600
#define LADO 20
#define MAX_INIMIGOS 10
#define PAREDE 3
#define N_TRAPS 5

// Defina o tamanho do mapa (número de células em largura e altura)
#define MAPA_LARGURA (LARGURA / LADO)
#define MAPA_ALTURA (ALTURA / LADO)

// váriavel global das vidas

int vidas = 3;


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

//////////////////////////////////////////////////////////////////////////////////////////////// faz as paredes do mapa

void constroi_parede(int startX, int startY, int endX, int endY, int openingX, int openingY, int mapa[MAPA_LARGURA][MAPA_ALTURA])
{

    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

    for (int x = startX; x != endX + stepX; x += stepX)
    {
        for (int y = startY; y != endY + stepY; y += stepY)
        {
            if (x >= 0 && x < MAPA_LARGURA && y >= 0 && y < MAPA_ALTURA && (x != openingX || y != openingY))
            {
                mapa[x][y] = 1;
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////



int deveMover(int x, int y, int dx, int dy, int alt, int larg, int mapa[MAPA_LARGURA][MAPA_ALTURA])
{
    int posicao_x = x + (dx * LADO); // Posição após o deslocamento, posição inicial + deslocamento.
    int posicao_y = y + (dy * LADO);

    // Verifica se a posição calculada está dentro dos limites da tela
    if (posicao_x < 0 || posicao_x >= LARGURA || posicao_y < 0 || posicao_y >= ALTURA)
    {
        return 0;
    }

    // Calcula as coordenadas da célula do mapa correspondente à nova posição
    int mapa_x = posicao_x / LADO;
    int mapa_y = posicao_y / LADO;

    // Verifica se a nova posição corresponde a uma célula com parede
    if (mapa[mapa_x][mapa_y] == 1)
    {
        return 0;
    }

    return 1; // Caso esteja fora dos limites ou não seja uma célula com parede.
}


int move(int dx, int dy, int *x, int *y)
{
    *x += dx * 20;
    *y += dy * 20;
}

///////////////////////////int main ()////////////////////////////////////////////////////////////////////////

int main(void)
{
///// MAPA

    int mapa[MAPA_LARGURA][MAPA_ALTURA] = {0};

    // constroi as paredes com abertura
    for (int i = 0; i < LARGURA; i++)
    {
        if (i == 3 || i == 10 || i == 17)    // 3 paredes verticais
        {
            constroi_parede(i, 2, i, ALTURA / LADO - 4, i, LADO / 2, mapa);

        }
    }

    for (int i = 0; i < ALTURA; i++)
    {
        if (i == 5 || i == 12)    // 2 paredes horizontais
        {
            constroi_parede(i, i, LARGURA / LADO - 4, i, i, 6, mapa);
        }
    }

    srand(time(NULL));

    // cria parede nas bordas
    for (int x = 0; x < MAPA_LARGURA; x++)
    {
        mapa[x][0] = 1;
        mapa[x][MAPA_ALTURA - 1] = 1;
    }
    for (int y = 0; y < MAPA_ALTURA; y++)
    {
        mapa[0][y] = 1;
        mapa[MAPA_LARGURA - 1][y] = 1;
    }

void gerarArmadilhas(int mapa[MAPA_LARGURA][MAPA_ALTURA], int x, int y)
{
    for (int i = 0; i < N_TRAPS; i++)
    {
        int trapX, trapY;

        do
        {
            trapX = GetRandomValue(1, MAPA_LARGURA - 2);
            trapY = GetRandomValue(1, MAPA_ALTURA - 2);
        } while (mapa[trapX][trapY] != 0 || (trapX == x && trapY == y));

        mapa[trapX][trapY] = 2; // Marque as armadilhas no mapa
    }
}


//return 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int x = ((rand()% 40)*LADO);
    int y = ((rand()% 40)*LADO);

//Inicializacões

    InitWindow(LARGURA, ALTURA, "Jogo");//Inicializa janela, com certo tamanho e tıtulo
    SetTargetFPS(20);// Ajusta a execução do jogo para 60 frames por segundo


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
    int enemy_update_freq = 3;


    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigo[i].dxi = GetRandomValue(-1, 1);
        inimigo[i].dyi = GetRandomValue(-1, 1);
        inimigo[i].xi = GetRandomValue(0, LARGURA);
        inimigo[i].yi = GetRandomValue(0, ALTURA);
    }
////// TEMPO

    double TempoDeJogo = GetTime(); // Inicializa tempo
    char tempoTexto[16];
    //// Armadilhas
     gerarArmadilhas(mapa, x, y);


    while (!WindowShouldClose())
    {


        double TempoJogando = GetTime() - TempoDeJogo;
        int minutos = (int)(TempoJogando / 60);
        int segundos = (int)(TempoJogando) % 60;
        snprintf(tempoTexto, sizeof(tempoTexto), "%02d:%02d", minutos, segundos);

// Verifica as entradas do teclado para mover o quadrado
        if (IsKeyDown(KEY_RIGHT))
        {
            dx = 1;
            dy = 0;
            if (deveMover(x, y, dx, dy, LARGURA, ALTURA, mapa))
            {
                move(dx, dy, &x, &y);
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            dx = -1;
            dy = 0;
            if (deveMover(x, y, dx, dy, LARGURA, ALTURA, mapa))
            {
                move(dx, dy, &x, &y);
            }
        }

        if (IsKeyDown(KEY_DOWN))
        {
            dy = 1;
            dx = 0;
            if (deveMover(x, y, dx, dy, ALTURA, LARGURA, mapa))
            {
                move(dx, dy, &x, &y);
            }
        }
        else if (IsKeyDown(KEY_UP))
        {
            dy = -1;
            dx = 0;
            if (deveMover(x, y, dx, dy, ALTURA, LARGURA, mapa))
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
// Verifica colisão com inimigos
for (int i = 0; i < MAX_INIMIGOS; i++)
{
    if (CheckCollisionRecs((Rectangle){x, y, LADO, LADO}, (Rectangle){inimigo[i].xi, inimigo[i].yi, LADO, LADO}))
    {
        vidas--;
    }
}

// Verifica colisão com armadilhas
for (int y = 0; y < MAPA_ALTURA; y++)
{
    for (int x = 0; x < MAPA_LARGURA; x++)
    {
        if (mapa[x][y] == 2 && CheckCollisionRecs((Rectangle){x * LADO, y * LADO, LADO, LADO}, (Rectangle){x, y, LADO, LADO}))
        {
            vidas--;
        }
    }
}

// Atualiza a representacão visual a partir do estado do jogo

        BeginDrawing();//Inicia o ambiente de desenho na tela
        ClearBackground(RAYWHITE);//Limpa a tela e define cor de fundo

        // Desenha o mapa
        for (int y = 0; y < MAPA_ALTURA; y++)
        {
            for (int x = 0; x < MAPA_LARGURA; x++)
            {
                Rectangle rect = {x * LADO, y * LADO, LADO, LADO};
                if (mapa[x][y] == 1)
                {
                    DrawRectangleRec(rect, DARKGRAY);  // parede
                }
                else
                {
                    DrawRectangleRec(rect, RAYWHITE);  // caminho aberto
                }
            }
        }

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {

            DrawRectangle(inimigo[i].xi, inimigo[i].yi, LADO, LADO, ORANGE);
        };



// Move o quadrado roxo após verificar todas as colisões
if (deveMover(x, y, dx, dy, ALTURA, LARGURA, mapa))
{
    move(dx, dy, &x, &y);
}





//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posicao, tamanho e cor
// Calcula as coordenadas para o retângulo e o texto


        DrawRectangle(x, y, 20, 20, VIOLET);
        DrawRectangle(LARGURA - 80, ALTURA - 40, 70, 30, WHITE); // Parte de trás do relógio
       // DrawText(tempoTexto, LARGURA - 75, ALTURA - 35, 20, RED); // Relógio

        DrawText("Vidas:", LARGURA - 120, ALTURA - 35, 20, BLACK);
        DrawText(TextFormat("%d", vidas), LARGURA - 55, ALTURA - 35, 20, RED);

// ...

        EndDrawing();//Finaliza o ambiente de desenho na tela

    }

    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;

}
