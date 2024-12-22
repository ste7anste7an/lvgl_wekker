#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_main_time_action(lv_event_t * e);
extern void action_main_alarm_action(lv_event_t * e);
extern void action_main_snooze_action(lv_event_t * e);
extern void action_alarm_hour_plus_action(lv_event_t * e);
extern void action_alarm_hour_min_action(lv_event_t * e);
extern void action_alarm_minutes_plus_action(lv_event_t * e);
extern void action_alarm_minutes_min_action(lv_event_t * e);
extern void action_snooze_minutes_min_action(lv_event_t * e);
extern void action_snooze_minutes_plus_action(lv_event_t * e);
extern void action_alarm_on_off_action(lv_event_t * e);
extern void action_alarm_back_action(lv_event_t * e);
extern void action_snooze_back_action(lv_event_t * e);
extern void action_settings_back_action(lv_event_t * e);
extern void action_settings_backlight_action(lv_event_t * e);
extern void action_main_radio_action(lv_event_t * e);
extern void action_radio_back_action(lv_event_t * e);
extern void action_alarm_minutes_plus_10_action(lv_event_t * e);
extern void action_alarm_minutes_min_10_action(lv_event_t * e);
extern void action_alarm_vol_up_action(lv_event_t * e);
extern void action_alarm_vol_down_action(lv_event_t * e);
extern void action_radio_vol_up_action(lv_event_t * e);
extern void action_radio_vol_down_action(lv_event_t * e);
extern void action_radio_station_prev_action(lv_event_t * e);
extern void action_radio_station_next_action(lv_event_t * e);
extern void action_main_alarm_off(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/