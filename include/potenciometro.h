
/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Gestión GRAIN DENSITY
"potenciometro.h"
Lectura Potenciometro GAMETRAK
Marrón: 3.3v
verde: GND
Naranja: eje Z
Distancia mínima: 26
Distancia máxima: 360
*/

#include <Arduino.h>
#include <OSCMessage.h>
#include <ResponsiveAnalogRead.h>
#include "clip.h"

// Param Potes
#define PotDensity 35

int valPotes = 0;
int valPotes_scale_grain_du = 0; // escalado para pintar en Pantalla

int readingPot = 0;
int PotCState = 0;
int PotPState = 0;

int potVar = 0;
const int TIMEOUT_POT = 300;
const byte varthresholdPot = 1;
bool potMoving = true;
unsigned long PTimePot = 0;
unsigned long timerPot = 0;

int pot_min = 29;
int pot_max = 360;
///////////////////////////////////////////////

// Resposive analog Read
float snapMultipler = 0.01;
ResponsiveAnalogRead resposivePot;
///////////////////////////

// Lectura Potenciómetro
int Lectura_potenciometro()
{
    readingPot = analogRead(PotDensity);
    resposivePot.update(readingPot);
    PotCState = resposivePot.getValue();

    PotCState = clipValue(PotCState, pot_min, pot_max);

    potVar = abs(PotCState - PotPState);

    if (potVar > varthresholdPot)
    {
        PTimePot = millis();
    }
    timerPot = millis() - PTimePot;

    if (timerPot < TIMEOUT_POT)
    {
        potMoving = true;
    }
    else
    {
        potMoving = false;
    }
    if (potMoving == true)
    {
        valPotes_scale_grain_du = map(PotCState, 29, 360, 0, 100);
        valPotes = PotCState;

        // Envio Mensaje
        OSCMessage grainDu("/PotGrainDen");
        grainDu.add(valPotes_scale_grain_du);
        Udp.beginPacket(outIP, outPort); // 192.168.1.100 : 9999
        grainDu.send(Udp);
        Udp.endPacket();
        grainDu.empty();

        // Serial.print(" Potenciometro: ");
        // Serial.println(PotCState);

        // Serial.println();

        PotPState = PotCState;
    }

    return valPotes_scale_grain_du;
}
////// FIN LECTURA POTENCIOMETROS /////////

/*
  _____           _                         __ _              _____
 / ____|         | |                       / _(_)            / ____|
| |     __ _ _ __| |_ ___   __ _ _ __ __ _| |_ _  __ _ ___  | (___   ___  _ __   ___  _ __ __ _ ___
| |    / _` | '__| __/ _ \ / _` | '__/ _` |  _| |/ _` / __|  \___ \ / _ \| '_ \ / _ \| '__/ _` / __|
| |___| (_| | |  | || (_) | (_| | | | (_| | | | | (_| \__ \  ____) | (_) | | | | (_) | | | (_| \__ \
 \_____\__,_|_|   \__\___/ \__, |_|  \__,_|_| |_|\__,_|___/ |_____/ \___/|_| |_|\___/|_|  \__,_|___/
                            __/ |
                           |___/

 Honorino García Mayo 2025
*/