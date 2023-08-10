# jogo_algprog

Oi.... Precisamos fazer o Jogo.
Requisitos mínimos:
• Os elementos visuais do jogo devem ser implementados e exibidos em modo texto (atraves de caracteres).\n
• O jogo nao deve ter delay, ou seja, ao ser disparada uma acao do jogador, o jogo deve responder imediatamente
(exceto quando o delay é deliberado). Por exemplo: se o jogador movimentar o personagem para direita, ele
deve imediatamente ir para a direita, se o jogador atacar, o personagem deve realizar o ataque, etc.
• O mapa do jogo deverá ser carregado a partir de um arquivo texto nomeado “mapa<n´umero>.txt” (“mapa1.txt”,
“mapa2.txt”, “mapa3.txt”, etc.), onde o valor num´erico indica a fase correspondente ao mapa.
• Cada mapa deve ser estruturado como uma matriz de caracteres de 30 linhas por 60 colunas. O mapa deve ser
fechado (isto é, cercado de paredes)
# itens do jogo devem ser representados no arquivo do mapa com os seguintes caracteres:
Caractere Significado
J Posicao inicial do personagem
I Inimigo
B Bomba coletavel
P Portal para pr´oxima fase
"#" Parede
Espaco em branco Area de transito (posicao vazia)
X Fogueira (armadilha)

Tecla Significado
ESC Acessa o menu superior e espera o jogador escolher uma opc¸˜ao
Teclas (A/a, D/d, S/s, W/w)
Move o jogador uma posicao na direcao indicada
Setas (←, →, ↓ e ↑) Atira com o personagem na direcao indicada
E Posiciona uma bomba no mapa
R Recomeca o jogo
ersonagem e inimigos nao devem atravessar bombas ou paredes.
• O mapa de cada fase tera no maximo 15 inimigos (o n ´umero pode variar conforme a fase), podendo ter qualquer
n´umero de areas de transito, bombas, fogueiras e paredes.
• Cada mapa devera ter apenas uma posicao inicial do personagem e um portal para a pr ´oxima fase (ou fim de
jogo).
• Ha diferentes tipos de inimigos no jogo (https://bindingofisaac.fandom.com/wiki/The_Binding_of_Isaac_
Wiki), cada um com seu proprio padrao de movimento e ataques. Implemente ao menos um deles. Dica: escolha
monstros mais simples, como o Gaper ou o Pooter.
• Se o personagem entrar em contato com uma fogueira ou com um inimigo (sem chorar ou lan c¸ar uma bomba), e o
jogador possuir vidas extras, a quantidade de vidas do jogador é decrementada. Caso o jogador nao possua vidas
extras, o jogo termina (game over) em derrota. Quando um inimigo ´e atingido por um golpe, ele e eliminado.
• Os inimigos nao devem ser capazes de passar pelas paredes, mas podem passar, sem danos, por fogueiras.
• Alem do mapa da fase corrente, o jogo deve exibir a fase atual (1, 2, etc.), o tempo decorrido desde in´ıcio do
jogo e a quantidade de vidas do personagem.
• A pontuacao do jogador e determinada em funcao do tempo que ele leva para atingir o fim do jogo (concluir a
ultima fase). A pontuacao nao fica negativa (ela satura em zero).
• O programa deve ser capaz de funcionar com qualquer numero de fases (ate o maximo de 99). Por exemplo, se
forem incluıdos 99 arquivos de mapa disponıveis para o jogo (seguindo a ordem numerica), seu programa deve
ser capaz de possibilitar que o jogador avance pelas 99 fases. O jogo deve ser entregue com pelo menos 5 fases.
• O menu (exibido sobre a tela do jogo, no cabecalho ou rodape da tela) deve ser navegavel com o pressionar de
teclas possuir as seguintes opcoes:
