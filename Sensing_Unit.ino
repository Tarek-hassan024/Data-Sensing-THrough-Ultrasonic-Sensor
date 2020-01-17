int trig = 14;
int echo = 12;

float Tt;
float s = 0;
float v = 0.0344;
float t = 0;

void setup() {
  // put your setup code here, to run once:


  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:

    digitalWrite(trig,LOW);
    delayMicroseconds(2);

    digitalWrite(trig,HIGH);
    delayMicroseconds(10);

    digitalWrite(trig,LOW);
   
   Tt = pulseIn(echo,HIGH);
    t = (float)Tt/2;

    s = v*t;
    Serial.println(s);
}
