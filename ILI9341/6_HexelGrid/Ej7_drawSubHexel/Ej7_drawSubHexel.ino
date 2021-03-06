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

//Variables globales de TFT y de malla
int width, height;
  //Numero de filas, columnas, anchura y altura de subpixel
int col, row;

void setup() {
  Serial.begin(9600);
  tft.begin(); // Begin ILI9341

  tft.setRotation(1); 
  tft.fillScreen(WHITE);

  width = tft.width();
  height = tft.height();


  drawSubHexel(0,0,GREEN);
  drawSubHexel(1,1,YELLOW);
  drawSubHexel(1,0,GREEN);
  drawSubHexel(0,1,YELLOW);
  drawSubHexel(0,2,BLUE);
  drawSubHexel(1,2,BLUE);

  drawGrid();
}

void loop() {

}

//Esta funcion debe ser capaz de dibujar uno de los triangulos de la mall, especificando la fila y la columna dado por el convenio definido en https://github.com/blascarr/TFTCourse
void drawSubHexel(int row, int col, uint16_t color){
    float w = width;
    float h = height/2;

    //Absolut Displacement width and height
    int d_w=(col)/6;
    int d_h=(row)/6;
    float plus_w,plus_h;
    bool inv, inv_x, inv_y;

    int mode = 0;

    float x1 = 0;
    float x2 = 0;
    float y1 = 0;
    float y2 = 0;
    float x3 = 0;
    float y3 = 0;
    
      h = w*sqrt(4/3);
      h = 2*height;
      //Desplazamiento entre cuadriculas
      plus_w = (col)/6*2*w;
      plus_h = (row)/4*h;

      if ((col%6) >= 3){
        plus_w = plus_w + w;
      } 

      if (row%4 >=2){
        plus_h = plus_h + h/2;
      }

      //Identificación del modo de la cuadricula
      if ((col%6 >= 3)^(row%4 >=2)){
          inv = true;
          //Serial.println("Mode 2");
          if ((2*(col%3)+row%2) <= 2){
            row++;
          }else{
            row--;
          }
      }else{
          inv = false;
          //Serial.println("Mode 1");
      }

      //Identificación de la mitad a la que pertenece
      if ((2*(col%3)+row%2)>=2){
          inv_x = true;

      }else{
          inv_x = false;
      }

      

      //Inicializacion de la referencia
      x1 = 0;
      x2 = 0;
      //Identificacion del triangulo al que pertenece
      switch ((col%3+2*(row%2))%4){

        //Case for parameters [0,0] & [2,1]
        case 0:
          x2 = w/2;
          y2 = h/4;
          x3 = 2*w/3;
          y3 = 0;

        break;

        //Case for parameters [1,0] 
        case 1:
          x2 = w/3;
          y2 = h/2;
          x3 = w/2;
          y3 = h/4;
        break;

        //Case for parameters [0,1] & [2,0] 
        case 2:
            x2 = 0;
            y2 = h/2;
            x3 = w/3;
            y3 = h/2;
        break;

        //Case for parameters [1,1] 
        case 3:
          x1 = w;
          y1 = h/2;
          x2 = 2*w/3;
          y2 = 0;
          x3 = w/2;
          y3 = h/4;

        break;
      }


      if(inv){
        y1 = h/2 - y1;
        y2 = h/2 - y2;
        y3 = h/2 - y3;
      }  

      if(inv_x){
        x1 = w-x1;
        x2 = w-x2;
        x3 = w-x3;
        y1 = h/2-y1;
        y2 = h/2-y2;
        y3 = h/2-y3;
      }

      //Debug
      /*Serial.print("Col, Row: ");
      Serial.print(col%3);
      Serial.print(" : ");
      Serial.println(row%2);
      Serial.print("Punto 1: ");
      Serial.print(x1);
      Serial.print(" , ");
      Serial.println(y1);
      Serial.print("Punto 2: ");
      Serial.print(x2);
      Serial.print(" , ");
      Serial.println(y2);
      Serial.print("Punto 3: ");
      Serial.print(x3);
      Serial.print(" , ");
      Serial.println(y3);
      Serial.println(2*(col%3)+row%2);
      Serial.println((col%3+2*(row%2))%4);*/

      tft.fillTriangle(   x1 + plus_w, y1 + plus_h, x2 + plus_w, y2 + plus_h,   x3 + plus_w, y3 + plus_h, color);
}

  
void drawGrid(){
  int posx = 0;
  int posy=0;
  subhexel(posx, posy, width, height, 1, BLACK);
  //subhexel(posx+width/2, posy, width/2, height/2, 0, BLACK);
  //subhexel(posx, posy+height/2, width/2, height/2, 0, BLACK);
  //subhexel(posx+width/2, posy+height/2, width/2, height/2, 1, BLACK);
}

void subhexel(float pos_x, float pos_y, int w , int h, bool sym, uint16_t color){

    float PX[] = {0 + pos_x ,w/3 + pos_x, w/2 + pos_x, 2*w/3 + pos_x, w + pos_x};
    float PY[]= {0 + pos_y, h/2+ pos_y, h+ pos_y};
    
    if (!sym){

      PY[0] = h + pos_y;
      PY[1] = h/2 + pos_y;
      PY[2] = 0 + pos_y;
    }

    //Vamos a crear 6 subtriangulos dentro de el area determinada 
    
    tft.drawTriangle(   PX[0], PY[0], PX[1], PY[2] , PX[0], PY[2], color);
    tft.drawTriangle(   PX[0], PY[0], PX[2], PY[1] , PX[1], PY[2], color);
    tft.drawTriangle(   PX[0], PY[0], PX[3], PY[0] , PX[2], PY[1], color);
    
    tft.drawTriangle(   PX[4], PY[2], PX[3], PY[0], PX[4], PY[0] , color);
    tft.drawTriangle(   PX[4], PY[2], PX[2], PY[1], PX[3], PY[0] , color);
    tft.drawTriangle(   PX[4], PY[2], PX[1], PY[2] , PX[2], PY[1] , color);
    
    //borderCorrection();
}

void borderCorrection(){
  tft.drawFastHLine(-2, -1, width,  BLACK);
  tft.drawFastVLine(-2, -1, height,  BLACK);
  tft.drawFastVLine(-1, -1, height,  BLACK);
}
