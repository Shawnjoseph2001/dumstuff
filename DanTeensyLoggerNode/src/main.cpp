// Renegade CAN Data logger and SF Stand message interpreter
// Unfortunately by Dan


#include <Arduino.h>
#include <FlexCAN.h>
#include <kinetis_flexcan.h>
#include <WireKinetis.h>
#include <SD.h>
#include <SPI.h>
//#include <SensorDefinitions.h>
//#include <SensorClass.h>
//#include <vector> 


CAN_message_t message0;
CAN_message_t message1;
elapsedMillis sinceGUIsend;

//loop iterator declarations
int i;
int j;
int k;

//This looks awful, but it creates arrays to store every possible CANID frame's bytes to then retransmit

int CANIDARRAYBytes[2048][8]; //array with positions for all possible CANIDs in 11 bit standard ID format for storing recent messages
bool CANIDARRAYLen[2048];

//array for using in the values converted from GUI
//This exists so that any value that doesn't get a conversion applied still gets sent to the Pi.
//That automates sending the state report frames, anything we didn't convert is passed as is.
//It also sends any frames that happen to not have been in our conversion code incidentally to the Pi for it's low rate logging code to still catch.
//This could be structured as ints instead of 2D array, but then you need to write CAN code to chop up the ints automatically for the sends.
int CANIDARRAYConvertedBytes[2048][8]; 

int counter = 0;



/*
  SD card read/write
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11, pin 7 on Teensy with audio board
 ** MISO - pin 12
 ** CLK - pin 13, pin 14 on Teensy with audio board
 ** CS - pin 4, pin 10 on Teensy with audio board
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 	 
 */
 


File myFile;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// Teensy audio board: pin 10
// Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD
// Wiz820+SD board: pin 4
// Teensy 2.0: pin 0
// Teensy++ 2.0: pin 20
const int chipSelect = BUILTIN_SDCARD;

void setup()
{

Can0.begin(500000);
Can1.begin(500000);




  // SD set up
//  pinMode(BUILTIN_SDCARD, OUTPUT);
//  if(!builtInSD.begin(BUILTIN_SDCARD))
//  {
//    Serial.println("Built in SD card failed or not present.");
//  }

  // set up the csv
//  File dataFile = builtInSD.open("datalog.csv", FILE_WRITE);
//  if(dataFile)
//  {
    // sensor columns
  //  for (SENSOR* sensor : sensorArray)
  //  {
  //    std::string name{sensor->getSensorName()};
  //    dataFile.print(name.c_str());
  //    dataFile.print(", ");
  //  }

    // valve status column
  //  dataFile.println("ValveStatus, ");
  //}
  //dataFile.close();


  
/*  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // open the file. 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  } */
}

void loop()
{
/// CAN read on CAN bus from prop stand/rocket
  Can0.read(message0);
/*   Serial.print("Received CAN message");
  Serial.println();
  Serial.print(message0.id);
  Serial.println();
  Serial.print(message0.buf[0]);
  Serial.print(", ");
  Serial.print(message0.buf[1]);
  Serial.print(", ");
  Serial.print(message0.buf[2]);
  Serial.print(", ");
  Serial.print(message0.buf[3]);
  Serial.print(", ");        
  Serial.print(message0.buf[4]);
  Serial.print(", ");
  Serial.print(message0.buf[5]);
  Serial.print(", ");
  Serial.print(message0.buf[6]);
  Serial.print(", ");
  Serial.print(message0.buf[7]);
  Serial.print(", "); */

    CANIDARRAYLen[message0.id] = message0.len;
/*     Serial.print(message0.len);
    Serial.println();
    Serial.print(CANIDARRAYLen[message0.id]);
    Serial.println(); */
    for (int i = 0; i < message0.len; i++)
    {
      CANIDARRAYBytes[message0.id][i] = message0.buf[i];
      CANIDARRAYConvertedBytes[message0.id][i] = message0.buf[i]; //fills second array to swap converted values over in later step
    }


/// CAN send on CAN bus to GUI, every 100 ms
  if (sinceGUIsend >= 1000) {
    //STICK SENSOR CONVERSIONS HERE!!!!!!!! Only do it for GUI refreshes not continuously
    //Use the CANIDARRAYConvertedBytes array to overwrite the converted values onto, 
    //that way anything like state reports that we don't convert pass through.
    //output of conversions should break the value back into CAN frame byte format to write to the send array
    
    for (int i = 0; i < 2048; i++)
    {
      /* code */
    }
    
/////BELOW IS THE CANSEND CODE, as long as you pack the converted values into CANIDARRAYConvertedBytes it will handle everything
    for (int j = 0; j < 2048; j++);
    {
      if (CANIDARRAYLen[j] != false) {
        Serial.print(CANIDARRAYLen[j]);
        Serial.println();
        Serial.print(j);
        Serial.println();
    
      
        message1.id = j;
        message1.len = CANIDARRAYLen[j];
        for (int k = 0; k < message1.len; k++);
        { 
          CANIDARRAYConvertedBytes[j][k] = message1.buf[k];  
        }
        
/*         Serial.print(message1.id);
        Serial.println();
        Serial.print(message1.buf[0]);
        Serial.print(", ");
        Serial.print(message1.buf[1]);
        Serial.print(", ");
        Serial.print(message1.buf[2]);
        Serial.print(", ");
        Serial.print(message1.buf[3]);
        Serial.print(", ");        
        Serial.print(message1.buf[4]);
        Serial.print(", ");
        Serial.print(message1.buf[5]);
        Serial.print(", ");
        Serial.print(message1.buf[6]);
        Serial.print(", ");
        Serial.print(message1.buf[7]);
        Serial.print(", "); */

        Can1.write(message1);
      }
    }
    counter = counter+1;
    Serial.println();
    Serial.print("GUI Frame Loop Counter: ");
    Serial.print(counter);
    Serial.println();
    sinceGUIsend = 0;  
  }

}

