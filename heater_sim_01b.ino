float Qrad(float Tc)
{
   // s="""
   // at square meter, radiative heat transfer Watt/m2
   // """
   float Stefan_Boltzmann_coeff=5.67;
   float TempK=Tc+273.15;
   float Watt_per_m2 = Stefan_Boltzmann_coeff*pow(TempK/100.0,4);
   return Watt_per_m2;
}

float Stephan(float Tc) {
   float dia=2.54E-2;
   float ring=3.14*dia;
   float L=2E-1; // #m to cm, lengthg of the pipe
   float area=L*ring;
//   print("area of radiation_cooling(m2)=",f'{area:.4f}')
   float S=area*Qrad(Tc);
//   print("Watt of radiation",f'{S:.4f}')
   return S;
}

float Heat_Capasity_RodBody()
   {
   float Volume_in_cm=20*4;
   float Veff=0.1*Volume_in_cm;
   float Weight_in_gram=1.5*Veff;
   float Effective_Cp=4.2*Weight_in_gram;
//   print("Heat_Capasity_RodBody",f'{rouCp_eff:.4f}')
   return Effective_Cp;
   }


byte incomingByte; // for incoming serial data
int dec;

float dt,Troom_c=20,K1,K2=1E-2,Tc,Q,Heat_Capasity;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  dt=10;
  Troom_c=20;
  K1=1;
  K2=1E-2;
  Tc=Troom_c;
  Heat_Capasity=Heat_Capasity_RodBody();
  Q=Heat_Capasity*(Troom_c+273.0);
 }

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    dec =(int)incomingByte;
//    Serial.println(dec);
   
    float Win;
    for(int i =1; i<=50; i++)
    {
      Win=dec;
      float Wout=K1*Stephan(Tc)+K2*(Tc-Troom_c);
      Q +=(Win - Wout)*dt;
      Tc=Q/Heat_Capasity-273.0;
    }
  //print(Tc)
   Serial.println(Tc);
   // say what you got:
    //analogWrite(9,dec);
  }
}
