#include "main.h"

/**
 * handleSIGINT - Handles the Ctrl+C signal in the prompt.
 *
 * @signal: The signal handler.
 */
void handleSIGINT(int signal)
{
  (void)signal;  /* Unused parameter warning.*/

  /* Write a message to the standard output.*/
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
