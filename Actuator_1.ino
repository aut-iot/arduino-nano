#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"
RF24 radio(9, 10);
int count=0;
int L1,L2,L3=0,L4,L5,L6,L7=0,L8,L9;
const uint64_t pipes[1] = {0xC2C2C2C2C6};
void ack(char text[]);

void ack(char index){
  //Serial.println("This is ack");
  char out[8]={0};
  char o[2]={0};
  o[0]=index;
  o[1]='\n';
  sprintf(out,"set%s",o);
  radio.openWritingPipe(pipes[0]);
  radio.stopListening();
  delayMicroseconds(200);
  for(int i=0;i<5;i++){
    radio.write("set1",sizeof("set1"));
    delayMicroseconds(200);
  }
}
void execute(char data[]){
  int index=0;
  for(int i=0;i<32;i++){
    //Serial.println(data[i]);
   // if(i<8)Serial.println(data[i]);
    if(data[i]=='-')
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
  while(i<index){
    a=0;
    if(data[i]=='@'){
      i=i+1;
      node_id=data[i];
    }
    else if(data[i]==','){
      command[0]=data[i+1];
      command[1]=data[i+2];
      command[2]=data[i+3];
      i=i+3;
      //Serial.print(command[0]);
      //Serial.print(command[1]);
      int light=(int)(command[1]-48);
      Serial.println(light);
      int state=(int)(command[2]-48);
      Serial.println(state);
      
      turn_on(light , state);
    }
      i=i+1;
  }
}
void turn_on(int light, int value){
  switch(light){
    case 1:
      if(L1==value){
      error();
      }
      else{
        digitalWrite(A0, value);
        L1=value;
      }
      break;
    case 2:
       if(L2==value){
      error();
      }
      else{
        digitalWrite(A1, value);
        L2=value;
      }
      break;
    case 3:
       if(L3==value){
        error();
      }else{
        digitalWrite(A2, value);
        L3=value;
      }
      break;
    case 4:
       if(L4==value){
      error();
      }else{
        digitalWrite(A3, value);
        L4=value;
      }
      break;
    case 5:
       if(L5==value){
        error();
      }else{
        digitalWrite(A4, value);
        L5=value;
      }
      break;
    case 6:
       if(L6==value){
        error();
      }else{
        digitalWrite(3, value);
        L6=value;
      }
      break;
    case 7:
       if(L7==value){
        error();
      }else{
        digitalWrite(4, value);
        L7=value;
      }
      break;
    case 8:
       if(L8==value){
        error();
      }else{
        digitalWrite(5, value);
        L8=value;
      }
      break;
  }
}
void error(){
  //char charbuff[50];
  radio.openWritingPipe(pipes[0]);
  radio.stopListening();
  radio.write("The value has beed set before",sizeof("The value has beed set before"));
  Serial.println("The value has beed set before");
}

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  printf_begin();
  radio.begin();
  radio.setRetries(10,5);
  radio.setPALevel( RF24_PA_MAX ) ;
  //radio.openReadingPipe(0, pipes[0]);
  radio.openWritingPipe(pipes[1]);
  radio.write("This is actuator 1",sizeof("This is actuator 1"));
  radio.openReadingPipe(1, pipes[1]);

  radio.startListening();
  radio.printDetails(); 
  pinMode(5,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  digitalWrite(A0,HIGH);
      delay(1000);
      digitalWrite(A0,LOW);
}

void loop()
{

  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
  if (radio.available())
  {
    //Serial.println("radio available");
    char text[32] = {0};  
    radio.read(&text, sizeof(text));
    Serial.println(text);
    ack(text[1]);
    execute(text);
    //digitalWrite(3,HIGH);
    //delay(1000);
    //Serial.println(count++);
  }
}

