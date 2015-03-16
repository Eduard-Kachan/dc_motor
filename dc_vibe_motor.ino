int potentiometer = 3;     // Potentiometer connected to analog pin 3
int vibeMotor = 9;         // Vibe Motor connected to digital pin 9
int timeBtn = 2;           // Button to record the duration connected to digital pin 2
int playBtn = 3;           // Button to start an stop the loop connected to digital pin 3

bool timeBtnState = false; // A boolean to know if the button is pressed down or not
bool playBtnState = false; // A boolean to know if the button is pressed down or not

bool play = false;         // A boolean to keep track if the user wants to play back the vibes or record them

int val = 0;               // Variable to store the read value from the potentiometer

//Arrays to hold the recorded value from the user
int arrayLenght = 20;
int intensity[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};          
unsigned long duration[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // [milliseconds] 

int i = 0;                 //integer used by loops

unsigned long startMillis = 0;    // [milliseconds] //
unsigned long lastToggleTime = 0; // [milliseconds] //

void setup() {
  pinMode(vibeMotor, OUTPUT);
  pinMode(timeBtn, INPUT);
  pinMode(playBtn, INPUT);
}

void loop() {
  if(digitalRead(playBtn) == HIGH && playBtnState == false){
    playBtnState = true;
    play = !play;
    if(!play) {resetArrays();}
    i = 0;
  }
  
  if(digitalRead(playBtn) == LOW && playBtnState == true){
    playBtnState = false;
  }
    
  if(play){
    
    if(duration[0] == 0) {
      play = false; 
      resetArrays(); 
      i = 0;
    }
    
    if(duration[i] == 0) {i = 0;}
    
    // delay idea taken from: http://www.megunolink.com/5-tips-for-arduino-programs/
    // delay timer. usefull for creating the delay but letting the rest of the code run
    if ((millis() - lastToggleTime) > duration[i]){
      lastToggleTime = millis();
      analogWrite(vibeMotor, intensity[i]);
      
      i += 1;
      if(i == arrayLenght -1){i = 0;}
    }
  }else{
    val = (analogRead(potentiometer) / 4);   // read & save the input
    analogWrite(vibeMotor, val);             // out put the value right away as the user selects the settning
    
    if(digitalRead(timeBtn) == HIGH && timeBtnState == false){
      timeBtnState = true;
      startMillis = millis();                // when user has pressed the time button start the timer
    }
    
    if(digitalRead(timeBtn) == LOW && timeBtnState == true){
      if(i == arrayLenght -1){
        resetArrays();
        i = 0;
      }
      
      intensity[i] = val;
      duration[i] = millis() - startMillis; // record the interval when the user has unpresed the button
      timeBtnState = false;
      i += 1;
    }
    
  }
  
}

void resetArrays(){                         // quicly set the arrays to zero
  for(i = 0; i < arrayLenght; i = i + 1){
    intensity[i] = 0;
    duration[i] = 0;
  }
}
