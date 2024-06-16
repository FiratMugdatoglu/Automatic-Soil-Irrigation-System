#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int rolePin = 2; //Bir röleyi kontrol etmek için kullanılacak dijital pin.
int nemPin = A0; //Bir nem sensörünün analog okuması için kullanılacak pin.

int nemdegeri; //Nem sensöründen okunan değeri tutmak için kullanılan değişken.
int nemEsikdegeri = 15; //Sulama yapılması gereken nem eşik değeri.

LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD adresi ve ekran boyutu

void setup()
{
  // Pin modlarını ayarla
  pinMode(rolePin, OUTPUT); // Sulama kontrol pini,rolePin adlı pine bağlı bir cihazın çıkış olarak kullanılacağını belirtir.
  pinMode(nemPin, INPUT);   // Nem sensörü pin
  Serial.begin(9600);       // Serial iletişim başlat

  // LCD ekranını başlat
  lcd.init();
  // LCD arka ışığını aç
  lcd.backlight();
  // LCD ekranına başlangıç pozisyonunu ayarla
  lcd.setCursor(0, 0);
  // Başlangıç mesajını ekrana yazdır
  lcd.print("Nem:");
}

void loop()
{
  // analogRead(nemPin) ile sensörden okunan analog değer alınır, ardından map fonksiyonu kullanılarak bu değer 0 ile 1023 arasından 0 ile 100 arasına dönüştürülür. 
  nemdegeri = map(analogRead(nemPin), 1023, 0, 0, 100);

  // Önceki nem değerini temizle
  lcd.setCursor(5, 0);
  lcd.print("   ");
  // Nem değerini ekrana yazdır
  lcd.setCursor(5, 0);
  lcd.print(nemdegeri);
  lcd.print("%");

  // Nem değeri nem eşik değerinden büyükse sulamayı kapat
  if (nemdegeri > nemEsikdegeri)
  {
    digitalWrite(rolePin, HIGH);
    // LCD ekranına sulama durumunu yazdır
    lcd.setCursor(0, 1);
    lcd.print("Sulama: KAPALI");
  }
  // Nem değeri nem eşik değerinden küçükse sulamayı aç
  else
  {
    digitalWrite(rolePin, LOW);
    // LCD ekranına sulama durumunu yazdır
    lcd.setCursor(0, 1);
    lcd.print("Sulama: ACIK");
  }

  // LCD ekranını güncellemek için bir süre bekleyin
  delay(500);
}