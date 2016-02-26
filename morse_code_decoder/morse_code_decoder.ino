
/*
  Morse Code decoder: key in code using a pushbutton. Another pushbutton to determine when a letter is finished entering
  Then the letter will display on screen.
*/

const int SIZE = 39;
const char alpha[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                       'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                       'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8',
                       '9', '0', ',', '.', '?'
                     };
const String morseArray[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                              "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
                              "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
                              "-.--", "--..", ".----", "..---", "...--", "....-", ".....",
                              "-....", "--...", "---..", "----.", "-----", "--..--",".-.-.-",
                              "..--.."};
                            

const int inputButton = 12;
const int endLetterButton = 13;
const int audioPin = 11;

int note = 1200;      // music note/pitch
int buttonState;                    // variable to store button state
int lastButtonState = LOW;              // variable to store last button state
long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch

bool doneTranslating=false;

String letterBuffer = "";


void setup() {
  Serial.begin(9600);
  //POSITIVE LOGIC BUTTON: pressed=HIGH   not pressed=LOW
  //for circuit setup: http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C8_SwitchLED.htm
  pinMode(inputButton, INPUT);
  pinMode(endLetterButton, INPUT);

}


void ProcessMorseCode(String codeStr) {
  int index = -1;
  for (int i = 0; i < 37; i++) {
    if (codeStr == morseArray[i]) {
      index = i;
    }
  }
   if (index == -1) {
     Serial.println("\nnot a valid Morse code");
     return;
   }
  char morseLetter = alpha[index];

  Serial.print(morseLetter);
  doneTranslating=true;

}


void loop() {
  // check for button press
  buttonState = digitalRead(inputButton);                   // read the button state and store

  if (buttonState == HIGH && lastButtonState == LOW ) {    // check for a low to high transition
    startTime = millis();                                   // store the start time
    tone(audioPin, note);
    delay(5);                                               // short delay to debounce switch
    lastButtonState = buttonState;                          // store buttonState in lastButtonState, to compare next time

  }

  else if (buttonState == LOW && lastButtonState == HIGH ) {    // check for a high to low transition
    // if true then found a new button press while clock is running - stop the clock and report
  
    elapsedTime =   millis() - startTime;              // store elapsed time
    noTone(audioPin);
    lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time

    //Serial.print("elapsed time: ");
    // Serial.println(elapsedTime);
    
    if (elapsedTime < 200 && elapsedTime > 0) {
      letterBuffer += '.';     
    }
    else {
      letterBuffer += '-';
    }
    doneTranslating=false;
  }

  if (digitalRead(endLetterButton) &&!doneTranslating) {
    if (letterBuffer.length()) {
      ProcessMorseCode(letterBuffer);
      letterBuffer="";
    }
  }


}
