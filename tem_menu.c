#include "raylib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LARGURA 1200
#define ALTURA 600
#define LADO 20
#define MAX_INIMIGOS 5
#define PAREDE 3
#define N_TRAPS 5

#define MAPA_LINHA 30
#define MAPA_COLUNA 60
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


//=======================================================================================================================================================//

int vidas = 3;
int lastUpdate = 1;
int colectedBombs = 0;
double lastMove = 0;

typedef struct   // CRIA UMA ESTRUTURA PARA ARMAZENAR A POSICAO DO JOGADOR E DOS INIMIGOS{
{
    int x;
    int y;
    int dx;
    int dy;
    int matrixPositionX;
    int matrixPositionY;
    int vivo;
} POSICAO;



typedef enum //Menu
{
    MENU_START,
    MENU_EXIT

} MenuOptions;


//=======================================================================================================================================================//
int deveMover(POSICAO *jogador, int alt, int larg, char mapa[MAPA_LINHA][MAPA_COLUNA])
{
    int newPositionX = jogador->matrixPositionX + jogador->dx;
    int newPositionY = jogador->matrixPositionY + jogador->dy;

    if (newPositionX < 0 || newPositionX >= MAPA_LINHA || newPositionY < 0 || newPositionY >= MAPA_COLUNA) // VERIFICA SE A POSICAO CALCULADA ESTA DENTRO DOS LIMITES DA TELA.
    {
        printf("fora dos limites\n");
        return 0;
    }

    if (mapa[newPositionX][newPositionY] == '#')   // VERIFICA SE A NOVA POSICAO CORRESPONDE A UMA PAREDE.
    {
        printf("parede\n");
        return 0;
    }

    if (mapa[newPositionX][newPositionY] == 'X')   // VERIFICA SE A NOVA POSICAO CORRESPONDE A UMA ARMADILHA.
    {
        printf("armadilha\n");
        vidas--;
    }

    if (mapa[newPositionX][newPositionY] == 'I')   // VERIFICA SE A NOVA POSICAO CORRESPONDE A UMA ARMADILHA.
    {
        printf("inimigo\n");
        printf("vidas: %d\n", vidas);
        vidas--;
        return 0;
    }

    if (mapa[newPositionX][newPositionY] == 'B')   // VERIFICA SE A NOVA POSICAO CORRESPONDE A UMA BOMBA.
    {
        printf("bomba\n");
        colectedBombs++;
    }

    return 1; // CASO ESTEJA FORA DOS LIMITES OU SEJA UMA PAREDE.
}

int isPortal(char mapa[MAPA_LINHA][MAPA_COLUNA], POSICAO jogador)
{
    if (mapa[jogador.matrixPositionX + jogador.dx][jogador.matrixPositionY + jogador.dy] == 'P')
    {
        return 1;
    }
    return 0;
}

void DrawMenu(MenuOptions currentOption)   // Funcao que abre o MENU
{
    ClearBackground(RAYWHITE);  // Limpa o fundo da tela com a cor branca.

    // Desenha o t�tulo do jogo no centro da tela.
    DrawText("SAIA VIVO DO LABIRINTO", GetScreenWidth() / 2 - MeasureText("SAIA VIVO DO LABIRINTO", 40) / 2, 120, 50, PURPLE);

    // Verifica se a op��o atual � "Iniciar Jogo" e desenha-a de forma destacada ou n�o.
    if (currentOption == MENU_START)
        DrawText("> Iniciar Jogo <", GetScreenWidth() / 2 - MeasureText("> Iniciar Jogo <", 20) / 2, GetScreenHeight() / 2 - 20, 20, GRAY);
    else
        DrawText("Iniciar Jogo", GetScreenWidth() / 2 - MeasureText("Iniciar Jogo", 20) / 2, GetScreenHeight() / 2 - 20, 20, DARKGRAY);

    // Verifica se a op��o atual � "Sair" e desenha-a de forma destacada ou n�o.
    if (currentOption == MENU_EXIT)
        DrawText("> Sair <", GetScreenWidth() / 2 - MeasureText("> Sair <", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
    else
        DrawText("Sair", GetScreenWidth() / 2 - MeasureText("Sair", 20) / 2, GetScreenHeight() / 2 + 20, 20, DARKGRAY);
}


//=======================================================================================================================================================//

int moveInimigo(POSICAO *inimigo, int larg, int alt, char mapa[MAPA_LINHA][MAPA_COLUNA])
{
    while(true){

        int dx = GetRandomValue(-1, 1); // Dire��o aleat�ria
        int dy = GetRandomValue(-1, 1); // Dire��o aleat�ria

        while (dx == 0 && dy == 0)
        {
            dx = GetRandomValue(-1, 1);
            dy = GetRandomValue(-1, 1);
        }
        inimigo->dx = dx;
        inimigo->dy = dy;
        if (deveMover(inimigo, larg, alt, mapa)){
            inimigo->matrixPositionX += dx;
            inimigo->matrixPositionY += dy;
            return 1;
        }
    }
    
    return 0;

}

//=======================================================================================================================================================//

void printMap (char mapa[MAPA_LINHA][MAPA_COLUNA])
{
    for (int i = 0; i < MAPA_LINHA; i++)
    {
        for (int j = 0; j < MAPA_COLUNA; j++)
        {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

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

int leMapa(char *nome, POSICAO *jogador, POSICAO inimigos[], int *num_inimigos, char mapa[MAPA_LINHA][MAPA_COLUNA]) // ACHO Q N PRECISA RECEBER OS INIMIGOS E O JOGADOR COMO ARGUMENTO N SEI
{

    char caractere; // REPRESENTA OS CARACTERES PRESENTES NO ARQUIVO.


    FILE *mapa_arq = fopen(nome, "r");

    if (mapa_arq == NULL)         // CONFERE SE O ARQUIVO FOI ABERTO COM SUCESSO.
    {
        printf("Erro ao abrir o arquivo\n");

        return 0;
    }

    else
    {

        for (int i = 0; i < MAPA_LINHA; i++) {
        for (int j = 0; j < MAPA_COLUNA; j++) {
            char c = fgetc(mapa_arq);
            if (c == '\n') {  // Skip newline characters
                j--;
                continue;
            }
            mapa[i][j] = c;
            if (c == 'J')
                {
                    jogador->x = i * LADO;
                    jogador->y = j * LADO;
                    printf("jogador y: %d\n", jogador->y);
                    jogador->dx = 0;
                    jogador->dy = 0;
                    jogador->matrixPositionX = i;
                    jogador->matrixPositionY = j;
                    printf("jogador matrix y: %d\n", jogador->matrixPositionY);
                    printf("jogador matrix x: %d\n", jogador->matrixPositionX);
                }


            if (c == 'I')
            {
                if (*num_inimigos < MAX_INIMIGOS)
                {
                    inimigos[*num_inimigos].x = j * LADO;
                    inimigos[*num_inimigos].y = i * LADO;
                    inimigos[*num_inimigos].matrixPositionX = i;
                    inimigos[*num_inimigos].matrixPositionY = j;
                    inimigos[*num_inimigos].dx = GetRandomValue(-1, 1);
                    inimigos[*num_inimigos].dy = GetRandomValue(-1, 1);
                    inimigos[*num_inimigos].vivo = 1;
                    (*num_inimigos)++;
                }
            }
        }
        }

        printf("num inimigos: %d\n", *num_inimigos);

        fclose(mapa_arq);

        return 1;
    }
}


//=======================================================================================================================================================//

// MOVIMENTO DO JOGADOR.



//=======================================================================================================================================================//


void move(POSICAO *jogador)
{
    jogador->matrixPositionX += jogador->dx;
    jogador->matrixPositionY += jogador->dy;

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

int canShoot(char mapa [MAPA_LINHA][MAPA_COLUNA], POSICAO jogador, int direction){
    int x = jogador.matrixPositionX;
    int y = jogador.matrixPositionY;
    int dx = 0;
    int dy = 0;
    switch (direction)
    {
        case UP:
            dx = -1;
            break;
        case DOWN:
            dx = 1;
            break;
        case LEFT:
            dy = -1;
            break;
        case RIGHT:
            dy = 1;
            break;
        default:
            break;
    }
    if (mapa[x + dx][y + dy] == '#')
    {
        return 0;
    }
    return 1;
}

//=======================================================================================================================================================//
void atualizarMapaJogador(char mapa[MAPA_LINHA][MAPA_COLUNA], POSICAO jogador)
{
    // Limpe a posi��o anterior do jogador no mapa
    mapa[(jogador.matrixPositionX - jogador.dx)][(jogador.matrixPositionY - jogador.dy)] = ' ';

    // Atualize a nova posi��o do jogador no mapa
    mapa[jogador.matrixPositionX][jogador.matrixPositionY] = 'J';
}

void atualizarMapaInimigo(char mapa[MAPA_LINHA][MAPA_COLUNA], POSICAO inimigo)
{
    // Limpe a posi��o anterior do jogador no mapa
    mapa[(inimigo.matrixPositionX - inimigo.dx)][(inimigo.matrixPositionY - inimigo.dy)] = ' ';

    // Atualize a nova posi��o do jogador no mapa
    mapa[inimigo.matrixPositionX][inimigo.matrixPositionY] = 'I';
}

void atualizarMapaGrafico(char mapa[][MAPA_COLUNA], POSICAO jogador)
{
    for (int i = 0; i < MAPA_LINHA; i++)
    {
        for (int j = 0; j < MAPA_COLUNA; j++)
        {
            char caractere = mapa[i][j];
            Color color = WHITE;

            // Verifique se o caractere � 'J' (jogador)
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
                case 'U':
                    color = YELLOW;
                    break;
                case 'D':
                    color = YELLOW;
                    break;
                case 'L':
                    color = YELLOW;
                    break;
                case 'R':
                    color = YELLOW;
                    break;
                default:
                    break;
                }
            }

            // Apague o quadrado anterior
            DrawRectangle(j * LADO, i * LADO, LADO, LADO, RAYWHITE);

            // Desenhe o novo quadrado na posi��o atual com a cor correspondente
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
    srand(time(NULL));





//=======================================================================================================================================================//




    InitWindow(LARGURA, ALTURA, "Jogo"); //INICIALIZA A JANELA

    SetTargetFPS(60);

    double TempoDeJogo = GetTime(); // Inicializa tempo
    char tempoTexto[16];

//...........................................................................................................................//

    if (leMapa("mapa2.txt", &jogador, inimigos, &num_inimigos, mapa))
    {
        atualizarMapaGrafico(mapa, jogador); // Atualiza a representa��o gr�fica inicial
    }


//...........................................................................................................................//
MenuOptions currentOption = MENU_START;  // Define a op��o de menu atual como "Iniciar Jogo".
    int enterPressed = 0;  // Vari�vel para rastrear se a tecla Enter foi pressionada.

    while (!WindowShouldClose())
    {
        // L�gica do menu
        if (IsKeyPressed(KEY_UP))
        {
            currentOption = (currentOption == MENU_START) ? MENU_EXIT : MENU_START;  // Alterna entre as op��es de menu para cima.
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            currentOption = (currentOption == MENU_EXIT) ? MENU_START : MENU_EXIT;  // Alterna entre as op��es de menu para baixo.
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            enterPressed = 1;  // Define a vari�vel enterPressed como 1 quando a tecla Enter � pressionada.
        }

        // Renderiza��o
        BeginDrawing();  // Inicia o processo de renderiza��o.
        DrawMenu(currentOption);  // Chama a fun��o para desenhar o menu na tela.
        EndDrawing();  // Finaliza o processo de renderiza��o.

        // Processamento da sele��o
        if (enterPressed)
        {

            if (currentOption == MENU_START)
            {

                //Para iniciar o jogo, o corpo coloquei o c�digo
                // Fim do loop do menu

//...........................................................................................................................//

    while (!WindowShouldClose())
    {

        BeginDrawing();
        
        // clear the screen
        ClearBackground(RAYWHITE);

//...........................................................................................................................//

//...........................................................................................................................//


        int frame_counter = 0;
        int enemy_update_freq = 2;



        atualizarMapaGrafico(mapa, jogador);
        
////// TEMPO


        jogador.dx = 0;
        jogador.dy = 0;


        double TempoJogando = GetTime() - TempoDeJogo;
        int minutos = (int)(TempoJogando / 60);
        int segundos = (int)(TempoJogando) % 60;
        snprintf(tempoTexto, sizeof(tempoTexto), "%02d:%02d", minutos, segundos);

//...........................................................................................................................//

// VERIFICA AS ENTRADAS DO TECLADO PARA MOVER O JOGADOR.
        // make sure that the player can only move every 10 frames using time from last move


        // update the projectile position by reading all the map and checking if there is a projectile
        // if there is a projectile, update the position of the projectile
        // if the projectile hits a wall, destroy the projectile
        // if the projectile hits an enemy, destroy the projectile and the enemy
        
        for (int i = 0; i < MAPA_LINHA; i++)
        {
            for (int j = 0; j < MAPA_COLUNA; j++)
            {
                if (mapa[i][j] == 'U')
                {
                    if (mapa[i - 1][j] == '#')
                    {
                        mapa[i][j] = ' ';
                    }
                    else
                    {
                        if (mapa[i - 1][j] == 'I')
                        {
                            for (int k = 0; k < num_inimigos; k++)
                            {
                                if (inimigos[k].matrixPositionX == i - 1 && inimigos[k].matrixPositionY == j)
                                {
                                    inimigos[k].vivo = 0;
                                }
                            }
                        }
                        mapa[i][j] = ' ';
                        mapa[i - 1][j] = 'U';
                        
                    }
                }
                if (mapa[i][j] == 'L')
                {
                    if (mapa[i][j - 1] == '#')
                    {
                        mapa[i][j] = ' ';
                    }
                    else
                    {
                        if (mapa[i][j - 1] == 'I')
                        {
                            for (int k = 0; k < num_inimigos; k++)
                            {
                                if (inimigos[k].matrixPositionX == i && inimigos[k].matrixPositionY == j - 1)
                                {
                                    inimigos[k].vivo = 0;
                                }
                            }
                        }
                        mapa[i][j] = ' ';
                        mapa[i][j - 1] = 'L';
                        
                    }
                }
            }
        }

        for (int i = MAPA_LINHA - 1; i >= 0; i--){
            for (int j = MAPA_COLUNA - 1; j >= 0; j--){
                if (mapa[i][j] == 'R')
                {
                    if (mapa[i][j + 1] == '#')
                    {
                        mapa[i][j] = ' ';
                    }
                    else
                    {
                        if (mapa[i][j + 1] == 'I')
                        {
                            for (int k = 0; k < num_inimigos; k++)
                            {
                                if (inimigos[k].matrixPositionX == i && inimigos[k].matrixPositionY == j + 1)
                                {
                                    inimigos[k].vivo = 0;
                                }
                            }
                        }
                        mapa[i][j] = ' ';
                        mapa[i][j + 1] = 'R';
                    }
                }
                if (mapa[i][j] == 'D')
                {
                    if (mapa[i + 1][j] == '#')
                    {
                        mapa[i][j] = ' ';
                    }
                    else
                    {
                        if (mapa[i + 1][j] == 'I')
                        {
                            for (int k = 0; k < num_inimigos; k++)
                            {
                                if (inimigos[k].matrixPositionX == i + 1 && inimigos[k].matrixPositionY == j)
                                {
                                    inimigos[k].vivo = 0;
                                }
                            }
                        }
                        mapa[i][j] = ' ';
                        mapa[i + 1][j] = 'D';
                    }
                }
            }
        }

        if (GetTime() - lastMove > 0.1) // define velocidade jogador
        {
            lastMove = GetTime();
            if (IsKeyDown(KEY_D))
            {
                jogador.dx = 0;
                jogador.dy = 1;
                
                if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
                {
                    if (isPortal(mapa, jogador))
                    {
                        CloseWindow();
                    }
                    move(&jogador);
                    atualizarMapaJogador(mapa, jogador);
                }
            }
            else if (IsKeyDown(KEY_A))
            {
                jogador.dx = 0;
                jogador.dy = -1;

                if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
                {
                    if (isPortal(mapa, jogador))
                    {
                        CloseWindow();
                    }
                    move(&jogador);
                    atualizarMapaJogador(mapa, jogador);
                }
            }

            if (IsKeyDown(KEY_S))
            {
                jogador.dy = 0;
                jogador.dx = 1;

                if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
                {
                    if (isPortal(mapa, jogador))
                    {
                        CloseWindow();
                    }
                    move(&jogador);
                    atualizarMapaJogador(mapa, jogador);
                }
            }
            else if (IsKeyDown(KEY_W))
            {
                jogador.dy = 0;
                jogador.dx = -1;

                if (deveMover(&jogador, MAPA_LINHA, MAPA_COLUNA, mapa))
                {
                    if (isPortal(mapa, jogador))
                    {
                        CloseWindow();
                    }
                    move(&jogador);
                    atualizarMapaJogador(mapa, jogador);
                }
            }
            // print the TempoJogando
            // printf("segundos: %d\n", segundos);
            
            

            if (frame_counter >= enemy_update_freq)  // !!!!!!!! NAO SEI OQ ISSO AQUI FAZ
            {

                frame_counter = 0;
            }
        }

        if(IsKeyDown(KEY_UP)){
            if(canShoot(mapa, jogador, UP)){
                mapa[jogador.matrixPositionX - 1][jogador.matrixPositionY] = 'U';
            }
        }
        if(IsKeyDown(KEY_DOWN)){
            if(canShoot(mapa, jogador, DOWN)){
                mapa[jogador.matrixPositionX + 1][jogador.matrixPositionY] = 'D';
            }
        }
        if(IsKeyDown(KEY_LEFT)){
            if(canShoot(mapa, jogador, LEFT)){
                mapa[jogador.matrixPositionX][jogador.matrixPositionY - 1] = 'L';
            }
        }
        if(IsKeyDown(KEY_RIGHT)){
            if(canShoot(mapa, jogador, RIGHT)){
                mapa[jogador.matrixPositionX][jogador.matrixPositionY + 1] = 'R';
            }
        }

        if (segundos % enemy_update_freq == 0) // MOVIMENTA O INIMIGO
            {
                if (lastUpdate != segundos)
                {
                    for (int i = 0; i < num_inimigos; i++)
                    {
                        if (inimigos[i].vivo == 1)
                        {
                            if(moveInimigo(&inimigos[i], MAPA_LINHA, ALTURA, mapa))
                                atualizarMapaInimigo(mapa, inimigos[i]);
                        }
                    }
                    lastUpdate = segundos;
                    printf("segundos: %d\n", segundos);
                }
                // printMap(mapa);
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


// Atualiza a representac�o visual a partir do estado do jogo


// Move o quadrado roxo ap�s verificar todas as colis�es
        // if (deveMover(&jogador, LARGURA, ALTURA, mapa))
        // {
        //     move(&jogador);
        // }

//DrawText(texto, 400, 300, 40, YELLOW);//Desenha um texto, com posicao, tamanho e cor
// Calcula as coordenadas para o ret�ngulo e o texto


        DrawRectangle(jogador.x, jogador.y, 20, 20, VIOLET);
                DrawMenu(currentOption);
        atualizarMapaGrafico(mapa,jogador);
        DrawRectangle(LARGURA - 80, ALTURA - 40, 70, 30, WHITE); // Parte de tr�s do rel�gio
        DrawText(tempoTexto, LARGURA - 75, ALTURA - 35, 20, RED); // Rel�gio

        DrawText("Vidas:", LARGURA - 780, ALTURA - 40, 20, BLACK);
        DrawText(TextFormat("%d", vidas), LARGURA - 720, ALTURA - 40, 20, RED);




        EndDrawing();//Finaliza o ambiente de desenho na tela

    }
      
    }
    if (currentOption == MENU_EXIT)
                {
                    CloseWindow();  // Fecha a janela do jogo.
                }
                enterPressed = 0;  // Redefine enterPressed para 0 ap�s o processamento da sele��o.
    }
    }// Fim do loop do menu


    return 0;

}
