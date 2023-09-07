idf_component_register(SRCS "app_main.c"
                    INCLUDE_DIRS "."
                    REQUIRES mqtt esp_wifi nvs_flash wifi-connect mqtt-connect display)
