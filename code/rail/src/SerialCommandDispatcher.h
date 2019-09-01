#ifndef SERIALCOMMANDDISPATCHER_H
#define SERIALCOMMANDDISPATCHER_H

#include <Arduino.h>

extern const char *key_arrow_left;
extern const char *key_arrow_up;
extern const char *key_arrow_right;
extern const char *key_arrow_down;

struct SerialCommand
{
    const char *cmdcode;
    void (*func)(void);
};

class SerialCommandDispatcher
{
private:
    HardwareSerial &serial;
    const SerialCommand *cmdtable;
    unsigned int cmdtable_size;

public:
    SerialCommandDispatcher(
        HardwareSerial &serial,
        const SerialCommand *cmdtable,
        unsigned int cmdtable_size)
        : serial(serial),
          cmdtable(cmdtable),
          cmdtable_size(cmdtable_size) {};
    void process(void);

};

#endif /* SERIALCOMMANDDISPATCHER_H */
