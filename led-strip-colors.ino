#include <IRremote.h>

#define music 0xFF4AB5			//0 on remote
#define redLight 0xFF6897		//1 on remote
#define greenLight 0xFF9867		//2 on remote
#define blueLight 0xFFB04F		//3 on remote
#define orangeLight 0xFF30CF	//4 on remote
#define cyanLight 0xFF18E7		//5 on remote
#define fuschiaLight 0xFF7A85	//6 on remote
#define whiteLight 0xFF10EF		//7 on remote
#define hexLight 0xFF38C7		//8 on remote
#define standby 0xFF5AA5		//9 on remote
#define futureUse1 0xFF42BD		//star on remote
#define futureUse2 0xFF52AD		//# on remote

#define mic A0
#define Red 6     
#define Green 5
#define Blue 9

int sound;
int sound1;
int RECV_PIN = 11;
int test = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup(){           	//Initialize Pins
	irrecv.enableIRIn();	//Start IR receiver
	pinMode(mic, INPUT);
	pinMode(Red, OUTPUT);
	pinMode(Green, OUTPUT);
	pinMode(Blue, OUTPUT);
}

void loop(){
	
	if(irrecv.decode(&results)){
		
		irrecv.resume();	//Receive next value from Remote Control
		
		switch(results.value){

			case music: //LEDs react according to volume of any sound
				while(results.value == 0xFF4AB5){
					if(irrecv.decode(&results)){
							irrecv.resume();
					}            
					sound = analogRead(mic);    
					if(sound > 520){
						sound1 = map(sound,520,750,0,255);
					}
 
					if(sound1 > 105){
						analogWrite(Red,sound1+25);  
						analogWrite(Green,sound1+25);
						analogWrite(Blue,sound1+25);
					}  
					else if(sound1 > 65){
						analogWrite(Red,sound1+25);  
						analogWrite(Green,sound1+25);
						digitalWrite(Blue,LOW); 
					}
					else if(sound1 > 45){
						analogWrite(Red,sound1+25);   
						digitalWrite(Green,LOW);
						digitalWrite(Blue,LOW);     
					}
					else if(sound1 > 25){
						analogWrite(Red,sound1+25);  
						digitalWrite(Green,LOW);   
						analogWrite(Blue,sound1+25);
					}
					else if(sound1 > 15){
						digitalWrite(Red,LOW);   
						digitalWrite(Green,LOW);  
						analogWrite(Blue,sound1+25);             
					}
					else{
						digitalWrite(Red,LOW);   
						digitalWrite(Green,LOW);   
						digitalWrite(Blue,LOW);  
					}
					delay(10);
				}
			break; 

			case redLight:
				digitalWrite(Red,HIGH);   
				digitalWrite(Green,LOW); 
				digitalWrite(Blue,LOW);
			break;

			case greenLight:
				digitalWrite(Red,LOW);   
				digitalWrite(Green,HIGH);  
				digitalWrite(Blue,LOW);
			break;

			case blueLight:
				digitalWrite(Red,LOW);   
				digitalWrite(Green,LOW); 
				digitalWrite(Blue,HIGH);
			break; 

			case fuschiaLight:
				analogWrite(Red,255);   
				analogWrite(Green,0); 
				analogWrite(Blue,200);
			break;

			case cyanLight:
				analogWrite(Red,0);   
				analogWrite(Green,255); 
				analogWrite(Blue,220);
			break;

			case orangeLight:
				analogWrite(Red,255);   
				analogWrite(Green,165); 
				analogWrite(Blue,0);
			break;

			case whiteLight:
				analogWrite(Red,255);   
				analogWrite(Green,255); 
				analogWrite(Blue,255);
			break;

			case hexLight:
				analogWrite(Red,85);   
				analogWrite(Green,0); 
				analogWrite(Blue,255);
			break;

			case standby:
				digitalWrite(Red,LOW);   
				digitalWrite(Green,LOW); 
				digitalWrite(Blue,LOW);
			break;

		}
    }
}
