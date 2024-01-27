// Define the PWM channel, frequency, resolution, and GPIO pin
#define PWM_CHANNEL 0
#define PWM_FREQUENCY 100000 // Frequency in Hz
#define PWM_RESOLUTION 8   // Resolution in bits (1-16)
#define PWM_PIN 16         // Output pin

#define V_IN 35
#define I_IN 15

//float V_old = 0;
//float I_old = 0;
float V_new = 0;
float I_new = 0;
float P;

//const int length = 50;

//float new_Varr[length];
//float new_Iarr[length];

//float old_Varr[length];
//float old_Iarr[length];


float V_old = analogRead(V_IN) * (3.3 / 255) * 10;
float I_old = analogRead(I_IN) * (3.3 / 255) * 2 / 10;

int ref_dc = 180;
int dc;

void setup() {

    // Setup the PWM
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  
  // Attach the PWM to the GPIO pin
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  analogReadResolution(8);
  Serial.begin(115200);

/*
  //for(int i=0; i<length; i++){
  //old_Varr[i] = analogRead(V_IN) * (3.3 / 255) * 10;
  //old_Iarr[i] = analogRead(I_IN) * (3.3 / 255) * 2 / 10;
}

for(int i = 0; i<length; i++){
    V_old += old_Varr[i];
    I_old += old_Iarr[i];
}

  V_old /= length;
  I_old /= length;

*/
}



int improvedInc(float V_new, float I_new, float V_old, float I_old, int dc){
  float dV = V_new - V_old;
  float dI = I_new - I_old;
  int step = 2;

  if(dV<=0.01*V_new && dV >= -0.01*V_new)
    if(dI<=0.01*I_new && dI >= -0.01*I_new)
      return dc;
    else
      if(dI>0)
        return dc+step;
      else return dc-step;
  
  else 
    if(I_new + V_new * dI/dV == 0)
      return dc;
    else
      if(I_new + V_new * dI/dV > 0)
        if(dV*dI>0)
          if(dV>0)
            return dc-step;
          else return dc+step;
        else return dc+step;
      else return dc-step;
}

void writePWM(int dc){
  ledcWrite(PWM_CHANNEL, dc);
}

void loop() {

  V_new = analogRead(V_IN) * (3.3 / 255) * 10;
  I_new = analogRead(I_IN) * (3.3 / 255) * 2 / 10;
/*
  for(int i=0; i<length; i++){
  new_Varr[i] = analogRead(V_IN) * (3.3 / 255) * 10;
  new_Iarr[i] = analogRead(I_IN) * (3.3 / 255) * 2 / 10;
  }

  for(int i = 0; i<length; i++){
    V_new += new_Varr[i];
    I_new += new_Iarr[i];
  }

  V_new /= length;
  I_new /= length;
*/
  dc = improvedInc(V_new, I_new, V_old, I_old, ref_dc);

  if(dc < 60 || dc > 235)
    dc = 128;

  writePWM(dc);

  V_old = V_new;
  I_old = I_new;
  ref_dc = dc;

  Serial.print(V_new, 4); Serial.println(" V");
  Serial.print(I_new, 4); Serial.println(" A");
  Serial.print(V_new * I_new, 4); Serial.println(" W");
  Serial.print(dc/255.0*100, 0); Serial.println("% Duty Cycle (Inverted)");
  Serial.println("-----------");
  
  delay(100);
}