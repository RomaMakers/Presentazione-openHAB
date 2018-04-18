#include <SimpleModbusSlave.h>

#define MODBUS_ID 1
#define MODBUS_PINSINK 2
#define RELE_LIGHT_SOFA 3
#define PIR 5


const int regDimension = 16;
static unsigned int holdingRegs[regDimension]; // function 3 and 16 register array

void setup()
{
  modbus_configure(&Serial, 57600, SERIAL_8N2, MODBUS_ID, MODBUS_PINSINK, regDimension, holdingRegs);

  for (int i=3; i<=4; i++){
      pinMode(i, OUTPUT);
      digitalWrite(i, LOW);  
    }
  
  pinMode(PIR, INPUT);
  for (int i=0; i<regDimension; i++) holdingRegs[i] = 0;

}

void loop()
{  
  int error = modbus_update();
  
  digitalWrite(RELE_LIGHT_SOFA, (holdingRegs[0] +1 ) %2);
  holdingRegs[1] = digitalRead(PIR);
  
  digitalWrite(13, (holdingRegs[1]));
  
}

