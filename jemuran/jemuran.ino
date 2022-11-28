#include <SoftwareSerial.h>
#include "Wire.h"
#include "DHT.h"
#define DHTPIN 13 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//  Indikator Timer (Pewaktuan Menjemur)
unsigned long wkt_jemur   = 0;
unsigned long start_jemur = 0;
const long lama_jemur     = 120000; // 1 Detik = 1000
unsigned long tampil      = 0; 

int sensorAir       = A0;
int sensorLdr       = A1;

int lampu1          = 2;
int lampu2          = 3;

#define enA 9
#define in1 7
#define in2 6

int waktu_tunda = 1000; //waktu tunda
int kecepatan = 150; //kecepatan default tutorial ini (max kecepatan) 255


void setup() {
  // put your setup code here, to run once:
  //Output
  pinMode(lampu1,OUTPUT);
  pinMode(lampu2,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);

  //Input
  pinMode(sensorAir,INPUT); 
  pinMode(sensorLdr,INPUT);  

  //Posisi Awal
  digitalWrite(lampu1, HIGH);
  digitalWrite(lampu2, HIGH);

  Serial.begin(9600);
  dht.begin(); //Sensor Dht 11
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

  float DataKelembaban = dht.readHumidity();    // Baca Data Kelembaban
  float DataSuhu = dht.readTemperature(); // Baca Data Suhu
  
  //  Baca Sensor Air Dan Ldr
  int DataAir  = analogRead(sensorAir); // Baca Data Air
  int DataLdr = analogRead(sensorLdr);  // Baca Data Ldr

  Serial.print ("Data Suhu = ");
  Serial.println (DataSuhu);
  Serial.print ("Data Kelembaban = ");
  Serial.println (DataKelembaban);  
  Serial.print ("Data Air = ");
  Serial.println (DataAir);
  Serial.print ("Data Cahaya = ");
  Serial.println (DataLdr);
  delay(1000);

  if((DataLdr <= 250) && (DataAir >= 500) && (DataKelembaban <= 70) && (DataSuhu >= 30)) {
      keluar();
      Serial.print("Jemuran Keluar");
  }

  if((DataLdr > 250) && (DataAir < 500) && (DataKelembaban > 70) && (DataSuhu < 30)){
      masuk();
      Serial.print("Jemuran Masuk"); 
  }
}

void keluar() {
  digitalWrite(lampu1, HIGH);
  digitalWrite(lampu2, HIGH);

//Kedua motor bergerak CW sesuai dengan kecepatan 150, dalam waktu 1 detik
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 40);
  delay(200);
}

void masuk() {
  digitalWrite(lampu1, LOW);
  digitalWrite(lampu2, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 40);
}
