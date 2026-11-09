
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Inicializamos la pantalla LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool juegoIniciado = false; // Bandera de control de inicio
int valorX = 0;
int valorY = 0;

void setup() {
    Serial.begin(9600); // Sincronizamos la UART con el esclavo
    
    lcd.init();         // Inicializamos el LCD
    lcd.backlight();    // Encendemos la retroiluminación
    
    lcd.setCursor(0, 0);
    lcd.print("Esperando Start..");
}

void loop() {
    // Verificamos si hay datos disponibles en el puerto serie
    if (Serial.available() > 0) {
        uint8_t datoRecibido = Serial.read();

        // Verificamos si se presionó el botón de inicio (255)
        if (datoRecibido == 255) {
            juegoIniciado = true;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Juego Iniciado");
        } 
        // Si el juego ya dio inicio, procesamos las coordenadas de los ejes
        else if (juegoIniciado) {
            if (datoRecibido <= 100) {
                valorX = datoRecibido; // Eje X (0-100)
            } else {
                valorY = datoRecibido - 100; // Eje Y normalizado (0-100)
            }

            // Mostramos los valores actuales en la segunda línea del LCD
            lcd.setCursor(0, 1);
            lcd.print("X:");
            lcd.print(valorX);
            lcd.print(" Y:");
            lcd.print(valorY);
            lcd.print("   ");
        }
    }
}