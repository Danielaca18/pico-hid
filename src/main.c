#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"


bool tud_hid_not_ready() {
    return !tud_hid_ready();
}

static void send_hid_report(uint8_t report_id, uint8_t key) {
    if (tud_hid_not_ready()) return;

    static bool has_key = false;

    if (key) {
        uint8_t keycode[6] = {0};
        keycode[0] = key;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_key = true;
    } else {
        if (has_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_key = false;
    }
}

void hid_task(void) {
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;
    uint32_t time = board_millis();

    if (time - start_ms < interval_ms) return;
    start_ms += interval_ms;

    uint32_t const btn = HID_KEY_6;
    if (tud_suspended() && btn) tud_remote_wakeup();
    else send_hid_report(REPORT_ID_KEYBOARD, btn);
}

void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len) {
    (void) instance;

    uint8_t next_report = report[0] + 1;
    if (next_report < REPORT_ID_COUNT) send_hid_report(next_report, board_button_read());
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
  return (uint16_t) 1;
}

int main() {
    board_init();
    tusb_init();

    sleep_ms(1000);
    while(true) {
        tud_task();
        hid_task();
    }
}