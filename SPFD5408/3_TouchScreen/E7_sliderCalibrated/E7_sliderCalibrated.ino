#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

// These are the pins for the shield!
//Estos son los pines que definen el modo de conexion de las resistencias de la pantalla tactil
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

//Hay que calibrar primero este parametro para hacer que funcione este ejemplo. 
#define MINPRESSURE 400
#define MAXPRESSURE 1000
#define MINX_VALUE 20
#define MINY_VALUE 20

/*#define TS_MINX 28
#define TS_MINY 66
#define TS_MAXX 451
#define TS_MAXY 240*/

short TS_MINX=28;
short TS_MINY=81;
short TS_MAXX=451;
short TS_MAXY=228;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int width, height;

void setup(void) {
  Serial.begin(9600);

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(0); 
  tft.setTextSize(4);
  tft.setTextColor(BLACK);

  width = tft.width() - 1;
  height = tft.height() - 1;

  Serial.println(F("TFT LCD test"));

  tft.fillScreen(GREEN);
  
  //Apretar una vez para comenzar la calibracion
  waitOneTouch();

  calibrate_TS();
  
  waitOneTouch();
}

void loop(void) {
  //TSPoint es el detector de presion sobre cada uno de los pixeles y que se activa en el momento que la pantalla detecta una diferencia de presion
  // Se observa que esta descalibrado
  // En X va fatal ya que no es direccional en las 4 esquinas
  
  TSPoint p = waitOneTouch();
  /*int16_t dp_x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  if(dp_x < 100){
    Serial.println("Pressed 100");
  }*/

  //En la direccion Y si que funciona bien ya que es homogenea en pares de esquinas
  //Hay que borrar cada vez parte del rectangulo para actualizar su campo
  
  if (p.y > MINPRESSURE && p.y < MAXPRESSURE && p.x > MINX_VALUE && p.z > MINY_VALUE) {
     Serial.print("X = "); Serial.print(p.x);
     Serial.print("\tY = "); Serial.print(p.z);
     Serial.print("\tPressure = "); Serial.println(p.y);
  }// a point object holds x y and z coordinates
  
  int16_t dp_y = map(p.z, TS_MINY, TS_MAXY, 0, tft.height());
  tft.fillRect(width/2, 20, 40, dp_y, RED);  
  
  tft.fillRect(width/2, dp_y, 70, height - dp_y+20, GREEN);
  //tft.setCursor(width/2,300);
  Serial.println(mapYValue(p));
}

//Esta funcion devuelve un punto tactil una vez se verifica que ha sido presionado y obtiene valores validos 
TSPoint waitOneTouch() {
  
  TSPoint p;
  
  do {
    p= ts.getPoint(); 
    
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);
  
  } while( (p.y < MINPRESSURE )|| (p.y > MAXPRESSURE) || (p.x < MINX_VALUE)|| (p.z < MINY_VALUE) );
  /*Serial.print("Screen Touched: x -> ");
  Serial.print(p.x);
  Serial.print(" y-> ");
  Serial.print(p.z);
  Serial.print("\t pressure-> ");
  Serial.print(p.y);
  Serial.print("\tPixel X = ");Serial.print(mapXValue(p));
  Serial.print("\tPixel Y = ");Serial.println(mapYValue(p));*/
  return p;
}

// Calibration of Touch Screen (resistive)

void calibrate_TS(void) {

  // Based in code posted in https://forum.arduino.cc/index.php?topic=223769.15
  
  TSPoint p1, p2;
  int16_t temp;
  int32_t tempL;
  
  // Este metodo no funciona bien cuando se establece una rotacion distinta a la 0
  // Las resistencias de calibracion no se modifican cuando se realiza un cambio en la rotacion
  
  tft.fillCircle(4,4,4,BLUE); //show the first point
  tft.setCursor(5, 30); 
  tft.setTextColor(BLUE); 
  tft.setTextSize(1);
  Serial.println("Please touch the dot");

  //Limite minimo aproximado como para considerar el punto como el menor
  uint16_t limit = 40;

  //Calibra los ejes de una esquina que se corresponden con los valores mas bajos y guarda su valor en p1
  do {
  
    p1 = waitOneTouch();

  } while (!(mapXValue(p1) < limit && mapYValue(p1) < limit));
  
  
  tft.fillCircle(234,314,4,BLUE); //show the 2nd point
  tft.setCursor(50, 280);
  Serial.println("Please touch the other dot");
  delay (500); // debunce

  do {
  
    p2 = waitOneTouch();
  
  } while (!(mapXValue(p2) > (width - limit) && mapYValue(p2) > (height - limit)));
  
  
  delay (300); 
  
  temp=p2.x-p1.x; // Calculate the new coefficients, get X difference
  tempL=((long)temp*1024)/(tft.width()-20);
  TS_MINX=p1.x-( (tempL*10)>>10);// 10 pixels du bord
  TS_MAXX=p1.x+( (tempL*tft.width())>>10);// 220 pixels entre points
  temp=p2.z-p1.z; // ¨get Y difference
  tempL=((long)temp*1024)/(tft.height()-20);
  TS_MINY=p1.z-( (tempL*10)>>10);// 10 pixels du bord
  TS_MAXY=TS_MINY+( (tempL*tft.height())>>10);
  
  // Show results
  
  //  p1.x = map(p1.x, TS_MAXX,TS_MINX, tft.width(), 0);
  //  p1.y = map(p1.y, TS_MAXY,TS_MINY, tft.height(), 0);
  //  p2.x = map(p2.x, TS_MAXX,TS_MINX, tft.width(), 0);
  //  p2.y = map(p2.y, TS_MAXY,TS_MINY, tft.height(), 0);

    p1.x = mapXValue(p1);
    p1.y = mapYValue(p1);
    p2.x = mapXValue(p2);
    p2.y = mapYValue(p2);

    Serial.println();
    Serial.println("Last touched points: ");
    Serial.print("Pt 1: ");Serial.print(p1.x);Serial.print(" : ");Serial.println(p1.y);
    Serial.print("Pt 2: ");Serial.print(p2.x);Serial.print(" : ");Serial.println(p2.y);

    Serial.println("After calibration: ");
    Serial.print("TS_MINX= ");Serial.println(TS_MINX);
    Serial.print("TS_MINY= ");Serial.println(TS_MINY);
    Serial.println();
    Serial.print("TS_MAXX= ");Serial.println(TS_MAXX);
    Serial.print("TS_MAXY= ");Serial.println(TS_MAXY);
    Serial.println();
  
    // Wait a touch
    
    Serial.println("Touch to proceed");

    waitOneTouch();
}

//Mapea el valor del eje X cuando se toca un punto y lo identifica con su posicion a lo ancho
uint16_t mapXValue(TSPoint p) {

  uint16_t x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

  //Correct offset of touch. Manual calibration
  //x+=1;
  
  return x;

}

//Mapea el valor del eje Y cuando se toca un punto y lo identifica con su posicion a lo alto

uint16_t mapYValue(TSPoint p) {

  uint16_t y = map(p.z, TS_MINY, TS_MAXY, 0, tft.height());

  //Correct offset of touch. Manual calibration
  //y-=2;

  return y;
}
