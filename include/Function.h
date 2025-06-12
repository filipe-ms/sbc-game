// File: Function.h
#pragma once

typedef void (*Function_Call)(void); // (() => {})()
typedef void (*Function_Call_Args1)(void* arg1); // ( (x) => {} )(y)

typedef void* Function; // () => {}
typedef Function_Call_Args1 Function_Arg1; // (x) => {}

void Function_Invoke(Function function);
void Function_Invoke_Arg1(Function_Arg1 function, void* arg1);

// (Filipe) Adicionando aqui novas defini��es de fun��o:

// Fun��o de correspond�ncia.
// Deve retornar 1 se o item corresponder ao crit�rio (ex: igualdade) ou 0 caso contr�rio.
typedef int (*MatchFunction)(void* context, void* item);

// Fun��o de compara��o de dois elementos similar � fun��o de compara��o usada em qsort.
// Deve retornar um valor negativo se data1 < data2, um positivo se o contr�rio for verdade e 0 se igual.
typedef int (*ComparisonFunc)(void* item1, void* item2);