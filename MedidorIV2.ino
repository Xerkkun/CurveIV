#include <LiquidCrystal.h>
#include <TimerOne.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Variables
int inV = 0;
int inI = 1;

int lecturasV[10];
int lecturasI[10];
int val, j = 0, i = 0, totalV = 0, totalI = 0, V = 0, I = 0;
float Vmax , Imax, promedioV = 0.0, promedioI = 0.0, R = 1.0;

void setup() {
  Serial.begin(9600);
  lcd.begin(8, 2);
  lcd.clear();

  //Refrescar valores en LCD cada 1 s
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(LCD);

  //Inicializar el vector
  for (i = 0; i < 10; i++)
    lecturasV[i] = 0;
  i = 0;

  for (j = 0; j < 10; j++)
    lecturasI[j] = 0;
  j = 0;
}


void loop() {
  while (j < 25) {

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
    if (i >= 10) {
      i = 0;
      promedioV = totalV / 10;
      promedioI = totalI / 10;

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
