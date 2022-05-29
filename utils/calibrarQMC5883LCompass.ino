/*

SKETCH DE CALIBRAÇÃO
SEM USO FUNCIONAL

*/

#include <QMC5883LCompass.h>

QMC5883LCompass giroscopio;

int dadoCalibracao[3][2];
bool mudou = false;
bool pronto = false;
int t = 0;
int c = 0;

void setup()
{
    Serial.begin(9600);
    giroscopio.init();

    Serial.println("Isso ira calibrar o sensor de QMC5883L");
    Serial.println("Calibração ira começar em 5 segundos.");
    delay(5000);
}

void loop()
{
    int x, y, z;

    // Ler os valores do giroscópio
    giroscopio.read();

    // Retorna os valores de x, y e z
    x = giroscopio.getX();
    y = giroscopio.getY();
    z = giroscopio.getZ();

    mudou = false;

    if (x < dadoCalibracao[0][0])
    {
        dadoCalibracao[0][0] = x;
        mudou = true;
    }
    if (x > dadoCalibracao[0][1])
    {
        dadoCalibracao[0][1] = x;
        mudou = true;
    }

    if (y < dadoCalibracao[1][0])
    {
        dadoCalibracao[1][0] = y;
        mudou = true;
    }
    if (y > dadoCalibracao[1][1])
    {
        dadoCalibracao[1][1] = y;
        mudou = true;
    }

    if (z < dadoCalibracao[2][0])
    {
        dadoCalibracao[2][0] = z;
        mudou = true;
    }
    if (z > dadoCalibracao[2][1])
    {
        dadoCalibracao[2][1] = z;
        mudou = true;
    }

    if (mudou && !pronto)
    {
        Serial.println("Calibrando... Continue a mexer o sensor.");
        c = millis();
    }
    t = millis();

    if ((t - c > 5000) && !pronto)
    {
        pronto = true;
        Serial.println("Pronto. Copie o código abaixo para o seu código.");
        Serial.println();

        Serial.print("giroscopios.setCalibration(");
        Serial.print(dadoCalibracao[0][0]);
        Serial.print(", ");
        Serial.print(dadoCalibracao[0][1]);
        Serial.print(", ");
        Serial.print(dadoCalibracao[1][0]);
        Serial.print(", ");
        Serial.print(dadoCalibracao[1][1]);
        Serial.print(", ");
        Serial.print(dadoCalibracao[2][0]);
        Serial.print(", ");
        Serial.print(dadoCalibracao[2][1]);
        Serial.println(");");
    }
}