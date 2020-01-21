#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

/**
 * Customization variables
 */
#define SCREEN_GREETING "Hola Poque!"


/**
 * Do not edit below this point
 */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

// Init OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Init RTC
RTC_DS1307 RTC;

void setup() {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay();

  Wire.begin();
  RTC.begin();
  // This will reflect the time that your sketch was compiled
  RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {  
  // Clear display
  display.clearDisplay();  
  // Start at top-left corner
  display.setCursor(0,0);

  // Update greeting
  update_greeting();

  // Update time
  update_time();

  // Display & delay
  display.display();
  delay(1000);
}

void update_greeting(void) {

  // Configure text; Normal 1:1 pixel scale
  display.setTextSize(1);
  // Draw 'inverse' text
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
  // Display greeting
  display.println(F(SCREEN_GREETING));
}

void update_time(void) {
  // Get time
  DateTime now = RTC.now();

  // Configure text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Print time 
  char buf3[] = "DDD, MMM DD YYYY";
  display.println(now.toString(buf3));
  char buf1[] = "hh:mm:ss";
  display.setTextSize(2);
  display.println(now.toString(buf1));
}
