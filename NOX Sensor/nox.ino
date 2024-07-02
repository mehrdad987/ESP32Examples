#include <Wire.h>

#include <CAN.h>                

//---------------------------------- Lambda O2 Nox Sensors /
float ADV_Oxygen;                    //-
float ADV_Lambda;                    //-
int Lambda_sensor = 218038273;       //-
int Nox_sensor = 418385746;          //-
float ADV_NOX;                       //-
int packetSize;                      //-
unsigned int count_for_nox = 0;      //- first the heater then the data
String O2;                           //-
String LAM;                          //-
String NOX;                          //-

void setup(void) {

  Serial.begin(115200);
  if (!CAN.begin(250E3)) {
    Serial.println("Starting CAN failed!");
  }

}

void loop(void) {

  
  if (CAN.available()) {
    CAN.beginExtendedPacket(0x18FEDF00);
    CAN.write(0);
    CAN.write(0);
    CAN.write(0);
    CAN.write(0);
    CAN.write(0);
    CAN.write(0);
    CAN.write(0);
    CAN.write(4);
    CAN.endPacket();
  }
  
    for (int ia = 0; ia <= 10; ia++) {
      packetSize = CAN.parsePacket();
      if (packetSize) {
        if (CAN.packetExtended()) {
        }
        if (CAN.packetRtr()) {
        }
        if ((CAN.packetId()) == Nox_sensor) {
          while (CAN.available()) {
            //                readnox++;
            byte buff[8];
            CAN.readBytes((char *)buff, 8);
            unsigned int byte0 = buff[0];
            unsigned int byte1 = buff[1];
            unsigned int byte2 = buff[2];
            unsigned int byte3 = buff[3];
            unsigned int byte4 = buff[4];
            unsigned int byte5 = buff[5];
            unsigned int byte6 = buff[6];
            unsigned int byte7 = buff[7];
            ADV_NOX = ((((byte1 * 256) + byte0) * 0.05) - 200);
            ADV_NOX = roundf(ADV_NOX * 100) / 100;
            ADV_Oxygen = ((((byte3 * 256) + byte2) * 0.000514) - 12);
            ADV_Oxygen = roundf(ADV_Oxygen * 100) / 100;
            if (ADV_NOX <= 0) {
              ADV_NOX = 0;
              
            }
            int pikup=byte4+byte5+byte6+byte7;
            Serial.print(pikup);
            //                Serial.println(ADV_NOX);
            //                Serial.print("Oxygen status: ");
            //                Serial.println(ADV_Oxygen);
          }
          
          NOX = String(ADV_NOX);
          O2 = String(ADV_Oxygen);
          break;
        }
      }
    }
  CAN.end(); CAN.begin(250E3);
}
/*-----------------------------------------TSK 6 GPS-----------------------------------------*/

