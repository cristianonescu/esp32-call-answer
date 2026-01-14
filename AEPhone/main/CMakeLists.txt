idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    PRIV_INCLUDE_DIRS ""
    REQUIRES bt esp_driver_gpio
    PRIV_REQUIRES nvs_flash
)