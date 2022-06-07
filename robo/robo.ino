#include <Wire.h>
#include <LiquidCrystal.h>
#include <QMC5883LCompass.h>
#include "caracteres.hpp"

static const bool MotoresAtivados = false;
static const uint8_t SENSORES_LINHA[] = {28, 30, 24, 22, 26};
static const uint8_t MOTORES[] = {8, 9, 10, 11};

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
QMC5883LCompass giroscopio;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    giroscopio.init();
    giroscopio.setCalibration(-603, 702, -1713, 0, -793, 665);

    for (int sensor = 0; sensor < (sizeof(SENSORES_LINHA) / sizeof(SENSORES_LINHA[0])); sensor++)
    {
        pinMode(SENSORES_LINHA[sensor], INPUT);
    }

    for (int motor = 0; motor < (sizeof(MOTORES) / sizeof(MOTORES[0])); motor++)
    {
        pinMode(MOTORES[motor], OUTPUT);
    }

    lcd.begin(16, 2);
    lcd.createChar(1, setaEsquerda);
    lcd.createChar(2, setaDireita);
    lcd.createChar(3, setaFrente);
    lcd.createChar(4, caudaEsquerda);
    lcd.createChar(5, caudaDireita);
    lcd.createChar(6, grausSimbolo);

    lcd.setCursor(0, 0);
    if (!MotoresAtivados)
    {
        lcd.write("Alerta: Motores");
        lcd.setCursor(0, 1);
        lcd.write("desativados!");
        delay(5000);
    }
}

void loop()
{
    giroscopio.read();
    lcd.clear();
    if (!digitalRead(SENSORES_LINHA[0]) && !digitalRead(SENSORES_LINHA[1]) && !digitalRead(SENSORES_LINHA[2]) && !digitalRead(SENSORES_LINHA[3]))
    {
        frente();
    }
    else if (!digitalRead(SENSORES_LINHA[0]) && !digitalRead(SENSORES_LINHA[1]) && !digitalRead(SENSORES_LINHA[4]))
    {
        frente();
    }
    else if (!digitalRead(SENSORES_LINHA[2]) && !digitalRead(SENSORES_LINHA[3]) && !digitalRead(SENSORES_LINHA[4]))
    {
        frente();
    }
    else if (!digitalRead(SENSORES_LINHA[0]) && !digitalRead(SENSORES_LINHA[1]))
    {
        direita90();
    }
    else if (!digitalRead(SENSORES_LINHA[2]) && !digitalRead(SENSORES_LINHA[3]))
    {
        esquerda90();
    }
    else if (!digitalRead(SENSORES_LINHA[0]))
    {
        direita();
    }
    else if (!digitalRead(SENSORES_LINHA[2]))
    {
        esquerda();
    }
    else
    {
        frente();
    }
    delay(100);
}

void frente()
{
    lcd.write((byte)3);
    lcd.setCursor(15, 0);
    lcd.write((byte)3);
    lcd.setCursor(0, 1);
    lcd.write("Indo para frente");
    if (!MotoresAtivados)
        return;
    digitalWrite(MOTORES[0], HIGH);
    digitalWrite(MOTORES[1], LOW);
    digitalWrite(MOTORES[2], HIGH);
    digitalWrite(MOTORES[3], LOW);
    delay(50);
    digitalWrite(MOTORES[0], LOW);
    digitalWrite(MOTORES[1], LOW);
    digitalWrite(MOTORES[2], LOW);
    digitalWrite(MOTORES[3], LOW);
}

void esquerda()
{
    lcd.write((byte)1);
    lcd.write((byte)4);
    lcd.setCursor(7, 0);
    lcd.write("Virando a");
    lcd.setCursor(8, 1);
    lcd.write("esquerda");
    if (!MotoresAtivados)
        return;
    digitalWrite(MOTORES[0], HIGH);
    digitalWrite(MOTORES[1], LOW);
    digitalWrite(MOTORES[2], LOW);
    digitalWrite(MOTORES[3], HIGH);
    delay(100);
    digitalWrite(MOTORES[0], LOW);
    digitalWrite(MOTORES[1], LOW);
    digitalWrite(MOTORES[2], LOW);
    digitalWrite(MOTORES[3], LOW);
}

void direita()
{
    lcd.write("Virando a");
    lcd.setCursor(14, 0);
    lcd.write((byte)5);
    lcd.write((byte)2);
    lcd.setCursor(0, 1);
    lcd.write("direita");
    if (!MotoresAtivados)
        return;
    digitalWrite(MOTORES[0], LOW);
    digitalWrite(MOTORES[1], HIGH);
    digitalWrite(MOTORES[2], HIGH);
    digitalWrite(MOTORES[3], LOW);
    delay(100);
    digitalWrite(MOTORES[0], LOW);
    digitalWrite(MOTORES[1], LOW);
    digitalWrite(MOTORES[2], LOW);
    digitalWrite(MOTORES[3], LOW);
}

void direita90()
{
    lcd.write("Virando a");
    lcd.setCursor(14, 0);
    lcd.write((byte)5);
    lcd.write((byte)2);
    lcd.setCursor(0, 1);
    lcd.write("90");
    lcd.write((byte)6);
    lcd.write("direita");
    delay(2000);
    const int anguloAntes = giroscopio.getAzimuth();
    int anguloTotal = anguloAntes + 90;
    if (anguloTotal > 360)
        anguloTotal -= 360;

    Serial.print("Angulo antes: ");
    Serial.println(anguloAntes);
    Serial.print("Angulo total: ");
    Serial.println(anguloTotal);

    do
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(giroscopio.getAzimuth());
        lcd.write((byte)6);
        lcd.setCursor(0, 1);

        lcd.write("Girando...");

        if (MotoresAtivados)
        {
            digitalWrite(MOTORES[0], HIGH);
            digitalWrite(MOTORES[1], LOW);
            digitalWrite(MOTORES[2], LOW);
            digitalWrite(MOTORES[3], HIGH);
        }

        delay(10);
        giroscopio.read();
    } while (giroscopio.getAzimuth() < anguloTotal);

    if (MotoresAtivados)
    {
        digitalWrite(MOTORES[0], LOW);
        digitalWrite(MOTORES[1], LOW);
        digitalWrite(MOTORES[2], LOW);
        digitalWrite(MOTORES[3], LOW);
    }
}

void esquerda90()
{
    lcd.write((byte)1);
    lcd.write((byte)4);
    lcd.setCursor(7, 0);
    lcd.write("Virando a");
    lcd.setCursor(5, 1);
    lcd.write("90");
    lcd.write((byte)6);
    lcd.write("esquerda");
    delay(2000);
    const int anguloAntes = giroscopio.getAzimuth();
    int anguloTotal = anguloAntes - 90;
    if (anguloTotal < 0)
        anguloTotal += 360;

    Serial.print("Angulo antes: ");
    Serial.println(anguloAntes);
    Serial.print("Angulo total: ");
    Serial.println(anguloTotal);

    do
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(giroscopio.getAzimuth());
        lcd.write((byte)6);
        lcd.setCursor(0, 1);

        lcd.write("Girando...");
        if (MotoresAtivados)
        {
            digitalWrite(MOTORES[0], LOW);
            digitalWrite(MOTORES[1], HIGH);
            digitalWrite(MOTORES[2], HIGH);
            digitalWrite(MOTORES[3], LOW);
        }

        delay(10);
        giroscopio.read();
    } while (giroscopio.getAzimuth() > anguloTotal);

    if (MotoresAtivados)
    {
        digitalWrite(MOTORES[0], LOW);
        digitalWrite(MOTORES[1], LOW);
        digitalWrite(MOTORES[2], LOW);
        digitalWrite(MOTORES[3], LOW);
    }
}