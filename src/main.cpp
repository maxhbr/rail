#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "PhotoRail.h"

const int button_move_forward = 16;
const int button_move_backward = 4;
const int button_start = 17;
const int button_alt = 5;
const int status_led = 15;
const char *ssid = "***";
const char *password = "***";

PhotoRail rail(32, 33, 25, 26, 27, 14, 12, 2);

AsyncWebServer server(80);
QueueHandle_t queue;

void dotask(void *parameter)
{
    while (1)
    {
        int distance;
        xQueueReceive(queue, &distance, portMAX_DELAY);
        rail.move(distance, 3);
    }
}

void setup() {
    Serial.begin(9600);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED);
    Serial.println(WiFi.localIP());

    queue = xQueueCreate(2, sizeof(int));

    server.on(
        "/move",
        HTTP_POST,
        [](AsyncWebServerRequest *request){},
        NULL,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
            if (len != 2 * sizeof(uint32_t))
            {
                request->send(400);
                return;
            }
            int distance = (int) ntohl(*(uint32_t *)data);
            unsigned int max_speed = ntohl(*(uint32_t *)(data + 4));
            // Serial.println("post: distance = " + String(distance));
            // rail.move(distance, max_speed);
            xQueueSend(queue, &distance, portMAX_DELAY);
            request->send(200);
        });
    server.begin();

    xTaskCreate(
        dotask,                  /* pvTaskCode */
        "Workload1",            /* pcName */
        10000,                   /* usStackDepth */
        NULL,                   /* pvParameters */
        3,                      /* uxPriority */
        NULL);                /* pxCreatedTask */


    pinMode(button_move_forward, INPUT);
    pinMode(button_move_backward, INPUT);
    pinMode(button_start, INPUT);
    pinMode(status_led, OUTPUT);

    digitalWrite(status_led, LOW);
    delay(250);
    digitalWrite(status_led, HIGH);
    delay(250);
    digitalWrite(status_led, LOW);
}

void loop() {
    if (digitalRead(button_start) == HIGH)
    {
        rail.stack(100);
    }
    else if (digitalRead(button_move_forward) == HIGH)
    {
        rail.move(32, 3);
    }
    else if (digitalRead(button_move_backward) == HIGH)
    {
        rail.move(-32, 3);
    }
    else if (digitalRead(button_alt) == HIGH)
    {
        rail.log_state();
        delay(1000);
    }
}
