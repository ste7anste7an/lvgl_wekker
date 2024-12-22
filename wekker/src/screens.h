#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *alarm;
    lv_obj_t *main;
    lv_obj_t *snooze;
    lv_obj_t *settings;
    lv_obj_t *radio;
    lv_obj_t *boot;
    lv_obj_t *alarm_on_off;
    lv_obj_t *alarm_alarm_time;
    lv_obj_t *alarm_btn_hr_plus;
    lv_obj_t *alarm_vol_up;
    lv_obj_t *alarm_vol_down;
    lv_obj_t *alarm_alarm_volume;
    lv_obj_t *main_time;
    lv_obj_t *main_alarm;
    lv_obj_t *main_radio_station;
    lv_obj_t *main_snooze;
    lv_obj_t *main_alarm_set;
    lv_obj_t *main_radio_title;
    lv_obj_t *snooze_snooze_time;
    lv_obj_t *snooze_btn_min_plus;
    lv_obj_t *snooze_min_plus;
    lv_obj_t *snooze_btn_min_min;
    lv_obj_t *settings_slider_backlight;
    lv_obj_t *radio_vol_up;
    lv_obj_t *radio_vol_down;
    lv_obj_t *alarm_alarm_volume_1;
    lv_obj_t *radio_station;
    lv_obj_t *radio_title;
    lv_obj_t *obj0;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_ALARM = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_SNOOZE = 3,
    SCREEN_ID_SETTINGS = 4,
    SCREEN_ID_RADIO = 5,
    SCREEN_ID_BOOT = 6,
};

void create_screen_alarm();
void tick_screen_alarm();

void create_screen_main();
void tick_screen_main();

void create_screen_snooze();
void tick_screen_snooze();

void create_screen_settings();
void tick_screen_settings();

void create_screen_radio();
void tick_screen_radio();

void create_screen_boot();
void tick_screen_boot();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/