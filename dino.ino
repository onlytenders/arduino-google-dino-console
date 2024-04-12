#include <LiquidCrystal_I2C.h>  //  Library used to work with 
 
LiquidCrystal_I2C lcd(0x27, 16, 2); //  Initializing the 

//  Defining special characters to represent game 
byte DINO_STOP_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001}; 
byte DINO_STOP_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000}; 
byte DINO_RIGHT_FOOT_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001}; 
byte DINO_RIGHT_FOOT_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B00000}; 
byte DINO_LEFT_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00000}; 
byte DINO_LEFT_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000}; 
byte TWO_BRANCHES_PART_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100}; 
byte TWO_BRANCHES_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100}; 
byte BIRD_WINGS_PART_1[8] = {B00001, B00001, B00001, B00001, B01001, B11111, B00000, B00000}; 
byte BIRD_WINGS_PART_2[8] = {B00000, B10000, B11000, B11100, B11110, B11111, B00000, B00000}; 


int dino_col_1 = 1; //  Column of the first character of 
int dino_col_2 = 2; //  Column of the second character of 
int dino_row = 1;   //  Row on which dino is 
unsigned long clock1 = 0;   //  Helper timer to make dino's legs 
int flag = 1;               //  Used to represent the position of dino's 
int row_branch = 0;         //  
int col_branch = 13; 
int period_2 = 150; //  time interval for moving
unsigned long clock2 = 0; 
int a = 0; 
int b = 1; 
int c = 2; 
int d = 0; 
unsigned long clock3 = 0; 
unsigned long clock5 = 0;
int period_3 = 100; 
int period_5 = 600;
int points = 0; 
int points_2 = 0; 
int randomnum = 0; 
int birdcol = 13; 
int e = 0; 
int birdrow = 1; 
int currsignal = 0; 
int oldsignal = 0; 
int f = 13; 
int acceleration = 1; 
unsigned long clock4 = 0; 
int period_4 = 800; 
int button = 11; //   Pushbutton pin - for making the Dinosaur jump 
int buzzer = 10; //   Passive Buzzer pin - for sound effects 
int cd = 0;
 
 
void setup() { 
  for (int i = 2; i <= 17; i++)  pinMode(i, OUTPUT); 
 
  pinMode(button, INPUT); 
 
  pinMode(buzzer, OUTPUT); 
 

  //  generating characters
  lcd.init(); 
  lcd.backlight(); 
  lcd.createChar(0, DINO_STOP_PART_1); 
  lcd.createChar(1, DINO_STOP_PART_2); 
  lcd.createChar(2, DINO_RIGHT_FOOT_PART_1); 
  lcd.createChar(3, DINO_RIGHT_FOOT_PART_2); 
  lcd.createChar(4, DINO_LEFT_PART_1); 
  lcd.createChar(5, DINO_LEFT_PART_2); 
  lcd.createChar(6, TWO_BRANCHES_PART_1); 
  lcd.createChar(7, TWO_BRANCHES_PART_2); 
} 
void loop() { 

  //  tracking a long jump
  if (millis() > clock5 + period_5 && currsignal == 1) {
    lcd.setCursor(1, 0); 
    lcd.print("  "); 
    clock5 = millis();
    oldsignal = currsignal;
    currsignal = 0;
    cd = 1;
  }

  //  feet animation flags
  if (millis() > clock1 + period_2) { 
    clock1 = millis(); 
    if (flag == 1) { 
      flag = 2; 
    } 
    else if (flag == 2) { 
      flag = 1; 
 
    } 
 
 
  } 
  
  //  update of branches and game acceleration
  if (millis() > clock2 + period_2) { 
    clock2 = millis(); 
 
    col_branch = col_branch - 1; 
    if (col_branch < 0) { 
      col_branch = 13; 
      period_2 = period_2 - acceleration; 
      randomnum = random(0, 3); 
    } 
 
    f = col_branch + 1; 
    lcd.setCursor(f, 1); 
    lcd.print(" "); 
 
    f = col_branch + 1; 
    lcd.setCursor(f, 0); 
    lcd.print(" "); 
 
 
    lcd.setCursor(0, 1); 
    lcd.print(" "); 
 
    lcd.setCursor(0, 0); 
    lcd.print(" "); 
 
    a = 1; 
  } 
 
  //  drawing feet animation
  if (d == 0) { 
    if (flag == 1) { 
      lcd.setCursor(dino_col_1, dino_row); 
      lcd.write(byte(2));
      lcd.setCursor(dino_col_2, dino_row); 
      lcd.write(byte(3)); 
    } 
    if (flag == 2) { 
      lcd.setCursor(dino_col_1, dino_row); 
      lcd.write(byte(4)); 
      lcd.setCursor(dino_col_2, dino_row); 
      lcd.write(byte(5)); 
    } 
  } 
 
 //   Placing obstacles randomly
  if (a == 1) { 
 
    if (randomnum == 1) { 
      row_branch = 1; 
      lcd.createChar(6, TWO_BRANCHES_PART_1); 
      lcd.setCursor(col_branch, row_branch); 
      lcd.write(byte(6)); 
 
    } 
    else if (randomnum == 2) { 
      row_branch = 1; 
      lcd.createChar(7, TWO_BRANCHES_PART_2); 
      lcd.setCursor(col_branch, row_branch); 
      lcd.write(byte(7)); 
 
    } 
    else { 
 
      birdcol = col_branch; 
      birdcol = birdcol - 1; 
      row_branch = 0; 
      lcd.createChar(6, BIRD_WINGS_PART_1); 
      lcd.setCursor(birdcol, row_branch); 
      lcd.write(byte(6)); 
 
      lcd.createChar(7, BIRD_WINGS_PART_2); 
      lcd.setCursor(col_branch, row_branch); 
      lcd.write(byte(7)); 
 
    } 
 
    a = 0; 
  } 
   
 
  //  Game over if collision
  if (currsignal == 1 && (col_branch == 1 || col_branch == 2 || birdcol == 1 || birdcol == 2) && row_branch == 0 ) { 
    int note[] = {200, 150}; 
    for (int i = 0; i < 2; i++) { 
      tone(buzzer, note[i], 250); 
      delay(200); 
    } 

    for (int i = 0; i < 5; i++) { 
      lcd.clear(); 
      lcd.setCursor(i, 0); 
      lcd.print("GAME"); 
      lcd.setCursor(12 - i, 1); 
      lcd.print("OVER"); 
      delay(100); 
    } 
    delay(2000); 
    lcd.clear(); 
    col_branch = 15; 
    period_2 = 100; 
    points = 0; 
    points_2 = 0; 
    period_2 = 100; 
 
  } 
 
 //   Additional game over conditions
  if ((col_branch == b || col_branch == c) && row_branch == 1) { 
    int note[] = {200, 150}; 
    for (int i = 0; i < 2; i++) { 
      tone(buzzer, note[i], 250); 
      delay(200); 
    } 
 
    for (int i = 0; i < 5; i++) { 
      lcd.clear(); 
      lcd.setCursor(i, 0); 
      lcd.print("GAME"); 
      lcd.setCursor(12 - i, 1); 
      lcd.print("OVER"); 
      delay(100); 
    } 
 
    delay(2000); 
    lcd.clear(); 
    col_branch = 15; 
    period_2 = 100; 
    points = 0; 
    points = 2; 
    period_2 = 100; 
  } 
 
  //    Jump logic
  if (currsignal == 1 && cd == 0) { 
 
    b = 50;  
    c = 50; 
 
    if (d == 0) { 
      lcd.setCursor(0, 1);   
      lcd.print("    "); 
    } 
    d = 1; 
 
    lcd.setCursor(dino_col_1, 0);
    lcd.write(byte(2));
    lcd.setCursor(dino_col_2, 0);
    lcd.write(byte(3));

    //    Sound signal 
    if (millis() > clock4 + period_4) {  
      clock4 = millis(); 
 
      int note[] = {600}; 
      for (int i = 0; i < 1; i++) { 
        tone(buzzer, note[i], 150); 
        delay(20); 
      } 
    } 
  } 
  else { 
    b = 1;   
    c = 2; 
    d = 0; 
  } 
   
  //  score incrementer
  if (millis() > clock3 + period_3) {  
    clock3 = millis(); 
    lcd.setCursor(14, 1); 
    lcd.print(points); 

    points = points + 1; 

    //  hundreds incrementer
    if (points == 100) { 
      int note[] = {800, 900}; 
      points = 0; 
      points_2 = points_2 + 1; 
      for (int i = 0; i < 2; i++) { 
        tone(buzzer, note[i], 150); 
        delay(150); 
        if (points_2 == 100) { 
          points_2 = 0; 
        } 
 
      } 

    } 
 
 
    lcd.setCursor(14, 1); 
    lcd.print(points); 
    lcd.setCursor(14, 0); 
    lcd.print(points_2); 
 
    //  Reading the state of the button
    currsignal = digitalRead(button); 
    if (currsignal != oldsignal) 
    { 
      cd = 0;
      if (currsignal == 1) {
        clock5 = millis();
      }
      //  clearing the display if the state changes
      lcd.setCursor(1, 0); 
      lcd.print("  "); 
    } 
    oldsignal = currsignal; 
  } 
}
