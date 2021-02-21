int pin=2;
char current;
int button;
char prev;
int a=250;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //for(int i=0; i<255; i++){
    button=digitalRead(pin);
    nilai();
    Serial.println(a);
    if(current==prev){
      Serial.println("NILAI SAMA");
 //     break;
    }
    else if(current!=prev){
      Serial.println("Different State");
      konfersi();
      prev=current;
    }
    else{}
 //}
}
void nilai(){
  if (button==1){
    current='A';
    Serial.println("HIGH");
    Serial.println(current);
  }
  else if(button==0){
    current='B';
    Serial.println("LOW");
    Serial.println(current);
  }
  else{}
}
void konfersi(){
  if(current=='A'){
   a++; 
  }
  else if(current=='B'){
   a--;
  }
  else{}
}
