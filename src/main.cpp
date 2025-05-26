
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
*/

#include <Arduino.h>
#include "pantalla.h"
#include "potenciometro.h"

int valorPot = 0;

void setup()
{
  Serial.begin(115200);
  delay(100);

  analogReadResolution(10);
  delay(100);

  lcd.init(); // initialize the 16x2 lcd module
  lcd.backlight();

  Pantalla_inicio();

  lcd.clear();
  delay(100);

  ConexionWiFi(); // inicia la comunicacion WiFi

  lcd.clear();
  delay(100);

  // Caracteres fijos Pantalla
  lcd.createChar(7, gauge_empty);  // middle empty gauge
  lcd.createChar(1, gauge_fill_1); // filled gauge - 1 column
  lcd.createChar(2, gauge_fill_2); // filled gauge - 2 columns
  lcd.createChar(3, gauge_fill_3); // filled gauge - 3 columns
  lcd.createChar(4, gauge_fill_4); // filled gauge - 4 columns
  lcd.createChar(0, warning_icon); // warning icon - just because we have one more custom character that we could use
  lcd.backlight();                 // enable backlight for the LCD module
  delay(100);

  // Suabizado Lecturas Potenciómetro
  resposivePot = ResponsiveAnalogRead(PotDensity, true, snapMultipler);
}

void loop()
{
  if (conexion)
  {
    valorPot = Lectura_potenciometro();

    dibujoPantalla(valorPot);
  }
}

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
