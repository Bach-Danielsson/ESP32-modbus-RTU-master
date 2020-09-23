/*

  Basic.pde - example using ModbusMaster library

  Library:: ModbusMaster
  Author:: Doc Walker <4-20ma@wvfans.net>

  Copyright:: 2009-2016 Doc Walker

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

/*
board used NodeMcu32S , ledbuiltin GPIO 2
*/

#include <ModbusMaster.h>

#define SmartMeter 2  // slave index 
#define _reg_V1 256

// instantiate ModbusMaster object
ModbusMaster node;


void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(9600);  // ESP32 (9600) => Device 9600

  // communicate with Modbus slave ID 2 over Serial (port 0)
  node.begin(SmartMeter, Serial);
}


void loop()
{
  uint32_t result;
  uint16_t data[6];
  // slave: read (6) 16-bit registers starting at register 2 to RX buffer
  result = node.readHoldingRegisters(_reg_V1, 1);

  Serial.println (result);
  
  // do something with data if read is successful
  if (result == node.ku8MBSuccess) { 
    data[0] = node.getResponseBuffer(0);
    Serial.print ("V1=: ");
    Serial.println ((float) data[0]/10);
  }
  else {
    Serial.println ("No (float) data[0]/10 -- recived ");
  }

  delay(1000);

}
