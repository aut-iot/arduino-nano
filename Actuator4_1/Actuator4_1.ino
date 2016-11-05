#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
#include <IRremote.h>

#define IRLEDpin A5





/*24
01010000 00000000 00010001 00000000 10101111 11111111 11101110 11111111
25
01010000 00000000 10010001 00000000 10101111 11111111 01101110 11111111*/



unsigned long on1=0b01010000000000001110000100000000; 
unsigned long on2=0b10101111111111110001111011111111;

unsigned long T17=0b01010000000000001000000100000000; 
unsigned long T17b=0b10101111111111110111111011111111; 

unsigned long T18=0b01010000000000000100000100000000; 
unsigned long T18b=0b10101111111111111011111011111111;

unsigned long T19=0b01010000000000001100000100000000 ; 
unsigned long T19b=0b10101111111111110011111011111111;

unsigned long T20=0b01010000000000000010000100000000; 
unsigned long T20b=0b10101111111111111101111011111111;

unsigned long T21=0b01010000000000001010010100000000 ; 
unsigned long T21b=0b10101111111111110101101011111111 ;

unsigned long T22=0b01010000000000000110010100000000; 
unsigned long T22b=0b10101111111111111001101011111111;

unsigned long T23=0b01010000000000001110010100000000; 
unsigned long T23b=0b10101111111111110001101011111111;

unsigned long T24=0b01010000000000000001010100000000; 
unsigned long T24b=0b10101111111111111110101011111111 ;

unsigned long T25=0b01010000000000001001010100000000; 
unsigned long T25b=0b10101111111111111110101011111111 ;

unsigned long T26=0b01010000000000000101010100000000; 
unsigned long T26b=0b10101111111111111110101011111111;

unsigned long T27=0b01010000000000001101010100000000; 
unsigned long T27b=0b10101111111111111110101011111111;

unsigned long T28=0b01010000000000000011010100000000; 
unsigned long T28b=0b10101111111111111110101011111111;

unsigned long T29=0b01010000000000001011010100000000; 
unsigned long T29b=0b10101111111111111110101011111111;

unsigned long T30=0b01010000000000000111010100000000; 
unsigned long T30b=0b10101111111111111000101011111111;

unsigned long C_auto1=0b01010000000000001001000100000000;
unsigned long C_auto2=0b10101111111111110110111011111111; 

unsigned long cool1=0b01010000000000001001010100000000;
unsigned long cool2=0b10101111111111110110101011111111;

unsigned long dry1=0b01010000000000001001100100000000;
unsigned long dry2=0b10101111111111110110011011111111;

unsigned long fan1=0b01010000000000001001110100000000;
unsigned long fan2=0b10101111111111110110001011111111;

unsigned long heat1=0b01010000000000001001001100000000;
unsigned long heat2=0b10101111111111110110110011111111;

unsigned long speed_hi1=0b01010000000001001001001100000000;
unsigned long speed_hi2=0b10101111111110110110110011111111;

unsigned long speed_low1=0b01010000000000001001001100000000;
unsigned long speed_low2=0b10101111111111110110110011111111;

unsigned long off1=0b01010000000000001110000000000000; 
unsigned long off2=0b10101111111111110001111111111111;

RF24 radio(9, 10);
int count=0;
int l1=0,l2=0,l3=0,l4=0,l5=0,l6=0,l7=0,l8=0,l9=0;
const uint64_t pipes[2] = {0xC2C2C2C2C5};
const char node='1';
String response_m="";
char charbuff[50];
void ack(char text[]);

void IRsetup(void)
{
  pinMode(IRLEDpin, OUTPUT);
  digitalWrite(IRLEDpin, LOW);
}
void IRcarrier(unsigned int IRtimemicroseconds)
{
  int i;
  for(i=0; i<(IRtimemicroseconds / 50); i++)
  {
    digitalWrite(IRLEDpin, HIGH);
    delayMicroseconds(25);
    digitalWrite(IRLEDpin, LOW);
    delayMicroseconds(25);
  }
}
void IRsendCode(unsigned long code1,unsigned long code2)
{
  
  
  int i;
  unsigned long c;
  IRcarrier(6200);
  delayMicroseconds(7400);


  for (i=0; i<32; i++)
  {
      IRcarrier(600);
      if (code1 & 0x80000000)
        delayMicroseconds(3400);
      else
        delayMicroseconds(1400);
      code1<<=1;
  }
  
  for (i=0; i<32; i++)
  {
      IRcarrier(600);
      if (code2 & 0x80000000)
        delayMicroseconds(3400);
      else
        delayMicroseconds(1400);
      code2<<=1;
  }
  //delayMicroseconds(440);
  IRcarrier(600);
  delayMicroseconds(7400);
  IRcarrier(600);

}
void Command(String command)
{
 


   
      if(command.equals("ON")){
        IRsetup();
        IRsendCode(on1,on2);
        
      }
      else if(command.equals("OFF")){
        
  
        IRsetup();
        IRsendCode(off1,off2);
      }
      else if(command.equals( "T17")){

     
        IRsetup();
        IRsendCode(T17,T17b);
      }
      else if(command.equals( "T18")){
     
        IRsetup();
        IRsendCode(T18,T18b);
      }
      else if(command.equals( "T19")){

     
        IRsetup();
        IRsendCode(T19,T19b);
      }
        
      else if(command.equals( "T20")){
        IRsetup();
        IRsendCode(T20,T20b);
      }

      else if(command.equals( "T21")){
        IRsetup();
        IRsendCode(T21,T21b);
      }

      else if(command.equals( "T22")){
        IRsetup();
        IRsendCode(T22,T22b);
      }

      else if(command.equals( "T23")){
        IRsetup();
        IRsendCode(T23,T23b);
      }

     else if(command.equals( "T24")){
        IRsetup();
        IRsendCode(T24,T24b);
       }

     else if(command.equals( "25")){
        IRsetup();
        IRsendCode(T25,T25b);
     }
   
    else if(command.equals( "T26")){
        IRsetup();
        IRsendCode(T26,T26b);
    }

       else if(command.equals( "T27")){
        IRsetup();
        IRsendCode(T27,T27b);
    }

       else if(command.equals( "T28")){
        IRsetup();
        IRsendCode(T28,T28b);
        
       }
      else if(command.equals( "T29")){
        IRsetup();
        IRsendCode(T29,T29b);
      }

      else if(command.equals( "T30")){
        IRsetup();
        IRsendCode(T30,T30b);
      }

      else if(command.equals( "auto")){
        IRsetup();
        IRsendCode(C_auto1,C_auto2);
      }

     else if(command.equals( "cool")){
        IRsetup();
        IRsendCode(cool1,cool2);
     }

     else if(command.equals( "dry")){
        IRsetup();
        IRsendCode(dry1,dry2);
     }

    else if(command.equals( "fan")){
        IRsetup();
        IRsendCode(fan1,fan2);
    }

   else if(command.equals( "heat")){
        IRsetup();
        IRsendCode(heat1,heat2);
   }

   else if(command.equals( "HIGH")){
        IRsetup();
        IRsendCode(speed_hi1,speed_hi2);
   }

   else if(command.equals( "LOW")){
        IRsetup();
        IRsendCode(speed_low1,speed_low2);
   }

    
}
void ack(char index)
{
  //Serial.println("This is ack");
  char out[8]={0};
  char o[2]={0};
  o[0]=index;
  
  sprintf(out,"set%s",o);
  radio.openWritingPipe(pipes[0]);
  radio.stopListening();
  delayMicroseconds(200);
  
   radio.write(out,4);
   
   
   
    
  
}
void execute(char data[])
{
  int index=0;
  for(int i=0;i<32;i++){
    //Serial.println(data[i]);
   // if(i<8)Serial.println(data[i]);
    if(data[i]=='.')
      index=i+1;
  }
 // Serial.println("index");
  //Serial.println(index);
  char node_id=data[1];
  char delim[2]={'@' ,','};
  int i=0;
  int a=0;
  //char node_id;
  char command[3];
 
  while(i<index ){
    a=0;
    if(data[i]=='@')
    {
      i=i+1;
      node_id=data[i];
       if(node!=node_id or index >32)
       {
       // Serial.println("Exiting");
        error();
    
          return;
        }
        else
        {
          ack(node);
        }
    }
    else if(data[i]==','){
      command[0]=data[i+1];
      command[1]=data[i+2];
      command[2]=data[i+3];
      i=i+3;
      //Serial.print(command[0]);
      //Serial.print(command[1]);
      if(command[0] == 'c' ){
       // Serial.println"IR_SEND");
       char tmp_command[2];
       tmp_command[0]=command[1];
       tmp_command[1]=command[2];
        int c;
       
        sscanf(tmp_command , "%d" , &c);
        Serial.println(c);

        switch(c){
        case 11:
        Serial.println("ON");
          Command("ON");
          break;

        case 0:
          Command("OFF");
          break;

        case 17:
          Command("T17");
          break;
       
        case 18:
          Command("T18");
          break;
        
        case 19:
          Command("T19");
          break;
        
        case 20:
          Command("T20");
          break;
        
        case 21:
          Command("T21");
          break;
        
        case 22:
          Command("T22");
          break;       
        
        case 23:
          Command("T23");
          break;

        
        case 24:
        Command("T24");
          break;
        
        case 25:
          Command("T25");
          break;
        
        case 26:
          Command("T26");
          break;

        
        case 27:
          Command("T27");
          break;
        
        case 28:
          Command("T28");
          break;
        
        case 29:
          Command("T29");
          break;
        
        case 30:
          Command("T30");
          break;
        
        case 31:
          Command("auto");
          break;
  
        case 32:
          Command("cool");
          break;
        
        case 33:
          Command("dry");
          break;

        case 34:
          Command("fan");
          break;

        case 35:
          Command("heat");
          break;

        case 36:
          Command("HIGH");
          break;
        
        case 37:
          Command("LOW");
          break;
        }  
      }
    else{
        
      int light=(int)(command[1]-48);
     // Serial.println(light);
      int state=(int)(command[2]-48);
     // Serial.println(state);
      
      turn_on(light , state);
      // Serial.println("Sent1");
      
      }
    }
      i=i+1;
  }
   
}
void turn_on(int light, int value)
{
  switch(light){
    case 1:
      if(l1==value){
      digitalWrite(A0, !value);
      digitalWrite(A0, value);
      error();
      }
      else{
        digitalWrite(A0, value);
        l1=value;
      }
      break;
    case 2:
       if(l2==value){
      digitalWrite(A1, !value);
      digitalWrite(A1, value);
      error();
      }
      else{
        digitalWrite(A1, value);
        l2=value;
      }
      break;
    case 3:
       if(l3==value){
        digitalWrite(A2, !value);
        digitalWrite(A2, value);
        error();
      }else{
        digitalWrite(A2, value);
        l3=value;
      }
      break;
    case 4:
       if(l4==value){
      digitalWrite(A3, !value);
      digitalWrite(A3, value);
      error();
      }else{
        digitalWrite(A3, value);
        l4=value;
      }
      break;
    case 5:
       if(l5==value){
        digitalWrite(A4, !value);
        digitalWrite(A4, value);
        error();
      }else{
        digitalWrite(A4, value);
        l5=value;
      }
      break;
    case 6:
       if(l6==value){
        digitalWrite(3, !value);
        digitalWrite(3, value);
        error();
      }else{
        digitalWrite(3, value);
        l6=value;
      }
      break;
    case 7:
       if(l7==value){
        digitalWrite(4, !value);
        digitalWrite(4, value);
        error();
      }else{
        digitalWrite(4, value);
        l7=value;
      }
      break;
    case 8:
       if(l8==value){
        digitalWrite(5, !value);
        digitalWrite(5, value);
        error();
      }else{
        digitalWrite(5, value);
        l8=value;
      }
      break;
     case 9:
       if(l9==value){
        digitalWrite(6, !value);
        digitalWrite(6, value);
        error();
      }else{
        digitalWrite(6, value);
        l9=value;
      }
      break;
  }
}
void error()
{
  //char charbuff[50];
  //radio.openWritingPipe(pipes[0]);
  //radio.stopListening();
  //radio.write("The value has beed set before",sizeof("The value has beed set before"));
  //Serial.println("The value has beed set before");
}
void get_request(char data[])
{
  int message_size=0;
  response_m="";
  for(int i=0;i<32;i++){
    //Serial.println(data[i]);
    if(data[i]=='.' || i>30)
      message_size=i+1;
    //if(data[i]!='.' && i>30)
     // message_size=i+1;
  }
  Serial.print("message_size:");
  Serial.println(message_size);
  char node_id=data[1];
  int i=0;
  char command[3];
  
  while(i<message_size ){
  if(data[i]=='g')
  {
      
      i=i+1;
      node_id=data[i];
    if(node!=node_id or message_size >32)
    {
      error();
    }
    else
    {
      response_m=response_m+'g'+node;
    }
  }
  else if(data[i]==',')
  {
  command[0]=data[i+1];
  command[1]=data[i+2];
  command[2]=data[i+3];
  
  if(command[0]=='l' && command[1]=='1' && command[2]=='s')
    response_m=response_m+","+"l1"+l1;
 
  if(command[0]=='l' && command[1]=='2' && command[2]=='s')
    response_m=response_m+","+"l2"+l2;

  if(command[0]=='l' && command[1]=='3' && command[2]=='s')
    response_m=response_m+","+"l3"+l3;

  if(command[0]=='l' && command[1]=='4' && command[2]=='s')
    response_m=response_m+","+"l4"+l4;
 
  if(command[0]=='l' && command[1]=='5' && command[2]=='s')
    response_m=response_m+","+"l5"+l5;

  if(command[0]=='l' && command[1]=='6' && command[2]=='s')
    response_m=response_m+","+"l6"+l6;
 
  if(command[0]=='l' && command[1]=='7' && command[2]=='s')
    response_m=response_m+","+"l7"+l7;

  if(command[0]=='l' && command[1]=='8' && command[2]=='s')
    response_m=response_m+","+"l8"+l8;

  if(command[0]=='l' && command[1]=='9' && command[2]=='s')
    response_m=response_m+","+"l9"+l9;

  i=i+3;
  }
  i=i+1;  
 }
  response_m=response_m+".";
  radio.openWritingPipe(pipes[0]);
  radio.stopListening();
  Serial.println(response_m);
  response_m.toCharArray(charbuff, message_size);
  delayMicroseconds(130);
  radio.write(charbuff,message_size);
}
void setup()
{
  while (!Serial);
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setRetries(2,15);
  radio.setPALevel( RF24_PA_MAX ) ;
  radio.setChannel(0);
  radio.setDataRate(RF24_250KBPS);
  radio.printDetails();
  radio.openWritingPipe(pipes[0]);
  radio.stopListening();
  
  radio.write("g1,l10,l20,l30,l40,l50.", 24);
  radio.write("g1,l10,l20,l30,l40,l50.", 24);
  radio.write("g1,l60,l70,l80,l90.", 20);
  radio.write("g1,l60,l70,l80,l90.", 20);
  
  
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);

  
}
void loop()
{
  radio.openReadingPipe(0, pipes[0]);
  radio.startListening();
  if (radio.available())
  {
    //Serial.println("radio available");
    char text[32] = {0};  
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if(text[0]=='g'){
      get_request(text);
    }
    else if(text[0]=='@'){
      execute(text);
    }
  }
  
  
 
}
  

