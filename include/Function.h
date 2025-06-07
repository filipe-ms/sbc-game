#pragma once

typedef void* Function;
typedef void (*Function_Call)(void);

void Function_Invoke(Function function);