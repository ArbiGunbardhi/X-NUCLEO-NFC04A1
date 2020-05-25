/**
 ******************************************************************************
   @file    X_NUCLEO_NFC04A1_HelloWorld.ino
   @author  STMicroelectronics
   @version V1.0.0
   @date    22 November 2017
   @brief   Arduino test application for the STMicrolectronics
            X-NUCLEO-NFC04A1. NFC tag based on ST25DV device.
            This application makes use of C++ classes obtained from the C
            components' drivers.
 ******************************************************************************
   @attention

   <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
     1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.
     2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the documentation
        and/or other materials provided with the distribution.
     3. Neither the name of STMicroelectronics nor the names of its contributors
        may be used to endorse or promote products derived from this software
        without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ******************************************************************************
*/

/**
******************************************************************************
  How to use this sketch

  This sketch uses the I2C interface to communicate with the NFC device.
  It writes an NFC tag type URI (Uniform Resource Identifier) and reads this same tag.
  Choose the uri by changing the content of uri_write.

  When the NFC module is started and ready, the message "Sytstem init done!" is
  displayed on the monitor window. Next, the tag is written, read and printed on
  the monitor window.

  You can also use your smartphone to read/write a tag.
  On Android, donwload a NFC Tools. Then start the app, check if NFC is activated
  on your smartphone. Put your smartphone near the tag, you can read it. You can
  write a tag with this app.
******************************************************************************
*/

#include "x_nucleo_nfc04.h"

#define SerialPort      Serial

void setup() {
  const char uri_write_message[] = "st.com/st25";       // Uri message to write in the tag
  const char uri_write_protocol[] = URI_ID_0x01_STRING; // Uri protocol to write in the tag
  String uri_write = String(uri_write_protocol) + String(uri_write_message);
  String uri_read;

  // Initialize serial for output.
  SerialPort.begin(115200);

  if (X_Nucleo_Nfc04.begin() == 0) {
    SerialPort.println("System Init done!");
    X_Nucleo_Nfc04.ledOn(GREEN_LED);
  } else {
    SerialPort.println("System Init failed!");
    while (1);
  }

  if (X_Nucleo_Nfc04.writeURI(uri_write_protocol, uri_write_message, "")) {
    SerialPort.println("Write failed!");
    while (1);
  }

  X_Nucleo_Nfc04.ledOn(BLUE_LED);

  delay(100);

  if (X_Nucleo_Nfc04.readURI(&uri_read)) {
    SerialPort.println("Read failed!");
    while (1);
  }

  SerialPort.println(uri_read.c_str());

  if (strcmp(uri_read.c_str(), uri_write.c_str()) == 0) {
    SerialPort.println("Successfully written and read!");
    X_Nucleo_Nfc04.ledOn(YELLOW_LED);
  } else {
    SerialPort.println("Read bad string!");
  }
}

void loop() {
  //empty loop
}