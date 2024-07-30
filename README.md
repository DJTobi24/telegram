# So weiß man wenn jemand im Orange ist.

Wir hatten öfters das Problem das man nicht wusste wenn jemand im Orange ist und man vorbeikommen kann. Mit dieser einfachen Lösung muss man nur einen Schalter betätigen und sofort wird eine Telegram Nachricht in die Gruppe gesendet das jemand im Orange ist.

So weiß man direkt wenn man vorbeikommen kann. Natürlich könnte derjenige im Orange ist auch eine Nachricht schicken aber das währe ja zu einfach 😂

## Was du für so einen Button Brauchst:

- Einen ESP32 oder ESP8266 (für dieses Projekt langt ein 8266)
- Ein Button (in unserem fall: [AmazonLINK](https://www.amazon.de/Giovenzana-Grobhandtaster-Pilztaster-IP66-schwarz/dp/B014J65KPK/)
- Ein 5V 1A Ladekabel


## Jetzt können wir mit einem Simplen Code eine Nachricht an Telegram schicken.

Dafür benötigst du einen Telegram Bot und den Bot-Token und die Channel ID, hier die schritte wie du einen Bot erstellst:

1. Zuerst müssen du eine Nachricht "/newbot" an einen Bot namens BotFather unter @botfather schicken. Der Bot wird dardurch erstellt.
2. Jetzt kannst du Namen für den Bot festlegen. So kannst du ihn später leichter zuordnen.
3. Anschließend musst du einen Benutzernamen für den Bot festlegen. Unter diesem wird der Bot zukünftig erreichbar sein. Den Benutzernamen kannst du später nicht mehr ändern, der Anzeigename ist jederzeit anpassbar.
4. Nachdem du den Benutzernamen festgelegt hast, erhalten du einen Token. Diese Kennung sollten Sie sich außerhalb von Telegram notieren und nicht an andere Nutzer weitergeben. Der Token ermöglicht jedem den Zugriff auf deinen Bot.
5. Über "/mybots" kannst du den Bot auswählen. Via "/editbot" kannst du ihn anpassen.


## Wir erstellen jetzt eine Gruppe mit dem Bot der dort dann die Nachricht schickt:

1. Gruppe erstellen
2. Den Telegram-Bot der Gruppe hinzufügen
3. Eine Nachricht in die Gruppe schicken
4. Mit diesem Befehl kannst du nun die Chat ID herausfinden:
```
https://api.telegram.org/botDURCH_DEIN_BOT_TOKEN_ERSETZEN/getUpdates
```
Dadurch erhältst du eine Gruppen-ID die mit "-" anfängt

## Im Nächsten Schritt erstellen wir den Code.
Dafür musst du die Arduino IDE herunterladen.

Ändere einfach deine WLAN-Daten und deine Bot Daten.

hier noch die Pins die du Benötigst
```cpp
int buttonPin = 23; // Der Pin, an dem der Button angeschlossen ist
bool buttonState = HIGH; // Aktueller Status des Buttons, angenommen er ist anfangs nicht gedrückt
int blueLedPin = 16; // Der Pin, an dem die blaue LED angeschlossen (Blinkt wenn die Nachricht gesendet wird)
int greenLedPin = 4; // Füge den Pin für die grüne LED hinzu (Leuchtet wenn die Nachricht gesendet wurde)
int redLedPin = 5;  // Füge den Pin für die rote LED hinzu (Leuchtet wenn es einen Fehler gibt)
```
Hier ein Extra code Stück um mit dem Befehl  `/online ` zu testen ob der ESP Ereichbar ist und auf Telegram nachrichten Reagieren kann:
```cpp
if (text == "/online") {
    String byMessage = "Ich bin da und warte darauf, dass ich gedrückt werde";
    bot.sendMessage(chat_id, byMessage, "");
 }
```
Den weiteren code findest du in diesem Lab, viel spaß mit dem ausprobieren.

Tobi

- [x] Drücken wenn man im Orange ist
- [x] /online befehl um zu überprüfen ob der ESP Online ist
- [ ] Knopf um zu zeigen wenn keiner mehr im Orange ist
