#include<Wire.h>
 
//Endereco I2C do MPU6050
const int MPU=0x68;  

//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
long int xTemp=0, yTemp=0, zTemp=0;
float anguloX, anguloY, anguloZ;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
//  //Inicializa o MPU-6050
//  Wire.write(0); 
//  Wire.endTransmission(true);
//
//  for (int temp=0;temp<100;temp++) {
//    Wire.beginTransmission(MPU);
//    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//    Wire.endTransmission(false);
//    //Solicita os dados do sensor
//    Wire.requestFrom(MPU,14,true);
//    xTemp+=Wire.read()<<8|Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
//    yTemp+=Wire.read()<<8|Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//    zTemp+=Wire.read()<<8|Wire.read(); //0x3F (ACCEL_YOUT_H) & 0x40 (ACCEL_YOUT_L)
//  }
//  xTemp /=100;
//  yTemp /=100;
//  zTemp /=100;
//  Serial.println(xTemp); //275
//  Serial.println(yTemp); //459
//  Serial.println(zTemp); //15622
  //Valores obtidos da calibração
//  xTemp = 275;
//  yTemp = 459;
//  zTemp = 15622;
}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  anguloX = AcX/sqrt(square(AcY)+square(AcZ));
  Serial.print("AnguloX = "); Serial.println(anguloX);
  
//  //Calcula a temperatura em graus Celsius
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);

  delay(10000);
}
