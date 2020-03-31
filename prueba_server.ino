
int couter=0;
void setup() {
  Serial.begin(9600);
  
}

void loop() {
  Serial.print(++couter, DEC);
  delay(2000);

}
