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
  tft.fillScreen(WHITE);

  width = tft.width();
  height = tft.height();

  //Una linea requiere de 4 parametros. Posicion inicial --> Esquina superior izquierda
  // Posicion en X --> Direccion horizontal (De izquierda a derecha)
  // Posicion en Y --> Direccion vertical (De arriba a abajo)
  // Longitud --> Distancia en pixeles
  // Color --> En hexadecimal

  // Hay que crear una malla con un offset de 50 pixeles en x y 45 pixeles en y
  // Un offset es una ligera separacion de el origen que sirve para compensar un error de desplazamiento 
  // Las filas y columnas se desplazan demasiado con respecto a la zona visible de la pantalla.
  // Plantea una solucion para que sigan apareciendo el numero de filas y columnas definido a pesar de el offset excesivo
  int offset_x = 50;
  int offset_y = 45;

  // Hay un numero de filas y columnas definido con las funciones drawFastHLine y drawFastVLine

  // Numero de filas 8 y numero de columnas 8
  
  int rows = 8;
  int columns = 8;

  //La relacion de separacion de columnas se define como la separacion de anchura entre columna y columna
  //La relacion de separacion de filas se define como la separacion de altura entre fila y fila
  int w = width/columns;
  int h = height/rows;
  
  if(offset_x > w){
  //Escribir la solucion al desplazamiento en x en una linea
    
  }

  if(offset_y > h ){
  //Escribir la solucion al desplazamiento en y en una linea
  
  }
  
  //Dibujar las lineas horizontales
  for (int i; i <rows; i++){
    tft.drawFastHLine(0, offset_y + i*h, width, BLACK);
  }

  //Dibujar las lineas horizontales
  for (int i; i <columns; i++){
    tft.drawFastVLine( offset_x + i*w, 0, height, BLACK);
  }
}


void loop() {

}
