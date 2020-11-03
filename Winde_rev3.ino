// Je nachdem, welcher Drehregeler-Eingang (4,7,8) auf LOW gezogen wird, bestimmt den Gang
// Fußschalter (2) startet den Schleppvorgang

//Langsam = 80, Mittel = 90, Schnell = 130 --> Werte für Regleransteuerung, eingestellt durch Poti


/*Beschaltung:

  LC-Display: siehe AnagVision Word-Dok.

  Regler:           9
  Seilführung:      10
  Fußschalter:      13

  Drehzahl-Poti:    A0
  Spannungseingang: A1

*/


#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define VERZH 0
#define VERZR 5
#define FUEHRGESCHW 1000 // Je kleiner, desto schneller bewegt sich der Führ-Arm der Trommel
#define LCDDAUER 2300 // Anzeigedauer der Daten in ms

Servo Regler;
Servo Spur;

float power = 30;
int fusstaster, u, o, poti, potimap, potianzeige, z = 0, f, x = 0, d = 0, spg, Min = 0, Sek = 0, Stu = 0;
unsigned long long int myTimer = 0, myTimer2 = 0, myTimer3 = 0, myTimer4 = 0;

void setup()
{
  lcd.begin(16, 2);

  pinMode(A0, INPUT); // Poti für max. Drehzahl
  pinMode(A1, INPUT); // Eingang für Batteriespannung
  pinMode(13, INPUT); // Fußtaster

  pinMode(13, INPUT_PULLUP); // Pullup am Fußtaster-Eingang aktiv schalten

  Regler.attach(9); // Regler an Ausgang 9
  Spur.attach(10); // Führungs-Servo an Ausgang 10

  Regler.write(30);
  Spur.write(20);

  u = 1;
  o = 0;
  f = 0;
  Serial.begin(115200);



  lcd.setCursor(2, 0);
  lcd.print("Schleppwinde");
  lcd.setCursor(5, 1);
  lcd.print(" V1.0");
  delay(1200);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("manufactured by");
  lcd.setCursor(6, 1);
  lcd.print("...");
  delay(1200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("* Till Wagner ");
  lcd.setCursor(0, 1);
  lcd.print("* Tim Sternagel");
  delay(1200);
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int q = 0; q < 6; q++)
  {
    lcd.print("## All rights ##");
    lcd.setCursor(0, 1);
    lcd.print("##  reserved  ##");
    delay(200);
    lcd.clear();
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.clear();
    delay(90);
  }

  delay(300);


}


void loop()
{
  while ((digitalRead(13) == 1) && (f == 0) && (x == 0))
  {
    if (d == 0 && f == 0)
    {
      lcd.setCursor(0, 0);
      lcd.print("Drehzahl einst.");
      lcd.setCursor(0, 2);
      lcd.print("und bestaetigen");
      delay (2000);
      lcd.clear();
      d = 1;
    }

    poti = analogRead(A0);
    potimap = map(poti, 0, 1023, 40, 130);
    potianzeige = map(potimap, 40, 130, 10, 99);
    lcd.setCursor(0, 0);
    lcd.print("Spindeldrehzahl:");
    lcd.setCursor(6, 1);
    lcd.print(potianzeige);
    lcd.setCursor(8, 1);
    lcd.print("%");

    if ((digitalRead(13) == 0) && (f == 0))
    {
      f = 1;
    }
  }

  if (x == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("### Achtung ###");
    lcd.setCursor(0, 1);
    lcd.print("! System aktiv !");
    delay(2500);
    x = 1;
    lcd.clear();
  }

  //_________________________________________________________


  BetrZeit_erstellen();
  if (f == 1) { // Hier startet der Programmlauf

    if (millis() > (LCDDAUER + myTimer3)) {
      myTimer3 = millis();
      if (z > 2)
      {
        z = 0;
      }
      z++;

      //Serial.println(z);
      lcd.clear();
    }

    if (z == 1) {
      Spindeldrehzahl_anzeigen();
    }

    if (z == 2) {
      UBat_anzeigen();
    }

    if (z == 3) {
      BetrZeit_anzeigen();
    }

    fusstaster = digitalRead(13);
    poti = analogRead(A0);
    potimap = map(poti, 0, 1023, 40, 130);
    potianzeige = map(potimap, 40, 130, 10, 99);

    if (fusstaster == LOW)
    {
      hochfahren();
    }

    if (fusstaster == HIGH)
    {
      herunterfahren();
    }

    Regler.write(power);
    Spurservo_fahren();
  }
}
