
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
#include <ResponsiveAnalogRead.h>
#include "clip.h"

// Param Potes
#define PotGrain 33

int valPotes = 0;
int valPotes_scale = 0; // escalado para pintar en Pantalla

int readingPot = 0;
int PotCState = 0;
int PotPState = 0;
const char *envioPot[] = {"/PotGrain"};

int potVar = 0;
const int TIMEOUT_POT = 300;
const byte varthresholdPot = 1;
bool potMoving = true;
unsigned long PTimePot = 0;
unsigned long timerPot = 0;

int pot_min = 26;
int pot_max = 360;
///////////////////////////////////////////////

// Resposive analog Read
float snapMultipler = 0.01;
ResponsiveAnalogRead resposivePot;
///////////////////////////

// Lectura Potenciómetro
int Lectura_potenciometro()
{
    readingPot = analogRead(PotGrain);
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
        valPotes_scale = map(PotCState, 26, 360, 0, 100);
        valPotes = PotCState;

        // Serial.print(" Potenciometro: ");
        // Serial.println(PotCState);

        // Serial.println();

        PotPState = PotCState;
    }

    return valPotes_scale;
}
////// FIN LECTURA POTENCIOMETROS /////////