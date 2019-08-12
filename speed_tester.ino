#include <LiquidCrystal.h>
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define sensor_a A10
#define sensor_b A11

int lcd_key     = 0;
int adc_key_in  = 0;
int c_button = 0;
int nilai_a, nilai_b;
int light_limit = 50;
int suffle_delay= 1000; //satuan milli second
float range = 10; //satuan meter;
float start_timer,stop_timer, speed_time, speed_jam;
float range_km = range / 1000;
bool action_flag = false;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void setup() {
  // put your setup code here, to run once:
  pinMode(sensor_a, INPUT);
  pinMode(sensor_b, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);           
  lcdprint(0,0,"  SPEED TESTER  ");
}
void loop() {
  // put your main code here, to run repeatedly:
  nilai_a = analogRead(sensor_a);
  nilai_b = analogRead(sensor_b);

  if(nilai_a > light_limit && nilai_b < light_limit && action_flag == false){
    lcd.clear();
    deteksi_forward();
  }else if(nilai_b > light_limit && nilai_a < light_limit && action_flag == false){
    lcd.clear();
    deteksi_reverse();
  }else{
     reset();
  }
}

void deteksi_forward()
{
  //kondisi sensor a mati dan sensor b hidup
  Serial.println("masuk ke fungsi deteksi forward");
  lcdprint(0,0,"  WAITING  ");
  start_timer = millis();
  do {
    nilai_b = analogRead(sensor_b);
  }while(nilai_b < light_limit);
  stop_timer = millis() - start_timer;
  speed_time = range_km / (stop_timer / 3600000); // rumus menghitung kecepatan : Jarak / waktu;
  String txt = (String) speed_time;
  txt += " KM/H";
  lcdprint(0,0,txt);
  
  String txt2 = (String) stop_timer;
  txt2 += " ms";
  lcdprint(0,1,txt2);
  delay(suffle_delay);
  reset();
}

void deteksi_reverse()
{
  //kondisi sensor a hidup dan sensor b mati
  Serial.println("masuk ke fungsi deteksi reverse");
  lcdprint(0,0,"  WAITING  ");
  start_timer = millis();
  do {
    nilai_a = analogRead(sensor_a);
  }while(nilai_a < light_limit);
  stop_timer = millis() - start_timer;
  speed_time = range_km / (stop_timer / 3600000); // rumus menghitung kecepatan : Jarak / waktu;
  Serial.println(speed_time);
  String txt = (String)speed_time;
  txt += " KM/H";
  lcdprint(0,0,txt);

  String txt2 = (String) stop_timer;
  txt2 += " ms";
  lcdprint(0,1,txt2);
  delay(suffle_delay);
  reset();
}

void reset()
{
  speed_time = 0;
  start_timer = 0;
  speed_time = 0;
  nilai_a = 0;
  nilai_b = 0;
}

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);   
 
 if (adc_key_in > 1000) return btnNONE; 
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 return btnNONE;  
}

void lcdprint(int row, int col, String data){
  lcd.setCursor(row,col);
  lcd.print(data);
}
