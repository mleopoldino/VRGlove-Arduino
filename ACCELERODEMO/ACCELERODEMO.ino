/*
 TCC Fatec - Control VRGlove
 AcceleroDemo - Teste AcelerometroMMA7361
 */

// include the library code:
#include <LiquidCrystal.h>
#include <AcceleroMMA7361.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// constants won't change. They're used here to set pin numbers:
const int buttonPin = A4;     // the number of the pushbutton pin

AcceleroMMA7361 accelero;   //Variavel Aceletrometro
int x;    //Pos. X
int y;    //Pos. Y
int z;    //Pos. Z

//Variavel controle de Posição
char pos;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  //Config Serial COM
  Serial.begin(9600);   //Inicia Serialização e Define velocidade de Comunicação

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
   
  // set up the Accelero ports:
  //accelero.begin(13, 12, 11, 10, A0, A1, A2); 
  accelero.begin(13, 12, 11, 2, A0, A1, A2);      //Alterado o pino 10 para 2 devido uso do shield de LCD 
  accelero.setARefVoltage(3.3);                   //sets the AREF voltage to 3.3V -- Efetuar jump por wire wrap no shield (3.3v para AREF)
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  accelero.calibrate();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("TCC Fatec");
  buttonState = LOW;
 
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  
  x = accelero.getXRaw();  //Leitura da posição X -- também posso efetuar a leitura em volts getYVolt()
  y = accelero.getYRaw();  //Leitura da posição Y
  z = accelero.getZRaw();  //Leitura da posição Z

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // Button on:
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Botao on");

    //Set Fire
    Serial.write(4);
    Serial.flush();
    
  } else {
    // Button off:
    //Set Fire
    //Serial.write(5);
    //Serial.flush();
    
    lcd.setCursor(0,0);
    lcd.print("TCC Fatec");  
    
    lcd.setCursor(3,1);            // move to the begining of the second line 
    lcd.print("UD");                // Print pos Y 
    lcd.setCursor(5,1);
    lcd.print(y);
  
    lcd.setCursor(9,1);           // move to the begining of the second line 
    lcd.print("LR");                // Print pos Z
    lcd.setCursor(11,1);
    lcd.print(z);

    //Definição de Posição do Joystick
    if(y>=600){
      //pos = 'UP';
      Serial.write(0);
      Serial.flush();
    }

    if(y<=400){
      //pos = 'DOWN';
      Serial.write(1);
      Serial.flush();
    }

    if(z>=600){
      //pos = 'RIGHT';
      Serial.write(2);
      Serial.flush();
    }

    if(z<=450){
      //pos = 'LEFT';
      Serial.write(3);
      Serial.flush();
    }    
  }

  //Delay time to complete de Readcycle
  delay(250);

  
}


