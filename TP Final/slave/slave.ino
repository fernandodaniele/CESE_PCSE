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



byte datosRecibidos [100];

volatile byte indice=0;

volatile bool recepcionTerminada=false;



uint16_t color;



const int XP=8,XM=A2,YP=A3,YM=9; //arduino nano                                                         

const int TS_LEFT=105,TS_RT=899,TS_TOP=889,TS_BOT=115;  //Valores obtenidos del ejemplo de calibración de la librería. Para arduino UNO usar const int TS_LEFT=66,TS_RT=883,TS_TOP=924,TS_BOT=108;  

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);      //Objeto para pantalla táctil ¿porqué 300?



Adafruit_GFX_Button boton[20];

Adafruit_GFX_Button  prueba;



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

    Serial.println("recep terminada");

  }

  else

  {

    datosRecibidos[indice] = datoActual;

    indice++;

  } 

}



void loop()

{ 

  if (recepcionTerminada)

  {

    switch (datosRecibidos[0])

    {

      case 0:            

        break;

      case 1:

        inicializarTFT();

        break;

      case 2:

        tft.fillScreen(datosRecibidos[2]|(((uint16_t)datosRecibidos[1])<<8));

        break;

      case 3:

        tft.setCursor(datosRecibidos[2]|(((uint16_t)datosRecibidos[1])<<8),datosRecibidos[4]|(((uint16_t)datosRecibidos[3])<<8));

        break;

      case 4:

        /*for(int j=1; j < indice; j++)

        {

          tft.print((char)datosRecibidos[j]);

        } */

        tft.print("hola");

        break;

      case 9:

        /*boton[0].initButton(&tft,

                            datosRecibidos[3]|(((int16_t)datosRecibidos[2])<<8),

                            datosRecibidos[5]|(((int16_t)datosRecibidos[4])<<8),

                            datosRecibidos[7]|(((int16_t)datosRecibidos[6])<<8),

                            datosRecibidos[9]|(((int16_t)datosRecibidos[8])<<8),

                            datosRecibidos[11]|(((int16_t)datosRecibidos[10])<<8),

                            datosRecibidos[13]|(((int16_t)datosRecibidos[12])<<8),

                            datosRecibidos[15]|(((int16_t)datosRecibidos[14])<<8),

                            "CALIBRAR",

                            datosRecibidos[indice]);*/

        prueba.initButton(&tft,  80, 150, 140, 40, WHITE, CYAN, BLACK, "CALIBRAR", 2); // (gfx, x, y, w, h, outline, fill, textcolor, "Calibracion", textsize)

        prueba.drawButton(false);

        break;

    }

    recepcionTerminada = false;

    indice=0;

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
