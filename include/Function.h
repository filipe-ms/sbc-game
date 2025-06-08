#pragma once

typedef void (*Function_Call)(void); // (() => {})()
typedef void (*Function_Call_Args1)(void* arg1); // ( (x) => {} )(y)

typedef void* Function; // () => {}
typedef Function_Call_Args1 Function_Arg1; // (x) => {}

void Function_Invoke(Function function);
void Function_Invoke_Arg1(Function_Arg1 function, void* arg1);