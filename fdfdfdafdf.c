  #include <SPI.h>
  #include <DMD2.h>
  #include <fonts/Arial14.h>
  /*--------------------------------------------------------------------------------------*/
  #include <SoftwareSerial.h>
  /*--------------------------------------------------------------------------------------*/
  SoftwareSerial s(11,10);
  SoftwareSerial s1(9,8);
  SoftwareSerial s2(7,6);
  SoftwareSerial s3(5,4);
  
  int jumlah, error_slave_1, error_slave_2, error_slave_3, error_slave_4;
  String jumlah_eror,Eror_Satu,Eror_Dua,Eror_Tiga,Eror_Empat;
  int toleransi=1000;
  void setup() {
    s.begin(9600);
    s1.begin(9600);
    s2.begin(9600);
    s3.begin(9600);
  }
  
  void loop() {
    slave1();
    slave2();
    slave3();
    slave4();
    kalkulasieror();
    Serial.println("JUMLAH ORANG");
    Serial.println(jumlah)
}
  //
  void slave1(){//membaca serial data dari slave 1
  if(s.available()>0){
    if(s.read()=="A"){jumlah++;}
    else if(s.read()=="B"){jumlah--;}
    else if(s.read()=="B"){/*Do Nothing*/}
    else{}
  }
  else {
    error_slave_1 ++;}
  }

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

  void slave4(){//membaca serial data dari slave 4
  if(s3.available()>0){
    if(s3.read()=="J"){jumlah++;}
    else if(s3.read()=="K"){jumlah--;}
    else if(s.read()=="L"){/*Do Nothing*/}
    else{}
  }
  else {error_slave_4++;}
  }

  void kalkulasieror(){
    if (error_slave_1 < toleransi && error_slave_2 < toleransi && error_slave_3 < toleransi && error_slave_4< toleransi){
      Serial.println(" TIDAK ADA EROR");
      /*Do Nothing*/
    }
    else{
        if (error_slave_1 > toleransi )
        {
          Eror_Satu="DEVICE 1";
        }
        else if (error_slave_1 < toleransi)
        {
          Eror_Satu=" ";
        }
        else if (error_slave_2 > toleransi)
        {
          Eror_Dua="DEVICE 2";
        }
        else if (error_slave_2 < toleransi)
        {
          Eror_Dua=" ";
        }
        else if (error_slave_3 > toleransi)
        {
          Eror_Tiga="DEVICE 3";
        }
        else if (error_slave_3 < toleransi)
        {
          Eror_Tiga=" ";
        }
        else if (error_slave_4 > toleransi)
        {
          Eror_Empat="DEVICE 4";
        }
        else if (error_slave_4 < toleransi)
        {
          Eror_Empat=" ";
        }
        else {/* Do Nothing */}
        jumlah_eror=Eror_Satu+Eror_Dua+Eror_Tiga+Eror_Empat+" EROR HARAP CEK KONEKSI";
        Serial.println(jumlah_eror);      
    }

  }
