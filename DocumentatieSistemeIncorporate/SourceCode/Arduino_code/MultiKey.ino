///192.168.43.84///
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define Password_Length 5
#define SS_PIN 10
#define RST_PIN 13
int RelayPin = A2;
int FlashPin = A0;
int FaceDetect = A1;
int RfidLeds = 8;
int parity = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);
char Data[Password_Length];
char Master[Password_Length] = "1111";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
bool Rfid_is_good;
char customKey;
int i;
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {3, 2, 18, 19}; //connect to the column pinouts of the kpd

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(RelayPin, OUTPUT);
  pinMode(RfidLeds, OUTPUT);
  pinMode(FlashPin, OUTPUT);
  Rfid_is_good = false;
  Pass_is_good = false;

  digitalWrite(RelayPin, LOW);
  digitalWrite(RfidLeds, HIGH);
  delay(500);
  digitalWrite(RfidLeds, LOW);
  delay(500);
  digitalWrite(RfidLeds, HIGH);
}

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  i=0;
  return;
}

bool checkCard() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  String content = "";
  byte letter;
  for (byte j = 0; j < mfrc522.uid.size; j++)
  {
    Serial.print(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[j], HEX);
    content.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[j], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "5A 5D BE 82")
  {
    Serial.print(" Authorized card access ");
    Rfid_is_good = true;
    return true;
  }
  else {
    Serial.println(" Access card denied ");
  }
  return false;
}

bool key() {
  //if (Pass_is_good) return;
  //if (checkCard() || Rfid_is_good) return;
  for(i=0; i<Password_Length; i++)
  {
    checkCard();
    if(Rfid_is_good)
    {
       clearData();
       return false;
    }
    customKey = customKeypad.getKey();
    if (customKey)
    {
      Data[data_count] = customKey;
      data_count++;
    }else if (customKey == '#')
    {
      clearData();
      return false;
    }
    
    if (data_count == Password_Length - 1)
    {
      if (!strcmp(Data, Master))
      {
        Pass_is_good = true;
        Serial.print("Correct password ");
        clearData();
        return true;
      }else
      {
        Serial.print("Incorrect password ");
        Serial.println(Data);
        clearData();
        return false;
      }
    }
  }
  return false;
}

void Camera_Flash() {
  int sensorValue = analogRead(A3);
  float voltage = sensorValue * (5.0 / 1023.0);
  if (voltage < 0.2) {
    digitalWrite(FlashPin, HIGH);
  }
  else {
    digitalWrite(FlashPin, LOW);
  }
  //Serial.println(voltage);
}


void loop()
{
  int time = 5000;
  float detect = analogRead(FaceDetect)*(5.0/1023.0);
  key();
  checkCard();
  Camera_Flash();
  if (Pass_is_good || Rfid_is_good)
  {
    while( (detect < 1.9) && (time > 0) )
      {
        time --;
        delay(1);
        Camera_Flash();
        detect = analogRead(FaceDetect)*(5.0/1023.0);
      }
    if(detect>1.9)
     {
       digitalWrite(RelayPin, HIGH);
       digitalWrite(RfidLeds, LOW);
       Serial.println(" + face detected == unlock door  \' :)\' ");
       delay(3000);
       digitalWrite(RelayPin, LOW);
       digitalWrite(RfidLeds, HIGH);
     }
    Pass_is_good = false;
    Rfid_is_good = false;
  }
}
