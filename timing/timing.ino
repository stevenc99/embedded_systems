int button_Start=13;
int pot=A0;
int state;
int PWM2=9;
int PWM3=10;
int PWM4=11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWM2,OUTPUT);
  pinMode(PWM3,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(button_Start,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int Reading=analogRead(pot)/4;
  state=digitalRead(button_Start);
  PWM_Welding (4000,1000,Reading,PWM2,state);
  PWM_Welding (4000,1000,Reading,PWM3,state);
  PWM_Welding (4000,1000,Reading,PWM4,state);
}
void PWM_Welding (int on_delay,int off_delay,int duty_cycle,int Pin,boolean state)
{
   unsigned long previousMillis=0;
   unsigned long currentMillis = millis();
   if (state ==LOW)
   {
      if(currentMillis == on_delay){
       analogWrite(Pin,duty_cycle);
       
      }
      
   }
    if (state== HIGH)
  {   
      previousMillis = currentMillis;
      if(currentMillis-previousMillis>=off_delay){
        analogWrite(Pin,0);
      }
  }
}

