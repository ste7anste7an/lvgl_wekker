#include "ui.h"
#include "actions.h"
#include "vars.h"
//#include "WString.h"

extern uint8_t alarm_indicator;
extern uint8_t alarm_hours;
extern uint8_t alarm_minutes;
extern uint8_t alarm_volume;
extern uint8_t snooze_minutes;

extern uint8_t cur_volume;
extern uint8_t max_volume;
extern uint8_t radio_station;
extern uint8_t max_stations;
extern bool alarm_off_pressed;
extern uint8_t alarm_volume;
extern uint8_t radio_volume;

//extern String station_names[];

// void audio_set_volume(uint8_t cur_volume); 

void update_alarm_volume() {
  char tmp_str[10] = { 0 };
  sprintf(tmp_str, "%2d", alarm_volume);
  set_var_text_alarm_volume(tmp_str);
}


void update_radio_volume() {
  char tmp_str[10] = { 0 };
  sprintf(tmp_str, "%2d", cur_volume);
  set_var_text_radio_volume(tmp_str);
}


void update_alarm() {
  char tmp_str[20] = { 0 };
  sprintf(tmp_str, "%02d:%02d", alarm_hours, alarm_minutes);
  set_var_text_alarm_time(tmp_str);
}

void update_snooze() {
  char tmp_str[20] = { 0 };
  sprintf(tmp_str, "%2d min", snooze_minutes);
  set_var_text_snooze(tmp_str);
}


extern void action_main_time_action(lv_event_t * e){
    lv_log("time clicked\r\n");
     loadScreen(SCREEN_ID_SETTINGS);
}

extern void action_main_alarm_action(lv_event_t * e){
    lv_log("alarm clicked");
    lv_event_code_t code = lv_event_get_code(e);
    lv_log("event: %d\r\n",code);
    loadScreen(SCREEN_ID_ALARM);
}

extern void action_main_snooze_action(lv_event_t * e){
    lv_log("snooze clicked");
    lv_event_code_t code = lv_event_get_code(e);
    lv_log("event: %d\r\n",code);
    loadScreen(SCREEN_ID_SNOOZE);


}

extern void action_alarm_back_action(lv_event_t * e){
    loadScreen(SCREEN_ID_MAIN);
}

extern void action_snooze_back_action(lv_event_t * e){
    loadScreen(SCREEN_ID_MAIN);
}

extern void action_settings_back_action(lv_event_t * e){
   loadScreen(SCREEN_ID_MAIN);

}
extern void action_settings_backlight_action(lv_event_t * e){
    lv_obj_t *obj = lv_event_get_current_target(e);
    int32_t val =  lv_bar_get_value(obj);
    lv_log("bar val: %d\r\n",val);
    analogWrite(33, val * 255 / 100);
}

void action_alarm_vol_up_action(lv_event_t *e) {
  if (alarm_volume<max_volume) {
    alarm_volume++;
    update_alarm_volume();
  }
    // TODO: Implement action alarm_vol_up_action here
}

void action_alarm_vol_down_action(lv_event_t *e) {
  if (alarm_volume>0) {
    alarm_volume--;
    update_alarm_volume();
  }
    // TODO: Implement action alarm_vol_down_action here
}

extern void action_alarm_hour_plus_action(lv_event_t * e){
  lv_log("hrs plus clicked\r\n");
  if (alarm_hours==23) alarm_hours=0;
  else alarm_hours++;
  update_alarm();

}

extern void action_alarm_hour_min_action(lv_event_t * e){
  lv_log("hrs min clicked\r\n");
  if (alarm_hours==0) alarm_hours=23;
  else alarm_hours--;
  update_alarm();
}

extern void action_alarm_minutes_plus_action(lv_event_t * e){
  lv_log("min plus clicked\r\n");
  if (alarm_minutes==59) alarm_minutes=0;
  else alarm_minutes++;
  update_alarm();
}

extern void action_alarm_minutes_min_action(lv_event_t * e){
  lv_log("min min clicked\r\n");
  if (alarm_minutes==0) alarm_minutes=59;
  else alarm_minutes--;
  update_alarm();
}

void action_alarm_minutes_plus_10_action(lv_event_t *e) {
  int round_minutes=((alarm_minutes + 9) / 10) * 10;
  if (round_minutes>50) alarm_minutes=0;
  else alarm_minutes=round_minutes;
  update_alarm();
}


void action_alarm_minutes_min_10_action(lv_event_t *e) {
 int round_minutes=((alarm_minutes + 9) / 10) * 10;
  if (round_minutes<10) alarm_minutes=50;
  else alarm_minutes=round_minutes-10;
  update_alarm();
}


extern void action_snooze_minutes_min_action(lv_event_t * e){
  if (snooze_minutes>4) snooze_minutes--;
  update_snooze();

}

extern void action_snooze_minutes_plus_action(lv_event_t * e){
if (snooze_minutes<20) snooze_minutes++;
  update_snooze();

}

extern void action_alarm_on_off_action(lv_event_t * e){
  alarm_indicator=! get_var_alarm_set();
  set_var_alarm_indicator(alarm_indicator);
  printf("alarm_indicator = %d\n",alarm_indicator);

}


void action_main_alarm_off(lv_event_t *e) {
    // TODO: Implement action main_alarm_off here
    alarm_off_pressed = true;
}


extern void action_main_radio_action(lv_event_t * e){
  loadScreen(SCREEN_ID_RADIO);
}

void action_radio_back_action(lv_event_t *e) {
    loadScreen(SCREEN_ID_MAIN);
}


void action_radio_vol_up_action(lv_event_t *e) {
    // TODO: Implement action radio_vol_up_action here
    if (cur_volume<max_volume) {
    cur_volume++;
    update_radio_volume();
  }
}


void action_radio_vol_down_action(lv_event_t *e) {
    // TODO: Implement action radio_vol_down_action here
    if (cur_volume>0) {
    cur_volume--;
    update_radio_volume();
  }
}


void action_radio_station_next_action(lv_event_t *e) {
    // TODO: Implement action radio_station_prev_action here
    if (radio_station<(max_stations-1)) {
      radio_station++;
//      set_var_text_radio_station(station_names[radio_station]);
    }
}

void action_radio_station_prev_action(lv_event_t *e) {
    // TODO: Implement action radio_station_next_action here
    if (radio_station>0) {
      radio_station--;
//      set_var_text_radio_station(station_names[radio_station]);
    }
}

