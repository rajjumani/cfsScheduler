#include "main.h"

// Handles write message after interrupt occurs
void IOHandler::write()
{
    cout << "Completed writing message ";
}

// Handles read message after interrupt occurs
void IOHandler::read()
{
    cout << "Completed reading message ";
}