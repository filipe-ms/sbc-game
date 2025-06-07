#include <Function.h>

void Function_Invoke(Function function) {
    if(!function) return;
	((Function_Call)function)();
}