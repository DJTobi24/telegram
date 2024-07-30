#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Ersetze mit deinen Netzwerkdaten
const char* ssid = "DEIN_WLAN_NAME";
const char* password = "DEIN_WLAN_PASSWORT";

// Ersetze mit deinen Bot-Daten
const char* token = "DEIN_TOKEN";
const String chatId = "DEINE_CHANNEL_ID";
WiFiClientSecure secured_client;
UniversalTelegramBot bot(token, secured_client);

int buttonPin = 23; // Der Pin, an dem der Button angeschlossen ist
bool buttonState = HIGH; // Aktueller Status des Buttons, angenommen er ist anfangs nicht gedrückt
int blueLedPin = 16; // Der Pin, an dem die blaue LED angeschlossen ist (D2 auf dem ESP32)
int greenLedPin = 4; // Füge den Pin für die grüne LED hinzu
int redLedPin = 5;  // Füge den Pin für die rote LED hinzu
unsigned long lastTimeBotRan;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);

  Serial.begin(115200);
  WiFi.setHostname("DrueckmichbyDJTobi24");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi verbunden");
  secured_client.setInsecure();

  String ipMessage = "Verbunden: \nIP: " + WiFi.localIP().toString() +
                     "\nSSID: " + WiFi.SSID() +
                     "\nSignalstärke: " + String(WiFi.RSSI()) + "dBm";
  bot.sendMessage(chatId, ipMessage, "");

  lastTimeBotRan = millis();
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/online") {
      String response = "Ich bin da und warte darauf, dass ich gedrückt werde";
      bot.sendMessage(chat_id, response, "");
    }
    if (text == "/by") {
      String byMessage = "Dieser Code ist von DJTobi24";
      bot.sendMessage(chat_id, byMessage, "");
    }
  }
}

void loop() {
  if (millis() - lastTimeBotRan > 10000) { // Überprüfe alle 10 Sekunden auf neue Nachrichten
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  bool newButtonState = digitalRead(buttonPin);

  if (newButtonState == LOW && buttonState == HIGH) {
    Serial.println("Button wurde gedrückt. Sende Nachricht...");
    digitalWrite(blueLedPin, HIGH); // Blaue LED blinkt während der Nachrichtensendung

    bool success = bot.sendMessage(chatId, "Es ist jemand im Orange", "");
    digitalWrite(blueLedPin, LOW); // Schalte die blaue LED aus

    if (success) {
      Serial.println("Nachricht erfolgreich gesendet");
      digitalWrite(greenLedPin, HIGH);
      delay(2000);
      digitalWrite(greenLedPin, LOW);
    } else {
      Serial.println("Fehler beim Senden der Nachricht");
      digitalWrite(redLedPin, HIGH);
      delay(3000);
      digitalWrite(redLedPin, LOW);
    }
  }

  buttonState = newButtonState;
  delay(100);
}
