#include <SPI.h>  
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

// These definitions map display functions to the Adduino UNO display header pins
#define sclk 15
#define mosi 16
#define cs   7
#define dc   0
#define rst  1
    
// Assign human-readable names to some common 16-bit color values:
  #define BLACK 0x0000
  #define WHITE 0xFFFF
  #define BLUE 0x001F
  #define GREEN   0x07E0
  #define YELLOW 0xFFE0 
  #define RED     0xF800
  #define BROWN 0x99AA66
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F

//Declaracion objeto TFT
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);


//Variables globales de TFT y de malla
int width, height;
  //Numero de filas, columnas, anchura y altura de subpixel
int col, row;

void setup() {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB); // Tab Label for ST7735 TFT Screen (INITR_GREENTAB 0x0, INITR_REDTAB 0x1, INITR_BLACKTAB 0x2);

  tft.setRotation(0); 
  tft.fillScreen(YELLOW);

  width = tft.width();
  height = tft.height();

  //La malla será en este momento triangular con unas dimensiones definidas 
  // y una disposición que nos permita acceder a cada uno de estos triangulos mediante la definicion de la fila y la columna que queremos dibujar.

  //Pero ahora vamos a crear cada una de las columnas de la malla desplazando hacia abajo la mitad de la altura del triangulo para que aparezca ajustado
  
  //Numero de columnas *Solo necesitamos conocer las columnas, ya que las filas las calcularemos mediante una formula trigonometricae base a este numero.
  col = 17;
  
  hexelgrid(col, row, BLACK);
}

void loop() {

}

void hexelgrid(int8_t col, int8_t row, uint16_t color){

    //Calculamos cuantos pixeles hay que dibujar de ancho para cada triangulo. 
    float w = width/col;

    //Conociendo el ancho de columna, establecemos la altura de cada triangulo con la siguiente formula. 
    float h = w*sqrt(4/3);
    
    //Sabiendo la altura total de la pantalla de cada triangulo, podemos calcular el numero de filas que vamos a dibujar dentro del bucle
    int n_rows = height/h;

    //Comenzamos dibujando las columnas
    for (int i = 0; i <= col; ++i){

      //Esta funcion sirve para crear un limite superior con la mitad de un triangulo
      //tft.drawTriangle(   w*(i-1), 0, w*i, 0 , w*(i-1), h/2, color);
      for (int j = 0; j <= n_rows; ++j){
        
        //El primer triangulo esta desplazado hacia arriba h/2
        //tft.drawTriangle(   0, h/2+h*(j-1), w, h*j , 0, h/2+h*j, color);
        //tft.drawTriangle(   w, h+h*(j-1), 2*w, h*j+h/2 , w, h+h*j, color);
        //tft.drawTriangle(   2*w, h/2+h*(j-1), 3*w, h*j , 2*w, h/2+h*j, color);
        //------
        //tft.drawTriangle(   w*(i-1), h/2+h*(j-1), w*i, h*j , w*(i-1), h/2+h*j, color);

        //En este caso solo desplazaremos hacia abajo las columnas pares,mientras que las impares deben permanecer igual. Para resolver este problema, aplicamos la funcion modulo %.
        tft.drawTriangle(   w*(i-1), h/2*(i%2+1)+h*(j-1), w*i, h/2*(i%2)+h*j , w*(i-1), h/2*(i%2+1)+h*j, color);

        if(j== 0){
          Serial.print("Distancia de la fila");
          Serial.println(w*(i-1));
          Serial.println("--------");
        }

      }
    }
    //Border Correction
    /*
    tft.drawFastHLine(-2, -1, width,  color);
    tft.drawFastVLine(-2, -1, height,  color);
    tft.drawFastVLine(-1, -1, height,  color);
    */
  }

