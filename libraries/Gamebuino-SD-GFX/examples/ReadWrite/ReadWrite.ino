#include <SD.h>
#include <SPI.h>
#include <Adafruit_ZeroDMA.h>
#include <Adafruit_ASFcore.h>
#include <Adafruit_GFX.h>
#include <Image.h>
#include <Adafruit_ST7735.h>
#include <Gamebuino-SD-GFX.h>


#define TFT_CS    (30)
#define TFT_RST   (0)
#define TFT_DC    (31)
#define SD_CS     (26)
#define BTN_CS    (25)
#define NEOPIX    (38)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Image image = Image(16, 16, ColorMode::RGB565);
Image imageIndex = Image(16, 16, ColorMode::INDEX);

void setup() {
  SerialUSB.begin(9600);
  //while (!SerialUSB);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setColor(BLACK);
  tft.fillScreen();

  Gamebuino_SD_GFX::debugOutput = &tft;
  
  if (!SD.begin(SD_CS)) {
    tft.setColor(RED, BLACK);
    tft.println("FAILED");
    delay(1000);
  }
  else {
    tft.setColor(GREEN, BLACK);
    tft.println("OK");
  }
/*
  //RGB888 BITMAP
  tft.setColor(WHITE, BLACK);

  Gamebuino_SD_GFX::readImage(image, "RGB888.BMP");
  SerialUSB.println(image._width);
  SerialUSB.println(image._height);
  for (int i = 0; i < (image._width * image._height); i++) {
    SerialUSB.print(image._buffer[i], HEX);
  }
  tft.drawImage(120, 30, image, 32, 32);

  Gamebuino_SD_GFX::writeImage(image, "WRITE888.BMP");
*/
  //INDEX4 BITMAP
   tft.setColor(WHITE, BLACK);

  Gamebuino_SD_GFX::readImage(imageIndex, "INDEX4.BMP");
  SerialUSB.println(imageIndex._width);
  SerialUSB.println(imageIndex._height);
  tft.setColor(BLACK);
  tft.fillScreen();
   tft.setColor(WHITE, BLACK);
  tft.setCursor(0,0);
  for (int i = 0; i < (imageIndex._width * imageIndex._height / 4); i++) {
    if(!(i%4)){
      tft.print("\n");
    }
    //tft.print(imageIndex._buffer[i], HEX);
    tft.print((imageIndex._buffer[i]>>12)&0x000F, HEX);
    tft.print((imageIndex._buffer[i]>>8)&0x000F, HEX);
    tft.print((imageIndex._buffer[i]>>4)&0x000F, HEX);
    tft.print((imageIndex._buffer[i])&0x000F, HEX);
  }
  
  image.drawImage(0,0, imageIndex);
  tft.drawImage(120, 8, image, 32, 32);

  //Gamebuino_SD_GFX::writeImage(image, "WRITE4.BMP");
}

void loop() {
  SerialUSB.println("Waiting...");
  delay(1000);
}