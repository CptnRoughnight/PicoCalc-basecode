#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include "i2ckbd.h"


TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 320

const int SD_MISO = 16;  // AKA SPI RX
const int SD_MOSI = 19;  // AKA SPI TX
const int SD_CS = 17;
const int SD_SCK =  18;

const uint LEDPIN = 25;


File root;

void setup(void) {
//  Serial.begin(115200);  

  tft.init();

  tft.fillScreen(TFT_BLACK);
  tft.invertDisplay( true ); // Where i is true or false
  

  gpio_init(LEDPIN);
  gpio_set_dir(LEDPIN,GPIO_OUT);
  gpio_put(LEDPIN,1);
  sleep_ms(5000);
  gpio_put(LEDPIN,0);

  // Ensure the SPI pinout the SD card is connected to is configured properly
  // Select the correct SPI based on _MISO pin for the RP2040
  bool sdInitialized = false;
  SPI.setRX(SD_MISO);
  SPI.setTX(SD_MOSI);
  SPI.setSCK(SD_SCK);
  sdInitialized = SD.begin(SD_CS);


  if (!sdInitialized) {
    Serial.println("initialization failed!");
    
  } else
  {
    Serial.println("initialization done.");

    root = SD.open("/");

    printDirectory(root, 0);

    Serial.println("done!");
  }
  
  init_i2c_kbd();

}

void loop() {
   // Binary inversion of colours
  
  tft.setTextColor(random(5000));
  for (int x=0;x<(SCREEN_WIDTH);x+=8)
   for (int y=0;y<SCREEN_HEIGHT;y+=8)
    tft.drawChar('#',x,y);

  int key=-1;
  char strBuf[50];
  while (key!=KEY_ENTER)
  {
    key = read_i2c_kbd();
    sprintf(strBuf, "key  %c = %i",(char)key,key);
   /* if (key!=-1)
      Serial.println(strBuf);*/
    //tft.drawChar((uint16_t)key,100,100);
    tft.drawString(strBuf,100,100);
  }
  
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry = dir.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.print(entry.size(), DEC);
      time_t cr = entry.getCreationTime();
      time_t lw = entry.getLastWrite();
      struct tm* tmstruct = localtime(&cr);
      Serial.printf("\tCREATION: %d-%02d-%02d %02d:%02d:%02d", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
      tmstruct = localtime(&lw);
      Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
    }
    entry.close();
  }
}

