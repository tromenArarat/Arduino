/*
	Primer Autor: bitwiseAr - Capitulo 43 de Arduino desde cero en Español. 
    Programa que muestra una flecha hacia arriba con animación de movimiento en 9 cuadros.

  Continuación:
  Tipito que se mueve en el semáforo peatonal

  Documentación: https://wayoda.github.io/LedControl/pages/software

  Create a new LedControl variable.
    * We use pins 2, 3 and 4 on the Arduino for the SPI interface
        BUS: sistema digital que transfiere datos entre los componentes de una computadora.
        SPI: bus estándar para controlar casi cualquier dispositivo electrónico digital que 
            acepte un flujo de bits serie regulado por un reloj (comunicación sincrónica).

    * Pin 2 is connected to the DATA IN-pin of the first MAX7221

    
    * Pin 3 is connected to the CLK-pin of the first MAX7221
    * Pin 4 is connected to the LOAD(/CS)-pin of the first MAX7221
    * There will only be a single MAX7221 attached to the arduino 
   
LedControl lc1=LedControl(2,3,4,1); 

  POSIBLE BUG
  I solved the problem I had with a panel with 5 MAX7219 8x8. 
  I had to edit the library file, MD_MAX72xx_h, and set it to "USE_GENERIC_HW 1" since what comes standard is another.


*/

#include "LedControl.h" 		// incluye libreria LedControl

LedControl lc=LedControl(11,13,10,1);	// crea objeto

#define demora 250			// constante demora con valor de 250

uint64_t tipo_camina[] = {		// array de vectores para cada cuadro
  0x3030303030180808,  // primer cuadro
  0x3030181C7E382202,  // segundo cuadro
  0x30301C7A18242220,  // tercer cuadro
  0x30301818381C1810   // cuarto cuadro
};

void setup() {
  lc.shutdown(0, false);			// enciende la matriz
  lc.setIntensity(0, 4);			// establece brillo
  lc.clearDisplay(0);			    // blanquea matriz
}

void loop(){
  mostrar(0);	// primer cuadro
  delay(demora);	
  mostrar(1);	// segundo cuadro
  delay(demora);
  mostrar(2);	// tercer cuadro
  delay(demora);	
  mostrar(3);	// cuarto cuadro
  delay(demora);	
}

void mostrar(int index){
  uint64_t cuadro = tipo_camina[index];
  for (int i = 0; i < 8; i++) {  			        
    lc.setRow(0, i, (byte)(cuadro >> (8 * (7 - i))));  // Extrae cada byte y lo muestra en la fila correspondiente
  }
}
