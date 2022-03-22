// Pinii motor 1 //
#define mpin00 8
#define mpin01 9

// Pinii motor 2 //
#define mpin10 10
#define mpin11 11


// Pinii senzor ultrasonic //
#define echoPin 4 
#define trigPin 5

// Pinii buzzerului //
#define buzzerPin 12

long duration;
int distance;

int usedDistance;

int currentIndex;

void setup() {
  Serial.begin(9600); // Interfata Serial 0, pentru BT

  // configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT); 

  //configurarea pinilor pentru senzorul ultrasonic
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  //configurarea pinului pentru buzzer
  pinMode (buzzerPin, OUTPUT);
  digitalWrite (buzzerPin, LOW);

  currentIndex = 0;
  pinMode(LED_BUILTIN, OUTPUT);
}

String readValue = "";
int delayVal = 500;


void StartMotor (int m1, int m2, int forward, int speed)
{

  if (speed==0) // oprire
  {
    digitalWrite(m1, 0); 
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      
      analogWrite (m1, speed); // folosire PWM
      digitalWrite(m2, 0);
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
} 

void delayStopped(int ms)
{
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(ms);
}


void loop() {
  //digitalWrite (buzzerPin, HIGH);

  if(Serial.available()){
      readValue = Serial.readString();
      activateLed(readValue);
      activateBuzzer(readValue);
      activateMotorInt(readValue);
      readValue = "";
  }
  
  
  usedDistance = calculateDistance();
  if(usedDistance < 3){
    delayStopped(200);
    
  }
}

void activateBuzzer(String readValue){
  if (readValue.substring(0, 4).equals("beep")){
        digitalWrite (buzzerPin, LOW);
  }
  if (readValue.substring(0, 4).equals("BEEP")){
        digitalWrite (buzzerPin, 100);
  }
}

void activateLed(String readValue){
  String value = readValue.substring(0, 3);
  if (value.equals("led")){
        digitalWrite (LED_BUILTIN, LOW);
  }
  else if (value.equals("LED")){
        digitalWrite (LED_BUILTIN, HIGH);
  }
}

void activateMotorInt(String readValue){
  String value = readValue.substring(0, 1);
  
  if(value.equals("U")){
    StartMotor (mpin00, mpin01, 0, 255);
    StartMotor (mpin10, mpin11, 1, 255);
  }
  else if (value.equals("u")){
    delayStopped(200);
  }
  
  if(value.equals("D")){
    StartMotor (mpin00, mpin01, 1, 255);
    StartMotor (mpin10, mpin11, 0, 255);
  }
  else if (value.equals("d")){
    delayStopped(200);
  }
  
  if(value.equals("S")){
    StartMotor (mpin10, mpin11, 1, 255);
  }
  else if (value.equals("s")){
    delayStopped(200);
  }
  
  if(value.equals("R")){
    StartMotor (mpin00, mpin01, 0, 255);
  }
  else if (value.equals("r")){
    delayStopped(200);
  } 
}

void activateMotor(String readValue){
  String value = readValue.substring(0, 1);
  
  if(value.equals("U")){
    StartMotor (mpin00, mpin01, 0, 255);
    StartMotor (mpin10, mpin11, 1, 255);

    delay(1300);
    delayStopped(200);
  }
  if(value.equals("D")){
    StartMotor (mpin00, mpin01, 1, 255);
    StartMotor (mpin10, mpin11, 0, 255);

    delay(1300);
    delayStopped(200);
  }
  if(value.equals("S")){
    StartMotor (mpin10, mpin11, 1, 255);

    delay(1300);
    delayStopped(200);
  }
  if(value.equals("R")){
    StartMotor (mpin00, mpin01, 0, 255);

    delay(1300);
    delayStopped(200);
  }
  
}

int calculateDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;

  return distance;
}
