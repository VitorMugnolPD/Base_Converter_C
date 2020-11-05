#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 30

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

double algumaParaDezAntes(char* numero, int base, int tamanho)
{
  double ret = 0;

  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(isdigit(numero[indice]))
    {
      ret = ret + (double) ((numero[indice]-48) * pow(base, tamanho - indice-1));

    }
    else
    {
      

      ret = ret + (double) (toupper(numero[indice])-55) * pow(base, tamanho - indice-1);
    }

  }
  return ret;
}

double algumaParaDezDepois(char* numero, int base, int tamanho)
{
  double ret = 0;

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
      ret = ret + (double) (toupper(numero[indice])-55) * (1 / pow(base, indice + 1));
       int a =0;
    }
  }
  return ret;
}

char* dezParaOutraAntes(int antesVirgula,int base)
{

int indice=0;
char* conversaoInvertida = malloc(sizeof(char));

while((antesVirgula % base)!=0)
{
conversaoInvertida[indice] = (char)antesVirgula%base + 48;
antesVirgula=antesVirgula/base;
indice++;
realloc(conversaoInvertida,sizeof(char)+indice);
}


int tamanho = strlen(conversaoInvertida);
char* conversao= malloc(sizeof(char)*tamanho);

int i;
for(i=0;i<tamanho;i++)
{
conversao[tamanho-i-1] =conversaoInvertida[i];

}
free(conversaoInvertida);

return conversao;



}

char* dezParaOutraDepois(double depoisVirgula,int base)
{
  char*numero = malloc(sizeof(char));
  int indice=0;
  int digito=0;
  
  while(depoisVirgula!=0)
  {
    depoisVirgula*=base;

    digito = (int) depoisVirgula;

    
    numero[indice] = (char)digito+48;
    depoisVirgula-=digito;
    indice++;
    realloc(numero,sizeof(char)+indice);
    
   
  }
  int a=0;
return numero;
}

char* algumaParaDez(char *numeroAntes,char *numeroDepois, int baseInicial,int tamanhoAntes,int tamanhoDepois,int baseFinal)
{
  

  double antes = algumaParaDezAntes(numeroAntes, baseInicial, tamanhoAntes);

  double depois = algumaParaDezDepois(numeroDepois, baseInicial, tamanhoDepois);

  
 char* b = dezParaOutraDepois(depois,baseFinal);

 char* a = dezParaOutraAntes(antes,baseFinal);
char* c;

  strcat(a,".");
  strcat(a,b);
  
  strcat(c,a);
  free(a);
  free(b);

  
  return c;
}

int verificar(char *numero, int tamanho, int base)
{
  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(!isdigit(numero[indice]))
    {
      if((toupper(numero[indice])-55) > base - 1)
        return -1;
      }
    else
    {
      if((numero[indice]-48) > base - 1)
        return -1;
    }
  }
  return 1;
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

  separarPorVirgula(numeroInicial);

  int tamanhoAntes = strlen(antesVirgula);

  int tamanhoDepois = strlen(depoisVirgula);

  int a = verificar(antesVirgula, tamanhoAntes, baseInicial);
  int b = verificar(depoisVirgula, tamanhoDepois, baseInicial);
  printf("%i", a);
  printf("%i", b);

  //char* a = algumaParaDez(antesVirgula,depoisVirgula,baseInicial,tamanhoAntes,tamanhoDepois,baseFinal);
  //printf("\n%s",a);

  //printf("\nO resultado é: %s", numeroFinal);

  return 0;  
}
