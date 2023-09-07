
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "speech_commands_action.h"
#include "led.h"
#include "mqtt_client.h"
#include "mqtt_connect.h"

void speech_commands_action(int command_id)
{
    printf("Commands ID: %d.\n", command_id);
    switch (command_id)
    {
    case 0:
        printf("\n-TURN ON-\n");
        my_publish(1);
        led_on();
        break;
    case 1:
        printf("\n-TURN OFF-\n");
        my_publish(0);
        led_off();
        break;
    case 2:
        printf("\n-PALIM LEDICU-\n");
        my_publish(1);
        led_on();
        break;
    case 3:
        printf("\n-GASIM LEDICU-\n");
        my_publish(0);
        led_off();
        break;
    case 4:
        my_publish(2);
        break;
    case 5:
        my_publish(3);
        break;
    default:
        break;
    }
}
