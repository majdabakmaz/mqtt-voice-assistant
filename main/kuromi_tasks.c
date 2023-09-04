#include "oled_display.c"
#include "wifi_connect.h"

#define COMMAND_1 "Say Hello"
#define COMMAND_2 "What time is it?"

static const char *TAG = "KUROMI_TASKS";

void decode_command(char *command, int len)
{
    if (strcmp(command, COMMAND_1) == 0)
    {
        kuromi_speak("Hello!",6);
    } 
    else if (strcmp(command, COMMAND_2) == 0) 
    {
        char *time;
        time = get_sntp_time();
        char message[40];
        sprintf(message, "It's  %.*s    o'clock!", 5, time);
        kuromi_speak(message, 24);
    }
}