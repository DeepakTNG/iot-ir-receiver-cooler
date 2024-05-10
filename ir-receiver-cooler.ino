#include <IRremote.h>
#include <OSFS.h>
#include <EEPROM.h>


// Define the IR receiver pin
const int IR_PIN = 7; //D7

const int R1_PIN = 2; //D2
const int R2_PIN = 3; //D3
const int R3_PIN = 4; //D4
const int R4_PIN = 5; //D5

const int t_pin =13;

// Define the IR receiver object
IRrecv irrecv(IR_PIN);

//last read time
unsigned long last = millis();

//
struct relayStatusType{
  int r1; //speed 1
  int r2; //speed 2
  int r3; //spped 3
  int r4; //water pump
  int power; //power status
};

relayStatusType relayStatus;

// storage start hear
// Here we define the four pieces of information that OSFS needs to make a filesystem:
//
// 1) and 2) How large is the storage medium?
uint16_t OSFS::startOfEEPROM = 1;
uint16_t OSFS::endOfEEPROM = 1024;

// Var to hold the result of actions
OSFS::result r;

// Useful consts
const OSFS::result noerr = OSFS::result::NO_ERROR;
const OSFS::result notfound = OSFS::result::FILE_NOT_FOUND;



// 3) How do I read from the medium?
void OSFS::readNBytes(uint16_t address, unsigned int num, byte* output) {
	for (uint16_t i = address; i < address + num; i++) {
		*output = EEPROM.read(i);
		output++;
	}
}

// 4) How to I write to the medium?
void OSFS::writeNBytes(uint16_t address, unsigned int num, const byte* input) {
	for (uint16_t i = address; i < address + num; i++) {
		EEPROM.update(i, *input);
		input++;
	}
}

//storage end

void setup() {
  // Serial.println(F("Formatting device..."));
  // OSFS::format();


  Serial.begin(9600);
  irrecv.enableIRIn();

  //setup IR PINS
  pinMode(R1_PIN, OUTPUT);
  pinMode(R2_PIN, OUTPUT);
  pinMode(R3_PIN, OUTPUT);
  pinMode(R4_PIN, OUTPUT);
  pinMode(t_pin, OUTPUT);

  //read relay status from storage
  r = OSFS::getFile("relayStatus", relayStatus);

   if (r == notfound)
  	Serial.println(F("Not found"));
  else if (r == noerr) {
    Serial.println(F("file found as read"));
  } else {
  	Serial.print(F("Error: "));
  	Serial.println( (int) r );
  }

  //reading done

  switchRelay();
}

void loop() {
  


  // Check if the IR receiver has received a signal
  if (irrecv.decode()) {
    // Print the HEX value of the button press
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);

    if (millis() - last > 250) {
      Serial.println(irrecv.decodedIRData.command);

      readIRSignal();

      readData();

      switchRelay();
    }
    // Reset the IR receiver for the next signal
    last = millis();
    irrecv.resume();
  }
}

void readIRSignal(){
  int isChanged;
  isChanged = 0;

  if(irrecv.decodedIRData.command == 9){ //on off button
    Serial.print("Current status: ");
    Serial.println(relayStatus.power);
    if(relayStatus.power==0){
      relayStatus.power=1;
    }else{
      relayStatus.power=0;
    }

    Serial.print("new status: ");
    Serial.println(relayStatus.power);
    isChanged = 1;
  }

  if(irrecv.decodedIRData.command == 3){ //on off button
    if(relayStatus.r4==0){
      relayStatus.r4=1;
    }else{
      relayStatus.r4=0;
    }
    isChanged = 1;
  }

  if(irrecv.decodedIRData.command == 13){ //serial 1 is pressed
    if(relayStatus.r1==0){
      relayStatus.r1=1;
      relayStatus.r2=0;
      relayStatus.r3=0;
    }else{
      relayStatus.r1=0;
    }
    isChanged = 1;
  }
  
  if(irrecv.decodedIRData.command == 25){ //serial 2 is pressed
    if(relayStatus.r2==0){
      relayStatus.r1=0;
      relayStatus.r2=1;
      relayStatus.r3=0;
    }else{
      relayStatus.r2=0;
    }
    isChanged = 1;
  }

  if(irrecv.decodedIRData.command == 27){ //serial 3 is pressed
    if(relayStatus.r3==0){
      relayStatus.r1=0;
      relayStatus.r2=0;
      relayStatus.r3=1;
    }else{
      relayStatus.r3=0;
    }
    isChanged = 1;
  }

  if(isChanged==1)
  {
    Serial.println("File Saved");
    OSFS::newFile("relayStatus", relayStatus, true);
  }
}


void switchRelay()
{
  //power on off
  if(relayStatus.power==0) //off all relay
  {
    Serial.println("Power is off");
    digitalWrite(R1_PIN, HIGH);
    digitalWrite(R2_PIN, HIGH);
    digitalWrite(R3_PIN, HIGH);
    digitalWrite(R4_PIN, HIGH);
    digitalWrite(t_pin, LOW);
  }

  if(relayStatus.power==1) //on or off relay as per status
  {
    Serial.println("Power is on");
    digitalWrite(t_pin, HIGH);
    if(relayStatus.r1==1){
      digitalWrite(R1_PIN, LOW);
    }else{
      digitalWrite(R1_PIN, HIGH);
    }

    if(relayStatus.r2==1){
      digitalWrite(R2_PIN, LOW);
    }else{
      digitalWrite(R2_PIN, HIGH);
    }

    if(relayStatus.r3==1){
      digitalWrite(R3_PIN, LOW);
    }else{
      digitalWrite(R3_PIN, HIGH);
    }

    if(relayStatus.r4==1){
      digitalWrite(R4_PIN, LOW);
    }else{
      digitalWrite(R4_PIN, HIGH);
    }
  }
  
}
void readData(){

  ////////////////////////////

  Serial.println(F("Looking for complex data type..."));

  if (r == notfound)
  	Serial.println(F("Not found"));
  else if (r == noerr) {
    Serial.print("relayStatus.power: ");
    Serial.println(relayStatus.power);
    Serial.print("relayStatus.r1: ");
  	Serial.println(relayStatus.r1);
    Serial.print("relayStatus.r2: ");
  	Serial.println(relayStatus.r2);
    Serial.print("relayStatus.r3: ");
  	Serial.println(relayStatus.r3);
    Serial.print("relayStatus.r4: ");
  	Serial.println(relayStatus.r4);
  } else {
  	Serial.print(F("Error: "));
  	Serial.println( (int) r );
  }

  ////////////////////////////
}
