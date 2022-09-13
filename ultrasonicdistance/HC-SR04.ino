#define echoPin 10 // echo için pin numarası tanımlıyoruz.
#define trigPin 9 // trigger için pin numarası tanımlıyoruz.
#define pwm1 11  // motor sürücü bağlantıları belli ediliyor
#define pwm2 12 // diğer motor sürücü bağlantı noktası


int kirmizi=2; // ledlerin bağlandığı pinler
int sari=3;
int yesil=4;
long sure,uzaklik; // uzaklik ve süre değişkenleri tanımlanıyor 

void setup() {
pinMode(trigPin,OUTPUT); // trigger'ı sensörün çıkışı seçiyoruz.
pinMode(echoPin,INPUT);  // echo'yu sensörün girişi seçiyoruz.
pinMode(pwm1,OUTPUT); // motorun dönmesi için output verdik
pinMode(pwm2,OUTPUT);

pinMode(kirmizi,OUTPUT);  // Ledlerin yanması için output belirledik
pinMode(yesil,OUTPUT);
pinMode(sari,OUTPUT);
Serial.begin(9600);
}

void loop() {
 digitalWrite(trigPin,LOW); //İlk başta kapalı tutuyoruz.
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH); //Sinyal gelmesi için High yapıyoruz ve bekliyoruz
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW); //Sinyali ürettik sinyal üretimini kesmek için low yapıyoruz.

sure=pulseIn(echoPin,HIGH); //echoPin'e sinyal üretilip gelene kadar geçen süreyi hesaplaması için pulseIn komutu kullanıldı.
uzaklik= (sure/2)/29.1; // x=vt formülü kullanilarak süre uzaklığa dönüştürülüyor.


Serial.print("Mesafe:");
Serial.print(uzaklik);
Serial.println(" CM");

if(uzaklik<=450){
  digitalWrite(kirmizi,LOW); //Mesafe 450'den azsa diğerlerini kapatıp kırmızıyı yakıyoruz
  digitalWrite(yesil,LOW);
  digitalWrite(sari,LOW);
  digitalWrite(kirmizi,HIGH);
  
  digitalWrite(pwm1,LOW); // Dönüş yönünü belirlemek için bağlantı noktalarını bir açık bir kapalı yapıyoruz
  digitalWrite(pwm2,HIGH);

}
else if(uzaklik>450 && uzaklik<=550){
  digitalWrite(kirmizi,LOW);  // Mesafe 450 ve 550 arasıysa diğer ledleri low yapıp sarı'yı yakıyoruz. 
  digitalWrite(sari,LOW);
  digitalWrite(yesil,LOW);
  digitalWrite(sari,HIGH);
 
  digitalWrite(pwm1,LOW);  // Motorun dönmemesi için 2 kısmı da low yapıyoruz
  digitalWrite(pwm2,LOW);
}
else{ // 550 ve üstü için else komutunu kullanabiliyorum.
  digitalWrite(kirmizi,LOW); //Mesafe 550'den fazlaysa  diğerlerini low yapıp Yeşil'i yakıyoruz.
  digitalWrite(yesil,LOW);
  digitalWrite(sari,LOW);
  digitalWrite(yesil,HIGH);
  
  digitalWrite(pwm1,HIGH);  // Dönüş yönü için 2 pwm'i birbirine zıt yapıyoruz.
  digitalWrite(pwm2,LOW);
}
delay(50);
}
