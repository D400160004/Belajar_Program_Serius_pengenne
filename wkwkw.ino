#include <SPI.h>       
#include <TimerOne.h>
#include <DMD.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial14.h"
/*--------------------------------------------------------------------------------------*/
#include <SoftwareSerial.h>
/*--------------------------------------------------------------------------------------*/
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
/*--------------------------------------------------------------------------------------*/
SoftwareSerial s(11,10);
SoftwareSerial s1(9,8);
SoftwareSerial s2(7,6);
SoftwareSerial s3(5,4);
/*--------------------------------------------------------------------------------------*/
int Brightness = 10 ;
int shift;
/*--------------------------------------------------------------------------------------*/
String inString = "";    // string to hold input
int jumlah, error_slave_1, error_slave_2, error_slave_3, error_slave_4;
String jumlah_eror,Eror_Satu,Eror_Dua,Eror_Tiga,Eror_Empat;
int toleransi=1000;
/*--------------------------------------------------------------------------------------*/
char current1,current2,current3,current4;
char prev1,prev2,prev3,prev4;
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
  
}
/*--------------------------------------------------------------------------------------*/
void setup(void)
{

   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.pwm(PIN_DMD_nOE, Brightness); //dimming pin OE
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)  
   Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
   s.begin(9600);
   s1.begin(9600);
   s2.begin(9600);
   s3.begin(9600);
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/

void loop()
  {
  jumlah=random(10,2000);
  //set terang led
  Timer1.setPwmDuty(PIN_DMD_nOE, Brightness);
  slave1();
  slave2();
  slave3();
  slave4();
  kalkulasieror();
  //tampil_jumlah();
  // draw a border rectangle around the outside of the display
  dmd.drawBox(  0,  0, 63, 15, GRAPHICS_NORMAL );
   delay(1000);
  }
/*--------------------------------------------------------------------------------------*/  
  void slave1(){//membaca serial data dari slave 1
    if(s.available()>0){
      if(s.read()=="A"){jumlah++;}
      else if(s.read()=="B"){jumlah--;}
      else if(s.read()=="C"){/*Do Nothing*/}
      else{}
    }
    else {
      error_slave_1 ++;}
    }
/*--------------------------------------------------------------------------------------*/
  void slave2(){//membaca serial data dari slave 2
    if(s1.available()>0){
      if(s1.read()=="D"){jumlah++;}
      else if (s1.read()=="E"){jumlah--;}
      else if(s.read()=="F"){/*Do Nothing*/}
      else{}
    }
    else {
      error_slave_2 ++;} 
   }
/*--------------------------------------------------------------------------------------*/
  void slave3(){//membaca serial data dari slave 3
    if(s2.available()>0){
      if(s2.read()=="G"){jumlah++;}
      else if(s2.read()=="H"){jumlah--;}
      else if(s.read()=="I"){/*Do Nothing*/}
      else{}
    }
    else {
    error_slave_3 ++;}
    }
/*--------------------------------------------------------------------------------------*/
  void slave4(){//membaca serial data dari slave 4
    if(s3.available()>0){
      if(s3.read()=="J"){jumlah++;}
      else if(s3.read()=="K"){jumlah--;}
      else if(s.read()=="L"){/*Do Nothing*/}
      else{}
    }
    else {error_slave_4++;}
    }
/*--------------------------------------------------------------------------------------*/
  void kalkulasieror(){
    if (error_slave_1 < toleransi && error_slave_2 < toleransi && error_slave_3 < toleransi && error_slave_4< toleransi){
      Serial.println(" TIDAK ADA EROR");
      /*Do Nothing*/
        Serial.println("JUMLAH ORANG");
        Serial.println(jumlah);
        tampil_jumlah();

    }
    else{
        adasalah();

        
      }
    }
/*--------------------------------------------------------------------------------------*/

  void tampil_jumlah() {
    dmd.selectFont(SystemFont5x7);
    dmd.drawString( 2,  4, "TOTAL:", 6, GRAPHICS_NORMAL );
    if(jumlah < 10000){
      shift = 3 ;
      if(jumlah < 1000){
        shift = 2 ;
        if(jumlah < 100){
          shift = 1 ;
          if(jumlah < 10){
            shift = 0;
          }
        }
      }
    }
      
    dmd.drawChar( 38+(shift*6),  4, '0'+ (jumlah%10), GRAPHICS_NORMAL );   // units  
    if(jumlah>9){
    dmd.drawChar( 38+((shift-1)*6),  4, '0'+((jumlah%100)/10), GRAPHICS_NORMAL );   // tens  
    }
    else{dmd.drawChar( 44,  4, ' ',GRAPHICS_NORMAL );}    
    if(jumlah>99){
    dmd.drawChar( 38+((shift-2)*6),  4, '0'+((jumlah%1000)/100), GRAPHICS_NORMAL );   // hundreds
    }
    else{dmd.drawChar( 50,  4, ' ', GRAPHICS_NORMAL );}
    if(jumlah>999){
    dmd.drawChar( 38+((shift-3)*6),  4, '0'+((jumlah%10000)/1000), GRAPHICS_NORMAL );   // thousands
    }
    else{dmd.drawChar( 56,  4, ' ', GRAPHICS_NORMAL );}
    }
  
  void tampilEror(){
       dmd.clearScreen( true );
       if(millis() > time_now + period){
        time_now = millis();
        adasalah();
      } 
  }


  void adasalah(){
    if (error_slave_1 > toleransi && error_slave_2 > toleransi && error_slave_3 > toleransi && error_slave_4 > toleransi)
    {
      //Semua Device Eror
      }
    else if (error_slave_1 > toleransi && error_slave_2 > toleransi && error_slave_3 > toleransi && error_slave_4 < toleransi)
    {
      //Device 1,2,3
      }
    else if (error_slave_1 > toleransi && error_slave_2 > toleransi && error_slave_3 < toleransi && error_slave_4 > toleransi)
    {
      //Device 1,2,4
      }
    else  if (error_slave_1 > toleransi && error_slave_2 < toleransi && error_slave_3 > toleransi && error_slave_4 > toleransi){
      //Device 1,3,4
      }
    else  if (error_slave_1 > toleransi && error_slave_2 < toleransi && error_slave_3 > toleransi && error_slave_4 > toleransi){
      //Device 1,3,4
      }
    else  if (error_slave_1 < toleransi && error_slave_2 > toleransi && error_slave_3 > toleransi && error_slave_4 > toleransi){
      //Device 2,3,4
      }
    else  if (error_slave_1 > toleransi && error_slave_2 > toleransi && error_slave_3 < toleransi && error_slave_4 < toleransi){
      //Device 1,2
      }
    else  if (error_slave_1 > toleransi && error_slave_2 < toleransi && error_slave_3 > toleransi && error_slave_4 < toleransi){
      //Device 1,3
      }  
    else  if (error_slave_1 > toleransi && error_slave_2 < toleransi && error_slave_3 < toleransi && error_slave_4 > toleransi){
      //Device 1,4

      }
    else  if (error_slave_1 < toleransi && error_slave_2 > toleransi && error_slave_3 > toleransi && error_slave_4 < toleransi){
      //Device 2,3
      dmd.drawString( 16,  1, "D2 D3", 2, GRAPHICS_NORMAL );
      }    
    else  if (error_slave_1 < toleransi && error_slave_2 > toleransi && error_slave_3 < toleransi && error_slave_4 > toleransi){
      //Device 2,4
      dmd.drawString( 16,  1, "D2 D4", 2, GRAPHICS_NORMAL );
      }
    else  if (error_slave_1 < toleransi && error_slave_2 < toleransi && error_slave_3 > toleransi && error_slave_4 > toleransi){
      //Device 3,4
      dmd.drawString( 16,  1, "D3 D4", 2, GRAPHICS_NORMAL );
      }
    else  if (error_slave_1 < toleransi && error_slave_2 < toleransi && error_slave_3 < toleransi && error_slave_4 > toleransi){
      //Device 4
      dmd.drawString( 25,  1, "D4", 2, GRAPHICS_NORMAL );
      } 
    else  if (error_slave_1 < toleransi && error_slave_2 < toleransi && error_slave_3 > toleransi && error_slave_4 < toleransi){
      //Device 3
      dmd.drawString( 25,  1, "D3", 2, GRAPHICS_NORMAL );
      }   
    else  if (error_slave_1 < toleransi && error_slave_2 > toleransi && error_slave_3 < toleransi && error_slave_4 < toleransi){
      //Device 2
      dmd.drawString( 25,  1, "D2", 2, GRAPHICS_NORMAL );
      }  
    else  if (error_slave_1 > toleransi && error_slave_2 < toleransi && error_slave_3 < toleransi && error_slave_4 < toleransi){
      //Device 1
      dmd.drawString( 25,  1, "D1", 2, GRAPHICS_NORMAL );
      }
    else{}
  }
