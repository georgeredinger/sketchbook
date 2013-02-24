void setup() { 
  Serial.begin(9600); 
}
  int i=0;
  void loop() { 
  
  Serial.print("OK  221 1 ");    
  Serial.print(i%256);
  Serial.print(" ");
  Serial.println(i/256);
  i++;
  delay(1000);
} 
