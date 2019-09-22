#include <Arduino.h>

#include "AsyncWorker.h"


AsyncWorker::AsyncWorker()
{
    queue = xQueueCreate(2, sizeof(std::function<void()>));

    xTaskCreate(
        [](void *obj){static_cast<AsyncWorker *>(obj)->dowork();},
        "AsyncWorker::dowork",
        10000,
        this,
        3,
        NULL);
}

void AsyncWorker::dowork()
{
    while (1)
    {
        std::function<void()> func;
        xQueueReceive(queue, &func, portMAX_DELAY);
        func();
    }
}

void AsyncWorker::exec(std::function<void()> *func)
{
    xQueueSend(queue, func, portMAX_DELAY);
}
