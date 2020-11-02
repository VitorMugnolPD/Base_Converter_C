#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 30

char caracteres[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

char antesVirgula[MAX], depoisVirgula[MAX];

void separarPorVirgula(char numero[MAX])
{
  int indice=0;

  while(numero[indice]!=',' && numero[indice]!='\0')
  {
    antesVirgula[indice] = numero[indice];  
    indice = indice + 1;
  }
  
  if(numero[indice]==',')
  {
    int indiceAuxiliar=0;
    indice++;
    
    while(depoisVirgula[indiceAuxiliar]!='\0')
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

double algumaParaDezAntes(char* numero, int base)
{
  double ret = 0;
  char nmr[MAX] = {numero};
  int tamanho = (int) sizeof(nmr) / sizeof(nmr[0]);
  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(isdigit(nmr[indice]))
    {
      ret = ret + (double) (nmr[indice] * pow(base, tamanho - indice));
    }
    else
    {
      int n = getNumero(nmr[indice]);
      ret = ret + (double) (n * pow(base, tamanho - indice));
    }
  }
  return ret;
}

double algumaParaDezDepois(char* numero, int base)
{
  double ret = 0;
  char nmr[MAX] = {numero};
  int tamanho = (int) sizeof(nmr) / sizeof(nmr[0]);
  int indice;
  for(indice = 0; indice < tamanho; indice++)
  {
    if(isdigit(nmr[indice]))
    {
      ret = ret + (double) (nmr[indice] * (1 / pow(base, indice + 1)));
    }
    else
    {
      int n = getNumero(nmr[indice]);
      ret = ret + (double) (n * (1 / pow(base, indice + 1)));
    }
  }
  return ret;
}

double algumaParaDez(char numeroAntes[MAX],char numeroDepois[MAX], int baseInicial)
{
  
  double antes = algumaParaDezAntes(numeroAntes, baseInicial);

  printf("%lf",antes);

  double depois = algumaParaDezDepois(numeroDepois, baseInicial);

  char n[MAX];
  strcat(n, (char[]) {antes});
  strcat(n, '.');
  strcat(n, (char[]) {depois});
  return (double) *n;
}

/*double dezParaOutraAntes(double numero, int baseFinal)
{
  double nmr = numero;
  char ret[MAX] = "";
  while(nmr != 0)
  {
    char n = (char[]) {nmr};
    int tamanho = (int) (sizeof(n) / sizeof(n[0]));
  }
}*/

//double dezParaOutra(double numero, int baseFinal)
//{
  //double nmr[2] = separarPorVirgula(numero);
  //double antes = dezParaOutraAntes(nmr[0], baseFinal);
  //double depois = dezParaOutraDepois(nmr[1], baseFinal);
////}

int main()
{ 
  char numeroInicial[MAX], numeroFinal;
  unsigned int baseInicial, baseFinal;

  printf("\nDigite o numero desejado: ");
  fgets(numeroInicial, MAX, stdin);

  printf("\nDigite a base inicial: ");
  scanf("%u",&baseInicial);

  printf("\nDigite a base final: ");
  scanf("%u",&baseFinal);
  fflush(stdin);

  printf("%s", &numeroInicial);

  algumaParaDez(antesVirgula,depoisVirgula,baseInicial);

  //printf("\nO resultado é: %s", numeroFinal);

  return 0;  
}
