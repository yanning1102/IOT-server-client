#include <WiFi.h>
#include <PubSubClient.h>

char ap[]="1202";
char pw[]="11111111";

char mqtt_server[]="192.168.16.189";//每次都會不一樣
char clientID[]="1219";
char topic[]="home/idcard";

char clientIDff[]="1221";
char topicff[]="home/fire";

char clientIDtt[]="1223";
char topictt[]="home/temp";

char mqttUserName[]="yanning";
char mqttPwd[]="2222";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

//idcard
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

#define RST_PIN   4         
#define SS_PIN    5 //RC522卡上的SDA

MFRC522 mfrc522;   // 建立MFRC522實體

char *reference;

byte uid[]={0x62, 0xCE, 0xA2, 0x18};

//fire
#define Led 15
#define sensorpin  34
int val;


//ln
#include<WiFiClientSecure.h>
String Linetoken="MaAuSwJDE5LAr006F3t83BREs195Qu06P8AYlYfpqFg";

int aaa;

WiFiClientSecure client;
char host[]="notify-api.line.me";

//temp
#include <DHT.h>
#define DHTPIN 2 // pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//blue
/*#include<BluetoothSerial.h>
BluetoothSerial BT;
int red, green, blue;
int in=0;  
int in2=0;

//rgb
// setting LED pins
int pins[] = {18, 19, 5}; // R, G, B
// setting channel used (0 ~ 15)
int channels[] = {1, 2, 3};
// setting PWM properties
int freq = 5000;
int resolution = 8; // Using 8-bit PWM
*/
void setup() {
Serial.begin(115200);
Serial.print("Connecting AP.");
WiFi.begin(ap,pw);
while(WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
Serial.println();
Serial.print("WiFi.connected with IP: ");
Serial.println(WiFi.localIP());
mqtt_client.setServer(mqtt_server,1883);
Serial.print("connecting MQTT server.");
while(! mqtt_client.connect(clientID)){
  Serial.print(".");
  delay(1000);
  }
Serial.println();
Serial.println("MTQQ server connected...");

//idcard
 SPI.begin();
  
  mfrc522.PCD_Init(SS_PIN, RST_PIN); // 初始化MFRC522卡
  Serial.print(F("Reader "));
  Serial.print(F(": "));
  mfrc522.PCD_DumpVersionToSerial(); // 顯示讀卡設備的版本

//fire
 pinMode(Led, OUTPUT); //設定 LED 為輸出
 pinMode(sensorpin, INPUT); //設定感測器為輸入
 //LN
   client.setInsecure();

 //temp
 dht.begin(); 

/* //blue
BT.begin("home");

//rgb
  for (int i = 0; i < 3; i ++)
 {
 ledcSetup(channels[i], freq, resolution);
 ledcAttachPin(pins[i], channels[i]);
 } 
*/
}

void loop() {

  char msg[50];
  char msg2[50];
  char msg3[50];
  char msg4[50];
  char msg5[50];
  char msg6[50];
  mqtt_client.loop();
 
if(mqtt_client.connected()){
  Serial.print("-----------------------------------\n");
 Serial.print("mqtt connect!\n"); 
 Serial.print("idcard: Access Granted!=0 Access Denied!=1\n");
 Serial.print("fire: no fire!=3 have fire!=4\n");
 Serial.print("-----------------------------------\n");
 delay(2000);
      }

  
else{
  Serial.println("MQTT server does not connected..");
  while(! mqtt_client.connect(clientID)){
    Serial.print(".");
    delay(1000);
    
    }
  Serial.println();
  Serial.println("MQTT server connected...");
  
  }
if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      // 顯示卡片的UID
      Serial.print(F("Card UID:"));
      dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size); // 顯示卡片的UID
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
      Serial.println(mfrc522.PICC_GetTypeName(piccType));  //顯示卡片的類型
 // 初始值是假設為真 
 bool they_match = true; 
      for ( int i = 0; i < 4; i++ ) { // 卡片UID為4段，分別做比對
        if ( uid[i] != mfrc522.uid.uidByte[i] ) { 
          they_match = false; // 如果任何一個比對不正確，they_match就為false，然後就結束比對
          break; 
        }
      }

      //在監控視窗中顯示比對的結果
      if(they_match){
        //Serial.print(F("Access Granted!~"));
        double s1=0.0;
  dtostrf(s1,2,2,msg);
  //msg[50]={'Y'};
Serial.print("idcard publish message:  ");
Serial.println(msg); //改這!!
mqtt_client.publish(topic,msg); //新的系統名子跟發送的資訊

  delay(5000);
      }
      
      else{
       // Serial.print(F("Access Denied!~")); 
          //msg[50]={'N'};

  double s2=1.0;
dtostrf(s2,2,2,msg2);
Serial.print("idcard publish message:  ");
Serial.println(msg2); //改這!!
mqtt_client.publish(topic,msg2); //新的系統名子跟發送的資訊

  delay(5000);
       
      }
      mfrc522.PICC_HaltA();  // 卡片進入停止模式
    }

//fire
 val = digitalRead(sensorpin); //將感測器的值讀給 val
 if(val == HIGH){//當感測器檢測有信號時，LED 閃爍
   digitalWrite(Led, HIGH);
   aaa=1;
     double ff2=4.0;
dtostrf(ff2,2,2,msg3);
Serial.print("fire publish message:  ");
Serial.println(msg3); //改這!!
mqtt_client.publish(topicff,msg3); //新的系統名子跟發送的資訊

  delay(5000);
  } 

 else{
  digitalWrite(Led, LOW);
  aaa=0;
       double ff1=3.0;
dtostrf(ff1,2,2,msg4);
Serial.print("fire publish message:  ");
Serial.println(msg4); //改這!!
mqtt_client.publish(topicff,msg4); //新的系統名子跟發送的資//("字串",String(val).c_str());

  delay(5000);
  } 
//aaa = digitalRead(Led);//GPIO值(36為ADC0)
  //讀取成功
 // Serial.print("Sample OK: ");
  //Serial.println(aaa);

  //設定觸發LINE訊息條件為
  if (aaa==1) {
    //組成Line訊息內容
    String message = "發生火災";
//    message += "\n偵測品質=" + String(sensor) + " !";
    Serial.println(message);
    if (client.connect(host, 443)) {
      int LEN = message.length();
      //傳遞POST表頭
      String url = "/api/notify";
      client.println("POST " + url + " HTTP/1.1");
      client.print("Host: "); client.println(host);
      //權杖
      client.print("Authorization: Bearer "); client.println(Linetoken);
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: "); client.println( String((LEN + 8)) );
      client.println();      
      client.print("message="); client.println(message);
      client.println();
      //等候回應
      delay(2000);
      String response = client.readString();
      //顯示傳遞結果
      Serial.println(response);
      client.stop(); //斷線，否則只能傳5次
    }
    else {
      //傳送失敗
      Serial.println("connected fail");
    }
  }


//temp

int temp, humi;

 temp = dht.readTemperature();
 humi = dht.readHumidity();
 //Serial.print("Temperature: ");
 //Serial.println(temp);
// Serial.print("Humidity: ");
 //Serial.println(humi);
 // Wait a few seconds between measurements.
 delay(5000);

  double t1=0.0;
  t1=temp;
 
  dtostrf(t1,2,2,msg5);
  //msg[50]={'Y'};
Serial.print("temp publish message:  ");
Serial.println(msg5); //改這!!
mqtt_client.publish(topictt,msg5); //新的系統名子跟發送的資訊


 /* double t2=0.0;
  t2=humi;
 
  dtostrf(t2,2,2,msg6);
  //msg[50]={'Y'};
Serial.print("humi publish message:  ");
Serial.println(msg6); //改這!!
mqtt_client.publish(topictt,msg6); //新的系統名子跟發送的資訊*/

    /*    if(BT.available()){
          BT.print("bluetooth received(tmp MAX):");
    in=BT.read();
    Serial.print("bluetooth received(tmp MAX):");
    Serial.println(in);
    
    BT.print("bluetooth received(tmp Min):");
   in2=BT.read();
    Serial.print("bluetooth received(tmp Min):");
    Serial.println(in2);


    } 

        if(temp==in||temp>in){
         for (red = 0; red < 256; red += 10){
    ledcWrite(channels[0], red);
    }
      }
      
           if(temp==in2||temp<in2){
         for (blue = 0; blue < 256; blue += 10){
 ledcWrite(channels[2], blue);
 } 
        } */

}


void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
