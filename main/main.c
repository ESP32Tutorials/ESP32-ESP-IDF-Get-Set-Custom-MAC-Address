/** For more information vist following link*/
/** https://esp32tutorials.com/esp32-esp-idf-get-set-custom-mac-address ***/
#include <stdio.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define MAC_ADDR_SIZE 6

uint8_t mac_address[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};

static void get_mac_address()
{
    uint8_t mac[MAC_ADDR_SIZE];
    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
    ESP_LOGI("MAC address", "MAC address: %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static void set_mac_address(uint8_t *mac)
{
    esp_err_t err = esp_wifi_set_mac(ESP_IF_WIFI_STA, mac);
    if (err == ESP_OK) {
        ESP_LOGI("MAC address", "MAC address successfully set to %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    } else {
        ESP_LOGE("MAC address", "Failed to set MAC address");
    }
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    get_mac_address();
    set_mac_address(mac_address);
}
