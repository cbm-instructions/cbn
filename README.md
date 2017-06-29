# CBN

## Projekt


## Point of View
> Wie können wir den Studenten helfen, Kontakt zu anderen Fakultäten aufzubauen.

## 1. Material und Werkzeug
### Material für Netzwerkverbindung
* LAN-Kabel
* Switch
* (Alternativ Wi-Fi auf Raspberry-Pi für Netzwerkaufbau)

### Material für jeweils ein Spielgerät
* 1x Raspberry-Pi
* 1x Arduino-Mega
* 1x LCD
* 1x LED-Matrix
* 1x Webcam
* 4x Buttons für Steuerung
* 1x Button für Spielbereit/Spielstarten
* 1x Adapter für die Stromversorgung der Matrix (2A/5V)
* 1x Adapter für die Stromversorgung des Raspberry-Pi
* 1x USB to FireWire (Männlich/Männlich)
* Lötzinn
* 5 Widerstände
* 16GB Micro SD Karte

### Werkzeug
* Holzberarbeitungswerkzeug für das Gehäuse
* Holzleim für das Gehäuse
* Lötkolben
* Schraubendreher

## 2. Arduino-Mega (Labyrinth-Spiel)
### Anschlüsse / Verkabelung

<img src="images/IMG_20170627_120535_451.jpg" width="500">

<img src="images/IMG_20170627_120605_405.jpg" width="500">

<img src="images/IMG_20170627_120628_387.jpg" width="500">

<img src="images/IMG_20170627_120620_243.jpg" width="500">

## Software

1. Die Bibliothek 
[RGB-matrix-Panel](https://drive.google.com/file/d/0B50TDmuMFSKsUUpuMk5kRlZKdFk/view?usp=sharing) und [Adafruit-GFX](https://drive.google.com/file/d/0B50TDmuMFSKsV3NNSXlYT0RGSzA/view?usp=sharing) herunterladen
1. Die [Datei](Matrix-Game/CBM-Matrix-Game.ino) mit Hilfe der Arduino-IDE öffnen
2. Nun auf den Reiter Sketch gehen dort den Unterpunkt Bibliothek einbinden wählen und hier dann .ZIP Bibliothek einbinden auswählen, dies für beide gedownloadeten Zip-Bibliotheken durchführen
3. Nun kann man durch klicken auf den Hochladen Button das Programm auf den Arduino aufspielen
<img src="images/Upload.PNG" width="500">

___
## 3. Matrix
Die Matrix wird wie folgt angeschlossen:
<img src="images/IMG_20170627_123144_122.jpg" width="500">

___
## 4. Raspberry-PI
Alle notwendigen Einstellungen sind im folgenden [Image](https://goo.gl/BdDGMM) enthalten.
Dazu einfach die SD-Karte mit diesem [Image](https://goo.gl/BdDGMM) bespielen.
Hierfür diese Anleitung für [Windows](https://www.raspberrypi.org/documentation/installation/installing-images/windows.md), [Mac OS](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md) und [Linux](https://www.raspberrypi.org/documentation/installation/installing-images/linux.md) benutzen.
Für diese Installation ist es wichtig, dass eine mindestens 16GB große Micro SD-Karte benutzt wird, da sonst das Image nicht aufgespielt werden kann.

### Anschluss
<img src="images/IMG_20170627_123144_122.jpg" width="500">

### Konfiguration

Die Konfiguration erfolgt durch anschließen einer Maus und Tastatur an das Raspberry-PI.
1. Nach dem Start des Gerätes ```ALT+F4``` drücken, um den Browser zu schließen der das Webcambild des anderen PIs anzeigen sollte
2. ```nano /home/pi/restApi.py```
3. In der Datei die IP-Adresse des Partner PIs eintragen
4. ```CTRL+X``` drücken und die Datei speichern
5. ```sudo nano /home/pi/kiosk.sh```
6. Schritt 3. und 4. widerholen
7. Das Raspberry PI neustarten (sudo reboot)

## Ausblick
