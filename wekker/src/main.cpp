#include <Arduino.h>

/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/integration/framework/arduino.html  */

#include <lvgl.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#include "ui.h"
#include "vars.h"
#endif
#define TOUCH

#include <time.h>
const char* ntpServer = "pool.ntp.org";  // NTP server
const long  gmtOffset_sec = 1*3600;           // GMT offset in seconds
const int   daylightOffset_sec = 0;   // Daylight offset in seconds
struct tm timeinfo;
struct tm timealarm;

uint8_t alarm_hours=7;
uint8_t alarm_minutes=0;
uint8_t snooze_minutes=5;
uint8_t radio_volume=5;
uint8_t alarm_volume=15;

bool alarm_is_set=false;
bool alarm_is_triggered=false;
bool alarm_is_snoozing=false;
bool alarm_off_pressed=false;
static lv_timer_t * flash_time_timer = NULL; // declare a timer that used to get time info 
static lv_timer_t * snooze_timer = NULL; // declare a timer that used to get time info 

void snooze_timer_callback(lv_timer_t * timer);

#include <Preferences.h>
#include <SPI.h>
#include <WiFi.h>
#include "Audio.h" //see my repository at github "https://github.com/schreibfaul1/ESP32-audioI2S"

// I2S pins
#define I2S_DOUT      19
#define I2S_BCLK      20
#define I2S_LRC       21
#define IR_RECV       22


Preferences pref;
Audio audio;
// void audio_set_volume(uint8_t cur_volume);

String ssid =     "xxx";
String password = "xxxx";

String stations[] ={
        "https://icecast.omroep.nl/radio4-bb-mp3",
        "http://192.168.1.102:8000/mixkit-city-alert-siren-loop-1008.mp3",
        "https://icecast.vrtcdn.be/klara-high.mp3",
         "https://as-hls-ww-live.akamaized.net/pool_904/live/ww/bbc_radio_three/bbc_radio_three.isml/bbc_radio_three-audio%3d96000.norewind.m3u8",
         "https://wwfm.streamguys1.com/live-mp3",
};

// "https://stream.radiofrance.fr/francemusiquebaroque/francemusiquebaroque_hifi.m3u8",
//  "https://stream.radiofrance.fr/francemusiqueconcertsradiofrance/francemusiqueconcertsradiofrance_hifi.m3u8",

String station_names[] ={
        "NPO Radio 4",
        "alarm",
        "VRT Klara",
        "BBC 3 Classic",
        "Classical music stream",
        
};

uint8_t max_volume   = 21;
uint8_t max_stations = 3;   //will be set later
uint8_t cur_station  = 0;   //current station(nr), will be set later
uint8_t cur_volume   = 2;   //will be set from stored preferences
uint8_t old_volume   = 2;
uint8_t radio_station=0;
uint8_t old_radio_station=0;

char info_id3[100];

TFT_eSPI tft = TFT_eSPI(); 

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 *Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 *as the examples and demos are now part of the main LVGL library. */

//#include <examples/lv_examples.h>
//#include <demos/lv_demos.h>
#define TOUCH_MISO 19
#define TOUCH_MOSI 23
#define TOUCH_SCLK 18

#define TOUCH_CS 26
// used for screen: 
// io12, io13, io14, io15, io26,io27, io32, io33


//XPT2046_Touchscreen ts(TOUCH_CS, -1);
#define TOUCH_CALIB_X_MIN 200
#define TOUCH_CALIB_X_MAX 3800
#define TOUCH_CALIB_Y_MIN 200
#define TOUCH_CALIB_Y_MAX 3800
/*Set to your screen resolution and rotation*/
#define TFT_HOR_RES   240
#define TFT_VER_RES   320
#define TFT_ROTATION  LV_DISPLAY_ROTATION_270

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

#if LV_USE_LOG != 0
void my_print( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

/* LVGL calls it when a rendered image needs to copied to the display*/
void my_disp_flush( lv_display_t *disp, const lv_area_t *area, uint8_t * px_map)
{
    /*Copy `px map` to the `area`*/
    
    /*For example ("my_..." functions needs to be implemented by you)
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    my_set_window(area->x1, area->y1, w, h);
    my_draw_bitmaps(px_map, w * h);
     */

    /*Call it to tell LVGL you are ready*/
    lv_display_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_t *indev_driver, lv_indev_data_t *data) {

#ifdef TOUCH
    uint16_t x_raw,y_raw;
    if (tft.getTouchRaw(&x_raw, &y_raw) && tft.getTouchRawZ()>500) {
        int16_t x = map(x_raw, TOUCH_CALIB_X_MIN, TOUCH_CALIB_X_MAX, 0, TFT_HOR_RES);
        int16_t y = map(y_raw, TOUCH_CALIB_Y_MIN, TOUCH_CALIB_Y_MAX, 0, TFT_VER_RES);

    //     // Clip values to screen size
        x = constrain(x, 0, TFT_HOR_RES - 1);
        y = constrain(y, 0, TFT_VER_RES - 1);

        data->point.x = x;
        data->point.y = y;
        Serial.printf("x_raw=%5d, y_raw=%5d, x=%5d, y=%5d, z=%5d\r\n",x_raw,y_raw,x,y,tft.getTouchRawZ());
        data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_RELEASED; // No touch detected

    }
#endif
}

void play_alarm() {
  if (alarm_is_triggered) {
    Serial.println("play alarm");
    audio.setVolume(alarm_volume); 
    //audio.connecttohost("http://192.168.1.102:8000/mixkit-city-alert-siren-loop-1008.mp3");
    audio.connecttohost("http://192.168.1.102:8000/Ring-sound-effect.mp3");
    
  }
}


void get_time()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void snooze_timer_callback(lv_timer_t * timer)
{
  snooze_timer    = lv_timer_create(snooze_timer_callback, 1000*snooze_minutes, NULL);
  play_alarm();

}


void flash_time_timer_callback(lv_timer_t * timer)
{
  static unsigned int counter = 0;
  char current_time[16];
  get_time();
  memset(current_time, 0, sizeof(current_time));
  sprintf(current_time, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  Serial.printf("alarm trigger %d, get_alarm_indicator():%d, hr: %d, min: %d\r\n",alarm_is_triggered,get_var_alarm_indicator() ,alarm_hours,alarm_minutes);
  if (alarm_is_triggered==false && get_var_alarm_indicator() && alarm_hours==timeinfo.tm_hour && alarm_minutes==timeinfo.tm_min) {
    Serial.println("alarm gaat af");
    alarm_is_triggered=true;
    //snooze_timer    = lv_timer_create(snooze_timer_callback, 1000*snooze_minutes, NULL);
    play_alarm();
  }
  set_var_text_time(current_time);
  
}



void connect_to_wifi()
{
   loadScreen(SCREEN_ID_BOOT);
   WiFi.begin(ssid.c_str(), password.c_str());
   int progress=0;
   while (WiFi.status() != WL_CONNECTED){
        lv_timer_handler(); /* let the GUI do its work */
        ui_tick();
        delay(20);
        progress++;
        Serial.printf("progress %d\r\n",progress/100);
        set_var_boot_progress(progress);
    }
   // log_i("Connect to %s", WiFi.SSID().c_str());
   // log_i("Connect to %s", WiFi.localIP().c_str());
   Serial.println(WiFi.localIP());
    set_var_boot_ip_text(WiFi.localIP().toString().c_str());
    for (int i=0; i<300; i++) {}
      delay(30);
        lv_timer_handler(); /* let the GUI do its work */
        ui_tick();
      
    loadScreen(SCREEN_ID_MAIN);
}


void audio_set_volume(uint8_t cur_volume)
{
  audio.setVolume(cur_volume); 
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
    return millis();
}

void replace_newlines(char *str, char replacement) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (*str == '\n') {
            *str = replacement;
        }
        if (*str<32 or *str>127) {
          *str = '_';
        }
        str++;
    }
}


void loop_ui_check(){
  if (cur_volume!=old_volume) {
    audio.setVolume(cur_volume);
    old_volume=cur_volume;
    //audio_id3data(info_id3);
    //  Serial.print("id3data     ");Serial.println(info_id3);
  }
  if (cur_station!=radio_station) {
    cur_station=radio_station;
    audio.connecttohost(stations[cur_station].c_str());
    set_var_text_radio_station(station_names[cur_station].c_str()); 
    set_var_text_radio_title("");
  }
  if (alarm_off_pressed) {
    alarm_off_pressed=false;
    audio.connecttohost(stations[cur_station].c_str());
    audio.setVolume(cur_volume);
    set_var_text_radio_station(station_names[cur_station].c_str()); 
    set_var_text_radio_title("");
    alarm_is_triggered=false;
    /*
    if (snooze_timer) {
          lv_timer_del(snooze_timer);
          snooze_timer = NULL;  // Set to NULL to avoid dangling pointer
    }
    */
  }
}


void setup()
{
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.begin( 115200 );
    Serial.println( LVGL_Arduino );


    max_stations= sizeof(stations)/sizeof(stations[0]); log_i("max stations %i", max_stations);

    pref.begin("WebRadio", false);  // instance of preferences for defaults (station, volume ...)
    if(pref.getShort("volume", 1000) == 1000){ // if that: pref was never been initialized
        pref.putShort("volume", 10);
        pref.putShort("station", 0);
    }
    else{ // get the stored values
        cur_station = pref.getShort("station");
        cur_volume = pref.getShort("volume");
    }
  
    lv_init();

    /*Set a tick source so that LVGL will know how much time elapsed. */
    lv_tick_set_cb(my_tick);

    /* register print function for debugging */
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print );
#endif

    lv_display_t * disp;
#if LV_USE_TFT_ESPI
    /*TFT_eSPI can be enabled lv_conf.h to initialize the display in a simple way*/
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    //lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
    
    lv_display_set_rotation(disp, TFT_ROTATION);

#else
    /*Else create a display yourself*/
    disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif

    /*Initialize the (dummy) input device driver*/
    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);

    ui_init();
    set_var_text_alarm_time("23:40");
    set_var_text_snooze("5 min");
    set_var_alarm_set(alarm_is_set);
    set_var_alarm_symbol(LV_SYMBOL_BELL);
    Serial.println("ui_init done");
    connect_to_wifi();
    Serial.println("wifi setup done");
          lv_timer_handler(); /* let the GUI do its work */
        ui_tick();
  
    loadScreen(SCREEN_ID_MAIN);
          lv_timer_handler(); /* let the GUI do its work */
        ui_tick();
  
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(cur_volume); // 0...21
    audio.connecttohost(stations[cur_station].c_str());
    set_var_text_radio_station(station_names[cur_station].c_str());

    Serial.println("audio done");
    
    flash_time_timer    = lv_timer_create(flash_time_timer_callback, 371, NULL);
    // lv_obj_t *label = lv_label_create( lv_screen_active() );
    // lv_label_set_text( label, "Hello Arduino, I'm LVGL!" );
    // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
    //loadScreen(SCREEN_ID_ALARM);
    Serial.println( "Setup done" );
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    ui_tick();
    audio.loop();
    //delay(5); /* let this time pass */
    loop_ui_check();
 
}


void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
    // if alarm still running restart
    if (alarm_is_triggered) {
      audio.setVolume(alarm_volume); 
      //audio.connecttohost("http://192.168.1.102:8000/mixkit-city-alert-siren-loop-1008.mp3");
      audio.connecttohost("http://192.168.1.102:8000/Ring-sound-effect.mp3");
    }

}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}


void audio_showstreamtitle(const char *info){
    char tmp_title[200];
    Serial.print("streamtitle ");Serial.println(info);
    strcpy(tmp_title,info);
    replace_newlines(tmp_title, ' ');
    set_var_text_radio_title(tmp_title);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
