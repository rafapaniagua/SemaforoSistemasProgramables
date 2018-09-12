#define boton 2
#define led_rojo 4
#define led_ama 7
#define led_verde 8
#define led_peat_verde 12
#define led_peat_rojo 13
#define pot A0

int valorPot;
int segundos;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_verde,OUTPUT);
  pinMode(led_ama,OUTPUT);
  pinMode(led_rojo,OUTPUT);
  pinMode(led_peat_verde,OUTPUT);
  pinMode(led_peat_rojo,OUTPUT);
  pinMode(boton,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  valorPot = analogRead(pot);
  segundos = (valorPot*2)/100;
  Serial.print("Segundos en verde: ");
  Serial.println(segundos);
  verde();
  amarillo();
  rojo();
}

void verde(){
  digitalWrite(led_verde,HIGH);
  digitalWrite(led_peat_rojo,HIGH);
  for(int x=0;x<segundos;x++){
    delay(1000);
    if(digitalRead(boton) == LOW){
      Serial.print("-----Se detuvo a los ");
      Serial.print(x+1);
      Serial.println(" segundos");
      x=segundos;
    }
  }
  digitalWrite(led_verde,LOW);
  delay(500);
  for(int x=0;x<3;x++){
    digitalWrite(led_verde,HIGH);
    delay(500);
    digitalWrite(led_verde,LOW);
    delay(500);
  }
}

void amarillo(){
  digitalWrite(led_ama,HIGH);
  delay(3000);
  digitalWrite(led_ama,LOW);
  digitalWrite(led_peat_rojo,LOW);
  delay(1000);
}

void rojo(){
  digitalWrite(led_rojo,HIGH);
  digitalWrite(led_peat_verde,HIGH);
  delay(4000);
  digitalWrite(led_rojo,LOW);
  digitalWrite(led_peat_verde,LOW);
  delay(1000);
}
