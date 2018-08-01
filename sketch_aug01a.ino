#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_R 2//LED Vermelho
#define LED_G 3 //LED Verde
char st[20];
 
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
void setup()
{
  // Inicia a serial
  Serial.begin(9600);
  // Inicia  SPI bus 
  SPI.begin();
  // Inicia MFRC522    
  mfrc522.PCD_Init();
  Serial.print("Ready");
  Serial.println("#EOL#");
  pinMode(LED_R, 2);
  pinMode(LED_G, 3);
}
 
void loop()
{
  digitalWrite (LED_G, LOW);
  digitalWrite (LED_R, HIGH);
 
  // Busca novos cartões 
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Seleciona um catão a ser lido
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Mostra ID na serial
  Serial.print("readedTag:");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  } 
  conteudo.toUpperCase();
 
  Serial.print(conteudo.substring(1));
  Serial.println("#EOL#");
    digitalWrite (LED_G, HIGH);
    digitalWrite (LED_R, LOW);
    delay(50);//Delay apagar LED Verde
    digitalWrite (LED_G, LOW);
    digitalWrite (LED_R, HIGH);
  
    
}
