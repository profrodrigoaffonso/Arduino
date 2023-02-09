int valor;

void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(A5);
  //Serial.println(valor);
  delay(valor);
  tone(11, 1600, 50); 
  delay(valor);
}
