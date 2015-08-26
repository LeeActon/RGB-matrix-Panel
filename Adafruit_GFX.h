#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

// Default is everything is supported
#define GFX_FONT_SUPPORT
#define GFX_LINE_SUPPORT
#define GFX_HLINE_SUPPORT
#define GFX_VLINE_SUPPORT
#define GFX_FILL_SUPPORT
#define GFX_CIRCLE_SUPPORT
#define GFX_RECTANGLE_SUPPORT
#define GFX_TRIANGLE_SUPPORT

// GFX_MIN removes all optional features
#ifdef GFX_MIN
#undef GFX_FONT_SUPPORT
#undef GFX_LINE_SUPPORT
#undef GFX_HLINE_SUPPORT
#undef GFX_VLINE_SUPPORT
#undef GFX_FILL_SUPPORT
#undef GFX_CIRCLE_SUPPORT
#undef GFX_RECTANGLE_SUPPORT
#undef GFX_TRIANGLE_SUPPORT
#endif

// Turn on requested features
#ifdef GFX_INCLUDE_FONT
    #define GFX_FONT_SUPPORT
#endif
#ifdef GFX_INCLUDE_LINE
    #define GFX_LINE_SUPPORT
#endif
#ifdef GFX_INCLUDE_FILL
    #define GFX_FILL_SUPPORT
#endif
#ifdef GFX_INCLUDE_CIRCLE
    #define GFX_CIRCLE_SUPPORT
#endif
#ifdef GFX_INCLUDE_RECTANGLE
    #define GFX_RECTANGLE_SUPPORT
#endif
#ifdef GFX_INCLUDE_TRIANGLE
    #define GFX_TRIANGLE_SUPPORT
#endif

// Turn on dependant features
#ifdef GFX_FONT_SUPPORT
    #define GFX_FILL_SUPPORT
#endif
#ifdef GFX_FILL_SUPPORT
    #define GFX_VLINE_SUPPORT
#endif
#ifdef GFX_RECTANGLE_SUPPORT
    #define GFX_HLINE_SUPPORT
    #define GFX_VLINE_SUPPORT
#endif
#ifdef GFX_CIRCLE_SUPPORT
    #define GFX_HLINE_SUPPORT
    #define GFX_VLINE_SUPPORT
#endif
#ifdef GFX_TRIANGLE_SUPPORT
    #define GFX_LINE_SUPPORT
    #define GFX_HLINE_SUPPORT
#endif

// Display what's inluded
#if 0
    #warning "GFX features:"
    #ifdef GFX_FONT_SUPPORT
    #warning "    - Font"
    #endif
    #ifdef GFX_LINE_SUPPORT
    #warning "    - Line"
    #endif
    #ifdef GFX_HLINE_SUPPORT
    #warning "    - HLine"
    #endif
    #ifdef GFX_VLINE_SUPPORT
    #warning "    - VLine"
    #endif
    #ifdef GFX_FILL_SUPPORT
    #warning "    - Fill"
    #endif
    #ifdef GFX_CIRCLE_SUPPORT
    #warning "    - Circle"
    #endif
    #ifdef GFX_RECTANGLE_SUPPORT
    #warning "    - Rectangle"
    #endif
    #ifdef GFX_TRIANGLE_SUPPORT
    #warning "    - Triangle"
    #endif
    #warning "---- End of list"
#endif

#if ARDUINO >= 100
 #include "Arduino.h"
#ifdef GFX_FONT_SUPPORT
 #include "Print.h"
#endif
#else
 #include "WProgram.h"
#endif

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#ifdef GFX_FONT_SUPPORT
class Adafruit_GFX : public Print
#else
class Adafruit_GFX
#endif
{
 public:

  Adafruit_GFX(int16_t w, int16_t h); // Constructor

  // This MUST be defined by the subclass:
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
#ifdef GFX_LINE_SUPPORT
  virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
#endif
#ifdef GFX_VLINE_SUPPORT
  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
#endif
#ifdef GFX_HLINE_SUPPORT
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
#endif
#ifdef GFX_RECTANGLE_SUPPORT
  virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
#endif
#ifdef GFX_FILL_SUPPORT
  virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  virtual void fillScreen(uint16_t color);
#endif
  virtual void invertDisplay(boolean i);

  // These exist only with Adafruit_GFX (no subclass overrides)
#ifdef GFX_CIRCLE_SUPPORT
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      uint16_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      int16_t delta, uint16_t color);
#endif
#ifdef GFX_TRIANGLE_SUPPORT
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
#endif
#ifdef GFX_RECTANGLE_SUPPORT
    #ifdef GFX_CIRCLE_SUPPORT
      void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
          int16_t radius, uint16_t color);
      void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
          int16_t radius, uint16_t color);
    #endif
#endif
  void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
      int16_t w, int16_t h, uint16_t color);
#ifdef GFX_FONT_SUPPORT
  void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
      uint16_t bg, uint8_t size);
  void setCursor(int16_t x, int16_t y);
  void setTextColor(uint16_t c);
  void setTextColor(uint16_t c, uint16_t bg);
  void setTextSize(uint8_t s);
  void setTextWrap(boolean w);
#endif
  void setRotation(uint8_t r);

#ifdef GFX_FONT_SUPPORT
#if ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void   write(uint8_t);
#endif
#endif

  int16_t
    height(void),
    width(void);

  uint8_t getRotation(void);

 protected:
  const int16_t
    WIDTH, HEIGHT;   // This is the 'raw' display w/h - never changes
  int16_t
    _width, _height; // Display w/h as modified by current rotation
#ifdef GFX_FONT_SUPPORT
  int16_t
    cursor_x, cursor_y;
  uint16_t
    textcolor, textbgcolor;
  uint8_t
    textsize;
  boolean
    wrap; // If set, 'wrap' text at right edge of display
#endif
  uint8_t
    rotation;
};

#endif // _ADAFRUIT_GFX_H

