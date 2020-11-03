void hochfahren(void)
{
  if (millis() > VERZH + myTimer ) {
    myTimer = millis();

    if (power < potimap)
    {
      power++;
    }
  }
}

void herunterfahren(void)
{
  if (millis() > VERZR + myTimer ) {
    myTimer = millis();

    if (power > 30)
    {
      power--;
    }
  }
}



void Spurservo_fahren(void) {

  if (u == 1 && o == 0) {

    static int i = 20;

    if (millis() > (FUEHRGESCHW / power) + myTimer2 ) {
      myTimer2 = millis();

      Spur.write(i);
      if (power > 30) {
        i++;
      }
      //Serial.println(i);

      if (i == 160) {
        o = 1;
        u = 0;
        i = 20;
      }

    }
  }



  if (u == 0 && o == 1) {

    static int s = 160;

    if (millis() > (FUEHRGESCHW / power) + myTimer2 ) {
      myTimer2 = millis();

      Spur.write(s);

      if (power > 30) {
        s--;
      }
      //Serial.println(s);

      if (s == 20) {
        o = 0;
        u = 1;
        s = 160;
      }

    }
  }
}


void Spindeldrehzahl_anzeigen(void)
{
  lcd.setCursor(0, 0);
  lcd.print("Spindeldrehzahl:");
  lcd.setCursor(6, 1);
  lcd.print(potianzeige);
  lcd.setCursor(8, 1);
  lcd.print("%");
}


void UBat_anzeigen(void)
{
  spg = analogRead(A1);
  spg = map(spg, 0, 1024, 0, 5);
  lcd.setCursor(0, 0);
  lcd.print("   Spannung:");
  lcd.setCursor(6, 1);
  lcd.print(spg);
}

void BetrZeit_erstellen(void)
{
  if (millis() > 1000 + myTimer4 )
  {
    myTimer4 = millis();
    Sek++;
    Serial.println(Sek);
    if (Sek == 60)
    {
      Min++;
      Sek = 0;
    }

    if (Min == 60)
    {
      Stu++;
      Min = 0;
    }
  }
}

void BetrZeit_anzeigen(void)
{
  lcd.setCursor(0, 0);
  lcd.print(" Betriebszeit:");
  lcd.setCursor(1, 1);
  lcd.print("h:");
  lcd.setCursor(3, 1);
  lcd.print(Stu);
  lcd.setCursor(6, 1);
  lcd.print("m:");
  lcd.print(Min);
  lcd.setCursor(11, 1);
  lcd.print("s:");
  lcd.print(Sek);
  
}
