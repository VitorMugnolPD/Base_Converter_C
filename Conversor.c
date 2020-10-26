#include <stdio.h>
#include <string.h>
#include <math.h>

int baseInicial;
int baseFinal;
char numeroInicial[];
char antesVirgula[] = " ";
char depoisVirgula[];
char caracteres[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

char caractere(int n)
{
  n = n - 10;
  return caracteres[n];
}

void algumaParaDez()
{
  char antes[] = "";
  int i;
  for(i = 0; i < sizeof(antesVirgula)/sizeof(antesVirgula[0]); i++)
  {
    if(isdigit(antesVirgula[i]))
      strcat(antes, (char) antesVirgula[i]);
    else
    {
    
      int n;
      for(n = 0; n < sizeof(caracteres); n++)
      {
        if(caracteres[n] == antesVirgula[i])
          strcat(antes, (char) caracteres[n]);
      }
    }
  }
}

void dezParaOutra()
{

}

void SepararPorVirgula(char* numero)
{
  int indice;

  while(strcmp (numero[indice],",")!=0 && indice < sizeof(numero)/sizeof(numero[0]))
  {
    antesVirgula[indice] = numero[indice];
    indice = indice + 1;
  }
  
  if(strcmp (numero[indice],",")==0)
  {
    int indiceAuxiliar;
    indice++;
    
for(indiceAuxiliar=0;indice<sizeof(numero)/sizeof(numero[0]);indice++,indiceAuxiliar++)
    {
     depoisVirgula[indiceAuxiliar] = numero[indice]; 
    }
  }
}

int main()
{ 
  printf("\nDigite a base inicial: ");
  fflush(stdout);

  scanf("%i",&baseInicial);
  fflush(stdin);

  printf("\nDigite a base final: ");
  fflush(stdout);

  scanf("%i",&baseFinal);
  fflush(stdin);

  printf("\nDigite o numero desejado: ");
  fflush(stdout);

  scanf("%s",&numeroInicial);
  fflush(stdin);

  SepararPorVirgula(&numeroInicial);

  return 0;
}
