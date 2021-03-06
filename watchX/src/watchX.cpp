

//#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
//#include <TimeLib.h>
#include "watchX.h"
#include "oled.h"
#include "cpu.h"


#include "gyrocube.h"
#include "mag3110.h"
//#include "pressure.h"

#include "resources.h"

#include "watchface.h"

#include "menu.h"
#include "battery.h"
#include "torch.h"
#include "altitude.h"
#include "pressure.h"
#include "temperature.h"
#include "rtc.h"
#include <Tones.h>
#include "soundfx.h"
#include "menu.h"

#include "bluetooth.h"
//#include "watchXmpu6050.h"
#include "tinyMpu6050.h"
//#include <tinyMpu6050.h>
#include "settings.h"


// Declared weak in Arduino.h to allow user redefinitions.
//int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
//void initVariant() __attribute__((weak));
//void initVariant() { }

//void setupUSB() __attribute__((weak));
//void setupUSB() { }
/*
int main(void)
{
//	init();

	//initVariant();

#if defined(USBCON)
	//USBDevice.attach();
#endif

	setup();

	for (;;) {
		loop();
	//	if (serialEventRun) serialEventRun();
	}

	return 0;
}
*/


//BMP280 bmp280;
int16_t ac[7]; /// acceleration detect

unsigned char animation_offsetY=0; /// screen transitions position

volatile uint8_t animating=1;
const uint8_t melody[]={NOTE_B0};
//volatile uint8_t mpuIsReady=1;

extern volatile uint8_t animating;
volatile unsigned long lastcolon;

char strtmpbuf[15];

//extern volatile unsigned long lastcolon;
func_type functions[HANDLEDFUNCTIONS_COUNT+3];

func_type nextUIFunc=NULL;

//MPU6050 accelgyro(0x69);

//func_type usbFunc =NULL,sw1Func=NULL,sw2Func=NULL,sw3Func=NULL,uiFunc=NULL;
unsigned char DEVICESTATE=0;
unsigned char Old_DEVICESTATE=DEVICESTATE;


//func_type usbFunc =NULL,sw1Func=NULL,sw2Func=NULL,sw3Func=NULL,uiFunc=NULL,batteryFunc=NULL,bleFunc=NULL;









void updateThings( ){

//get3231Date();
//  dt =Rtc.GetDateTime();// RtcDateTime(__DATE__, __TIME__);

//  if(seconds==0) {   /// TODO change batteryread to something more global


  if(millis()-batteryread>50){
    updateMpu6050();
     handleBle();
    batterylevel=readBattery(BATTERY_EN,BATTERY_PIN);
     //updateMpu6050();
  //  updateMpu6050();
if(batterylevel<530){

}else{

//   mpu.readRawGyro();
// MPU6050_update();
//  MPU6050_calc();
//  getPressure();
//  handleBle(true);
}



  batteryread=millis();

}else{


}
  //}
}

void nextSecond( ){

//if(lastcolon>=160){



//}
switch(watchMode){
  case 0:
  case 1:
if(!animating) lastcolon=0;
  animating=!animating;
curtm[0]+=animating;
if(animating){
  if(curtm[0]==60){

     curtm[0]=0;

     curtm[1]++;
          if(curtm[1]==60){
              curtm[1]=0;
              curtm[2]++;
              if(curtm[2]==24){
                  curtm[2]=0;
                  curtm[3]++;
                  curtm[4]++;
                  if(curtm[4]>=30){
                    //// need read  time ?

                  }

              }

          }

  }
}



break;
default :

break;
}
//lastcolon=0;
///secondsofday+=animating;


}

void   gotoWatchFace(){

stopSqw();

watchMode=0;
          nextUIFunc= drawWatchFace;//printWatchFace;//printWatchFace;// drawWatchFace;// printWatchFace;
          functions[sw1Func]=gotoMenu; /// TODO here i am
          functions[sw2Func]=NULL;
          functions[sw3Func]=NULL;

    //     functions[usbFunc]=drawUsb;
    //  functions[batteryFunc]=drawBattery;
    //  functions[updateFunc]=updateThings;
  //    }
  }


  void   gotoBlueToothSettings(){

//  stopSqw();
//  EEPROM.write(0,8);
//  Serial.println(EEPROM.read(0));
nextUIFunc=drawSettings;
functions[sw1Func]=gotoMenu; /// TODO here i am
functions[sw2Func]=settingsSw1;
functions[sw3Func]=settingsSw2;
/*
  watchMode=0;
            nextUIFunc= drawWatchFace;//printWatchFace;//printWatchFace;// drawWatchFace;// printWatchFace;
            functions[sw1Func]=gotoMenu; /// TODO here i am
            functions[sw2Func]=NULL;
            functions[sw3Func]=NULL;
*/
      //     functions[usbFunc]=drawUsb;
      //  functions[batteryFunc]=drawBattery;
      //  functions[updateFunc]=updateThings;
    //    }
    }

void gotoMenu( ){
stopSqw();


menuspeed=0;
if(menuapp==1){
  menuapp=0;
  menuindex=MENUCOUNT-1;
}


        nextUIFunc=drawMenus;

         functions[sw1Func]=menusw1;
       functions[sw2Func]=menusw2;
          functions[sw3Func]=menusw3;

        //  functions[batteryFunc]=NULL;

//     functions[usbFunc]=NULL;
         // Old_DEVICESTATE=DEVICESTATE; /// TODO DEFINE ACTIONCOMPLETE


}

void gotoSettings( ){
stopSqw();
menuapp=1;
menuindex=0;
//    ssd1306_clearScreen();
        //  usbFunc= drawUsb;
      ///  nextUIFunc=functions[ uiFunc];
  //  nextUIFunc=drawSettings;
    nextUIFunc=drawMenus;
         functions[sw1Func]=menusw1;
         functions[sw2Func]=menusw2;
          functions[sw3Func]=menusw3;
        //  speed=0;
        //  functions[batteryFunc]=NULL;
        //  batteryFunc=drawBattery;
      //functions[usbFunc]=NULL;
         // Old_DEVICESTATE=DEVICESTATE; /// TODO DEFINE ACTIONCOMPLETE



}


  void gotoGyroFace(){
    stopSqw();

            nextUIFunc=drawGyroCube;//printWatchFace;//printWatchFace;// drawWatchFace;// printWatchFace;
            functions[sw1Func]=gotoMenu;
            functions[sw2Func]=NULL;
            functions[sw3Func]=NULL;
            //    nextUIFunc=functions[ uiFunc];
          //  sw2Func=gotoMenu;
          //  sw3Func=NULL;
      //  functions[  bleFunc] =handleBle;
      //     functions[usbFunc]=NULL;
    //    functions[batteryFunc]=NULL;
      //  functions[updateFunc]=updateThings;

    }
void gotoStopWatch(){
  stopSqw();
   watchMode = 1;
              nextUIFunc=drawWatchFace;
              functions[sw1Func]=gotoMenu;
              functions[sw2Func]=watchsw1;
              functions[sw3Func]=watchsw2;

}
void gotoBlueTooth(){
  sound.tone(1200, 1000,600, 500,1800, 400);
  stopSqw();
    //if(animation_offsetY==0)
        //   if( (~SW1_WASPUSHED)&SW1_PUSHED){
                nextUIFunc=drawBle;
              functions[sw1Func]=gotoMenu;
              functions[sw2Func]=NULL;
              functions[sw3Func]=NULL;
    //  }
}

void gotoTorch(){
  stopSqw();

              functions[uiFunc]=drawTorch;
              functions[sw1Func]=gotoMenu;
              functions[sw2Func]=NULL;
              functions[sw3Func]=NULL;

}




/*
void intUpdate(){

mpuIsReady=1;
}
*/
void setup()
{
      /// stopSqw();
      menuspeed=0;

      sound.tone(1200, 100,1000, 50,1800, 200);
      //setPrescale();


      Wire.begin();

      //timerOneFunc=timerOneTones;
      /* Set timer1 interrupt to 20Hz */
      //  startTimerOne();

      //Serial.println("Hello");
      SPI.begin();



  //    Serial.begin(115200);
    //  while(!Serial);
    //  for(int a=0;a<32;a++)
    //  Serial.write(EEPROM.read(100+a));
      pinMode(MPU_INT,INPUT_PULLUP);
      pinMode(CHARGE_PIN,INPUT);
      pinMode(13,OUTPUT);
      pinMode(rstPin, OUTPUT);
      pinMode(LED1, OUTPUT);
      pinMode(LED2, OUTPUT);
      pinMode(cesPin, OUTPUT);
      pinMode(dcPin, OUTPUT);

      digitalWrite(rstPin, HIGH);
      digitalWrite(MPU_INT,LOW);
      digitalWrite(rstPin, HIGH);
      digitalWrite(dcPin, HIGH);
      digitalWrite(cesPin, HIGH);
      pinMode(SW1,INPUT_PULLUP);
      pinMode(SW2,INPUT_PULLUP);
      pinMode(SW3,INPUT_PULLUP);



      pinMode(BATTERY_EN, OUTPUT);
      digitalWrite(BATTERY_EN,LOW);

      pinMode(PIN_INTERRUPT, INPUT_PULLUP);





 attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), nextSecond, CHANGE);
 /*
 curtm[0]=50; //seconds
 curtm[1]=05; //minutes
 curtm[2]=21; /// hours
 curtm[3]=0; /// day of week ?
 curtm[4]=14; /// day
 curtm[5]=4; /// month
 curtm[6]=18; ///  year - 2000
       setDateTime();
*/
 getDateTime();
 startSqw(); /// Starts 1 second SquareWave from DS3231




//devices=EEPROM.read(0);
//devices=1;
 ble_connect();
if(BLOOTOOTH_STATE==1){
    /* Disable command echo from Bluefruit */


   ble.echo(false);
   ble.verbose(false);  // debug info is a little annoying after this point!


ble.setMode(BLUEFRUIT_MODE_DATA);
}

else{
  //  delay(100);
/*
  ble.sendCommandCheckOK(F( "AT+HWMODELED=DISABLE" ));
//  delay(100);
  ble.sendCommandCheckOK(F( "AT+UARTFLOW=OFF" ));
//  delay(100);
  ble.sendCommandCheckOK(F( "AT+BLEPOWERLEVEL=-12" ));
  //delay(100);
  ble.sendCommandCheckOK(F( "AT+BLEMIDIEN=OFF" ));
  //delay(100);
  ble.sendCommandCheckOK(F( "AT+GAPSTOPADV" ));
  ble.end();
  */
}

//ble_connect();
//functions[  bleFunc] =handleBle;

   ssd1306_configure();


getDateTime();
//gotoBlueToothSettings();

//gotoSettings();
      gotoWatchFace();
///gotoStopWatch();
startMpu6050();
updateThings();


}

uint8_t anmof=0;
void drawLoop( ){

 memset(mbuf, 0x00, 1024);
//return;
//clearAll();

 if(nextUIFunc!=NULL){

   animation_offsetY=anmof-64;

   handleFunction(nextUIFunc);

animation_offsetY=anmof;
    handleFunction(functions[uiFunc]);


anmof+=(64-anmof)/16+1;


     if(anmof>64){

      anmof=0;
      if(nextUIFunc!=NULL)
      functions[uiFunc]=nextUIFunc;
       nextUIFunc=NULL;
       startSqw();
       digitalWrite(13,LOW);
       digitalWrite(6,LOW);
       return;
      }

 }else{
animation_offsetY=0;

for(uint8_t a=0;a<HANDLEDFUNCTIONS_COUNT;a++)
handleFunction(functions[a]);


 }




  ssd1306_drawBuffer(0, 0, 128,64, mbuf);
}



void loop()
{



   DEVICESTATE= (USBDEVICE)|((((~PINB) & B11010000)+B00010000)>>5);//;//|((digitalRead(SW2)==LOW)<<1)|((digitalRead(SW3)==LOW)<<2);

  if(DEVICESTATE!=Old_DEVICESTATE){


if(DEVICESTATE&B00000111){


  switch(DEVICESTATE&B00000111){
      case 1:
      if(~(SW1_WASPUSHED)&&SW1_PUSHED){
         handleFunction(functions[sw1Func]);
      }

      break;
      case 2:
        if(~(SW2_WASPUSHED)&&SW2_PUSHED)
        handleFunction(functions[sw2Func]);
      break;
      case 4:
      if(~(SW3_WASPUSHED)&&SW3_PUSHED)
        handleFunction(functions[sw3Func]);
      break;



  }


buttonFX(500|((DEVICESTATE&B00000111)*300));

}

      Old_DEVICESTATE=DEVICESTATE;
    }

digitalWrite(LED2,sound.playing()?HIGH: LOW);
updateThings();
  drawLoop();






}

void handleFunction(func_type f){
  if(f!=NULL)f(   );

}
