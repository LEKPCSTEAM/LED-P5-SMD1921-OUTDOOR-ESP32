/*
  EPS32S3 + LED P5 OUTDOOR SMD 1921 LED MATRIX PANEL
*/

#include <Arduino.h>
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include "ESP32-VirtualMatrixPanel-I2S-DMA.h"

// Panel configuration
#define PANEL_RES_X 64
#define PANEL_RES_Y 32

#define NUM_ROWS 3
#define NUM_COLS 2

// === CUSTOM PINS For SMD 1921 OUTDOOR ===
#define R1_PIN 36
#define G1_PIN 38
#define B1_PIN 40
#define R2_PIN 35
#define G2_PIN 16
#define B2_PIN 4

#define A_PIN 2
#define B_PIN 18
#define C_PIN 42
#define D_PIN 21
#define E_PIN -1
#define LAT_PIN 1
#define OE_PIN 9
#define CLK_PIN 8

MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel *virtualDisp = nullptr;

void testDisplay()
{
  // ======== TEST PANEL ========
  for (int row = 0; row < NUM_ROWS; row++)
  {
    for (int col = 0; col < NUM_COLS; col++)
    {
      int panelIdx = row * NUM_COLS + col;
      int panelX = col * PANEL_RES_X;
      int panelY = row * PANEL_RES_Y;

      virtualDisp->setTextColor(virtualDisp->color565(255, 255, 255));
      virtualDisp->setCursor(panelX + 7, panelY + PANEL_RES_Y / 2 - 4);
      virtualDisp->print("Panel " + String(panelIdx + 1));
    }
  }

  String resolutionStr = String(virtualDisp->width()) + "x" + String(virtualDisp->height());
  int textSize = 1;
  int charWidth = 6 * textSize;
  int strWidth = resolutionStr.length() * charWidth;
  int x = (virtualDisp->width() - strWidth) / 2;

  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 0));
  virtualDisp->setCursor(x, 4);
  virtualDisp->print(resolutionStr);

  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 0));
  virtualDisp->setCursor(x, 4);
  virtualDisp->print(resolutionStr);

  virtualDisp->drawRect(1, 1, virtualDisp->width() - 2, virtualDisp->height() - 2, virtualDisp->color565(255, 0, 0));

  virtualDisp->drawLine(0, 0, virtualDisp->width() - 1, virtualDisp->height() - 1, virtualDisp->color565(255, 0, 0));
  virtualDisp->drawLine(virtualDisp->width() - 1, 0, 0, virtualDisp->height() - 1, virtualDisp->color565(255, 0, 0));
}

void scrollingText()
{
  String message = " LED P5 OUTDOOR SMD1921 LED Matrix Display Working Perfectly!  ";
  virtualDisp->setTextSize(1);
  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 255)); // cyan

  for (int x = PANEL_RES_X; x > -(message.length() * 6); x--)
  {
    virtualDisp->clearScreen();
    virtualDisp->setCursor(x, 12);
    virtualDisp->print(message);
    delay(100);
  }
}

void displayText()
{
  virtualDisp->clearScreen();

  virtualDisp->setTextSize(1);
  virtualDisp->setTextWrap(false);

  virtualDisp->setCursor(2, 2);
  virtualDisp->setTextColor(virtualDisp->color565(255, 0, 0)); // red
  virtualDisp->print("Hello SMD1921");

  virtualDisp->setCursor(2, 12);
  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 0)); // green
  virtualDisp->print("LED Matrix");

  virtualDisp->setCursor(2, 22);
  virtualDisp->setTextColor(virtualDisp->color565(0, 0, 255)); // blue
  virtualDisp->print("Working!");

  delay(3000);

  virtualDisp->clearScreen();
  virtualDisp->setTextSize(2);
  virtualDisp->setCursor(8, 8);
  virtualDisp->setTextColor(virtualDisp->color565(255, 255, 0));
  virtualDisp->print("BIG");
  delay(2000);

  scrollingText();
}

void testBasicDisplay()
{
  Serial.println("=== BASIC DISPLAY TEST ===");

  Serial.println("Test 1: RED screen (3 seconds)");
  virtualDisp->fillScreen(virtualDisp->color565(255, 0, 0));
  delay(3000);

  Serial.println("Test 2: GREEN screen (3 seconds)");
  virtualDisp->fillScreen(virtualDisp->color565(0, 255, 0));
  delay(3000);

  Serial.println("Test 3: BLUE screen (3 seconds)");
  virtualDisp->fillScreen(virtualDisp->color565(0, 0, 255));
  delay(3000);

  virtualDisp->clearScreen();

  Serial.println("Test 4: Text display");
  displayText();

  Serial.println("Basic test completed!");
}

void showTextMessages()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  virtualDisp->setCursor(5, 2);
  virtualDisp->setTextColor(virtualDisp->color565(255, 100, 0));
  virtualDisp->print("P5 LED SMD1921 LED");

  virtualDisp->setCursor(8, 12);
  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 100));
  virtualDisp->print("DISPLAY");

  virtualDisp->setCursor(15, 22);
  virtualDisp->setTextColor(virtualDisp->color565(100, 150, 255));
  virtualDisp->print("READY");
}

void showName()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  virtualDisp->setCursor(2, 2);
  virtualDisp->setTextColor(virtualDisp->color565(255, 0, 0));
  virtualDisp->print("LED P5 OUTDOOR SMD1921  \n@LEKPCSTEAM");
}

void showColorfulText()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  // แต่ละตัวอักษรสีต่างกัน
  String text = "RAINBOW";
  uint16_t colors[] = {
      virtualDisp->color565(255, 0, 0),    // แดง
      virtualDisp->color565(255, 165, 0),  // ส้ม
      virtualDisp->color565(255, 255, 0),  // เหลือง
      virtualDisp->color565(0, 255, 0),    // เขียว
      virtualDisp->color565(0, 0, 255),    // น้ำเงิน
      virtualDisp->color565(75, 0, 130),   // คราม
      virtualDisp->color565(238, 130, 238) // ม่วง
  };

  for (int i = 0; i < text.length(); i++)
  {
    virtualDisp->setCursor(2 + (i * 8), 12);
    virtualDisp->setTextColor(colors[i % 7]);
    virtualDisp->print(text.charAt(i));
  }
}

void showClock()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  // จำลองนาฬิกา
  virtualDisp->setCursor(8, 5);
  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 255));
  virtualDisp->print("TIME");

  virtualDisp->setTextSize(2);
  virtualDisp->setCursor(4, 15);
  virtualDisp->setTextColor(virtualDisp->color565(255, 255, 255));
  virtualDisp->print("12:34");
}

void showTemperature()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  virtualDisp->setCursor(12, 2);
  virtualDisp->setTextColor(virtualDisp->color565(255, 100, 0));
  virtualDisp->print("TEMP");

  virtualDisp->setTextSize(2);
  virtualDisp->setCursor(8, 12);
  virtualDisp->setTextColor(virtualDisp->color565(255, 0, 0));
   
  virtualDisp->print("" + String(temperatureRead()));

  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(40, 12);
  virtualDisp->setTextColor(virtualDisp->color565(255, 255, 0));
  virtualDisp->print("o");
  virtualDisp->setCursor(46, 18);
  virtualDisp->print("C");
}

void showStatus()
{
  virtualDisp->clearScreen();
  virtualDisp->setTextSize(1);

  virtualDisp->setCursor(2, 2);
  virtualDisp->setTextColor(virtualDisp->color565(0, 255, 0));
  virtualDisp->print("WIFI: ON");

  virtualDisp->setCursor(2, 12);
  virtualDisp->setTextColor(virtualDisp->color565(255, 255, 0));
  virtualDisp->print("CPU: 85%");

  virtualDisp->setCursor(2, 22);
  virtualDisp->setTextColor(virtualDisp->color565(0, 150, 255));
  virtualDisp->print("MEM: 4.2GB");
}

void showScrollingBanner()
{
  String banner = "    Welcome to LED Matrix Display!    ";
  virtualDisp->setTextSize(1);
  virtualDisp->setTextColor(virtualDisp->color565(255, 50, 150));

  static int scroll_pos = PANEL_RES_X;

  virtualDisp->clearScreen();
  virtualDisp->setCursor(scroll_pos, 12);
  virtualDisp->print(banner);

  scroll_pos -= 2;
  if (scroll_pos < -(banner.length() * 6))
  {
    scroll_pos = PANEL_RES_X;
  }
}

void showPatternWithText()
{
  virtualDisp->clearScreen();
  for (int i = 0; i < PANEL_RES_X; i++)
  {
    virtualDisp->drawPixel(i, 0, virtualDisp->color565(0, 100, 255));
    virtualDisp->drawPixel(i, PANEL_RES_Y - 1, virtualDisp->color565(0, 100, 255));
  }
  for (int i = 0; i < PANEL_RES_Y; i++)
  {
    virtualDisp->drawPixel(0, i, virtualDisp->color565(0, 100, 255));
    virtualDisp->drawPixel(PANEL_RES_X - 1, i, virtualDisp->color565(0, 100, 255));
  }

  virtualDisp->setTextSize(1);
  virtualDisp->setCursor(12, 8);
  virtualDisp->setTextColor(virtualDisp->color565(255, 255, 255));
  virtualDisp->print("FRAMED");

  virtualDisp->setCursor(16, 18);
  virtualDisp->setTextColor(virtualDisp->color565(255, 200, 0));
  virtualDisp->print("TEXT");
}

void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("==========================================");
  Serial.println("    P5 LED SMD1921 HUB75 Panel Debug Mode");
  Serial.println("==========================================");

  Serial.println("Pin Configuration:");
  Serial.printf("R1=%d, G1=%d, B1=%d\n", R1_PIN, G1_PIN, B1_PIN);
  Serial.printf("R2=%d, G2=%d, B2=%d\n", R2_PIN, G2_PIN, B2_PIN);
  Serial.printf("A=%d, B=%d, C=%d, D=%d\n", A_PIN, B_PIN, C_PIN, D_PIN);
  Serial.printf("LAT=%d, OE=%d, CLK=%d\n", LAT_PIN, OE_PIN, CLK_PIN);
  Serial.println("");

  HUB75_I2S_CFG::i2s_pins _pins = {
      R1_PIN, G1_PIN, B1_PIN,
      R2_PIN, G2_PIN, B2_PIN,
      A_PIN, B_PIN, C_PIN, D_PIN, E_PIN,
      LAT_PIN, OE_PIN, CLK_PIN};

  HUB75_I2S_CFG config(
      PANEL_RES_X * 2,
      PANEL_RES_Y / 2,
      NUM_ROWS * NUM_COLS,
      _pins);

  Serial.println("Trying SHIFTREG driver first...");
  config.driver = HUB75_I2S_CFG::SHIFTREG;

  config.clkphase = false;
  config.latch_blanking = 1;
  config.i2sspeed = HUB75_I2S_CFG::HZ_20M;
  config.double_buff = false;
  config.min_refresh_rate = 60;

  Serial.println("Creating DMA display object...");
  dma_display = new MatrixPanel_I2S_DMA(config);

  Serial.println("Initializing DMA display...");
  if (!dma_display->begin())
  {
    Serial.println("");
    Serial.println("*** DMA INITIALIZATION FAILED! ***");
    Serial.println("");
    Serial.println("Troubleshooting checklist:");
    Serial.println("1. ตรวจสอบแหล่งจ่ายไฟ 5V (ต้องมีกระแส 2-4A)");
    Serial.println("2. ตรวจสอบสาย GND เชื่อมต่อระหว่าง ESP32 และ Panel");
    Serial.println("3. ตรวจสอบการเชื่อมต่อสาย Data ทั้ง 13 เส้น");
    Serial.println("4. ลองเปลี่ยน GPIO pins");
    Serial.println("5. ลองใช้ Panel อื่น");
    Serial.println("");

    while (1)
    {
      Serial.println("System halted. Please check connections.");
      delay(5000);
    }
  }

  Serial.println("*** DMA Display initialized successfully! ***");
  dma_display->setBrightness8(50);
  dma_display->clearScreen();

  Serial.println("Creating Virtual Panel...");
  virtualDisp = new VirtualMatrixPanel(
      *dma_display,
      NUM_ROWS, NUM_COLS,
      PANEL_RES_X, PANEL_RES_Y, CHAIN_TOP_RIGHT_DOWN);
  Serial.println("Setting scan rate to 1/8 scan...");
  virtualDisp->setPhysicalPanelScanRate(FOUR_SCAN_32PX_HIGH);

  Serial.println("Setup completed! Starting display test...");

  testDisplay();
  delay(5000);
}

void loop()
{
  static int test_mode = 0;
  static unsigned long last_change = 0;

  if (millis() - last_change > 8000)
  {
    virtualDisp->clearScreen();
    switch (test_mode)
    {
    case 0:
      Serial.println("Loop Test: Text Messages");
      showTextMessages();
      break;
    case 1:
      Serial.println("Loop Test: Numbers & Symbols");
      showName();
      break;
    case 2:
      Serial.println("Loop Test: Multi-color Text");
      showColorfulText();
      break;
    case 3:
      Serial.println("Loop Test: Clock Display");
      showClock();
      break;
    case 4:
      Serial.println("Loop Test: Temperature Display");
      showTemperature();
      break;
    case 5:
      Serial.println("Loop Test: Status Messages");
      showStatus();
      break;
    case 6:
      Serial.println("Loop Test: Scrolling Banner");
      showScrollingBanner();
      break;
    case 7:
      Serial.println("Loop Test: Pattern + Text");
      showPatternWithText();
      break;
    case 8:
      Serial.println("Loop Test: Pattern");
      testDisplay();
      break;
    }

    test_mode = (test_mode + 1) % 9;
    last_change = millis();
  }
}
