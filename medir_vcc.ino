
#define Vccinput A0
#define Vmax 9.0  // Bateria de 9 Volt, da 9.6 Volt nueva
#define Vdiv 4.5 // Valor del divisor de voltaje, 4.5 corresponte a un divisor con R1=R2=10k
                 // Vout = Vin * (R2/(R1 + R2))
void setup() {
  Serial.begin(9600);

}

void loop() {

  float Vcc = readVcc() / 1000.0;
  float voltage = (analogRead(Vccinput) / 1024.0) * Vcc;
 
  Serial.print("V=");
  Serial.print(calcBatteryLevel(voltage));
  Serial.println(" volt");

  delay(3000);
}


long readVcc() {
   ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
   delay(2);
   ADCSRA |= _BV(ADSC);
   while (bit_is_set(ADCSRA, ADSC));
   
   long result = ADCL;
   result |= ADCH << 8;
   // 1126400L = 1.1 x 1024 x 1000, 1.1 V Referencia de Arduino
   result = 1126400L / result; // Back-calculate AVcc in mV
   return result;
}

float calcBatteryLevel(float Voltage) {
  return Voltage*Vmax/Vdiv;
}
