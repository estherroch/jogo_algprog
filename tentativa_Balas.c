#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LARGURA 800
#define ALTURA 800
#define LADO 20
#define MAX_INIMIGOS 10
#define PAREDE 3
#define N_TRAPS 5
#define MAX_BALAS 10

// Defina o tamanho do mapa (número de células em largura e altura)
#define MAPA_LARGURA (LARGURA / LADO)
#define MAPA_ALTURA (ALTURA / LADO)


/// Variável global da vida

int vidas = 3;

////////////////////////////////////////////////////////////////////////////////EstruturasE PERSONAGENS
typedef struct
{
    int xi;
    int yi;
    int dxi;
    int dyi;
} INIMIGO;


typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
} PLAYER;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int velocidade;
    bool ativa; // Para verificar se a bala está ativa ou não
} BALA;

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

// Para reiniciar o jogo se a vida chegar em 0

void reiniciarJogo(PLAYER *player, INIMIGO inimigo[], int *vidas, int mapa[MAPA_LARGURA][MAPA_ALTURA])
{

    player->x = ((rand() % 40) * LADO);
    player->y = ((rand() % 40) * LADO);
    *vidas = 3;

    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        inimigo[i].dxi = GetRandomValue(-1, 1);
        inimigo[i].dyi = GetRandomValue(-1, 1);
        inimigo[i].xi = GetRandomValue(0, LARGURA);
        inimigo[i].yi = GetRandomValue(0, ALTURA);
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



int deveMover(PLAYER *player, int alt, int larg, int mapa[MAPA_LARGURA][MAPA_ALTURA])
{
    int posicao_x = player->x + (player->dx * LADO); // Posição após o deslocamento, posição inicial + deslocamento.
    int posicao_y = player->y + (player->dy * LADO);

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

void move(PLAYER *player)
{
    player->x += player->dx * 20;
    player->y += player->dy * 20;
}

//// Função para disparar balas

void dispararBala(PLAYER *player, Bala balas[], int maxBalas) {
    for (int i = 0; i < maxBalas; i++) {
        if (!balas[i].ativa) {
            balas[i].ativa = true;
            balas[i].x = player->x + (LADO / 2); // Posição inicial da bala no centro do jogador
            balas[i].y = player->y + (LADO / 2);

            // Determina a direção da bala com base na tecla pressionada
            if (IsKeyDown(KEY_W)) {
                balas[i].dx = 0;
                balas[i].dy = -1;
            } else if (IsKeyDown(KEY_S)) {
                balas[i].dx = 0;
                balas[i].dy = 1;
            } else if (IsKeyDown(KEY_A)) {
                balas[i].dx = -1;
                balas[i].dy = 0;
            } else if (IsKeyDown(KEY_D)) {
                balas[i].dx = 1;
                balas[i].dy = 0;
            }

            balas[i].velocidade = 5; // Velocidade padronizada
            break;
        }
    }
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


    int armadilhas[N_TRAPS][2]; // Matriz para armazenar as coordenadas das armadilhas

    for (int i = 0; i < N_TRAPS; i++)
    {
        armadilhas[i][0] = (rand() % MAPA_LARGURA); // Coordenada X da armadilha
        armadilhas[i][1] = (rand() % MAPA_ALTURA);  // Coordenada Y da armadilha
        mapa[armadilhas[i][0]][armadilhas[i][1]] = 2; // Marca a célula do mapa como uma armadilha
    }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Inicializando o player, declarando estrutura

    PLAYER player;

    player.x = ((rand()% 40)*LADO);
    player.y = ((rand()% 40)*LADO);

    // Inicializando as balas
   for (int i = 0; i < MAX_BALAS; i++) {
    if (balas[i].ativa) {
        balas[i].x += balas[i].dx * balas[i].velocidade;
        balas[i].y += balas[i].dy * balas[i].velocidade;

        // Verifique se a bala saiu da tela ou atingiu um inimigo e desative-a se necessário
        if (balas[i].x < 0 || balas[i].x >= LARGURA || balas[i].y < 0 || balas[i].y >= ALTURA) {
            balas[i].ativa = false;
        } else {
            // Verifique colisão com inimigos aqui e desative a bala se atingir um inimigo
        }
    }
}



//Inicializacões

    InitWindow(LARGURA, ALTURA, "Jogo");//Inicializa janela, com certo tamanho e tıtulo
    SetTargetFPS(20);// Ajusta a execução do jogo para 60 frames por segundo


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


////   while (!WindowShouldClose()) /////////
    while (!WindowShouldClose())
    {
        player.dx = 0;

        player.dy = 0;


        double TempoJogando = GetTime() - TempoDeJogo;
        int minutos = (int)(TempoJogando / 60);
        int segundos = (int)(TempoJogando) % 60;
        snprintf(tempoTexto, sizeof(tempoTexto), "%02d:%02d", minutos, segundos);

// Verifica as entradas do teclado para mover o quadrado
        if (IsKeyDown(KEY_RIGHT))
        {
            player.dx = 1;
            player.dy = 0;
            if (deveMover(&player, LARGURA, ALTURA, mapa))
            {
                move(&player);
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            player.dx = -1;
            player.dy = 0;
            if (deveMover(&player, LARGURA, ALTURA, mapa))
            {
                move(&player);
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player.dy = 1;
            player.dx = 0;
            if (deveMover(&player, LARGURA, ALTURA, mapa))
            {
                move(&player);
            }
        }
        else if (IsKeyDown(KEY_UP))
        {
            player.dy = -1;
            player.dx = 0;
            if (deveMover(&player, LARGURA, ALTURA, mapa))
            {
                move(&player);
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
    if (CheckCollisionRecs((Rectangle){player.x, player.y, LADO, LADO},
                           (Rectangle){inimigo[i].xi, inimigo[i].yi, LADO, LADO}))
    {
        vidas--;
    }
    if (vidas <= 0)
    {
        reiniciarJogo(&player, inimigo, &vidas, mapa);
    }
}

// Verifica colisões com a armadilha
for (int i = 0; i < N_TRAPS; i++)
{
    int trapX = armadilhas[i][0];
    int trapY = armadilhas[i][1];

    // Verifica se a armadilha está ativa em uma determinada posição (trapX, trapY)
   if (mapa[trapX][trapY] == 2)
{
    Rectangle trapRect = {trapX * LADO, trapY * LADO, LADO, LADO};

    if (CheckCollisionRecs((Rectangle){player.x, player.y, LADO, LADO},
                           trapRect))
    {
        vidas--;
    }
    if (vidas <= 0)
    {
        reiniciarJogo(&player, inimigo, &vidas, mapa);
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
        if (deveMover(&player, LARGURA, ALTURA, mapa))
        {
            move(&player);
        }

//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posicao, tamanho e cor
// Calcula as coordenadas para o retângulo e o texto


        DrawRectangle(player.x, player.y, 20, 20, VIOLET);
        DrawRectangle(LARGURA - 80, ALTURA - 40, 70, 30, WHITE); // Parte de trás do relógio
        DrawText(tempoTexto, LARGURA - 75, ALTURA - 35, 20, RED); // Relógio

        DrawText("Vidas:", LARGURA - 780, ALTURA - 40, 20, BLACK);
        DrawText(TextFormat("%d", vidas), LARGURA - 720, ALTURA - 40, 20, RED);

        // desenha as armadilhas

        for (int i = 0; i < N_TRAPS; i++)
        {
            int trapX = armadilhas[i][0];
            int trapY = armadilhas[i][1];

            if (mapa[trapX][trapY] == 2) // Verifica se a célula contém uma armadilha
            {
                DrawRectangle(trapX * LADO, trapY * LADO, LADO, LADO, RED);
            }
        }

        // Desenha as balas

        for (int i = 0; i < MAX_BALAS; i++) {
    if (balas[i].ativa) {
        // Desenhe a bala na posição balas[i].x, balas[i].y
    }
}
        EndDrawing();//Finaliza o ambiente de desenho na tela

    }

    CloseWindow();// Fecha a janela e o contexto OpenGL
    return 0;
}
