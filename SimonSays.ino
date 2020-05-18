// pin numbers for LEDs and buttons
#define redLED 13
#define redButton 12
#define blueLED 11
#define blueButton 10
#define yellowLED 9
#define yellowButton 8
#define greenLED 7
#define greenButton 6

#define patternSize 50   // limit of entries in the pattern (how long you want the game to go for)

int pattern[50];        // each index represents an LED
int score = 0;          // tracks score and how many entries in pattern[]
int randNum = 0;   
int buttonPin = 0; 

void(* resetFunc) (void) = 0;

// returns pin number of the button that was pressed
int buttonWait(int buttonPin1, int buttonPin2, int buttonPin3, int buttonPin4) {
  int buttonState1 = 0;
  int buttonState2 = 0;
  int buttonState3 = 0;
  int buttonState4 = 0;
  while(1) {
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    buttonState3 = digitalRead(buttonPin3);
    buttonState4 = digitalRead(buttonPin4);
    if (buttonState1 == HIGH) {
      return buttonPin1;
    } else if (buttonState2 == HIGH) {
      return buttonPin2;
    } else if (buttonState3 == HIGH) {
      return buttonPin3;
    } else if (buttonState4 == HIGH) {
      return buttonPin4;
    } else {
      // wait
    }
  }
}

void ledOnOff(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(750);
    digitalWrite(ledPin, LOW);
    delay(250);
}

// displays score, flashes LEDs, resets program
void gameOver() {
  Serial.print("GAME OVER. Your final score is ");
  Serial.println(score);
  for (int i = 0; i < 3; i++) {
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(300);
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(300);
  }
  resetFunc();
}

void setup() {
  Serial.begin(9600);
  
  pinMode(redLED, OUTPUT);
  pinMode(redButton, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(blueButton, INPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(yellowButton, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(greenButton, INPUT);
  
  randomSeed(analogRead(5));
}

void loop() {
  for (int i = 0; i < patternSize; i++) {
    randNum = random(0, 4);
    pattern[i] = randNum;
    //delay(1000);

    // cycle through current pattern
    for (int j = 0; j <= score; j++) { 
      if (pattern[j] == 0) {       // RED
        ledOnOff(redLED);
      } else if (pattern[j] == 1) { // BLUE
        ledOnOff(blueLED);
      } else if (pattern[j] == 2) { // YELLOW
        ledOnOff(yellowLED);
      } else {                     // GREEN
        ledOnOff(greenLED);
      } 
    }

    // compare button input with pattern[]
    for (int j = 0; j <= score; j++) {
      buttonPin = buttonWait(redButton, blueButton, yellowButton, greenButton);
      if (pattern[j] == 0) {        // RED
        if (buttonPin == redButton) {
          ledOnOff(redLED);
        } else {
          gameOver();
        }
      } else if (pattern[j] == 1) {  // BLUE
        if (buttonPin == blueButton) {
          ledOnOff(blueLED);
        } else {
          gameOver();
        }
      } else if (pattern[j] == 2) {  // YELLOW
        if (buttonPin == yellowButton) {
          ledOnOff(yellowLED);
        } else {
          gameOver();
        }
      } else if (pattern[j] == 3) {  // GREEN
        if (buttonPin == greenButton) {
          ledOnOff(greenLED);
        } else {
          gameOver();
        }
      } else {
        // do nothing
      }
    }
    score++;
  }
   gameOver();
}
