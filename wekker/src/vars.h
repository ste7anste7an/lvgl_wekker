#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_TEXT_RADIO_STATION = 0,
    FLOW_GLOBAL_VARIABLE_TEXT_SNOOZE = 1,
    FLOW_GLOBAL_VARIABLE_TEXT_ALARM_TIME = 2,
    FLOW_GLOBAL_VARIABLE_TEXT_TIME = 3,
    FLOW_GLOBAL_VARIABLE_BOOT_IP_TEXT = 4,
    FLOW_GLOBAL_VARIABLE_BOOT_PROGRESS = 5,
    FLOW_GLOBAL_VARIABLE_ALARM_SET = 6,
    FLOW_GLOBAL_VARIABLE_ALARM_SYMBOL = 7,
    FLOW_GLOBAL_VARIABLE_TEXT_ALARM_VOLUME = 8,
    FLOW_GLOBAL_VARIABLE_TEXT_RADIO_VOLUME = 9,
    FLOW_GLOBAL_VARIABLE_ALARM_INDICATOR = 10,
    FLOW_GLOBAL_VARIABLE_TEXT_RADIO_TITLE = 11
};

// Native global variables

extern const char *get_var_text_radio_station();
extern void set_var_text_radio_station(const char *value);
extern const char *get_var_text_snooze();
extern void set_var_text_snooze(const char *value);
extern const char *get_var_text_alarm_time();
extern void set_var_text_alarm_time(const char *value);
extern const char *get_var_text_time();
extern void set_var_text_time(const char *value);
extern const char *get_var_boot_ip_text();
extern void set_var_boot_ip_text(const char *value);
extern int32_t get_var_boot_progress();
extern void set_var_boot_progress(int32_t value);
extern bool get_var_alarm_set();
extern void set_var_alarm_set(bool value);
extern const char *get_var_alarm_symbol();
extern void set_var_alarm_symbol(const char *value);
extern const char *get_var_text_alarm_volume();
extern void set_var_text_alarm_volume(const char *value);
extern const char *get_var_text_radio_volume();
extern void set_var_text_radio_volume(const char *value);
extern bool get_var_alarm_indicator();
extern void set_var_alarm_indicator(bool value);
extern const char *get_var_text_radio_title();
extern void set_var_text_radio_title(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/