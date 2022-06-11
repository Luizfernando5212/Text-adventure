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
#define LEN_TEXT 500
#define LEN_NICK 25

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <string.h>

//Variáveis globais
FILE *intro, *jogadores, *Load, *Novo_Load, *Novo_jogadores;
char text[LEN_TEXT];
char nick[LEN_NICK] = "ingrid\n";
char *result;
char C;
int i = 0;
int a, b, dado;

//Protótipos de funções
void getch(void);
int sorte(int num);
void introduction();
void createc(char *nome);
void load();
void save(char *fase);
void Delete_player();
void phase1();
void phase2();
void phase3();

int main ()
{
	setlocale (LC_ALL, "");
 // Delete_player();
  //load();
	//introduction();
  //createc(nick);
  save("fase4\n");
/*  int sorte1;
  dado = sorte(a);
  printf("%i\n", dado);*/
 
	//getch();
	return 0;
}


int sorte(int num)
{
  srand(time(NULL));
  num = rand()%20;
  //printf ("%i", num);
  return num;
}

void introduction()
{
  intro = fopen ("Intro.txt", "r");
	if (intro == NULL)
	{
		printf ("Problemas na abertura de arquivo.\n");	
	}

	C = fgetc(intro);
	while (!feof(intro))
  {
    text[i] = C;
	  printf("%c", C);
    i++;
    C = fgetc(intro);
  // usleep(10000);
  //  msleep(500);
  //  getch();
  //  fflush(stdin);
    }
  //printf("\n%s", text);
	fclose(intro);
  }

void createc(char *nome)
{
  int ver = 0; // Verificador, para adicionar nick se não existe
  jogadores = fopen ("jogadores.txt", "a+");
  if (jogadores == NULL)
  {
    printf ("Problemas na abertura de arquivo.\n");
  }
  else
  {
    seunick:
    printf("Digite seu nick: ");
    fgets(nome, LEN_NICK, stdin);
    while(!feof(jogadores))
      {
        fgets(text, LEN_NICK, jogadores);
        if (strcmp(nome, text) == 0)
        {
          printf("nick já existe, tente outro\n");
          rewind(jogadores);
          goto seunick;
        }
      }
      fputs(nome, jogadores);
  }
  printf("O nome digitado foi: %s", nome);
  fclose(jogadores);
}

void load()
{
  int ver = 0; // verificador para saber se foi encontrado o nick no arquivo de Load
  printf("Digite seu nick: ");
  fgets(nick, LEN_NICK, stdin);
  Load = fopen("Load.txt", "a+");
  // Passo pelas linhas do arquivo
  while(!feof(Load))
    {
      fgets(text, LEN_NICK, Load);
      // Se o nick é encontrado verificador soma 1
      if (strcmp(nick, text) == 0)
      {
        ver++;
        //pego a próxima linha que necessariamente indica a fase em que o jogador está.
        fgets(text, LEN_NICK, Load);
        // Esse if manda o jogador para a fase em que ele estava.
        if(strcmp(text, "fase1\n") == 0)
        {
          phase1();
        }
        else if (strcmp(text, "fase2\n") == 0)
        {
          phase2();
        }
      }
    }
  if(ver == 0)
  {
    printf("Nick não encontrado, tente novamente.\n");
    rewind(Load);
    fclose(Load);
    load();
  }
  fclose(Load);
}

void save(char *fase)
{
  int ver = 0;
  Load = fopen("Load.txt", "r");
  Novo_Load = fopen("transf.txt", "w");
  while (!feof(Load))
    {
      fgets(text, LEN_TEXT, Load);
      if (strcmp(nick, text) != 0)
      {
        fputs(text, Novo_Load);
      }
      else
      {
        fputs(text, Novo_Load);
        fputs(fase, Novo_Load);
        fgets(text, LEN_TEXT, Load);
      }
    }
  remove("Load.txt");
  rename("transf.txt", "Load.txt");
  fclose(Load);
  fclose(Novo_Load);
}

void Delete_player()
{
  int pos = 1, fase_line, ver = 1;
  // pos se refere a linha do arquivo
  // fase-line se refere a linha da fase no arquivo
  // verifica  server para impedir que o segundo while rode mais de uma 
  // vez
  printf ("Digite seu nick: ");
  fgets(nick, LEN_NICK, stdin);

  // Abrindo os arquivos da onde o jogador será retirado
  Load = fopen("Load.txt", "r");
  Novo_Load = fopen("transfere.txt", "w");
  jogadores = fopen("jogadores.txt", "r");
  Novo_jogadores = fopen("transf.txt", "w");

  // laço que copia os nicks diferentes do que deseja ser excluído de Load para um novo arquivo
  while (!feof(Load))
  {
    if(ver == 1)
    {
      while(!feof(Load))
        {
          fgets(text, LEN_NICK, Load);
          if(strcmp(nick, text) == 0)
          {
            fase_line = pos;
            pos = 1;
            rewind(Load);
            ver ++;
            break;
          }
          pos ++;
        }
    }
    fgets(text, LEN_NICK, Load);
    if(strcmp(nick, text) != 0)
    {
      if(pos != (fase_line + 1))
      {fputs(text, Novo_Load);}
    }
  pos ++;
  }
  // laço que copia os nicks diferentes do que deseja ser excluído de jogadores para um novo arquivo
  while (!feof(jogadores))
  {
    fgets(text, LEN_NICK, jogadores);
    if(strcmp(nick, text) != 0)
    {
      fputs(text, Novo_jogadores);
    }
  }
  // Nesssa sessão apago os arquios anteriores e renomeio os novos para o mesmo nome
  remove("Load.txt");
  rename("transfere.txt", "Load.txt");
  remove("jogadores.txt");
  rename("transf.txt", "jogadores.txt");
  fclose(Load);
  fclose(Novo_Load);
  fclose(jogadores);
  fclose(Novo_jogadores);
}

void phase1()
{
  printf("Fase 1");
}

void phase2()
{
  printf("Fase 2");
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
 }


