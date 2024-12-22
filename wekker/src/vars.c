

#include <string.h>
#include "vars.h"

char boot_ip_text[20] = { 0 };
char text_radio_station[100] = { 0 };
char text_radio_stream_title[100] = { 0 };

char text_snooze[10] = { 0 };
char text_alarm_time[10] = { 0 };
char text_time[10] = { 0 };


int32_t boot_progress;
bool alarm_set;
bool alarm_indicator=0;

char alarm_symbol[10] = { 0 };
char text_alarm_volume[10] = { 0 };

char text_radio_volume[10] = { 0 };
char text_radio_title[100] = { 0 };

const char *get_var_text_radio_title() {
    return text_radio_title;
}

void set_var_text_radio_title(const char *value) {
    strncpy(text_radio_title, value, sizeof(text_radio_title) / sizeof(char));
    text_radio_title[sizeof(text_radio_title) / sizeof(char) - 1] = 0;
}




const char *get_var_text_radio_volume() {
    return text_radio_volume;
}

void set_var_text_radio_volume(const char *value) {
    strncpy(text_radio_volume, value, sizeof(text_radio_volume) / sizeof(char));
    text_radio_volume[sizeof(text_radio_volume) / sizeof(char) - 1] = 0;
}

const char *get_var_text_alarm_volume() {
    return text_alarm_volume;
}

void set_var_text_alarm_volume(const char *value) {
    strncpy(text_alarm_volume, value, sizeof(text_alarm_volume) / sizeof(char));
    text_alarm_volume[sizeof(text_alarm_volume) / sizeof(char) - 1] = 0;
}



bool get_var_alarm_indicator() {
    return alarm_indicator;
}

void set_var_alarm_indicator(bool value) {
    alarm_indicator = value;
}

const char *get_var_alarm_symbol() {
    return alarm_symbol;
}

void set_var_alarm_symbol(const char *value) {
    strncpy(alarm_symbol, value, sizeof(alarm_symbol) / sizeof(char));
    alarm_symbol[sizeof(alarm_symbol) / sizeof(char) - 1] = 0;
}


bool get_var_alarm_set() {
    return alarm_set;
}

void set_var_alarm_set(bool value) {
    alarm_set = value;
}


const char *get_var_boot_ip_text() {
    return boot_ip_text;
}

void set_var_boot_ip_text(const char *value) {
    strncpy(boot_ip_text, value, sizeof(boot_ip_text) / sizeof(char));
    boot_ip_text[sizeof(boot_ip_text) / sizeof(char) - 1] = 0;
}

int32_t get_var_boot_progress() {
    return boot_progress;
}

void set_var_boot_progress(int32_t value) {
    boot_progress = value;
}



const char *get_var_text_radio_stream_title() {
    return text_radio_stream_title;
}

void set_var_text_radio_stream_title(const char *value) {
    strncpy(text_radio_stream_title, value, sizeof(text_radio_stream_title) / sizeof(char));
    text_radio_stream_title[sizeof(text_radio_stream_title) / sizeof(char) - 1] = 0;
}


const char *get_var_text_radio_station() {
    return text_radio_station;
}

void set_var_text_radio_station(const char *value) {
    strncpy(text_radio_station, value, sizeof(text_radio_station) / sizeof(char));
    text_radio_station[sizeof(text_radio_station) / sizeof(char) - 1] = 0;
}


const char *get_var_text_snooze() {
    return text_snooze;
}

void set_var_text_snooze(const char *value) {
    strncpy(text_snooze, value, sizeof(text_snooze) / sizeof(char));
    text_snooze[sizeof(text_snooze) / sizeof(char) - 1] = 0;
}

const char *get_var_text_alarm_time() {
    return text_alarm_time;
}

void set_var_text_alarm_time(const char *value) {
    strncpy(text_alarm_time, value, sizeof(text_alarm_time) / sizeof(char));
    text_alarm_time[sizeof(text_alarm_time) / sizeof(char) - 1] = 0;
}

const char *get_var_text_time() {
    return text_time;
}

void set_var_text_time(const char *value) {
    strncpy(text_time, value, sizeof(text_time) / sizeof(char));
    text_time[sizeof(text_time) / sizeof(char) - 1] = 0;
}

