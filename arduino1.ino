#include <Keypad.h>

//https://www.instructables.com/Communication-Between-Two-Arduino-Using-UART/
//https://deepbluembedded.com/serial-communication-between-two-arduino-boards/


const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char* send_password;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();
  if (key){
    Serial.print(key);
  }
}