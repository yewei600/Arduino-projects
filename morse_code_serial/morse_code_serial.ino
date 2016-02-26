
/*
  Morse code display on Serial: Enter a sentence on the Serial. Key 'Enter' to signal the end of sentence.
  The Morse code equivalent will display after.
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
                              "-....", "--...", "---..", "----.", "-----", "--..--", ".-.-.-",
                              "..--.."
                            };

// Create variable to define the output pins
int ledPin = 12;      // blink an led on output 12
int audioPin = 11;      // output audio on pin 8
int note = 1200;      // music note/pitch

int dotLen = 100;     // length of the morse code 'dot'
int dashLen = dotLen * 3;    // length of the morse code 'dash'
int elemPause = dotLen;  // length of the pause between elements of a character
int Spaces = dotLen * 3;     // length of the spaces between characters
int wordPause = dotLen * 7;  // length of the pause between words

String sentenceBuffer = "";
char DELIMITER = '\n';
char letter;

void setup() {
  Serial.begin(9600);
  Serial.println("enter a sentence: ");
}

void ProcessMorseLetter(char letter) {
  int index;
  for (int i = 0; i < 37; i++) {
    if (letter == alpha[i]) {
      index = i;
    }
  }
  String morseStr = morseArray[index];

  for (int i = 0; i < morseStr.length(); i++) {
    if (morseStr[i] == '.') {
      Serial.print('.');
      digitalWrite(ledPin, HIGH);  	// turn the LED on
      tone(audioPin, note, dotLen);	// start playing a tone
      delay(dotLen);             	// hold in this position

    }
    else if (morseStr[i] == '-') {
      Serial.print('-');
      digitalWrite(ledPin, HIGH);  	// turn the LED on
      tone(audioPin, note, dashLen);	// start playing a tone
      delay(dashLen);               // hold in this position
    }
    LightsOff(elemPause);
  }
}

// Turn Off
void LightsOff(int delayTime)
{
  digitalWrite(ledPin, LOW);    	// turn the LED off
  noTone(audioPin);	       	   	// stop playing a tone
  delay(delayTime);            	// hold in this position
}


void loop() {

  if (Serial.available()) {
    letter = (char)Serial.read();
    if (isupper(letter)) {
      letter = tolower(letter);
    }
    if (letter == DELIMITER) {      //end of a sentence
      Serial.println("you entered " + sentenceBuffer);
      //processing each letter
      for (int i = 0; i < sentenceBuffer.length() - 1; i++) {
        ProcessMorseLetter(sentenceBuffer[i]);
        Serial.print("   ");
        delay(250);
      }
      sentenceBuffer = "";
      Serial.println("\nenter a sentence: ");
    }
    else {
      sentenceBuffer += letter;
    }
  }
}

