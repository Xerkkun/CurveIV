#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Variables
int inV = 0;
int inI = 1;
int Out = 8;

int lecturasV[25];
int lecturasI[25];
int val, j = 0, i = 0, totalV = 0, totalI = 0, V = 0, I = 0;
float Vmax , Imax, promedioV = 0.0, promedioI = 0.0, R = 0.1;

void setup() {
  pinMode(Out, OUTPUT);
  digitalWrite(Out,LOW);
  Serial.begin(9600);
  lcd.begin(8, 2);
  lcd.clear();

  //Refrescar valores en LCD cada 1 s
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(LCD);

  //Inicializar el vector
  for (i = 0; i < 25; i++)
    lecturasV[i] = 0;
  i = 0;

  for (j = 0; j < 25; j++)
    lecturasI[j] = 0;
  j = 0;
}


void loop() {
  
  while (j < 25) {
    digitalWrite(Out,HIGH);
    //sustrae el total con la lectura inmediata anterior
    totalV = totalV - lecturasV[i];
    totalI = totalI - lecturasI[i];

    //recopila mediciones
    lecturasV[i] = analogRead(inV);
    lecturasI[i] = analogRead(inI);

    //suma las lecturas
    totalV = totalV + lecturasV[i];
    totalI = totalI + lecturasI[i];

    //calcula el promedio de las lecturas
    i = i + 1;
    if (i >= 25) {
      i = 0;
      promedioV = totalV / 25;
      promedioI = totalI / 25;

      V = promedioV/204.6;
      I = promedioI/(204.6*R);

      //busca valores maximos
      Vmax = max(Vmax, V);
      Imax = max(Imax, I);
    }

    j = j + 1;
    delay(1);
    Serial.print(V);
    Serial.print(",");
    Serial.println(I);
  }
  digitalWrite(Out,LOW);
  Vmax = Vmax;
  Imax = Imax;
}

void LCD() {
  lcd.clear();
  lcd.print("Icc = ");
  lcd.print(Imax);
  lcd.print(" A");
  lcd.setCursor(0, 1);
  lcd.print("Voc = ");
  lcd.print(Vmax);
  lcd.print(" V");
}
