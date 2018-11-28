/*


 */
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial scom(7, 6); // RX, TX

// LCD settings
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  scom.begin(9600);
  scom.flush();
}

int distance = -1;
int temperature = -1;
unsigned int lsb = 0;
unsigned int msb = 0;

void loop() { 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  if (distance<0) {
    lcd.print("?");
  } else {
    lcd.print(distance);
    lcd.print("mm");
  }
  lcd.setCursor(0, 1);
  lcd.print("Temperature:");
  if (temperature<0) {
    lcd.print("?");
  } else {
    lcd.print(temperature);    
    lcd.write(0xdf);
    lcd.print("C");
  }

  scom.write(0x55);
  delay(250);
  if (scom.available()>=2) {
    msb=scom.read();
    lsb=scom.read();
    distance = (msb*256)+lsb;    
  } else {
    distance = -1;
  }
  scom.write(0x50);
  delay(250);
  if (scom.available()>=1) {
    lsb=scom.read();
    temperature = lsb-45;
  } else {
    temperature = -1;
  }
}
