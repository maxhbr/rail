#include "SerialCommandDispatcher.h"

const char *key_arrow_left = "\x1b[D";
const char *key_arrow_up = "\x1b[A";
const char *key_arrow_right = "\x1b[C";
const char *key_arrow_down = "\x1b[B";

void SerialCommandDispatcher::process(void)
{
    unsigned int available = serial.available();
    if (available == 0)
        return;

    char content[available + 1] = {0};
    Serial.readBytes(content, available);

    for (unsigned int i = 0; i < cmdtable_size; i++)
    {
        if (strcmp(content, cmdtable[i].cmdcode) == 0)
        {
            cmdtable[i].func();
            break;
        }
    }
}
