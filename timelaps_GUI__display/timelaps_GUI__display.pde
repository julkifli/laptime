import processing.serial.*;

int lf = 10;    // Linefeed in ASCII
String myString = null;

float num; //to store incomming value from serial port
Serial arduino; //naming our serial port as "arduino"

void setup() {
   
  fullScreen(); //output window size full screen
  arduino = new Serial(this, Serial.list()[2], 9600); //initializing port, in my case arduino is no.4 in the list 
  arduino.clear();


}

void draw() {

  while (arduino.available() > 0) {
    background(200);
    myString = arduino.readStringUntil(lf);
    if (myString != null) {
    print(myString);  // Prints String
    num=float(myString);  // Converts and prints float
    println(num);
    }
    
    
    println(num);
    fill(0,0,0);
  textSize(300);
  textAlign(CENTER);

  text(num, width/2, height/2);
  }
  

arduino.clear();
    
}
