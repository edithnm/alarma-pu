#include <LowPower.h>   //Importar la librería LowPower (para el consumo de energía)

int led = 6;            // led en pin 6
int contacto = 4;       // reed switch en pin 4
int buzzer = 5;         // buzzer en pin 5

void setup() {
  pinMode (led, OUTPUT);      // led como salida
  pinMode (contacto, INPUT);  // reed switch como entrada
  pinMode (buzzer, OUTPUT);   // buzzer como salida
}

void loop() {
  //sleep(8);
  
  if(digitalRead(contacto) == LOW){       // Si los contactos del reed switch están separados (puerta abierta)
    for(int a=0; a<10; a++){              // inicializar ciclo for para interrupciones del led y buzzer
      
      digitalWrite(led,HIGH);             // Prende el LED         
      delay(50);                          // Tiempo         
      digitalWrite (buzzer, HIGH);        // Suena el buzzer
      delay(100);                         // Tiempo
      
      digitalWrite(led,LOW);              // Apaga el LED
      delay(50);                          // Tiempo   
      digitalWrite (buzzer, LOW);         // Silencia el buzzer
      delay(100);                         // Tiempo
    }
    
  }else{                                  // En caso de que los contactos del reed switch estén juntos (puerta cerrada)
      digitalWrite (buzzer, LOW);         // Silencia el buzzer
      digitalWrite (led, LOW);            // Apaga el led
      dormir(4);                          // Función dormir para reducir el consumo de energía en intervalos de 8 segs
  }
}

void dormir(int sec) {      // Función dormir
  while (sec >= 8) {        // contabiliza los segundos mayores o igual a 8
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);   // donde los valores de LowPower.PowerDown muestran:
                                                      // el tiempo que estará dormido usando el Watchdog
    sec -= 8;                                         // apaga los convertidores Analógicos a Digital
  }                                                   // y, apaga el circuito de Brown Out Detection
  if (sec >= 4) {
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
    sec -= 4;
  }
  if (sec >= 2) {
    LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    sec -= 2;
  }
  if (sec >= 1) {
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    sec -= 1;
  }
}
