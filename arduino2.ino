#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <string.h>

Servo servoMotor;

const int pir1SensorPin = 2;
const int pir2SensorPin = 3;
const int buzzer1Pin = 4;
const int buzzer2Pin = 5;
const int servoPin = 6;
int pir1State = 0;
int pir2State = 0;

bool systemArmed = true;

char password[6];

Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  
  servoMotor.attach(servoPin);
  lcd_1.begin(16, 2);
 
  pinMode(2, INPUT);
  pinMode(buzzer1Pin, OUTPUT);
  pinMode(buzzer2Pin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  
 pir1State = digitalRead(2);
 pir2State = digitalRead(3);
  
 int pirStates[2];
  
 pirStates[0] = pir1State;
 pirStates[1] = pir2State; 
 
  receive_password();
 Serial.print(password);
 
  if(strcmp(password,"ABCD4")==0){
    systemArmed=true;
  }
 if(systemArmed == true){
   lcd_1.setCursor(0, 0);
   lcd_1.print("System armed");
   alarm_trigger(pirStates);
 }
  
 if(systemArmed == false){
   lcd_1.setCursor(0, 0);
   lcd_1.print("System not armed");
 }
  
 delay(500); // Reduced delay for faster response
}

void alert(String message){
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(message);
}

void print_states(){
  Serial.println("PIR Motion Detection Test");

  Serial.print("PIR 1 State: ");
  Serial.println(pir1State);
  
  Serial.print("PIR 2 State: ");
  Serial.println(pir2State);
}

void zone_libere(){
    lcd_1.clear();
    lcd_1.setCursor(2, 0);
    lcd_1.print("Zone libere");
    noTone(buzzer1Pin);
  	noTone(buzzer2Pin);
    delay(1000);  // Wait for 1 second before checking again
}

void alarm_trigger(int pirStates[]){
  	
  if(pirStates[0]==1 && pirStates[1]==1){
  	alert("Alerta ambele camere");
    tone(buzzer1Pin,2000,1000);
    delay(1000);
    tone(buzzer2Pin,1000,750);
    delay(3000); // Reduced delay between consecutive alerts
  	}
  else if (pirStates[0] == 1) {
    alert("Alerta camera 1");
    tone(buzzer1Pin, 2000, 1000);
    delay(3000);  // Reduced delay between consecutive alerts
  } 
  else if(pirStates[1] == 1) {
    alert("Alerta camera 2");
    tone(buzzer2Pin, 2000, 1000);
    delay(3000);  // Reduced delay between consecutive alerts
  }
  else{
  	zone_libere();
  }
}

void receive_password(){
  
  for(int i=0;i<=strlen(password);i++){  
    if (Serial.available() > 0){
      password[i] = Serial.read();
    }
  }
  password[strlen(password)+1]='\0';
}