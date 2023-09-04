#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"
#include "images.h"

#define CONFIG_SDA_GPIO 21
#define CONFIG_SCL_GPIO 22
#define CONFIG_RESET_GPIO 15
#define CONFIG_OFFSETX 2

#define tag "OLED"

SSD1306_t dev;
bool kuromi_on_right;
uint8_t buff[1024];

void kuromi_laugh(void);
void kuromi_speak(char *text, int len);


void oled_init(void)
{
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);

    ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);

    ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	//kuromi_laugh();
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi_standing, 128, 64, false);
	kuromi_on_right = false;


}

void kuromi_laugh(void)
{
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi, 128, 64, false);
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi_laugh, 128, 64, false);
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi, 128, 64, false);
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi_laugh, 128, 64, false);
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi, 128, 64, false);
	ssd1306_bitmaps(&dev, 0, 0, image_data_kuromi_standing, 128, 64, false);
}

void kuromi_speak(char *text, int len)
{
	if(!kuromi_on_right){
		for(int i =0; i<33;i++){
			ssd1306_wrap_arround(&dev, SCROLL_RIGHT, 0, 7,0);
			kuromi_on_right = true;
		}
		ssd1306_get_buffer(&dev, buff);		
	} else {
		for(int i =3; i<6;i++){
			ssd1306_clear_line(&dev, i, true);
		}
		ssd1306_set_buffer(&dev, buff);
		ssd1306_show_buffer(&dev);
	}

	if (len <= 6){
		char text_display[50];
		sprintf(text_display, " %s", text);
		ssd1306_display_text(&dev, 3, text_display, len+1, true);
	} else if (len <= 15) {
		char text_display[50];
		sprintf(text_display, " %.*s",6, text);
		ssd1306_display_text(&dev, 3, text_display, 6+1, true);
		text+=6;
		sprintf(text_display, " %s", text);
		ssd1306_display_text(&dev, 4, text_display, len-6, true);
	} else if (len <= 25) {
		char text_display[50];
		sprintf(text_display, " %.*s",6, text);
		ssd1306_display_text(&dev, 3, text_display, 6+1, true);
		text+=6;
		sprintf(text_display, " %.*s",9, text);
		ssd1306_display_text(&dev, 4, text_display, 9, true);
		text+=9;
		sprintf(text_display, " %s", text);
		ssd1306_display_text(&dev, 5, text_display, len-6-9-1, true);
	}
}