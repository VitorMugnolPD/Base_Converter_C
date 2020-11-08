/*
Integrantes:
Pedro Go Iqueda - RA 19195
Vicente Pinto Tomás Junior - RA 19199
Vitor Mugnol Estevam de Araujo - RA 19200
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 30  // tamanho máximo que utilizamos ao instanciar as strings

char antesVirgula[MAX], depoisVirgula[MAX];
int ehNegativo = -1;  // -1 -> não é negativo, 1 -> é negativo

void separarPorVirgula(char numero[MAX])
{
  int indice=0;

  while((numero[indice]!=',' && numero[indice]!='.' )&& numero[indice]!='\0')  // enquanto o caractere atual for diferente de vírgula, ponto, e n estiver no final da string 
  {
    antesVirgula[indice] = numero[indice];  
    indice = indice + 1;
  }
  
  if(numero[indice]==',' || numero[indice]=='.')  // se for vírgula ou ponto
  {
    int indiceAuxiliar=0;
    indice++;
    
    while(numero[indice]!='\0')  // enquanto não estiver no final da string
    {
      depoisVirgula[indiceAuxiliar] = numero[indice]; 
      indice++;
      indiceAuxiliar++;
    }
  }
}

double algumaParaDezAntes(char* numero, int base, int tamanho)  // converter a parte anterior a vírgula de alguma base para a base dez
{
  double ret = 0;

  int indice;
  for(indice = 0; indice < tamanho; indice++)  // percorrer toda a string
  {
    if(isdigit(numero[indice]))  // se o caractere atual for um dígito
    {
      ret = ret + (double) ((numero[indice]-48) * pow(base, tamanho - indice-1));  // adiciona ao retorno o valor na base dez
    }
    else  // se não for um dígito
    {
      ret = ret + (double) (toupper(numero[indice])-55) * pow(base, tamanho - indice-1);// adiciona ao retorno o valor na base dez
    }

  }
  return ret;
}

double algumaParaDezDepois(char* numero, int base, int tamanho)  // converter a parte depois da vírgula de alguma base para a base dez
{
  double ret = 0;

  int indice;
  for(indice = 0; indice < tamanho; indice++)  // percorrer toda a string
  {
    if(isdigit(numero[indice]))  // se o caractere atual for um dígito
    {
      ret = ret + (double) ((numero[indice]-48) * (1 / pow(base, indice + 1)));  // adiciona ao retorno o valor na base dez
    }
    else  // se não for um dígito
    {
      ret = ret + (double) (toupper(numero[indice])-55) * (1 / pow(base, indice + 1));  // adiciona ao retorno o valor na base dez
    }
  }
  return ret;
}

char* dezParaOutraAntes(int antesVirgula,int base)  // converter a parte antes da vírgula da base dez para alguma outra base
{

  int indice=0;
  char* conversaoInvertida = malloc(sizeof(char));  // alocando espaço

  while((antesVirgula % base)!=0)  // enquanto o resto da divisão não for zero
  {
    conversaoInvertida[indice] = (char)(antesVirgula%base + 48);  // adiciona o resto da divisão na string
    antesVirgula=antesVirgula/base;  // divide o valor
    indice++;
    conversaoInvertida = realloc(conversaoInvertida,sizeof(char)+indice);  // realocando espaço
  }

  if(antesVirgula==base)  // caso for igual a base passada
  {
  conversaoInvertida = realloc(conversaoInvertida,sizeof(char)+indice+1);  // realocando espaço
    conversaoInvertida[indice] = (char)(antesVirgula%base + 48);  // adiciona o resto da divisão na string
    antesVirgula=antesVirgula/base;  // divide o valor
    conversaoInvertida[indice+1] = (char)(antesVirgula%base + 48);
  }

  int tamanho = strlen(conversaoInvertida);  // pegamos o tamanho sa string
  char* conversao= malloc(sizeof(char)*tamanho);  // alocando espaço

  int i;
  for(i=0;i<tamanho;i++)  // para percorrer toda a string
  {
    conversao[tamanho-i-1] =conversaoInvertida[i];  // adicionamos o valor em outra string, para inverter as posições
  }
  free(conversaoInvertida);  // liberamos o espaço

  return conversao;

}

char* dezParaOutraDepois(double depoisVirgula,int base)  // convertendo a parte depois da vírgula da base dez para outra base
{
  char*numero = malloc(sizeof(char));  // alocando espaço
  int indice=0;
  int digito=0;
  
  while(depoisVirgula!=0 && indice < 7)  // enquanto a parte depois da vírgua for diferente de dez, e o índice for menor do que 7
  {
    depoisVirgula*=base;

    digito = (int) depoisVirgula;

    
    numero[indice] = (char)(digito+48);  // adicionamos o valor ao número
    depoisVirgula-=digito;
    indice++;
    numero = realloc(numero,sizeof(char)+indice);  // realocando espaço
  
  }

return numero;
}

char* converter(char *numeroAntes,char *numeroDepois, int baseInicial,int tamanhoAntes,int tamanhoDepois,int baseFinal) // retornar a conversão
{
  char* antesNumero= malloc(sizeof(char));  // alocando espaço

  if(numeroAntes[0] == '-')  // se o caractere inicial for '-' (se o numero for negativo)
  {
    ehNegativo = 1;  // é negativo
    int indice;
    for(indice = 0; indice < tamanhoAntes-1; indice++)  // percorrendo todo o número
    {
      antesNumero= realloc(antesNumero,sizeof(char)+indice);  // realocando espaço
      antesNumero[indice] = numeroAntes[indice + 1];  // adiciona à string o valor seguinte do número passado  
    }
  }

  double antes;
  if(ehNegativo < 0)  // se não for negativo
    antes = algumaParaDezAntes(numeroAntes, baseInicial, tamanhoAntes);
  else
    antes = algumaParaDezAntes(antesNumero, baseInicial, tamanhoAntes-1);

  int d =strlen(numeroDepois);

  char* a = dezParaOutraAntes(antes,baseFinal);
  if(strlen(a) == 0)  // se o tamanho for zero
    strcat(a, "0");  // adiciona "0" a parte antes da vírgula

  if (d> 0)
  {
  double depois = algumaParaDezDepois(numeroDepois, baseInicial, tamanhoDepois);
  char* b = dezParaOutraDepois(depois,baseFinal);
  strcat(a,".");  // concatenar "."
  strcat(a,b);  // concatenar o valor após a vírgula
  free(b);
  }
  
  return a;  // retorna o valor convertido
}

int verificar(char *numero, int tamanho, int base)  // verificar se está de acordo com a base informada
{
  int indice;
  for(indice = 0; indice < tamanho; indice++)  // percorrer toda a string
  {
    if(!isdigit(numero[indice]))  // se o caractere atual não for um dígito
    {
      if((toupper(numero[indice])-55) > base - 1)
        return -1;  // não está de acordo
      }
    else  // se for um dígito
    {
      if((numero[indice]-48) > base - 1)
        return -1;  // não está de acordo
    }
  }
  return 1;  // está de acordo
}

int main()
{ 
  
  char numeroInicial[MAX], numeroFinal;
  unsigned int baseInicial=0, baseFinal=0;

  printf("\nDigite o numero desejado: ");
  scanf("%s",&numeroInicial);  // número que o usuário quer converter

  printf("\nDigite a base inicial: ");
  scanf("%u",&baseInicial);  // base do número informado

  printf("\nDigite a base final: ");
  scanf("%u",&baseFinal);  // base do número convertido

  fflush(stdin);
  fflush(stdout);

  separarPorVirgula(numeroInicial);  // separar por antes e depois da vírgula o número informado

  int tamanhoAntes = strlen(antesVirgula);

  int tamanhoDepois = strlen(depoisVirgula);

  int a = verificar(antesVirgula, tamanhoAntes, baseInicial);  // verificação de antes da vírgula
  int b = verificar(depoisVirgula, tamanhoDepois, baseInicial);  // verificação de depois da vírgula
  if(a < 0 || b < 0)  // se alguma das verificações não estiver de acordo
  {
    printf("O número fornecido não condiz com a base :(\n");
    return 0;
  }

  char* c = converter(antesVirgula,depoisVirgula,baseInicial,tamanhoAntes,tamanhoDepois,baseFinal);

  if(ehNegativo > 0)  // se o número for negativo
    printf("\nO resultado é: -%s\n", c);
  else  // se não for negativo
    printf("\nO resultado é: %s\n", c);
  
  free(c);

  return 0;  
}
