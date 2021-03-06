#include <SPI.h>  
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library

#define TFT_CS   7
#define TFT_DC   6

// Assign human-readable names to some common 16-bit color values:
#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

//Declaracion objeto TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int width, height;

void setup() {
  Serial.begin(9600);
  tft.begin(); // Begin ILI9341

  tft.setRotation(0); 
  tft.fillScreen(GREEN);

  width = tft.width();
  height = tft.height();

  //Un rectangulo requiere de 5 parametros. Posicion --> Esquina superior izquierda
  // Posicion en X --> Direccion horizontal (De izquierda a derecha)
  // Posicion en Y --> Direccion vertical (De arriba a abajo)
  // Anchura --> Distancia en pixeles
  // Altura --> Distancia en pixeles
  // Color --> En hexadecimal

  //Dibujar una cara con dos cuadrados y un rectangulo debajo
  
    //Dibujar dos cuadrados en linea en el centro de la pantalla de 50 pixeles de lado con una separacion de 30 pixeles
  
    // Dimensiones del rectangulo
    int lsize = 60;
    int space = 50;
    
    // Posicion del primer cuadrado
    int x1 = width/2 - lsize - space/2;
    int y1 = height/2 - lsize /2;
  
    uint16_t color1 = RED;
    
    tft.fillRect(x1, y1, lsize, lsize, color1);
  
    // Posicion del segundo cuadrado
    int x2 = width/2 +space/2;
    int y2 = height/2 - lsize /2;
  
    uint16_t color2 = RED;
    
    tft.fillRect(x2, y2, lsize, lsize, color2);

   // Dibujar rectangulo debajo de 150 pixeles de largo y 30 de ancho a una distancia de 40 pixeles de los ojos

   tft.fillRect(width/2-150/2, y1+lsize+40, 150, 30, color2);
}

void loop() {

}
