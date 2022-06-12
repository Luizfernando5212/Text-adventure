// Text Adventure
/*  O Jogo conta a história de um herói que vive em uma vila pequena ao norte de seu país, logo na base de uma montanha, apesar desta vila ser pequena, ela possui um grande segredo, um tesouro desejado por muitos reinos Um segredo confiado apenas aos guardiões
   daquela era. Certo dia um grupo de saqueadores invadem a vila, por
   coincidência, um dia em que o herói não se encontrava na cidade Ao
   confrontarem um dos guardiões a respeito dos tesouros da vila, como
   estratégia o guardião apontou um baú com tesouros menos valiosos. Porém, um
   dos saqueadores desconfiava que estava fácil de mais e que podia haver um
   tesouro maior ainda escondido logo ameaçou oo guardião, que com um pouco de
   tempo cedeu a informação da localização do segredo. Após coletarem tamanha
   jóia, foram embora da vila e acabaram encontrando com o herói na saída do
   vilarejo, como ele não sabia de nada, deixou-os irem embora com o tesouro
   mais precisoso. Ao entrar na vila, notou que algo havia acontecido e foi logo
   ao encontro dos guardiões, que o informaram do acontecido a partir daí,
   começa a saga do herói em busca desse misterioso tesouro.*/
#define LEN_TEXT 500
#define LEN_NICK 25
#define LEN_ANS 20
#define LEN_EQP 17
#define LEN_H 5
#define LEN_A 20

// Bibliotecas
#include <locale.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

// Variáveis globais
FILE *first, *intro, *jogadores, *Load, *Novo_Load, *Novo_jogadores;
FILE *pausar, *phase[6], *banco, *alt, *choice, *pt2s, *pt2n, *eqp;
FILE *tut;
char text[LEN_TEXT];
char nick[LEN_NICK];
char answer[LEN_ANS];
char player[LEN_NICK];
char equipment[LEN_EQP] = "arco";
char arm[LEN_A];
char *result;
int i = 0;
int a, b;
int Dadoi = 0, Dadoj = 0;
int vida = 3;
char teste;
int horas = 0;
char horass[LEN_H];
int tempo;

// Protótipos de funções
void texto(char caminho[LEN_TEXT], char fase[]);
char getch(void);
char* itoa(int num, char* buffer, int base);
int sorte(int num);
void first_screen();
void introduction();
void tutorial();
void createc();
void load();
void save(char *fase);
void Delete_player();
void phase1();
void phase2();
void phase3();
void phase4();
void phase5();
void fim();
void alternative();
int stop(char fase[], FILE *arquivo);
int donut();
char escolha();
char *checar(char *arquivo);
void bancof2();

int main() 
{
  setlocale(LC_ALL, "");
  // Delete_player();
  //load();
  //introduction();
  //createc();
  /*int  car = 10490;
  printf("%d", car);
  car = car / 70;
  printf("\n%d",car);*/
  //save("fase4\n");
  /*  int sorte1;
    dado = sorte(a);
    printf("%i\n", dado);*/
  //phase5();
  //phase3();
  //tutorial();
  first_screen();
  
  return 0;
}

int sorte(int num) 
{
  srand(time(NULL));
  num = rand() % num;
  // printf ("%i", num);
  return num;
}

void first_screen()
{
  char C;
  lay:
  system("clear");
  //Sessão imprime o layout na tela
  first = fopen("Layouts/layout.txt", "r");
  while (!feof(first))
    {
      fgets(text, LEN_TEXT, first);
      printf("%s", text);
    }
  inicio:
  C = getch();
  if (C == 'n' || C == 'N') //Se "n" - New game, e leva para intro do jogo 
  {
    if(strcmp(nick,"\0") == 0)
    {
      system("clear");
      printf("Crie seu nick primeiro.");
      getch();
      system("clear");
      rewind(first);
      goto lay;
    }
    else
    {
      system("clear");
      introduction();
    }
    
    
  }
    else if (C == 'l' || C == 'L') //Se "l" leva para opção de Load game.
    {
      system("clear");
      load();
    }
      else if (C == 't' || C == 'T')
      {
        system("clear");
        tutorial();
        rewind(first);
        goto lay;
      }
        else if(C == 'c' || C == 'C')
        {
          system("clear");
          createc();
          rewind(first);
          goto lay;
        }
  else goto inicio;
}

void tutorial()
{
  char C;
  int i;
  tut = fopen("História/Tutorial/Tutorial.txt", "r");
  choice = fopen("Layouts/escolhas.txt", "r");
  t2:
  fgets(text, LEN_TEXT, tut);
  printf("%s", text);
  Q1:
  while(!feof(choice))
    {
      fgets(text, LEN_TEXT, choice);
      printf("%s", text);
    }
  C = getch();
  if (C == '1')
  {
    printf("\nMuito bem!\n");
    fgets(text, LEN_TEXT, tut);
    getch();
    system("clear");
    goto Q2;
  }
  else if (C == '2')
  {
    printf("\nNão entendeu ? Tente novamente para entender\n");
    getch();
    rewind(tut);
    rewind(choice);
    system("clear");
    goto t2;
  }
  else
  {
     system("clear");
    rewind(choice);
    goto Q1;
  }
  Q2:
  for(i = 1; i < 4; i++)
    {
      fgets(text, LEN_TEXT, tut);
      printf("%s", text);
    }
  fgets(answer, LEN_ANS, stdin);
  banco = fopen("Banco/afirmar.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(text, answer) == 0)
       {
          printf("\nMuito bem!\n");
         getch();
         system("clear");
         goto Q3;
       }
    }
  fclose(banco);
  banco = fopen("Banco/negar.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(text, answer) == 0)
      {
        printf("\nNão entendeu ? Tente novamente!\n");
        getch();
        system ("clear");
        rewind(tut);
        fgets(text, LEN_TEXT, tut);
        fgets(text, LEN_TEXT, tut);
        goto Q2;
        fclose(banco);
      }
    }
  if(feof(banco))
  {
    printf("\nResposta inválida");
    getch();
    system ("clear");
    rewind(tut);
    fgets(text, LEN_TEXT, tut);
    fgets(text, LEN_TEXT, tut);
    goto Q2;
  }
  fclose(banco);
  Q3:
  fgets(text, LEN_TEXT, tut);
  printf("%s", text);
  getch();
  fgets(text, LEN_TEXT, tut);
  printf("%s", text);
  getch();
  while(Dadoi == 0)
    {
      Dadoi = sorte(6);    
    }
  fgets(text, LEN_TEXT, tut);
  printf("%s", text);
  getch();
  printf("%i\n", Dadoi);
  while(Dadoj == 0)
    {
      Dadoj = sorte(20);
    }
  fgets(text, LEN_TEXT, tut);
  printf("%s", text);
  getch();
  printf("%i", Dadoj);

  if (Dadoj >= 2 * Dadoi)
  {
    printf("\nParabéns, você ganhou!!");
  }
  else printf("\nNão foi dessa vez, mas talvez numa próxima.");
  getch();
  system("clear");
  while(!feof(tut))
  {
    fgets(text, LEN_TEXT, tut);
    printf("%s", text);
  }
  getch();
  fclose(tut);
  fclose(choice);
  return;
}

void introduction() 
{
  texto("História/Intro.txt", "intro\n");
  system("clear");
  phase1();
  fclose(intro);
}

void createc() 
{
  int ver = 0; // Verificador, para adicionar nick se não existe
  jogadores = fopen("Armazenamento/jogadores.txt", "a+");
  if (jogadores == NULL) 
  {
    printf("Problemas na abertura de arquivo.\n");
  } else {
  //Recebe nick
  seunick:
    printf("Digite seu nick: ");
    fgets(nick, LEN_NICK, stdin);
    while (!feof(jogadores)) 
    {
      //Verifica se o nick ja existe no arquivo
      fgets(arm, LEN_A, jogadores);
      if (strcmp(nick, arm) == 0) {
        printf("nick já existe, tente outro\n");
        rewind(jogadores);
        system("clear");
        goto seunick;
      }
    }
    //Se existe, insere o nick no arquivo
    fputs(nick, jogadores);
  }
  printf("O nome digitado foi: %s", nick);
  //Transfere o nick para a varável jogador sem \n
  while(nick[ver] != '\n')
    {
      player[ver] = nick[ver];
      ver++;
    }
  fclose(jogadores);
  return;
}

void load() 
{
  int ver = 0, i = 0; // verificador para saber se foi encontrado o nick no arquivo de Load
  printf("Digite seu nick: ");
  fgets(nick, LEN_NICK, stdin);
  while(nick[i] != '\n')
    {
      player[i] = nick[i];
      i++;
    }
  Load = fopen("Armazenamento/Load.txt", "a+");
  // Passo pelas linhas do arquivo
  while (!feof(Load)) {
    fgets(arm, LEN_A, Load);
    // Se o nick é encontrado verificador soma 1
    if (strcmp(nick, arm) == 0) 
    {
      ver++;
      // pego a próxima linha que necessariamente indica a fase em que o jogador está.
      fgets(arm, LEN_A, Load);
      // Esse if manda o jogador para a fase em que ele estava.
     // printf("%s %s", nick, arm);
      if(strcmp(arm, "intro\n") == 0)
      {
        fgets(horass, LEN_H, Load);
        fgets(equipment, LEN_EQP, Load);
        horas = atoi(horass);
        system("clear");
        introduction();
      }
      else if (strcmp(arm, "fase1\n") == 0) 
      {
        fgets(horass, LEN_H, Load);
        horas = atoi(horass);
        fgets(equipment, LEN_EQP,Load);
        system("clear");
        phase1();
      } 
      else if (strcmp(arm, "fase2\n") == 0) 
      {
        fgets(horass, LEN_H, Load);
        horas = atoi(horass);
        fgets(equipment, LEN_EQP,Load);
        system("clear");
        phase2();
      }
      else if (strcmp(arm, "fase4\n") == 0)
      {
        fgets(horass, LEN_H, Load);
        horas = atoi(horass);
        fgets(equipment, LEN_EQP, Load);
        system("clear");
        phase4();
      }
    }
  }
  if (ver == 0) 
  {
    printf("Nick não encontrado, tente novamente.\n");
    getch();
    rewind(Load);
    fclose(Load);
    load();
  }
  fclose(Load);
  exit(0);
}

void save(char fase[]) 
{
  int ver = 0;
  Load = fopen("Armazenamento/Load.txt", "r");
  Novo_Load = fopen("Armazenamento/transf.txt", "w");
  itoa(horas, horass, 10);

  while (!feof(Load)) 
  {
    //Verifica os nomes no arquivo, caso não exista insere nome e fase
    fgets(arm, LEN_A, Load);
    if (strcmp(nick, arm) != 0) 
    {
      fputs(arm, Novo_Load);
    } 
    else 
    {
      fputs(nick, Novo_Load);
      fputs(fase, Novo_Load);
      fputs(horass, Novo_Load);
      putc('\n', Novo_Load);
      fputs(equipment, Novo_Load);
      fgets(arm, LEN_A, Load);
      fgets(arm, LEN_A, Load);
      fgets(arm, LEN_A, Load);
      ver++;
    }
  }
  if (ver == 0) 
  {
    fputs(nick, Novo_Load);
    fputs(fase, Novo_Load);
    fputs(horass, Novo_Load);
    fputc('\n', Novo_Load);
    fputs(equipment, Novo_Load);
    fputc('\n', Novo_Load);
    fputc('\n', Novo_Load);
    }
  remove("Armazenamento/Load.txt");
  rename("Armazenamento/transf.txt", "Armazenamento/Load.txt");
  fclose(Load);
  fclose(Novo_Load);
}

int stop(char fase[], FILE *arquivo) 
{
  char c;
  pausar = fopen("Layouts/pause.txt", "r");
  if (getch() == '9')
  {
    system("clear");
    rewind(arquivo);
    while (!feof(pausar))
      {
        fgets(text, LEN_TEXT, pausar);
        printf("%s", text);
      }
    fclose(pausar);
    inicio:
    c = getch();
    if (c == 'p' || c == 'P')
    {   
      system("clear");
      return 'p';
    }
      else if(c == 's' || c == 'S')
      {
        system("clear");
        save(fase);
      }
    else goto inicio;
  }
  return 1;
}

void Delete_player() 
{
  int pos = 1, fase_line, ver = 1;
  // pos se refere a linha do arquivo
  // fase-line se refere a linha da fase no arquivo
  // verifica  server para impedir que o segundo while rode mais de uma
  // vez
  printf("Digite seu nick: ");
  fgets(nick, LEN_NICK, stdin);

  // Abrindo os arquivos da onde o jogador será retirado
  Load = fopen("Armazenamento/Load.txt", "r");
  Novo_Load = fopen("Armazenamento/transfere.txt", "w");
  jogadores = fopen("Armazenamento/jogadores.txt", "r");
  Novo_jogadores = fopen("Armazenamento/transf.txt", "w");

  // laço que copia os nicks diferentes do que deseja ser excluído de Load para
  // um novo arquivo
  while (!feof(Load)) 
  {
    if (ver == 1) 
    {
      while (!feof(Load)) {
        fgets(text, LEN_NICK, Load);
        if (strcmp(nick, text) == 0) {
          fase_line = pos;
          pos = 1;
          rewind(Load);
          ver++;
          break;
        }
        pos++;
      }
    }
    fgets(text, LEN_NICK, Load);
    if (strcmp(nick, text) != 0) {
      if (pos != (fase_line + 1)) {
        fputs(text, Novo_Load);
      }
    }
    pos++;
  }
  // laço que copia os nicks diferentes do que deseja ser excluído de jogadores
  // para um novo arquivo
  while (!feof(jogadores)) 
  {
    fgets(text, LEN_NICK, jogadores);
    if (strcmp(nick, text) != 0) 
    {
      fputs(text, Novo_jogadores);
    }
  }
  // Nesssa sessão apago os arquios anteriores e renomeio os novos para o mesmo
  // nome
  remove("Armazenamento/Load.txt");
  rename("Armazenamento/transfere.txt", "Armazenamento/Load.txt");
  remove("Armazenamento/jogadores.txt");
  rename("Armazenamento/transf.txt", "Armazenamento/jogadores.txt");
  fclose(Load);
  fclose(Novo_Load);
  fclose(jogadores);
  fclose(Novo_jogadores);
}

void phase1() 
{ 
  int cont = 0, i;
  char esc;
  i = 1;
  
  phase[0] = fopen("História/fase1/parte1.txt", "r");
  
  fgets(text, LEN_TEXT, phase[0]);
  printf("%s", text);
  stop("fase1\n", phase[0]);
  system("clear");
  while (!feof(phase[0]))
    {
       i++;
      fgets(text, LEN_TEXT, phase[0]);
      printf("%s", text);
      stop("fase1\n", phase[0]);
      if (i == 4)
      {
        printf("%s", player);
      }
    }
  fclose(phase[0]);
  phase[0] = fopen("História/fase1/parte2-2.txt", "r");
  question:
  pt2s = fopen("Layouts/equipamentos.txt", "r");
  /*if (strcmp(answer, "\0") != 0)
  {
    printf("- Gostaria de escolher seu equipamento ?");
  }*/
  printf("\nDigite: ");
  fgets(answer, LEN_ANS, stdin);
  system("clear");
  banco = fopen("Banco/afirmar.txt", "r");
  eqp = fopen("Armazenamento/equipamentos.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(text, answer) == 0)
      {
        fclose(banco);
        selecione:
        esc = '\0';
        while(!feof(pt2s))
          {
            fgets(text, LEN_TEXT, pt2s);
            printf("%s", text);
          }
        esc = getch();
        switch(esc)
          {
            case '1': 
              fgets(equipment, LEN_EQP, eqp);
              save("fase2\n");
              system("clear");
              goto end1;
              break;
            case '2':
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              save("fase2\n");
              fclose(eqp);
              system("clear");
              goto end1;
              break;
            case '3': 
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              system("clear");
              save("fase2\n"); 
              fclose(eqp);
              goto end1;
              break;
            case '4': 
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              fgets(equipment, LEN_EQP, eqp);
              system("clear");
              save("fase2\n"); 
              fclose(eqp);
              goto end1;
              break;
            default: 
              printf("\nResposta inválida");
              getch();
              system("clear");
              rewind(pt2s);
              goto selecione;
              break;
          }
         // phase2();
        return;
        }
    }
  fclose(banco);
  
  banco = fopen("Banco/negar.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(text, answer) == 0)
      {
        fclose(banco);
        for(i = 1; i <=4 ; i++)
          {
            fgets(equipment, LEN_EQP, eqp);
          }
        fgets(equipment, LEN_EQP, eqp);
        fclose(eqp);
        goto end2;
      }
    }
  fclose(banco);
  
  banco = fopen("Banco/procurar.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(text, answer) == 0)
      {
        inicio2:
        if (cont == 4)
        {
          printf("\n");
          if (escolha() == '1')
          {  
            alternative();
            return;
          }
          else
          {
            goto question;
          } 
        }
      for(i = 1; i <= 2; i++)
        {
          fgets(text, LEN_TEXT, phase[0]);
          printf("%s", text);
        }
        fclose(banco);
        getch();
        cont++;
        if (cont == 4) goto inicio2;
        system("clear");
        goto question;
      }
    }
  if (feof(banco))
      {
        printf("Resposta inválida.");
        getch();
        system("clear");
        fclose(banco);
        goto question;
      }
  
  end1:
  printf("%s", equipment);
  texto("História/fase1/parte2-s.txt", "fase2\n");
  //fclose(phase[0]);
  phase2();
  return;
  
  end2:
  texto("História/fase1/parte2-n.txt", "fase2\n");
  //fclose(phase[0]);
  phase2();
  return;
}

void phase2() 
{ 
  Dadoi = 0; Dadoj = 0;
  char C, *ver;
  setbuf(stdin, 0);
  system("clear");

  if (strcmp(equipment, "Magia\n") == 0)
  {
    system("clear");
    texto("História/fase2/parte1.txt", "fase2\n");
    system("clear");
    texto("História/fase2/parte2m.txt", "fase3\n");
    horas += 6;
    phase3();
    return;
  }
  texto("História/fase2/parte1.txt", "fase2\n");
  system("clear");
  phase[1] = fopen("História/fase2/parte2.txt", "r");
  get:
  for(i = 1; i <= 11; i++)
    {
      fgets(text, LEN_TEXT, phase[1]);
      printf("%s", text);
      stop("fase2\n", phase[1]);
    }
  
  printf("Opção: ");
  C = fgetc(stdin);
  system("clear");
  switch(C)
    {
      case '1': 
        fgets(text, LEN_TEXT, phase[1]); 
        printf("%s", text);
        while(Dadoi == 0) 
          {Dadoi = sorte(6);}
        while(Dadoj == 0)
          {Dadoj = sorte(20);}
        printf("\nResultado do inimigo: ");
        getch();
        printf("%i", Dadoi);
        getch();
        printf("\nSeu resultado: ");
        getch();
        printf("%i", Dadoj);
        fclose(phase[1]);
        getch();
        system("clear"); 
        goto p21;
        break;
      case '2': 
        fgets(text, LEN_TEXT, phase[1]); 
        fgets(text, LEN_TEXT, phase[1]);
        printf("%s", text);
        while(Dadoi == 0) 
          {Dadoi = sorte(6);}
        while(Dadoj == 0)
          {Dadoj = sorte(20);}
        printf("\nResultado do inimigo: ");
        getch();
        printf("%i", Dadoi);
        getch();
        printf("\nJogar dado: ");
        getch();
        printf("%i", Dadoj);
        fclose(phase[1]);
        getch();
        system("clear"); 
        goto p22;
        break;
      case '3':
        fgets(text, LEN_TEXT, phase[1]); 
        fgets(text, LEN_TEXT, phase[1]);
        fgets(text, LEN_TEXT, phase[1]);
        printf("%s", text);
        while(Dadoi == 0) 
          {Dadoi = sorte(6);}
        while(Dadoj == 0)
          {Dadoj = sorte(20);}
        printf("\nResultado do inimigo: ");
        getch();
        printf("%i", Dadoi);
        getch();
        printf("\nJogar dado: ");
        getch();
        printf("%i", Dadoj);
        fclose(phase[1]);
        getch();
        system("clear"); 
        goto p23;
        break;
      default: 
        system("clear");
        rewind(phase[1]); goto get; break;
    }
  p21:
  phase[1] = fopen("História/fase2/parte2-1.txt", "r");
  if (Dadoj >= 2 * Dadoi)
  {
    horas += 9;
    for (i = 1; i <= 9; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
        stop("fase2\n", phase[1]);
        printf("%s", text);
      }
    fclose(phase[1]);
    phase3();
    return;
  }  
  else if ((Dadoj > Dadoi) && (Dadoj < 2 * Dadoi))
  {
    horas += 11;
    for (i = 1; i <= 9; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
      }
    for (i = 1; i <= 7; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
        stop("fase2\n", phase[1]);
        printf("%s", text);
      }
    fclose(phase[1]);
    phase3();
    return;
  }
  else
  {
    horas += 13;
    for (i = 1; i <= 18; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
      }
    //texto()
    while(!feof(phase[1]))
    {
      fgets(text, LEN_TEXT, phase[1]);
      printf("%s", text);
      stop("fase2\n", phase[1]);
    }
    fclose(phase[1]);
    phase3();
    return;
  }

  p22:
  phase[1] = fopen("História/fase2/parte2-2.txt", "r");
  if (Dadoj >= 2 * Dadoi)
  {
    horas += 7;
    for (i = 1; i <= 9; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
        printf("%s", text);
        stop("fase2\n", phase[1]);
      }
    fclose(phase[1]);
    phase3();
    return;
  }
  else
  {
    horas += 13;
    for (i = 1; i <= 9; i++)
      {
        fgets(text, LEN_TEXT, phase[1]);
      }
    fgets(text, LEN_TEXT, phase[1]);
    printf("%s\n", text);
    stop("fase2\n", phase[1]);
    phase3();
    return;
  }
  p23:
  phase[1] = fopen("História/fase2/parte2-3.txt", "r");
  if (Dadoj >= 2 * Dadoi)
  {
    horas += 9;
    fgets(text, LEN_TEXT, phase[1]);
    printf("%s", text);
    stop("fase2\n", phase[1]);
    fclose(phase[1]);
    phase3();
    return;
  }
  else
  {
    horas += 13;
    fgets(text, LEN_TEXT, phase[1]);
    fgets(text, LEN_TEXT, phase[1]);
    fgets(text, LEN_TEXT, phase[1]);
    printf("%s\n", text);
    stop("fase2\n", phase[1]);
    phase3();
    return;
  }
}

void phase3()
{
  char C;
  system("clear");
  if(strcmp(equipment, "Magia\n") == 0)
  {
    texto("História/fase3/parte1m.txt", "fase3\n");
    horas += 1;
    phase4();
    return;
  }
  
  phase[2] = fopen("História/fase3/parte1.txt", "r");
  texto("História/fase3/parte1.txt", "fase3\n");
  fclose(phase[2]);
  
  phase[2] = fopen("História/fase3/parte2.txt", "r");
  system("clear");
  while(!feof(phase[2]))
    {
      C = fgetc(phase[2]);
      if(stop("fase3\n", phase[2]) == 'p')
      goto fim;
      printf("%c", C);
      tempo ++;
    }
  
  while(stop("fase3\n", phase[2]) != 'p')
    stop("fase4\n", phase[2]);
  fim:
  horas = horas + tempo/70;
  getch();
  phase4();
}

void phase4()
{
  setbuf(stdin, 0);
  int Dadoi = 0; Dadoj = 0;
  int i = 1;
  int num;
  phase[3] = fopen("História/fase4/parte1.txt", "r");
  questão:
  system("clear");
  if(strcmp(equipment, "Magia\n") == 0)
  {
    fgets(text, LEN_TEXT, phase[3]);
    fgets(text, LEN_TEXT, phase[3]);
    while(!feof(phase[3]))
      {
        fgets(text, LEN_TEXT, phase[3]);
        printf("%s", text);
        stop("fase4\n", phase[3]);
      }
    goto Q;
  }
  texto("História/fase4/parte1.txt", "fase4\n");
 Q:
do
  fgets(answer, LEN_A, stdin);
while(strcmp(answer, "\n") == 0);//if (strcmp(answer, "\0") == 0)
    //goto Q;
  banco = fopen("Banco/charada.txt", "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if(strcmp(answer, text) == 0)
      {
        fclose(banco);
        break;
        //fclose(phase[3]);
      }
    }
  if(feof(banco))
  {
    fclose(banco);
    goto p2;
  }
  
  system("clear");
  phase[3] = fopen("História/fase4/parte2.txt", "r");
  fgets(text, LEN_TEXT, phase[3]);
  printf("%s", text);
  stop("fase4\n", phase[3]);
  fclose(phase[3]);
  horas += 4;
  phase5();
  return;
  
  p2:
  phase[3] = fopen("História/fase4/parte2.txt", "r");
  fgets(text, LEN_TEXT, phase[3]);
  fgets(text, LEN_TEXT, phase[3]);
  for(i = 3; i <= 8; i++)
    {
    fgets(text, LEN_TEXT, phase[3]);
    printf("%s", text);
    stop("fase4\n", phase[3]);
    }
  do
  {
    scanf("%i", &num);
    system("clear");
    fflush(stdin);
    if (num != 1)
      printf("Digite: ");
  }
  while (num != 1);

  i = 1;
  system("clear");
  while(!feof(phase[3]))
    {
      i++;
      fgets(text, LEN_TEXT, phase[3]);
      printf("%s", text);
      if (i == 3)
      {
        while(Dadoi == 0) 
          {Dadoi = sorte(20);}
        printf("%i\n", Dadoi);
      }
      getch();
    }
  if(feof(phase[3]))
  {
    while(Dadoj == 0)
      {Dadoj = sorte(20);}
    printf("%i\n", Dadoj);
    getch();
    phase5();
    return;
  }
  if (Dadoj > 2 * Dadoi)
  {
    system("clear");
    horas += 8;
    phase5();
    return;
  }
  else
  {
    system("clear");
    printf("Game Over");
    return;
  }
  fclose(phase[3]);
}

void phase5()
{
  char C;
  int cont = 1;
  Dadoi = 0; Dadoj = 0;
  if (strcmp(equipment, "Magia\n") == 0)
  {
    phase[4] = fopen("História/fase5/parte1m.txt", "r");
    choice = fopen("História/fase5/escolhas-fim.txt", "r");
    for(i = 1; i <= 7; i++)
      {
        fgets(text, LEN_TEXT, phase[4]);
        printf("%s",  text);
        stop("fase5\n", phase[4]);
      }
    escolhaa:
    system("clear");
    while(!feof(choice))
    {
      fgets(text, LEN_TEXT, choice);
      printf("%s", text);
    }
  
    C = getch();
    switch(C)
      {
        case '1': 
            system("clear");
            fgets(text, LEN_TEXT, phase[4]);
            printf("%s", text);
            getch();
            donut();
            break;
        case '2':
            system("clear");
            fgets(text, LEN_TEXT, phase[4]);
            fgets(text, LEN_TEXT, phase[4]);
            printf("%s", text);
            getch();
            donut();
            break;
        case 'p': case 'P': stop("", choice);break;
        default: 
            printf("\nResposta inválida"); 
            getch();
            rewind(choice);
            goto escolhaa; 
            break;
      }
    fclose(choice);
    fclose(phase[4]);
    return;
  }
  else if (horas > 28)
  {
    texto("História/fase5/parte1-2.txt", "fase5\n");
    return;
  }
  else
  {   
    phase[4] = fopen("História/fase5/parte1.txt", "r");
    choice = fopen("História/fase5/escolhas-fim.txt", "r");
    system("clear");
    while(!feof(phase[4]))
      {
        if (cont > 6) break;
        fgets(text, LEN_TEXT, phase[4]);
        printf("%s", text);
        stop("fase5\n", phase[4]);
        cont++;
      }
    for (i = 1; i <= 4; i++)
      {
        while(Dadoi == 0)
            {Dadoi = sorte(6);}
        while(Dadoj == 0)
          {Dadoj = sorte(20);}
        fgets(text, LEN_TEXT, phase[4]);
        printf("%s", text);
        stop("fase5\n", phase[4]);
        if (i == 1)
        {
          printf("%i", Dadoi);
        }
        else if(i == 3)
          {
            printf("%i\n", Dadoj);  
            getch();
            if (Dadoj >= 2 * Dadoi)
            {
              fgets(text, LEN_TEXT, phase[4]);
              printf("%s", text);
            }
          } 
      }
    if (Dadoj <= 2 * Dadoi) goto fim2;
    escolha:
    system("clear");
    printf("1");
    while(!feof(choice))
      {
        fgets(text, LEN_TEXT, choice);
        printf("%s", text);
      }
    
    C = getch();
    switch(C)
      {
        case '1': 
          system("clear");
          fgets(text, LEN_TEXT, phase[4]);
          fgets(text, LEN_TEXT, phase[4]);
          printf("%s", text);
          getch();
          donut();
          break;
        case '2':
          system("clear");
          fgets(text, LEN_TEXT, phase[4]);
          fgets(text, LEN_TEXT, phase[4]);
          fgets(text, LEN_TEXT, phase[4]);
          printf("%s", text);
          getch();
          donut();
          break;
        case 'p': case 'P': stop("", choice);break;
        default: 
          printf("\nResposta inválida"); 
          getch();
          rewind(choice);
          goto escolha; 
          break;
      }
    fclose(phase[4]);
    fclose(choice);
  }
  fim2:
  system("clear");
  texto("História/fase5/parte2D.txt", "fase5\n");
  return;
}

void alternative()
{
  char C;
  int cont = 1;
  alt = fopen("História/Alternativo/alternativo.txt", "r");
  choice = fopen("História/Alternativo/escolhas-alt.txt", "r");
  system("clear");
  while(!feof(alt))
    {
      if (cont > 7) break;
      fgets(text, LEN_TEXT, alt);
      printf("%s", text);
      stop("", alt);
      cont++;
    }
  escolha:
  system("clear");
  while(!feof(choice))
    {
      fgets(text, LEN_TEXT, choice);
      printf("%s", text);
    }
  
  C = getch();
  switch(C)
    {
      case '1': 
          system("clear");
          fgets(text, LEN_TEXT, alt);
          printf("%s", text);
          getch();
          donut();
          break;
      case '2':
          system("clear");
          fgets(text, LEN_TEXT, alt);
          fgets(text, LEN_TEXT, alt);
          printf("%s", text);
          getch();
          donut();
          break;
      case 'p': case 'P': stop("", choice);break;
      default: 
          printf("\nResposta inválida"); 
          getch();
          rewind(choice);
          goto escolha; 
          break;
    }
  fclose(alt);
  fclose(choice);
}

void texto(char caminho[LEN_TEXT], char fase[])
{
  FILE *pont_arq;
  pont_arq = fopen(caminho, "r");
  while(!feof(pont_arq))
    {
      fgets(text, LEN_TEXT, pont_arq);
      printf("%s", text);
      stop(fase, pont_arq);
    }
  fclose(pont_arq);
}

char escolha()
{
  char C;
  choice = fopen("Layouts/escolhas.txt", "r");
  inicio:
  while(!feof(choice))
  {
    fgets(text, LEN_TEXT, choice);
    printf("%s", text);
  }
  C = getch();
  if (C != '1' && C != '2')
    {
      system("clear");
      rewind(choice);
      goto inicio;
    }
  fclose(choice);
  return C;
}

char *checar(char *arquivo)
{
  banco = fopen(arquivo, "r");
  while(!feof(banco))
    {
      fgets(text, LEN_TEXT, banco);
      if (strcmp(answer, text) == 0)
      {
        fclose(banco);
        return "s";
      }
    }
  fclose(banco);
    return "n";
}

char getch(void)
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
 //   printf("%c\n", buf);
    return buf;
 }

char* itoa(int num, char* buffer, int base)   
{  
  int current = 0;  
  if (num == 0)
  {  
    buffer[current++] = '0';  
    buffer[current] = '\0';  
    return buffer;  
  }  
  int num_digits = 0;  
  if (num < 0) 
  {  
    if (base == 10) 
    {  
      num_digits ++;  
      buffer[current] = '-';  
      current ++;  
      num *= -1;  
    }  
    else  
    return NULL;  
  }  
  num_digits += (int)floor(log(num) / log(base)) + 1;  
  while (current < num_digits)   
  {  
    int base_val = (int) pow(base, num_digits-1-current);  
    int num_val = num / base_val;  
     char value = num_val + '0';  
    buffer[current] = value;  
    current ++;  
    num -= base_val * num_val;  
  }  
  buffer[current] = '\0';  
  return buffer;  
}  

int donut()
{
  float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");
    for(;;) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 1761; k++) {
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
    return 0;
}
