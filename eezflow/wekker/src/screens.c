#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_alarm_alarm_on_off(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_alarm_set(value);
        }
    }
}

void create_screen_alarm() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.alarm = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // alarm_alarm_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.alarm_alarm_time = obj;
            lv_obj_set_pos(obj, 72, 126);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &ui_font_lcd_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffe12727), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // alarm_btn_hr_plus
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.alarm_btn_hr_plus = obj;
            lv_obj_set_pos(obj, 21, 70);
            lv_obj_set_size(obj, 84, 50);
            lv_obj_add_event_cb(obj, action_alarm_hour_plus_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "HRS +");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 21, 171);
            lv_obj_set_size(obj, 84, 50);
            lv_obj_add_event_cb(obj, action_alarm_hour_min_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "HRS -");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 121, 71);
            lv_obj_set_size(obj, 83, 50);
            lv_obj_add_event_cb(obj, action_alarm_minutes_plus_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_alarm_minutes_plus_10_action, LV_EVENT_LONG_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "MIN +");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 122, 171);
            lv_obj_set_size(obj, 82, 50);
            lv_obj_add_event_cb(obj, action_alarm_minutes_min_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_alarm_minutes_min_10_action, LV_EVENT_LONG_PRESSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "MIN -");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 220, 14);
            lv_obj_set_size(obj, 80, 40);
            lv_obj_add_event_cb(obj, action_alarm_back_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Back");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 17, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "OFF");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 142, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "ON");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 35, -2);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Alarm");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // alarm_on_off
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.alarm_on_off = obj;
            lv_obj_set_pos(obj, 76, 34);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_add_event_cb(obj, action_alarm_on_off_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_alarm_alarm_on_off, LV_EVENT_ALL, 0);
        }
        {
            // alarm_vol_up
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.alarm_vol_up = obj;
            lv_obj_set_pos(obj, 220, 72);
            lv_obj_set_size(obj, 83, 50);
            lv_obj_add_event_cb(obj, action_alarm_vol_up_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "VOL +");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // alarm_vol_down
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.alarm_vol_down = obj;
            lv_obj_set_pos(obj, 221, 172);
            lv_obj_set_size(obj, 83, 50);
            lv_obj_add_event_cb(obj, action_alarm_vol_down_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "VOL -");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // alarm_alarm_volume
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.alarm_alarm_volume = obj;
            lv_obj_set_pos(obj, 234, 125);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &ui_font_lcd_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffe12727), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_alarm() {
    {
        const char *new_val = get_var_text_alarm_time();
        const char *cur_val = lv_label_get_text(objects.alarm_alarm_time);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.alarm_alarm_time;
            lv_label_set_text(objects.alarm_alarm_time, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_alarm_set();
        bool cur_val = lv_obj_has_state(objects.alarm_on_off, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.alarm_on_off;
            if (new_val) lv_obj_add_state(objects.alarm_on_off, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.alarm_on_off, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_alarm_volume();
        const char *cur_val = lv_label_get_text(objects.alarm_alarm_volume);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.alarm_alarm_volume;
            lv_label_set_text(objects.alarm_alarm_volume, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 27, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Alarm:");
        }
        {
            // main_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_time = obj;
            lv_obj_set_pos(obj, 37, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, action_main_time_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &ui_font_lcd_large, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffc61c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main_alarm
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_alarm = obj;
            lv_obj_set_pos(obj, 27, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, action_main_alarm_action, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &ui_font_lcd_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffc61c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main_radio_station
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_radio_station = obj;
            lv_obj_set_pos(obj, 22, 83);
            lv_obj_set_size(obj, LV_PCT(80), LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, action_main_radio_action, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main_snooze
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_snooze = obj;
            lv_obj_set_pos(obj, 220, 33);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, action_main_snooze_action, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffc61c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 221, 14);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Snooze:");
        }
        {
            // main_alarm_set
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_alarm_set = obj;
            lv_obj_set_pos(obj, 120, 29);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // main_radio_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_radio_title = obj;
            lv_obj_set_pos(obj, 22, 115);
            lv_obj_set_size(obj, LV_PCT(80), LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 150, 13);
            lv_obj_set_size(obj, 54, 60);
            lv_obj_add_event_cb(obj, action_main_alarm_off, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "off");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    {
        const char *new_val = get_var_text_time();
        const char *cur_val = lv_label_get_text(objects.main_time);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_time;
            lv_label_set_text(objects.main_time, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_alarm_time();
        const char *cur_val = lv_label_get_text(objects.main_alarm);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_alarm;
            lv_label_set_text(objects.main_alarm, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_radio_station();
        const char *cur_val = lv_label_get_text(objects.main_radio_station);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_radio_station;
            lv_label_set_text(objects.main_radio_station, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_snooze();
        const char *cur_val = lv_label_get_text(objects.main_snooze);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_snooze;
            lv_label_set_text(objects.main_snooze, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_alarm_set();
        bool cur_val = lv_obj_has_flag(objects.main_alarm_set, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.main_alarm_set;
            if (new_val) lv_obj_add_flag(objects.main_alarm_set, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.main_alarm_set, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_alarm_symbol();
        const char *cur_val = lv_label_get_text(objects.main_alarm_set);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_alarm_set;
            lv_label_set_text(objects.main_alarm_set, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_radio_title();
        const char *cur_val = lv_label_get_text(objects.main_radio_title);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.main_radio_title;
            lv_label_set_text(objects.main_radio_title, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_snooze() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.snooze = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // snooze_snooze_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.snooze_snooze_time = obj;
            lv_obj_set_pos(obj, 84, 44);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &ui_font_lcd_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffc61c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // snooze_btn_min_plus
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.snooze_btn_min_plus = obj;
            lv_obj_set_pos(obj, 79, 105);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_snooze_minutes_plus_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // snooze_min_plus
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.snooze_min_plus = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "MIN +");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // snooze_btn_min_min
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.snooze_btn_min_min = obj;
            lv_obj_set_pos(obj, 79, 164);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_snooze_minutes_min_action, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "MIN -");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 72, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Snooze");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 203, 12);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_snooze_back_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Back");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_snooze() {
    {
        const char *new_val = get_var_text_snooze();
        const char *cur_val = lv_label_get_text(objects.snooze_snooze_time);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.snooze_snooze_time;
            lv_label_set_text(objects.snooze_snooze_time, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // settings_slider_backlight
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.settings_slider_backlight = obj;
            lv_obj_set_pos(obj, 43, 185);
            lv_obj_set_size(obj, 236, 29);
            lv_slider_set_range(obj, 1, 100);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_settings_backlight_action, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 191, 28);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_snooze_back_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Back");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 43, 147);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Intensity");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_settings() {
}

void create_screen_radio() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.radio = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 258, 12);
            lv_obj_set_size(obj, 49, 50);
            lv_obj_add_event_cb(obj, action_snooze_back_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Back");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // radio_vol_up
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.radio_vol_up = obj;
            lv_obj_set_pos(obj, 217, 167);
            lv_obj_set_size(obj, 83, 50);
            lv_obj_add_event_cb(obj, action_radio_vol_up_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "VOL +");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // radio_vol_down
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.radio_vol_down = obj;
            lv_obj_set_pos(obj, 35, 166);
            lv_obj_set_size(obj, 83, 50);
            lv_obj_add_event_cb(obj, action_radio_vol_down_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "VOL -");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // alarm_alarm_volume_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.alarm_alarm_volume_1 = obj;
            lv_obj_set_pos(obj, 140, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &ui_font_lcd_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffe12727), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // radio_station
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.radio_station = obj;
            lv_obj_set_pos(obj, 30, 88);
            lv_obj_set_size(obj, LV_PCT(80), LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_length(obj, 300, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 21, 20);
            lv_obj_set_size(obj, 56, 51);
            lv_obj_add_event_cb(obj, action_radio_station_prev_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "<<");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 110, 20);
            lv_obj_set_size(obj, 56, 51);
            lv_obj_add_event_cb(obj, action_radio_station_next_action, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, ">>");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // radio_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.radio_title = obj;
            lv_obj_set_pos(obj, 30, 120);
            lv_obj_set_size(obj, LV_PCT(80), LV_SIZE_CONTENT);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
            lv_label_set_text(obj, "");
        }
    }
}

void tick_screen_radio() {
    {
        const char *new_val = get_var_text_radio_volume();
        const char *cur_val = lv_label_get_text(objects.alarm_alarm_volume_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.alarm_alarm_volume_1;
            lv_label_set_text(objects.alarm_alarm_volume_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_radio_station();
        const char *cur_val = lv_label_get_text(objects.radio_station);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.radio_station;
            lv_label_set_text(objects.radio_station, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_text_radio_title();
        const char *cur_val = lv_label_get_text(objects.radio_title);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.radio_title;
            lv_label_set_text(objects.radio_title, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_boot() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.boot = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 33, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Connecting to wifi");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 33, 104);
            lv_obj_set_size(obj, 226, 32);
            lv_bar_set_range(obj, 0, 120);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 34, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_boot() {
    {
        const char *new_val = get_var_boot_ip_text();
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_alarm();
    create_screen_main();
    create_screen_snooze();
    create_screen_settings();
    create_screen_radio();
    create_screen_boot();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_alarm,
    tick_screen_main,
    tick_screen_snooze,
    tick_screen_settings,
    tick_screen_radio,
    tick_screen_boot,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
