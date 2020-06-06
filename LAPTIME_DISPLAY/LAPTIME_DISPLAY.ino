
#include "LedControl.h"


#define inPin 9   // sensor E18-D80NK
#define tAR 200  
#define tAct 10   

LedControl lc=LedControl(12,11,10,1);

void setup() {
  pinMode (inPin, INPUT_PULLUP);
  pinMode (13, OUTPUT);
  Serial.begin (9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,10);
  lc.clearDisplay(0);
}

bool count = false;
long tInicial = 0;
float seconds = 0;
String cadena = "";

void reset (){
  seconds = 0;
  tInicial = millis ();
}

void loop() {

//LOOP WHILE TIME IS NOT RUNNING
  while (count == 0) {
    digitalWrite (13, LOW);
    display7();
    if (!digitalRead (inPin)) {
      reset ();
      count = true;
      delay (tAR);
      break;
    }
  }

// RUN THE TIME
  while (count == 1) {
    digitalWrite (13, HIGH);
    seconds =  (float) (millis () - tInicial) / 1000;
    display7();
    if (!digitalRead (inPin)) {
      delay (tAR);
      count = false;
      break;
    }
  }
}

int value = 0;

void display7(){
  String sec = String (seconds,3);
  if (seconds < 10){
    sec = "0"+sec;
  }
  int tam = sec.length();
  if (tam>0){
    lc.clearDisplay(0);
    int e = 0;
    for (int i=0; i<tam; i++){
      if (sec.charAt(i)!='.'){
        String v = "";
        v+= sec.charAt(i);
        value = v.toInt ();
        lc.setDigit(0,6-e,value,false);
        e++;
      }else{
        lc.setDigit(0,6-e+1,value,true);
      }
    }
  }
}
