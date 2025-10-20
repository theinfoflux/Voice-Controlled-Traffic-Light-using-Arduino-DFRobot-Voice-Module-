#include "DFRobot_DF2301Q.h"
//I2C communication
DFRobot_DF2301Q_I2C asr;
int red=2;
int yellow=3;
int green=4;

void setup() {
  Serial.begin(115200);
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);

  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(7);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);

 asr.playByCMDID(1);   // Wake-up command

  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID

}

void loop() {
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  switch (CMDID) {
         case 116:        // Set to Red                                       
       digitalWrite(red,HIGH);    
          break;
         case 118:        // Set to Yellow                                       
       digitalWrite(yellow,HIGH);  
          break;   
         case 119:        //Set to green                                       
       digitalWrite(green,HIGH);
          break;
         case 82:        // reset                                      
       digitalWrite(red,LOW);
       digitalWrite(yellow,LOW);
       digitalWrite(green,LOW);
          break;                       
    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}
