// File: Function.h
#pragma once

typedef void (*Function_Call)(void); // (() => {})()
typedef void (*Function_Call_Args1)(void* arg1); // ( (x) => {} )(y)

typedef void* Function; // () => {}
typedef Function_Call_Args1 Function_Arg1; // (x) => {}

void Function_Invoke(Function function);
void Function_Invoke_Arg1(Function_Arg1 function, void* arg1);

// (Filipe) Adicionando aqui novas definições de função:

// Função de correspondência.
// Deve retornar 1 se o item corresponder ao critério (ex: igualdade) ou 0 caso contrário.
typedef int (*MatchFunction)(void* context, void* item);

// Função de comparação de dois elementos similar à função de comparação usada em qsort.
// Deve retornar um valor negativo se data1 < data2, um positivo se o contrário for verdade e 0 se igual.
typedef int (*ComparisonFunc)(void* item1, void* item2);