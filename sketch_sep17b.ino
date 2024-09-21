/*
	Primer Autor: bitwiseAr - Capitulo 43 de Arduino desde cero en Español. 
    Programa que muestra una flecha hacia arriba con animación de movimiento en 9 cuadros.

  Tipito que se mueve en el semásforo peatonal

  Documentación: https://wayoda.github.io/LedControl/pages/software

  Create a new LedControl variable.
    * We use pins 12, 11 and 10 on the Arduino for the SPI interface
        BUS: sistema digital que transfiere datos entre los componentes de una computadora.
        SPI: bus estándar para controlar casi cualquier dispositivo electrónico digital que 
            acepte un flujo de bits serie regulado por un reloj (comunicación sincrónica).

    * Pin 12 is connected to the DATA IN-pin of the first MAX7221

    
    * Pin 11 is connected to the CLK-pin of the first MAX7221
    * Pin 10 is connected to the LOAD(/CS)-pin of the first MAX7221
    * There will only be a single MAX7221 attached to the arduino 
   
LedControl lc1=LedControl(12,11,10,1); 

  POSIBLE BUG
  I solved the problem I had with a panel with 5 MAX7219 8x8. 
  I had to edit the library file, MD_MAX72xx_h, and set it to "USE_GENERIC_HW 1" since what comes standard is another.


*/

#include "LedControl.h" 		// incluye libreria LedControl

LedControl lc=LedControl(11,13,10,1);	// crea objeto

#define demora 250			// constante demora con valor de 250

byte tipo_camina_1[8] = {		// array con primer cuadro
  B00110000,
  B00110000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00001000,
  B00001000
};

byte tipo_camina_2[8] = {		// array con segundo cuadro 
  B00110000,
  B00110000,
  B00011000,
  B00011100,
  B01111110,
  B00111000,
  B00100010,
  B00000010
};

byte tipo_camina_3[8] = {		// array con tercer cuadro
  B00110000,
  B00110000,
  B00111000,
  B01111100,
  B00111100,
  B00111000,
  B00100100,
  B00000100
};

byte tipo_camina_4[8] = {		// array con cuarto cuadro
  B00110000,
  B00110000,
  B00011100,
  B01111010,
  B00011000,
  B00100100,
  B00100010,
  B00100000
};

byte tipo_camina_5[8] = {		// array con quinto cuadro
  B00110000,
  B00110000,
  B00011000,
  B00011000,
  B00111000,
  B00011100,
  B00011000,
  B00010000
};

void setup() {
  lc.shutdown(0,false);			// enciende la matriz
  lc.setIntensity(0,4);			// establece brillo
  lc.clearDisplay(0);			// blanquea matriz
}

void loop(){
  mostrar_1();				// llama funcion mostrar_1
  delay(demora);			// demora
  mostrar_2();				// llama funcion mostrar_2
  delay(demora);			// demora
  mostrar_3();				// llama funcion mostrar_3
  delay(demora);			// demora
  mostrar_4();				// llama funcion mostrar_4
  delay(demora);			// demora
  mostrar_5();				// llama funcion mostrar_5
  delay(demora);			// demora
}

void mostrar_1(){			// funcion mostrar_1
  for (int i = 0; i < 8; i++)  		// bucle itera 8 veces por el array
  {
    lc.setRow(0,i,tipo_camina_1[i]);
  }
}

void mostrar_2(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,tipo_camina_2[i]);
  }
}

void mostrar_3(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,tipo_camina_3[i]);
  }
}

void mostrar_4(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,tipo_camina_4[i]);
  }
}

void mostrar_5(){
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,tipo_camina_5[i]);
  }
}