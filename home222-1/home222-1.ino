
#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h> 
#define aaa
#include <stdio.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//OLED
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#define CREEN_WIDTH 128     //設定OLED螢幕的寬度像素
#define CREEN_HEIGHT 64     //設定OLED螢幕的寬度像素
#define OLED_RESET -1        //Reset pin如果OLED上沒有RESET腳位,將它設置為-1

Adafruit_SSD1306 display(CREEN_WIDTH, CREEN_HEIGHT, &Wire, OLED_RESET);     //OLED顯示器使用2C連線並宣告名為display物件
bool OLEDStatus = true;



char ap[]="1202";
char pw[]="11111111";

char mqtt_server[]="192.168.16.189";//每次都會不一樣
char clientID[]="12191219";
char topic[]="home/idcard";

char clientIDff[]="12211221";
char topicff[]="home/fire";

char clientIDtt[]="12231223";
char topictt[]="home/temp";


char mqttUserName[]="yanning";
char mqttPwd[]="2222";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

//fire
#define buzzer 15

    char tmp[50];
    int x;


//blue
#include<BluetoothSerial.h>
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


void callback(char *topic,byte *message,unsigned int length){
 Serial.print("---------------------------\n"); 
  Serial.print("Message arrived on topic: ");
  Serial.print(topic); //會根據主程式不同top傳來自動改top名稱
  Serial.print(".Message: " );

  for(int i=0;i<length;i++){
      Serial.print((char) message[i]); //mes的名稱寫為自己改因為只位址
  
 
    }
Serial.print("\n");
Serial.print("---------------------------\n");
  if((char)message[0]=='0'){
    lcd.setCursor(0,0);
  lcd.print("Access Granted!");
 
    }
      
    
    if((char)message[0]=='1'){
      lcd.setCursor(0,0);
  lcd.print("Access Denied!"); 
  
      }

    /*  if((char)message[0]=='3'){
      lcd.setCursor(0,0);
  lcd.print("Access Denied!"); 
  
      }*/

      if((char)message[0]=='4'){
   
       for (int i = 0; i < 80; i ++)
 {
 digitalWrite(buzzer, HIGH);
 delay(1);
 digitalWrite(buzzer, LOW);
 delay(1);
 }
      }

  char tmp[50];
    int x;
    for(int i=0;i<length;i++){
      tmp[i]=(char)message[i];
      tmp[length]='\0';
      }

      x=atoi(tmp); //x=message
char inputmax;
char inputmin;
int inmax,inmin=0;
      if(BT.available()){
   /* BT.print("bluetooth received(tmp MAX):");
    inputmax = BT.read();
    Serial.print("bluetooth received(tmp MAX):");
    Serial.println(inputmax);
*/
    BT.print("bluetooth received(tmp Min):");
   inputmin=BT.read();
    Serial.print("bluetooth received(tmp Min):");
    Serial.println(inputmin);



    
      
   /* if(inputmax=='a')
    {
      inmax=0;
    }
        if(inputmax=='b')
    {
      inmax=1;
    }
        if(inputmax=='c')
    {
      inmax=2;
    }
        if(inputmax=='d')
    {
      inmax=3;
    }
        if(inputmax=='e')
    {
      inmax=4;
    }
        if(inputmax=='f')
    {
      inmax=5;
    }
        if(inputmax=='g')
    {
      inmax=6;
    }
        if(inputmax=='h')
    {
      inmax=7;
    }
        if(inputmax=='i')
    {
      inmax=8;
    }
        if(inputmax=='j')
    {
      inmax=9;
    }
        if(inputmax=='k')
    {
      inmax=10;
    }
        if(inputmax=='l')
    {
      inmax=11;
    }
        if(inputmax=='m')
    {
      inmax=12;
    }
        if(inputmax=='o')
    {
      inmax=13;
    }
        if(inputmax=='p')
    {
      inmax=14;
    }
        if(inputmax=='q')
    {
      inmax=15;
    }
        if(inputmax=='r')
    {
      inmax=16;
    }
        if(inputmax=='s')
    {
      inmax=17;
    }
        if(inputmax=='t')
    {
      inmax=18;
    }
        if(inputmax=='u')
    {
      inmax=19;
    }
        if(inputmax=='v')
    {
      inmax=20;
    }
        if(inputmax=='w')
    {
      inmax=21;
    }
        if(inputmax=='x')
    {
      inmax=22;
    }
        if(inputmax=='y')
    {
      inmax=23;
    }
        if(inputmax=='z')
    {
      inmax=24;
    }
        if(inputmax=='A')
    {
      inmax=25;
    }
        if(inputmax=='B')
    {
      inmax=26;
    }
        if(inputmax=='C')
    {
      inmax=27;
    }
        if(inputmax=='D')
    {
      inmax=28;
    }
        if(inputmax=='E')
    {
      inmax=29;
    }
        if(inputmax=='F')
    {
      inmax=30;
    }
        if(inputmax=='G')
    {
      inmax=31;
    }
        if(inputmax=='H')
    {
      inmax=32;
    }
        if(inputmax=='I')
    {
      inmax=33;
    }
        if(inputmax=='J')
    {
      inmax=34;
    }
        if(inputmax=='K')
    {
      inmax=35;
    }
        if(inputmax=='L')
    {
      inmax=36;
    }
        if(inputmax=='M')
    {
      inmax=37;
    }
        if(inputmax=='N')
    {
      inmax=38;
    }
        if(inputmax=='O')
    {
      inmax=39;
    }
        if(inputmax=='P')
    {
      inmax=40;
    }
        if(inputmax=='Q')
    {
      inmax=41;
    }
        if(inputmax=='R')
    {
      inmax=42;
    }
        if(inputmax=='S')
    {
      inmax=43;
    }
        if(inputmax=='T')
    {
      inmax=44;
    }
        if(inputmax=='U')
    {
      inmax=45;
    }
        if(inputmax=='V')
    {
      inmax=46;
    }
        if(inputmax=='W')
    {
      inmax=47;
    }
        if(inputmax=='X')
    {
      inmax=48;
    }
        if(inputmax=='Y')
    {
      inmax=49;
    }
           if(inputmax=='Z')
    {
      inmax=50;
    }
*/

//MIN
    if(inputmin=='a')
    {
      inmin=0;
    }
        if(inputmin=='b')
    {
      inmin=1;
    }
        if(inputmin=='c')
    {
     inmin=2;
    }
        if(inputmin=='d')
    {
      inmin=3;
    }
        if(inputmin=='e')
    {
      inmin=4;
    }
        if(inputmin=='f')
    {
      inmin=5;
    }
        if(inputmin=='g')
    {
      inmin=6;
    }
        if(inputmin=='h')
    {
      inmin=7;
    }
        if(inputmin=='i')
    {
      inmin=8;
    }
        if(inputmin=='j')
    {
      inmin=9;
    }
        if(inputmin=='k')
    {
      inmin=10;
    }
        if(inputmin=='l')
    {
      inmin=11;
    }
        if(inputmin=='m')
    {
      inmin=12;
    }
        if(inputmin=='o')
    {
      inmin=13;
    }
        if(inputmin=='p')
    {
      inmin=14;
    }
        if(inputmin=='q')
    {
      inmin=15;
    }
        if(inputmin=='r')
    {
      inmin=16;
    }
        if(inputmin=='s')
    {
      inmin=17;
    }
        if(inputmin=='t')
    {
      inmin=18;
    }
        if(inputmin=='u')
    {
      inmin=19;
    }
        if(inputmin=='v')
    {
      inmin=20;
    }
        if(inputmin=='w')
    {
      inmin=21;
    }
        if(inputmin=='x')
    {
      inmin=22;
    }
        if(inputmin=='y')
    {
      inmin=23;
    }
        if(inputmin=='z')
    {
      inmin=24;
    }
        if(inputmin=='A')
    {
      inmin=25;
    }
        if(inputmin=='B')
    {
     inmin=26;
    }
        if(inputmin=='C')
    {
      inmin=27;
    }
        if(inputmin=='D')
    {
      inmin=28;
    }
        if(inputmin=='E')
    {
      inmin=29;
    }
        if(inputmin=='F')
    {
     inmin=30;
    }
        if(inputmin=='G')
    {
      inmin=31;
    }
        if(inputmin=='H')
    {
      inmin=32;
    }
        if(inputmin=='I')
    {
      inmin=33;
    }
        if(inputmin=='J')
    {
     inmin=34;
    }
        if(inputmin=='K')
    {
      inmin=35;
    }
        if(inputmin=='L')
    {
      inmin=36;
    }
        if(inputmin=='M')
    {
      inmin=37;
    }
        if(inputmin=='N')
    {
     inmin=38;
    }
        if(inputmin=='O')
    {
      inmin=39;
    }
        if(inputmin=='P')
    {
      inmin=40;
    }
        if(inputmin=='Q')
    {
     inmin=41;
    }
        if(inputmin=='R')
    {
      inmin=42;
    }
        if(inputmin=='S')
    {
      inmin=43;
    }
        if(inputmin=='T')
    {
      inmin=44;
    }
        if(inputmin=='U')
    {
      inmin=45;
    }
        if(inputmin=='V')
    {
     inmin=46;
    }
        if(inputmin=='W')
    {
      inmin=47;
    }
        if(inputmin=='X')
    {
     inmin=48;
    }
        if(inputmin=='Y')
    {
      inmin=49;
    }
           if(inputmin=='Z')
    {
      inmin=50;
    }
    
delay(100);


    } 
Serial.print("min值:");
Serial.print(inmin);
if(x==inmin||x<inmin){
           for (blue = 0; blue < 256; blue += 10){
 ledcWrite(channels[2], blue);
  ledcWrite(channels[1],LOW);
  
 } 

  }
  

  delay(2000);
 ledcWrite(channels[1],LOW);
 ledcWrite(channels[2],LOW); 
//fflush();
     if(x==10){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();

  
      }     
           if(x==11){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(1); 
display.print(x);
display.display();
  
      } 
           if(x==12){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==13){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==14){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==15){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==16){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==17){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==18){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==19){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==20){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==21){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==22){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==23){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==24){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==25){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==26){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==27){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==28){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==29){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==30){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 
           if(x==31){
  display.clearDisplay();    

display.setTextColor(WHITE);
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("temperature:");


display.setCursor(0,16);
display.setTextSize(3); 
display.print(x);
display.display();
  
      } 


      
    
}
    
 //   goto aaa;
  

    
  
//一定要宣告自己的call程式
 void callbackff(char *topicff,byte *messageff,unsigned int length){
 // mqtt_client.subscribe(topic);
//mqtt_client.setCallback(callback);
  Serial.print("---------------------------\n");
  Serial.print("Message arrived on topicff: ");
  Serial.print(topicff);
  Serial.print(".Message: " );

  for(int i=0;i<length;i++){
      Serial.print((char) messageff[i]);
 
 
    }

  Serial.print("\n");
  Serial.print("---------------------------\n");
  
   if((char)messageff[0]=='4'){
     for (int i = 0; i < 80; i ++)
 {
 digitalWrite(buzzer, HIGH);
 delay(1);
 digitalWrite(buzzer, LOW);
 delay(1);
 }
 // 兩秒後重新播放
 //delay(2000);
    }
 mqtt_client.subscribe(topic);
mqtt_client.setCallback(callback);
    
  }
  
 /*  void testdrawcharOLED(void) {
  display.clearDisplay();             //清除緩衝區資料
  display.setTextSize(1);             //設定文字尺寸為1,1:6x8,2:12x16,3:18x24...etc
  
  display.setCursor(0, 0);          //設定起始點位置(0,0)
  display.setTextColor(BLACK, WHITE);     //黑字白底
  display.println("Hello") ;        //將"Hello"存入RAM
  
  display.setCursor(0,16);          //設定起始點位置(0,16)
  display.setTextSize(2);             //設定文字尺寸為2
  display.setTextColor(WHITE);      //設定文字顏色為白色(亮點)
  display.println("Hello");         //將"Hello"存入RAM
  
  display.setTextSize(3);             //設定文字尺寸為3
  display.println("yanning");         //將"Hello"存入RAM
  display.display();//顯示所設定文字//必打 
   
display.setCursor(0,16);
display.setTextSize(3); 
display.setTextColor(WHITE);
display.display();

}*/

    
   void callbacktt(char *topictt,byte *messagett,unsigned int length){
 // mqtt_client.subscribe(topic);
//mqtt_client.setCallback(callback);
  Serial.print("---------------------------\n");
  Serial.print("Message arrived on topictt: ");
  Serial.print(topictt);
  Serial.print(".Message: " );

  for(int i=0;i<length;i++){
      Serial.print((char) messagett[i]);
  
 
    }
Serial.print("\n");
Serial.print("---------------------------\n");
 /*   char tmp[50];
    int x;
    for(int i=0;i<length;i++){
      tmp[i]=(char)messagett[i];
      tmp[length]='\0';
      }

      x=atoi(tmp);
      display.clearDisplay();
display.setCursor(0,16);
display.setTextSize(5); 
display.setTextColor(WHITE);
display.print(x);
display.print("C");
display.display();
   */

   
mqtt_client.subscribe(topicff);
mqtt_client.setCallback(callbackff);
    
  }


  
  
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
//mqtt_client.subscribe(topic);
//mqtt_client.setCallback(callback);
  lcd.init(); // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();

//fire
//mqtt_client.subscribe(topicff);
//mqtt_client.setCallback(callbackff);

//temp
mqtt_client.subscribe(topictt);
mqtt_client.setCallback(callbacktt);


pinMode(buzzer, OUTPUT);

//oled
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3c)) {        //設定位址為 0x3c
    Serial.println(F("SSD1306 allocation falled"));        //F(字串):將字串儲存在fash並非在RAM
    OLEDStatus = false;                  //開啟OLED失敗

    
  }
  
 /*f(OLEDStatus == true)
 display.setCursor(0,16);
display.setTextSize(3); 
display.setTextColor(WHITE);
display.print((char) message);
display.print("C");
display.display();*/


//blue
BT.begin("home");

//rgb
  for (int i = 0; i < 3; i ++)
 {
 ledcSetup(channels[i], freq, resolution);
 ledcAttachPin(pins[i], channels[i]);
 } 
 
}

void loop() {

 // char msg[50];
  mqtt_client.loop();

if(!mqtt_client.connected()){
Serial.println("mqtt server does not connected... ");
while( ! mqtt_client.connect(clientID)){
  Serial.print(".");
  delay(1000);
  
  }

  
  Serial.println();
  Serial.println("MQTT server reconnected...");
  mqtt_client.subscribe(topic);
  } 



   
  
}
