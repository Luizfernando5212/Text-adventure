//Text Adventure
/*  O Jogo conta a história de um herói que vive em uma vila pequena ao norte de seu país
    Apesar desta vila ser pequena, ela possui um grande segredo, um tesouro desejado por muitos reinos
    Um segredo confiado apenas aos guardiões daquela era.
    	Certo dia um grupo de saqueadores invadem a vila, por coincidência, um dia em que o herói não se encontrava na cidade
    Ao confrontarem um dos guardiões a respeito dos tesouros da vila, como estratégia o guardião apontou 
    um baú com tesouros menos valiosos. Porém, um dos saqueadores desconfiava que estava fácil de mais e que podia haver um tesouro maior ainda escondido
	logo ameaçou oo guardião, que com um pouco de tempo cedeu a informação da localização do segredo.
	Após coletarem tamanha jóia, foram embora da vila e acabaram encontrando com o herói na saída do vilarejo,
	como ele não sabia de nada, deixou-os irem embora com o tesouro mais precisoso.
		Ao entrar na vila, notou que algo havia acontecido e foi logo ao encontro dos guardiões, que o informaram do acontecido
	a partir daí, começa a saga do herói em busca desse misterioso tesouro.*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

//Variáveis globais
FILE *intro;
char text[];
char C;
int i = 0;
int c, d;

//Protótipos de funções
void getch(void);

int main ()
{
	setlocale (LC_ALL, "");
	intro = fopen ("Intro.txt", "r");
	if (intro == NULL)
	{
		printf ("Problemas na abertura de arquivo.\n");	
		return 0;
	}
	C = fgetc(intro);
	while (!feof(intro))
  {
    text[i] = C;
	  printf("%c", text[i]);
    i++;
    C = fgetc(intro);
  //  usleep(10000);
  //  msleep(500);
  //  getch();
  //  fflush(stdin);
    }
	fclose(intro);
	getch();
	return 0;
}



void getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
   // printf("%c\n", buf);
    //return buf;
 }

