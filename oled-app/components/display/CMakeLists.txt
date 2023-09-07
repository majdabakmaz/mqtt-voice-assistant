idf_component_register(SRCS "oled_display.c" "kuromi_tasks.c"
                       INCLUDE_DIRS "."
                       REQUIRES wifi-connect ssd1306 images)