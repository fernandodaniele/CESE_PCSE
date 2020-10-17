#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>
#include <Adafruit_GFX.h>  //librería gráfica para TFT
#include <MCUFRIEND_kbv.h> //librería especifica del módulo
#include <TouchScreen.h>   //librería para la parte táctil del módulo
#define MINPRESSURE 150   //Valor previo: 200- Rango de detección eje z táctil
#define MAXPRESSURE 1000


#define BLACK   0x0000    //Colores predefinidos. Se pueden agregar o modificar
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;        //Objeto pantalla gráfica

volatile byte datos [100];
volatile byte datosRecibidos [100];
volatile byte indice=0;
volatile byte cantidad=0;
volatile bool recepcionTerminada=false;

uint16_t color;

const int XP=8,XM=A2,YP=A3,YM=9; //arduino nano                                                         
const int TS_LEFT=105,TS_RT=899,TS_TOP=889,TS_BOT=115;  //Valores obtenidos del ejemplo de calibración de la librería. Para arduino UNO usar const int TS_LEFT=66,TS_RT=883,TS_TOP=924,TS_BOT=108;  
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);      //Objeto para pantalla táctil ¿porqué 300?

Adafruit_GFX_Button boton[20];
Adafruit_GFX_Button  prueba;

 void inicializarTFT();
 bool Touch_getXY(int *pixel_X,int *pixel_Y);

void setup()
{
  Serial.begin (115200); 
  SPCR |= bit (SPE); // Habilita el bus SPI en modo esclavo
  pinMode (MISO, OUTPUT);   // Configura el pin MISO como salida (slave out)
  indice = 0;
  recepcionTerminada = false;
  SPI.attachInterrupt();   // Habilita las interrupciones del bus SPI
} 
// Rutina de interrupcion del bus SPI
ISR (SPI_STC_vect)
{
  byte datoActual = SPDR; // Lee el rado recibido desde el registro SPDR del bus SPI

  if(datoActual == '\n'){
    recepcionTerminada = true;
    for(int i =0; i<indice; i++){
          datosRecibidos[i] = datos [i];
    }
    cantidad = indice;
    indice=0;
  }
  else
  {
    datos[indice] = datoActual;
    indice++;
  }
}

void loop()
{ 
  if (recepcionTerminada)
  {
    switch (datosRecibidos[0])
    {
      case '1':
        inicializarTFT();
        break;
      case '2':
        for(int j = 1; j < cantidad; j++)
        {
          tft.print((char)datosRecibidos[j]);
        }  
        break;
      case '3':
        {char cadena[5];
        for(int j = 1; j < cantidad; j++)
        {
          cadena [j-1] = ((char)datosRecibidos[j]);
        }
        uint16_t valor = atoi(cadena);
        tft.fillScreen(valor);
        break;}
      case '4':
        {char cadena[3];
        char cadena2[3];
        int j = 1;
        while(datosRecibidos[j]!= '-')
        {
          cadena [j-1] = ((char)datosRecibidos[j]);
          j++;
        }
        j++;
        int k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena2 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        uint16_t valor = atoi(cadena);
        uint16_t valor2 = atoi(cadena2);
        tft.setCursor(valor,valor2);
        break;}
      case '5':
        {char cadena3[3];
        char cadena4[3];
        char cadena5[3];
        char cadena6[3];
        char cadena7[5];
        int j = 1;
        while(datosRecibidos[j]!= '-')
        {
          cadena3 [j-1] = ((char)datosRecibidos[j]);
          j++;
        }
        j++;
        int k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena4 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena5 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena6 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena7 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        int16_t valor3 = atoi(cadena3);
        int16_t valor4 = atoi(cadena4);
        int16_t valor5 = atoi(cadena5);
        int16_t valor6 = atoi(cadena6);
        uint16_t valor7 = atoi(cadena7);
        tft.drawRect(valor3,valor4,valor5,valor6,valor7);
        break;}
      case '6':
        {char cadena[5];
        for(int j = 1; j < cantidad; j++)
        {
          cadena [j-1] = ((char)datosRecibidos[j]);
        }
        uint16_t valor = atoi(cadena);
        tft.setTextColor(valor);
        break;}
      case '7':
        {char cadena[2]; 
        for(int j = 1; j < cantidad; j++)
        {
          cadena [j-1] = ((char)datosRecibidos[j]);
        }
        uint16_t valor = atoi(cadena);
        tft.setTextSize(valor);
        break;}
      case '8':
        {char cadena3[3];
        char cadena4[3];
        char cadena5[3];
        char cadena6[3];
        char cadena7[5];
        int j = 1;
        while(datosRecibidos[j]!= '-')
        {
          cadena3 [j-1] = ((char)datosRecibidos[j]);
          j++;
        }
        j++;
        int k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena4 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena5 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena6 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena7 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        int16_t valor3 = atoi(cadena3);
        int16_t valor4 = atoi(cadena4);
        int16_t valor5 = atoi(cadena5);
        int16_t valor6 = atoi(cadena6);
        uint16_t valor7 = atoi(cadena7);
        tft.drawLine(valor3,valor4,valor5,valor6,valor7);
        break;}
      case '9':
        {char cadena3[3];
        char cadena4[3];
        char cadena5[5];
        int j = 1;
        while(datosRecibidos[j]!= '-')
        {
          cadena3 [j-1] = ((char)datosRecibidos[j]);
          j++;
        }
        j++;
        int k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena4 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        j++;
        k=0;
        while(datosRecibidos[j]!= '-')
        {
          cadena5 [k] = ((char)datosRecibidos[j]);
          j++;
          k++;
        }
        int16_t valor3 = atoi(cadena3);
        int16_t valor4 = atoi(cadena4);
        int16_t valor5 = atoi(cadena5);
        tft.drawPixel(valor3,valor4,valor5);
        break;}
    } 
    recepcionTerminada = false;
    cantidad = 0;
  }
}

bool Touch_getXY(int *pixel_X,int *pixel_Y){           //Touch_getXY() updates global vars
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);          //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);       //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
      *pixel_X = map(p.y, TS_LEFT, TS_RT, 0, 320);
      *pixel_Y = map(p.x, TS_TOP, TS_BOT, 0, 240);
    }
    return pressed;
}

 void inicializarTFT(){
  uint16_t ID = tft.readID();
  Serial.println(ID);
  if (ID == 0xD3D3)
    ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(1);            //horizontal
  tft.setTextSize(3);
}