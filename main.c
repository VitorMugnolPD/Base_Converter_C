#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 30

char caracteres[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

char antesVirgula[MAX], depoisVirgula[MAX];

void separarPorVirgula(char numero[MAX])
{
  int indice=0;

  while((numero[indice]!=',' && numero[indice]!='.' )&& numero[indice]!='\0')
  {
    antesVirgula[indice] = numero[indice];  
    indice = indice + 1;
  }
  
  if(numero[indice]==',' || numero[indice]=='.')
  {
    int indiceAuxiliar=0;
    indice++;
    
    while(numero[indice]!='\0')
    {
      depoisVirgula[indiceAuxiliar] = numero[indice]; 
      indice++;
      indiceAuxiliar++;
    }
  }
}

char getLetra(int numero)
{
  return caracteres[numero - 10];
}

int getNumero(char letra)
{
  int indice;
  for(indice = 0; indice < 26; indice++)
  {
    if(caracteres[indice] == letra)
      return indice + 10;
  }
}

double algumaParaDezAntes(char* numero, int base, int tamanho)
{
  double ret = 0;
 // printf("%s\n",base);
  //int tamanho = (int) sizeof(nmr) / sizeof(nmr[0]);
  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(isdigit(numero[indice]))
    {
      ret = ret + (double) ((numero[indice]-48) * pow(base, tamanho - indice-1));
     // printf("\nbatata: %lf",ret);
     // printf("\nteste: %i",tamanho);
    }
    else
    {
      
      int n = getNumero(numero[indice]);
      ret = ret + (double) (n * pow(base, tamanho - indice-1));
    }
    //printf("\n%lf",ret);
  }
  return ret;
}

double algumaParaDezDepois(char* numero, int base, int tamanho)
{
  double ret = 0;
  //char nmr[MAX] = {numero};
  //int tamanho = (int) sizeof(nmr) / sizeof(nmr[0]);
  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(isdigit(numero[indice]))
    {
      ret = ret + (double) ((numero[indice]-48) * (1 / pow(base, indice + 1)));
       int a =0;
    }
    else
    {
      int n = getNumero(numero[indice]);
      ret = ret + (double) (n * (1 / pow(base, indice + 1)));
       int a =0;
    }
  }
  return ret;
}

double algumaParaDez(char *numeroAntes,char *numeroDepois, int baseInicial,int tamanhoAntes,int tamanhoDepois)
{
  

  double antes = algumaParaDezAntes(numeroAntes, baseInicial, tamanhoAntes);

  double depois = algumaParaDezDepois(numeroDepois, baseInicial, tamanhoDepois);

  double n = antes+depois;
  
  return n;
}


//double dezParaOutra(double numero, int baseFinal)
//{
  //double nmr[2] = separarPorVirgula(numero);
  //double antes = dezParaOutraAntes(nmr[0], baseFinal);
  //double depois = dezParaOutraDepois(nmr[1], baseFinal);
////}

int main()
{ 
  char numeroInicial[MAX], numeroFinal;
  unsigned int baseInicial=0, baseFinal=0;

  printf("\nDigite o numero desejado: ");
  scanf("%s",&numeroInicial);
  fflush(stdin);

  printf("\nDigite a base inicial: ");
  scanf("%i",&baseInicial);
  fflush(stdin);
  fflush(stdout);
  printf("\nDigite a base final: ");
  scanf("%u",&baseFinal);
  fflush(stdin);

  //printf("mr potato head: %u\n", baseInicial);
 // printf("mr batata cabeça: %s\n",numeroInicial);

  separarPorVirgula(numeroInicial);

  int tamanhoAntes = strlen(antesVirgula);

  int tamanhoDepois = strlen(depoisVirgula);

  double a = algumaParaDez(antesVirgula,depoisVirgula,baseInicial,tamanhoAntes,tamanhoDepois);
  printf("%lf",a);

  //printf("olha o resultado aqui ó --> %lf", a);

  //printf("\nO resultado é: %s", numeroFinal);

  return 0;  
}
