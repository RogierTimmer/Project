#include <stdint.h>

#define CYCLE_START_PIN 34 //pin connected to pin 27
#define INPUT_ZCD 35 //pin connected to the optocoupler that detects the zero crossing of the mains sine wave
#define OUTPUT_PIN 27 //pin connected to 34


void isr(){
    Serial.println("Interrupt");
}

void setup() {
    attachInterrupt(digitalPinToInterrupt(CYCLE_START_PIN), isr, RISING);

    pinMode(INPUT_ZCD,INPUT);
    pinMode(OUTPUT_PIN,OUTPUT);
    Serial.begin(115200);
}

void loop(){
    if(analogRead(INPUT_ZCD)>4000){
        digitalWrite(OUTPUT_PIN, HIGH);
        //Serial.println("HIGH");
    }
    else{
        digitalWrite(OUTPUT_PIN, LOW);
        //Serial.println("LOW");
    }

}