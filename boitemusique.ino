
  #include <avr/pgmspace.h>
  #include "pitches.h"
  #include "songs.h"
  #include <rtttl.h>
  #include <Button.h>

 /* Plus haut on a chargé le fichier song.h.
  * Ce fichier regroupe toutes les chansons qui seront utilisées ici au format RTTTL
  */

  //Initialisation du player sur le pin D2 (le speaker)
  ProgmemPlayer player(2);

  //On enregistre les notes de la gammes pour mieux les réutiliser plus tard
  int gamme[] = {NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
  int gammeDiese[] = {NOTE_CS4,NOTE_DS4,NOTE_FS4, NOTE_GS4, NOTE_AS4};
  
  // Définissons les numéros de pin:
  int Speaker =  2; 
  int randomLed;
  int nbLeds = 6;
  
  int leds[] = {A5, A4, A3, A2, A1, A0};
  
  Button buttonDo = Button(4,INPUT);
  Button buttonRe = Button(5,INPUT);
  Button buttonMi = Button(6,INPUT);
  Button buttonFa = Button(7,INPUT);
  Button buttonSol = Button(8,INPUT);
  Button buttonLa = Button(9,INPUT);
  Button buttonSi = Button(10,INPUT);
  Button buttonDo2 = Button(11,INPUT);
  Button buttonInterrupt = Button(12,INPUT);
  
  //Helper pour le player
  bool keepgoing = true;
  
  void setup() {
     //Setup des pins en mode output
     for(int i=0; i<=7; i++){
       pinMode(leds[i], OUTPUT);
     }
     pinMode(Speaker, OUTPUT);
     Serial.begin(9600);
     
     //Première initialisation de randomLed.
     randomLed = random(nbLeds);
  
     //Jeu de lumière à l'allumage de la boite
     for(int i=0; i<nbLeds; i++){
       digitalWrite(leds[i],HIGH); delay(100);
     }
     for(int i=0; i<nbLeds; i++){
       digitalWrite(leds[i],LOW); delay(100);
     }
   
  }
  
  /*
   * Eteindre toutes les leds
   */
  void ledsOff(){
     for(int i=0; i<nbLeds; i++){
       digitalWrite(leds[i],LOW);
     }
  }
  
  /*
   * TurAllumer toutes les leds
   */
  void ledsOn(){
     for(int i=0; i<nbLeds; i++){
       digitalWrite(leds[i],HIGH);
     }
  }

  /*
   * Jouer la musique actuellement chargée en mémoire
   */
  void showMeWhatYouGot(){
      while(keepgoing && player.pollSong()){
        //Générer les sons, et gérer les interruptions
        delay(5); //Laisser à la musique le temps de démarrer
        //Si le bouton d'interruption est pressé, alors on arrête tout
        if(buttonInterrupt.uniquePress()){ 
          delay(5); //Filet de sécurité
          keepgoing = false;
          player.silence(); //Chanson: stop !
        }
        //Led to beam up, scotty !
        if(player.pollBeep()){
          digitalWrite(leds[randomLed],HIGH);
        }else{
          ledsOff();
          randomLed = random(nbLeds);
        }
      } 
      //Reinitialiser la chanson
      player.initSong(); 
      keepgoing = true; 
  }
  
  
  void loop() {

      if(buttonDo.uniquePress()||buttonRe.uniquePress()||buttonMi.uniquePress()||buttonFa.uniquePress()
        ||buttonSol.uniquePress()||buttonLa.uniquePress()||buttonSi.uniquePress()||buttonDo2.uniquePress()){
        randomLed = random(nbLeds);
      }
      
      //Les combinaisons d'abord 
      if(buttonInterrupt.isPressed() && buttonDo.isPressed()){ Serial.println("Perdu le Do"); player.setSong(songPerduLeDo); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonRe.isPressed()){ Serial.println("Small world"); player.setSong(songSmallWorld); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonMi.isPressed()){ Serial.println("Furet"); player.setSong(songFuret); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonFa.isPressed()){ Serial.println("Malbrough"); player.setSong(songMalbrough); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonSol.isPressed()){ Serial.println("Au bois"); player.setSong(songAuBois); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonLa.isPressed()){ Serial.println("Int+La : Looney"); player.setSong(songAvignon); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonSi.isPressed()){ Serial.println("Int+Si : Lorraine"); player.setSong(songLaurraine); showMeWhatYouGot(); }
      else if(buttonInterrupt.isPressed() && buttonDo2.isPressed()){ Serial.println("Int+Do2 : Hardi les gars"); player.setSong(songHardiLesGars); showMeWhatYouGot(); }

      //Ensuite, les combinaisons blague
      else if(buttonDo.isPressed() && buttonMi.isPressed() && buttonSol.isPressed()){
        Serial.println("Mario"); player.setSong(songMario); showMeWhatYouGot();
      }
      else if(buttonRe.isPressed() && buttonFa.isPressed() && buttonLa.isPressed()){
        Serial.println("Tetris"); player.setSong(songTetris); showMeWhatYouGot();
      }
      else if(buttonMi.isPressed() && buttonSol.isPressed() && buttonSi.isPressed()){
        Serial.println("Cantina"); player.setSong(songCantina); showMeWhatYouGot();
      }
      else if(buttonFa.isPressed() && buttonLa.isPressed() && buttonDo2.isPressed()){
        Serial.println("Cantina"); player.setSong(songStarwars); showMeWhatYouGot();
      }


      //Puis les dieses
      else if(buttonDo.isPressed() && buttonRe.isPressed()){
        Serial.println("DO diese"); tone(Speaker, gammeDiese[0]);
        digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonRe.isPressed() && buttonMi.isPressed()){
        Serial.println("RE diese"); tone(Speaker, gammeDiese[1]);
        digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonFa.isPressed() && buttonSol.isPressed()){
        Serial.println("FA diese"); tone(Speaker, gammeDiese[2]);
        digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonSol.isPressed() && buttonLa.isPressed()){
        Serial.println("SOL diese"); tone(Speaker, gammeDiese[3]);
        digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonLa.isPressed() && buttonSi.isPressed()){
        Serial.println("LA diese"); tone(Speaker, gammeDiese[4]);
        digitalWrite(leds[randomLed],HIGH);
      }
      
      // Et enfin les notes normales
      else if(buttonDo.isPressed()){
        Serial.println("DO"); tone(Speaker, gamme[0]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }      
      else if(buttonRe.isPressed()){
        Serial.println("RE"); tone(Speaker, gamme[1]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonMi.isPressed()){
        Serial.println("MI"); tone(Speaker, gamme[2]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonFa.isPressed()){
        Serial.println("FA"); tone(Speaker, gamme[3]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonSol.isPressed()){
        Serial.println("SOL"); tone(Speaker, gamme[4]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonLa.isPressed()){
        Serial.println("LA"); tone(Speaker, gamme[5]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonSi.isPressed()){
        Serial.println("SI"); tone(Speaker, gamme[6]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else if(buttonDo2.isPressed()){
        Serial.println("DO2"); tone(Speaker, gamme[7]);
        ledsOff(); digitalWrite(leds[randomLed],HIGH);
      }
      else{
        ledsOff();
        noTone(Speaker);
        Serial.println("not pressed");
      }     
  }


