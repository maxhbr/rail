#ifndef ASYNCWORKER_H
#define ASYNCWORKER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

class AsyncWorker
{
public:
    AsyncWorker();

    void exec(std::function<void()> *func);

private:
    QueueHandle_t queue;
    void dowork();
};

#endif /* ASYNCWORKER_H */
