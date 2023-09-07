#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define LARGURA 1200
#define ALTURA 600
#define LADO 20
#define MAX_INIMIGOS 5
#define PAREDE 3
#define N_TRAPS 5

#define MAPA_LINHA 30
#define MAPA_COLUNA 60


//=======================================================================================================================================================//

int vidas = 3;


typedef struct   // CRIA UMA ESTRUTURA PARA ARMAZENAR A POSICAO DO JOGADOR E DOS INIMIGOS{
{
    int x;
    int y;
    int dx;
    int dy;
} POSICAO;


typedef enum //Menu
{
    MENU_START,
    MENU_EXIT

} MenuOptions;


//=======================================================================================================================================================//

void DrawMenu(MenuOptions currentOption)   // Funcao que abre o MENU
{
    ClearBackground(RAYWHITE);  // Limpa o fundo da tela com a cor branca.

    // Desenha o título do jogo no centro da tela.
    DrawText("SAIA VIVO DO LABIRINTO", GetScreenWidth() / 2 - MeasureText("SAIA VIVO DO LABIRINTO", 40) / 2, 120, 50, PURPLE);

    // Verifica se a opção atual é "Iniciar Jogo" e desenha-a de forma destacada ou não.
    if (currentOption == MENU_START)
        DrawText("> Iniciar Jogo <", GetScreenWidth() / 2 - MeasureText("> Iniciar Jogo <", 20) / 2, GetScreenHeight() / 2 - 20, 20, GRAY);
    else
        DrawText("Iniciar Jogo", GetScreenWidth() / 2 - MeasureText("Iniciar Jogo", 20) / 2, GetScreenHeight() / 2 - 20, 20, DARKGRAY);

    // Verifica se a opção atual é "Sair" e desenha-a de forma destacada ou não.
    if (currentOption == MENU_EXIT)
        DrawText("> Sair <", GetScreenWidth() / 2 - MeasureText("> Sair <", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
    else
        DrawText("Sair", GetScreenWidth() / 2 - MeasureText("Sair", 20) / 2, GetScreenHeight() / 2 + 20, 20, DARKGRAY);
}


//=======================================================================================================================================================//

int moveInimigo(POSICAO *inimigo, int larg, int alt)
{

    if ((inimigo->x + LADO) < LARGURA && (inimigo->y + LADO) < ALTURA &&
            (inimigo->x) > 0 && (inimigo->y) > 0)
    {
        int dx = GetRandomValue(-1, 1); // Direção aleatória
        int dy = GetRandomValue(-1, 1); // Direção aleatória

        while (dx == 0 && dy == 0)
        {
            dx = GetRandomValue(-1, 1);
            dy = GetRandomValue(-1, 1);
        }
        inimigo->x += dx * LADO;
        inimigo->y += dy * LADO; //Atualiza posição

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

// REINICIA O JOGO - OS ELEMENTOS/ PERSONAGENS DO JOGO SEMPRE INICIAM NA MESMA POSICAO.

void reiniciarJogo(POSICAO *jogador, POSICAO inimigo[], POSICAO armadilha[], POSICAO *bomba, int *vidas, char mapa[MAPA_LINHA][MAPA_COLUNA])
{

    for (int i = 0; i < MAPA_LINHA; i++)
    {
        for (int j = 0; j < MAPA_COLUNA; j++)
        {
            if (mapa[i][j] == 'J')
            {
                jogador->x = j * LADO; // Define a coordenada x do jogador
                jogador->y = i * LADO; // Define a coordenada y do jogador
            }

            if (mapa[i][j] == 'I')
            {
                inimigo->x = j * LADO; // Define a coordenada x do inimigo.
                inimigo->y = i * LADO; // Define a coordenada y do inimigo.
            }

            if (mapa[i][j] == 'X')
            {
                armadilha->x = j * LADO; // Define a coordenada x da armadilha.
                armadilha->y = i * LADO; // Define a coordenada y da armadilha.
            }

            if (mapa[i][j] == 'B')
            {
                bomba->x = j * LADO; // Define a coordenada x da bomba.
                bomba->y = i * LADO; // Define a coordenada y da bomba.
            }
        }
    }

    *vidas = 3;
}


//=======================================================================================================================================================//

void drawSquare(int x, int y, int size, Color color)
{
    DrawRectangle(x * size, y * size, size, size, color);
}
// ARRUMARRRRRR!!!!!!!!!!

//=======================================================================================================================================================//

// LE O MAPA A PARTIR DE UM ARQUIVO TXT.

int leMapa(char *nome, POSICAO *jogador, POSICAO inimigos[], int *num_inimigos, char mapa[][MAPA_COLUNA]) // ACHO Q N PRECISA RECEBER OS INIMIGOS E O JOGADOR COMO ARGUMENTO N SEI
{

    int i = 0, j = 0;
    char caractere; // REPRESENTA OS CARACTERES PRESENTES NO ARQUIVO.


    FILE *mapa_arq = fopen(nome, "r");

    if (mapa_arq == NULL)         // CONFERE SE O ARQUIVO FOI ABERTO COM SUCESSO.
    {
        printf("Erro ao abrir o arquivo\n");

        return 0;
    }

    else
    {

        for (i = 0; i < MAPA_LINHA; i++)
        {
            for (j = 0; j < MAPA_COLUNA; j++)
            {
                caractere = getc(mapa_arq);
                mapa[i][j] = caractere;

                if (caractere == 'J')
                {
                    jogador->x = j * LADO;
                    jogador->y = i * LADO;
                    jogador->dx = 0;
                    jogador->dy = 0;
                }


                if (caractere == 'I')
                {
                    if (*num_inimigos < MAX_INIMIGOS)
                    {
                        inimigos[*num_inimigos].x = j * LADO;
                        inimigos[*num_inimigos].y = i * LADO;
                        inimigos[*num_inimigos].dx = GetRandomValue(-1, 1);
                        inimigos[*num_inimigos].dy = GetRandomValue(-1, 1);
                        (*num_inimigos)++;
                    }
                }
            }
            getc(mapa_arq);
        }

        fclose(mapa_arq);

        return 1;
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
        return; // Saia da função se o arquivo não puder ser aberto
    }

    // Registre a direção atual do movimento do inimigo no arquivo
    fprintf(arquivo, "Inimigo X: %d, Y: %d\n", inimigo->dx, inimigo->dy);


    // Feche o arquivo após concluir a escrita
    fclose(arquivo);
}


//=======================================================================================================================================================//
void atualizarMapaJogador(char mapa[MAPA_LINHA][MAPA_COLUNA], POSICAO jogador)
{
    // Limpe a posição anterior do jogador no mapa
    mapa[jogador.y / LADO][jogador.x / LADO] = ' ';

    // Atualize a nova posição do jogador no mapa
    mapa[jogador.y / LADO][jogador.x / LADO] = 'J';
}


void atualizarMapaGrafico(char mapa[][MAPA_COLUNA], POSICAO jogador)
{
    for (int i = 0; i < MAPA_LINHA; i++)
    {
        for (int j = 0; j < MAPA_COLUNA; j++)
        {
            char caractere = mapa[i][j];
            Color color = WHITE;

            // Verifique se o caractere é 'J' (jogador)
            if (caractere == 'J')
            {
                color = PURPLE; // Defina a cor do jogador como roxa
            }
            else
            {
                // Defina a cor com base no caractere atual
                switch (caractere)
                {
                case 'B':
                    color = BLUE;
                    break;
                case 'P':
                    color = GREEN;
                    break;
                case 'X':
                    color = ORANGE;
                    break;
                case 'I':
                    color = RED;
                    break;
                case '#':
                    color = PINK;
                    break;
                default:
                    break;
                }
            }

            // Apague o quadrado anterior
            DrawRectangle(j * LADO, i * LADO, LADO, LADO, RAYWHITE);

            // Desenhe o novo quadrado na posição atual com a cor correspondente
            DrawRectangle(j * LADO, i * LADO, LADO, LADO, color);
        }
    }
}





//=======================================================================================================================================================//
//=====================================================INT MAIN()========================================================================================//
//=======================================================================================================================================================//

int main(void)
{
    POSICAO jogador;
    POSICAO inimigos[MAX_INIMIGOS];
    POSICAO armadilha[N_TRAPS];
    POSICAO bomba;
    char mapa[MAPA_LINHA][MAPA_COLUNA];
    int num_inimigos = 0;
    int conta_armadilha = 0;
    FILE *mapa_arq;
    mapa_arq = fopen("maps.txt", "a");
    srand(time(NULL));





//=======================================================================================================================================================//




    InitWindow(LARGURA, ALTURA, "Jogo"); //INICIALIZA A JANELA

    SetTargetFPS(60);

        double TempoDeJogo = GetTime(); // Inicializa tempo
        char tempoTexto[16];

//...........................................................................................................................//

    if (leMapa("maps.txt", &jogador, inimigos, &num_inimigos, mapa))
    {
        atualizarMapaGrafico(mapa, jogador); // Atualiza a representação gráfica inicial
    }


//...........................................................................................................................//
MenuOptions currentOption = MENU_START;  // Define a opção de menu atual como "Iniciar Jogo".
    int enterPressed = 0;  // Variável para rastrear se a tecla Enter foi pressionada.

    while (!WindowShouldClose())
    {
        // Lógica do menu
        if (IsKeyPressed(KEY_UP))
        {
            currentOption = (currentOption == MENU_START) ? MENU_EXIT : MENU_START;  // Alterna entre as opções de menu para cima.
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            currentOption = (currentOption == MENU_EXIT) ? MENU_START : MENU_EXIT;  // Alterna entre as opções de menu para baixo.
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            enterPressed = 1;  // Define a variável enterPressed como 1 quando a tecla Enter é pressionada.
        }

        // Renderização
        BeginDrawing();  // Inicia o processo de renderização.
        DrawMenu(currentOption);  // Chama a função para desenhar o menu na tela.
        EndDrawing();  // Finaliza o processo de renderização.

        // Processamento da seleção
        if (enterPressed)
        {

            if (currentOption == MENU_START)
            {

                //Para iniciar o jogo, o corpo coloquei o código
                // Fim do loop do menu

//...........................................................................................................................//

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

//...........................................................................................................................//

//...........................................................................................................................//


        for (int i = 0; i < num_inimigos; i++)
        {
            moveInimigo(&inimigos[i], LARGURA, ALTURA);
        }

        int frame_counter = 0;
        int enemy_update_freq = 3;



        atualizarMapaGrafico(mapa, jogador);
        for (int i = 0; i < num_inimigos; i++)
        {
            moveInimigo(&inimigos[i], LARGURA, ALTURA);
        }
////// TEMPO


        jogador.dx = 0;
        jogador.dy = 0;


        double TempoJogando = GetTime() - TempoDeJogo;
        int minutos = (int)(TempoJogando / 60);
        int segundos = (int)(TempoJogando) % 60;
        snprintf(tempoTexto, sizeof(tempoTexto), "%02d:%02d", minutos, segundos);

//...........................................................................................................................//

// VERIFICA AS ENTRADAS DO TECLADO PARA MOVER O JOGADOR.

        if (IsKeyDown(KEY_RIGHT))
        {
            jogador.dx = 1;
            jogador.dy = 0;

            if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
            {

                move(&jogador);
                atualizarMapaJogador(mapa, jogador);
            }
        }
        else if (IsKeyDown(KEY_LEFT))
        {

            jogador.dx = -1;
            jogador.dy = 0;

            if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
            {

                move(&jogador);
                atualizarMapaJogador(mapa, jogador);
            }
        }

        if (IsKeyDown(KEY_DOWN))
        {

            jogador.dy = 1;
            jogador.dx = 0;

            if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
            {

                move(&jogador);
                atualizarMapaJogador(mapa, jogador);
            }
        }
        else if (IsKeyDown(KEY_UP))
        {

            jogador.dy = -1;
            jogador.dx = 0;

            if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
            {

                move(&jogador);
                atualizarMapaJogador(mapa, jogador);
            }
        }

        if (frame_counter % enemy_update_freq == 0) // MOVIMENTA O INIMIGO
        {
            for (int i = 0; i < MAX_INIMIGOS; i++)
            {
                moveInimigo(&inimigos[i], MAPA_LINHA, ALTURA);
            }
        }

        if (frame_counter >= enemy_update_freq)  // !!!!!!!! NAO SEI OQ ISSO AQUI FAZ
        {

            frame_counter = 0;
        }


//...........................................................................................................................//

// VERIFICA COLISAO COM OS INIMIGOS.

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {

            if (CheckCollisionRecs((Rectangle)
        {
            jogador.x, jogador.y, LADO, LADO
        }, (Rectangle)
        {
            inimigos[i].x, inimigos[i].y, LADO, LADO
            }))
            {

                vidas--;
            }

            if (vidas <= 0)
            {

                reiniciarJogo(&jogador, inimigos, armadilha, &bomba, &vidas, mapa);
            }
        }


// VERIFICA COLISAO COM ARMADILHAS

        for (int i = 0; i < N_TRAPS; i++)
        {

            if (CheckCollisionRecs((Rectangle)
        {
            jogador.x, jogador.y, LADO, LADO
        }, (Rectangle)
        {
            armadilha[i].x, armadilha[i].y, LADO, LADO
            }))
            {

                vidas--;
            }
        }


        if (vidas <= 0)
        {
            reiniciarJogo(&jogador, inimigos, armadilha, &bomba, &vidas, mapa);
        }


// Atualiza a representacão visual a partir do estado do jogo


// Move o quadrado roxo após verificar todas as colisões
        if (deveMover(&jogador, LARGURA, ALTURA, mapa))
        {
            move(&jogador);
        }

//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posicao, tamanho e cor
// Calcula as coordenadas para o retângulo e o texto


        DrawRectangle(jogador.x, jogador.y, 20, 20, VIOLET);
                DrawMenu(currentOption);
        atualizarMapaGrafico(mapa,jogador);
        DrawRectangle(LARGURA - 80, ALTURA - 40, 70, 30, WHITE); // Parte de trás do relógio
        DrawText(tempoTexto, LARGURA - 75, ALTURA - 35, 20, RED); // Relógio

        DrawText("Vidas:", LARGURA - 780, ALTURA - 40, 20, BLACK);
        DrawText(TextFormat("%d", vidas), LARGURA - 720, ALTURA - 40, 20, RED);



        EndDrawing();//Finaliza o ambiente de desenho na tela

    }
      if (currentOption == MENU_EXIT)
                {
                    CloseWindow();  // Fecha a janela do jogo.
                }
                enterPressed = 0;  // Redefine enterPressed para 0 após o processamento da seleção.
            }
        }
    }// Fim do loop do menu


    return 0;

}
