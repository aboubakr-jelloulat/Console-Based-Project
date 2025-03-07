#include "includes/main.h"

int main()

{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

    }

    return 0;
}
/*
	A circular reference in classes occurs when two or more classes depend on each other directly or indirectly,
	creating an infinite loop of dependencies.

*/
