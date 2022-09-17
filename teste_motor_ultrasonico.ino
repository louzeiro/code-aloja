//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 9
#define pino_echo 4
#define buzina 10
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);


class DCMotor {  
  int spd = 255, pin1, pin2;
  public:  
    void Pinout(int in1, int in2){ // Pinout é o método para a declaração dos pinos que vão controlar o objeto motor
      pin1 = in1;
      pin2 = in2;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      }   
    void Speed(int in1){ // Speed é o método que irá ser responsável por salvar a velocidade de atuação do motor
      spd = in1;
      }     
    void Forward(){ // Forward é o método para fazer o motor girar para frente
      analogWrite(pin1, spd);
      digitalWrite(pin2, LOW);
      }   
    void Backward(){ // Backward é o método para fazer o motor girar para trás
      digitalWrite(pin1, LOW);
      analogWrite(pin2, spd);
      }
    void Stop(){ // Stop é o metodo para fazer o motor ficar parado.
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      }
   };

   DCMotor Motor1, Motor2; // Criação de dois objetos motores, já que usaremos dois motores, e eles já estão prontos para receber os comandos já configurados acima. 

void setup() {
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  Motor1.Pinout(5,6); // Seleção dos pinos que cada motor usará, como descrito na classe.
  Motor2.Pinout(10,11); 
}

void loop() {
  //Le as informacoes do sensor, em cm e pol
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  Serial.println(cmMsec);
  
  while (cmMsec <= 10) {  
    Motor1.Stop(); // Comando para o motor parar
    Motor2.Stop();

    Motor1.Speed(200); // A velocidade do motor pode variar de 0 a 255, onde 255 é a velocidade máxima.
    Motor2.Speed(200); 
    Motor1.Forward(); // Comando para o motor ir para frente
    Motor2.Forward();
    
  }
}
