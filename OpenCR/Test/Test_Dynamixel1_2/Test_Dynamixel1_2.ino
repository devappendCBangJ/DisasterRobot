#include <SoftHalfDuplexSerial.h>
#include <DynamixelAx.h>

softHalfDuplexSerial port(8); // data pin 8
dxlAx dxlCom(&port);

String _readString;         // Input string from serial monitor
bool _strComplete = false;
int _id = 6;                // Default Dynamixel servo ID
int stat = 0;

void printServoId(String msg);
void printDxlResult();
void printDxlError(unsigned short dxlError);

void setup() {

  // Open serial communications and wait for port to open (PC communication)
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Starting COM!");

  dxlCom.begin(115200);

  dxlCom.ping(_id);
  printDxlResult();

}
void printDxlResult()
{
   while(!dxlCom.dxlDataReady());        // waiting the answer of servo
   printDxlError(dxlCom.readDxlError());
   Serial.println(dxlCom.readDxlResult());
}
void printDxlError(unsigned short dxlError)
{
  // after any operation error can be retrieve using dx::readDxlResult() (i.e. after read or write operation)
  if(dxlError == DXL_ERR_SUCCESS)
    Serial.println("OK");
  else
  {
    if (dxlError & DXL_ERR_VOLTAGE)
      Serial.print("voltage out of range-");
    if (dxlError & DXL_ERR_ANGLE)
      Serial.print("angle out of range-");
    if (dxlError & DXL_ERR_OVERHEATING)
      Serial.print("overheating-");
    if (dxlError & DXL_ERR_RANGE)
      Serial.print("cmd out of range-");
    if (dxlError & DXL_ERR_TX_CHECKSUM)
      Serial.print("Tx CRC invalid-");
    if (dxlError & DXL_ERR_OVERLOAD )
      Serial.print("overload-");
    if (dxlError & DXL_ERR_INSTRUCTION )
      Serial.print("undefined instruction-");
    if (dxlError & DXL_ERR_TX_FAIL )
      Serial.print("Tx No header-");
    if (dxlError & DXL_ERR_RX_FAIL )
      Serial.print("Rx No header-");
    if (dxlError & DXL_ERR_TX_ERROR  )
      Serial.print("Tx error-");
    if (dxlError & DXL_ERR_RX_LENGTH   )
      Serial.print("Rx length invalid-");  // Not implemented yet
    if (dxlError & DXL_ERR_RX_TIMEOUT)
      Serial.print("timeout-");
    if (dxlError & DXL_ERR_RX_CORRUPT)
      Serial.print("Rx CRC invalid-");
    if (dxlError & DXL_ERR_ID )
      Serial.print("Wrong ID answered-"); // ?? Hardware issue
    Serial.println();
  }
}
void loop()
{

    dxlCom.setTorqueLimit(_id,100);
    printDxlResult();
    dxlCom.setMovingSpeed(_id,100);
    printDxlResult();
    
    dxlCom.setGoalPosition(_id,900);
    printDxlResult();
    delay(5000);

    dxlCom. setTorqueLimit(_id,100);
    printDxlResult();
    dxlCom.setMovingSpeed(_id,100);
    printDxlResult();
    
    dxlCom.setGoalPosition(_id,100);
    printDxlResult();
    delay(5000);
  
}
