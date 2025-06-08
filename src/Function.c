#include <Function.h>

void Function_Invoke(Function function) {
	if (!function) return;
	((Function_Call)function)();
}

void Function_Invoke_Arg1(Function_Arg1 function, void* arg1) {
	if (!function) return;
	((Function_Call_Args1)function)(arg1);
}