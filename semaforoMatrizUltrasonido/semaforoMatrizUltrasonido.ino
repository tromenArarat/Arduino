#include <LedControl.h>

// Configuración de los pines para el sensor ultrasónico
const int trigPin = 7;
const int echoPin = 6;

// Pines de los LEDs del semáforo
const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;

// Configuración de la matriz de LEDs 8x8 (utilizando pines 11, 13, 10 para Data In, Clock, y Chip Select)
LedControl lc = LedControl(11, 13, 10, 1); // DIN=11, CLK=13, CS=10

// Distancia umbral para activar el semáforo (50 cm)
const int thresholdDistance = 50;

// Variables para la animación de la matriz de LEDs
const int animationDelay = 250; // Duración de la pausa entre cuadros
unsigned long previousMillis = 0;

// Patrones de animación para el "muñeco caminando" y "muñeco esperando" (quieto)
uint64_t walkFrames[4] = { 
  0x3030303030180808, 
  0x3030181C7E382202, 
  0x30301C7A18242220, 
  0x30301818381C1810 
};
uint64_t waitFrame = 0x3030303030180808; // Muñeco en posición de espera

void setup() {
  // Configuración de los LEDs del semáforo
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Configuración de los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicialización de la matriz de LEDs
  lc.shutdown(0, false);      // Activa la matriz de LEDs
  lc.setIntensity(0, 4);      // Ajusta el nivel de brillo
  lc.clearDisplay(0);         // Limpia la matriz de LEDs
}

void loop() {
  int distance = getDistance(); // Obtiene la distancia medida
  
  if (distance < thresholdDistance) {
    // Secuencia del semáforo cuando se detecta un objeto cerca
    digitalWrite(redPin, HIGH);  // Activa el LED rojo
    displayWalkAnimation();      // Muestra la animación de caminata en la matriz de LEDs
    delay(2000);                 // Duración del semáforo en rojo

    digitalWrite(redPin, LOW);   // Apaga el LED rojo
    digitalWrite(yellowPin, HIGH); // Activa el LED amarillo
    displayWaitFrame();          // Muestra el muñeco en espera en la matriz de LEDs
    delay(1000);                 // Duración del semáforo en amarillo

    digitalWrite(yellowPin, LOW); // Apaga el LED amarillo
    digitalWrite(greenPin, HIGH); // Activa el LED verde
    displayWaitFrame();          // Muestra el muñeco en espera en la matriz de LEDs
    delay(3000);                 // Duración del semáforo en verde

    digitalWrite(greenPin, LOW); // Apaga el LED verde
  } else {
    // Modo de espera cuando no se detecta un objeto cercano
    displayWaitFrame();         // Muestra el muñeco en espera en la matriz de LEDs
    digitalWrite(redPin, LOW);  
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  }
}

// Función para leer la distancia desde el sensor ultrasónico
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Función para mostrar la animación de caminata en la matriz de LEDs
void displayWalkAnimation() {
  for (int frame = 0; frame < 4; frame++) {   // Itera sobre los 4 cuadros de la animación
    uint64_t cuadro = walkFrames[frame];      // Obtiene el cuadro actual de la animación
    for (int i = 0; i < 8; i++) {             // Itera sobre cada fila de la matriz
      byte rowValue = (byte)(cuadro >> (8 * (7 - i))); // Extrae el valor de cada fila
      lc.setRow(0, i, rowValue);              // Envía el valor de la fila a la matriz
    }
    delay(animationDelay); // Pausa entre cuadros
  }
}

// Función para mostrar el muñeco en espera (quieto) en la matriz de LEDs
void displayWaitFrame() {
  uint64_t cuadro = waitFrame;               // Cuadro de la posición en espera
  for (int i = 0; i < 8; i++) {              // Itera sobre cada fila de la matriz
    byte rowValue = (byte)(cuadro >> (8 * (7 - i))); // Extrae el valor de cada fila
    lc.setRow(0, i, rowValue);               // Envía el valor de la fila a la matriz
  }
}

