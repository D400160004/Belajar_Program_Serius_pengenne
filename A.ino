#include <EEPROM.h>
unsigned int a=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  baca_eeprom();
}

void loop() {
  // put your main code here, to run repeatedly:
  a++;
  Serial.println(a);
  EEPROM.write(0, a);
 // EEPROM.update(0, a);
}

void baca_eeprom(){
  a=EEPROM.read(0);
  Serial.println("data terakhir : " +String(a));
}
