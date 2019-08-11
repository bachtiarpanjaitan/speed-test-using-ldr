#define sensor_a A10
#define sensor_b A11

int nilai_a, nilai_b;
int light_limit = 50;
float range = 10; //satuan meter;
float start_timer,stop_timer, speed_time, speed_jam;
float range_km = range / 1000;
bool action_flag = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensor_a, INPUT);
  pinMode(sensor_b, INPUT);
  Serial.begin(9800);
}
void loop() {
  // put your main code here, to run repeatedly:
  nilai_a = analogRead(sensor_a);
  nilai_b = analogRead(sensor_b);

  if(nilai_a > light_limit && nilai_b < light_limit && action_flag == false){
    deteksi_forward();
  }else if(nilai_b > light_limit && nilai_a < light_limit && action_flag == false){
    deteksi_reverse();
  }else{
     reset();
  }
}

void deteksi_forward()
{
  //kondisi sensor a mati dan sensor b hidup
  Serial.println("masuk ke fungsi deteksi forward");
  start_timer = millis();
  do {
    nilai_b = analogRead(sensor_b);
  }while(nilai_b < light_limit);
  stop_timer = millis() - start_timer;
  speed_time = range_km / (stop_timer / 3600000); // rumus menghitung kecepatan : Jarak / waktu;
  Serial.println(speed_time);
  delay(500);
  reset();
}

void deteksi_reverse()
{
  //kondisi sensor a hidup dan sensor b mati
  Serial.println("masuk ke fungsi deteksi reverse");
  start_timer = millis();
  do {
    nilai_a = analogRead(sensor_a);
  }while(nilai_a < light_limit);
  stop_timer = millis() - start_timer;
  speed_time = range_km / (stop_timer / 3600000); // rumus menghitung kecepatan : Jarak / waktu;
  Serial.println(speed_time);
  delay(500);
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
