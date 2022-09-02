#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define level1_btn 2
#define level2_btn 3
#define level3_btn 4

#define ir_sen1 8
#define ir_sen2 9
#define ir_sen3 10

#define relay1 A0
#define relay2 A1

boolean cal = true;
int movee;
void setup()
{
  pinMode(level1_btn, INPUT_PULLUP);
  pinMode(level2_btn, INPUT_PULLUP);
  pinMode(level3_btn, INPUT_PULLUP);

  pinMode(ir_sen1, INPUT);
  pinMode(ir_sen2, INPUT);
  pinMode(ir_sen3, INPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, HIGH); digitalWrite(relay2, HIGH);

  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--Three  Stage--");
  lcd.setCursor(0, 1);
  lcd.print("----SINK----");
  delay(2000);
  stop();
  while (cal == true)
  {
    lcd.setCursor(0, 0);
    lcd.print("Move Sink to");
    lcd.setCursor(0, 1);
    lcd.print("near stage");

    if (digitalRead(ir_sen1) == LOW and digitalRead(ir_sen2) == HIGH and digitalRead(ir_sen3) == HIGH)
    {
      lcd.setCursor(0, 0);
      lcd.print("Calibration Done");
      lcd.setCursor(0, 1);
      lcd.print("Sink stage : 1  ");
      movee = 1;
      delay(1500);
      lcd.clear();
      cal = false;
      break;
    }
    else if (digitalRead(ir_sen1) == HIGH and digitalRead(ir_sen2) == LOW and digitalRead(ir_sen3) == HIGH)
    {
      lcd.setCursor(0, 0);
      lcd.print("Calibration Done");
      lcd.setCursor(0, 1);
      lcd.print("Sink stage : 2  ");
      movee = 2;
      delay(1500);
      lcd.clear();
      cal = false;
      break;
    }
    else if (digitalRead(ir_sen1) == HIGH and digitalRead(ir_sen2) == HIGH and digitalRead(ir_sen3) == LOW)
    {
      lcd.setCursor(0, 0);
      lcd.print("Calibration Done");
      lcd.setCursor(0, 1);
      lcd.print("Sink stage : 3  ");
      movee = 3;
      delay(1500);
      lcd.clear();
      cal = false;
      break;
    }
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Press any level");
}
void loop()
{
  if (digitalRead(ir_sen1) == LOW and digitalRead(ir_sen2) == HIGH and digitalRead(ir_sen3) == HIGH)
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Current Level:  ");
    lcd.setCursor(14, 0);
    lcd.print("1 ");
  }
  else if (digitalRead(ir_sen1) == HIGH and digitalRead(ir_sen2) == LOW and digitalRead(ir_sen3) == HIGH)
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Current Level:  ");
    lcd.setCursor(14, 0);
    lcd.print("2 ");
  }
  else if (digitalRead(ir_sen1) == HIGH and digitalRead(ir_sen2) == HIGH and digitalRead(ir_sen3) == LOW)
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Current Level:  ");
    lcd.setCursor(14, 0);
    lcd.print("3 ");
  }
  if (digitalRead(level1_btn) == LOW and digitalRead(ir_sen1) == HIGH and (movee == 3 or movee == 2))
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Moving...");
    lcd.setCursor(10, 1);
    lcd.print(movee);
    lcd.setCursor(12, 1);
    lcd.print("D");
    delay(500);
    down();
    movee = 1;
  }
  if (digitalRead(level1_btn) == LOW and digitalRead(ir_sen1) == LOW and movee == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(" Already in 1  ");
    delay(500);
    stop();
    movee = 1;
  }



  if (digitalRead(level2_btn) == LOW and digitalRead(ir_sen2) == HIGH and movee == 1) //1 to 2
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Moving...");
    lcd.setCursor(10, 1);
    lcd.print(movee);
    lcd.setCursor(12, 1);
    lcd.print("U");
    delay(500);
    up();
    movee = 2;
  }
  if (digitalRead(level2_btn) == LOW and digitalRead(ir_sen2) == HIGH and movee == 3)//3 to 2
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Moving...");
    lcd.setCursor(10, 1);
    lcd.print(movee);
    lcd.setCursor(12, 1);
    lcd.print("D");
    delay(500);
    down();
    movee = 2;
  }
  if (digitalRead(level2_btn) == LOW and digitalRead(ir_sen2) == LOW and movee == 2)
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(" Already in 2  ");
    delay(500);
    stop();
    movee = 2;
  }


  if (digitalRead(level3_btn) == LOW and digitalRead(ir_sen3) == HIGH and (movee == 1 or movee == 2))
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Moving...");
    lcd.setCursor(10, 1);
    lcd.print(movee);
    lcd.setCursor(12, 1);
    lcd.print("U");
    delay(500);
    up();
    movee = 3;
  }
  if (digitalRead(level3_btn) == LOW and digitalRead(ir_sen3) == LOW and movee == 3)
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(" Already in 3  ");
    delay(500);
    stop();
    movee = 3;
  }

  if (digitalRead(ir_sen1) == LOW and movee == 1)
  {
    stop();
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("First stage");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Press any level");
    delay(500);
  }

  if (digitalRead(ir_sen2) == LOW and movee == 2)
  {
    stop();
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Second stage");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Press any level");
    delay(500);
  }

  if (digitalRead(ir_sen3) == LOW and movee == 3)
  {
    stop();
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Third stage");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Press any level");
    delay(500);
  }

}
void stop()
{
  digitalWrite(relay1, HIGH); digitalWrite(relay2, HIGH);
}
void up()
{
  digitalWrite(relay1, HIGH); digitalWrite(relay2, LOW);
}
void down()
{
  digitalWrite(relay1, LOW); digitalWrite(relay2, HIGH);
}
