void setup(){
  Serial1.begin(9600);
}

void loop(){
  if(Serial1.available()){
    Serial1.print((char)Serial1.read());
  }
}
