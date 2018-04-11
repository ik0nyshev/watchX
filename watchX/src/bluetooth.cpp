#include "watchX.h"

#include "bluetooth.h"
#include "oled.h"

/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


void ble_sw1(){
  if((~SW1_WASPUSHED)&SW1_PUSHED){
    gotoWatchFace();
    }
  }


  void handleBle( ){
    unsigned char i;
//if(!ble)return;
if(ble.available()){ i=0;

     while ( ble.available() )
        {

         strtmpbuf[i++]=ble.read();

 

        }

       if(i>0){
         strtmpbuf[i-1]=0;

      gotoBlueTooth( );

       }
}
    }
    const char title[] PROGMEM="< INCOMING MESSAGE >";
    void drawBle(){
     /// TODO do we need ?
        drawString_P(4,0,title,smallFont);
        drawString(0,8,strtmpbuf,smallFont);

      }
     // int timepassed=0;
void ble_connect(){

      //if(!ble)ble =new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
     if ( !ble.begin(true) )
      {
       //error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
      }

  /*
        if ( FACTORYRESET_ENABLE )
      {
        if ( ! ble.factoryReset() ){
         // error(F("Couldn't factory reset"));
        }
      }

    Disable command echo from Bluefruit */
  //    ble.echo(false);
  //    ble.verbose(false);  // debug info is a little annoying after this point!

      /* Wait for connection */
     // while (! ble.isConnected()) {
      //    delay(500);
     // }

      // Set module to DATA mode
      ble.setMode(BLUEFRUIT_MODE_DATA);


  }
