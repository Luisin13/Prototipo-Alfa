#include <Wire.h>

void setup()
{
    Serial.begin(9600);
    Wire.begin();
}

void loop()
{
    byte error, address;
    int nDevices;

    Serial.println("Procurando dispositivos...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Dispositivo I2C encontrado na endereço 0x");

            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Erro desconhecido na endereço 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("Nenhum dispositivo I2C encontrado.\n");
    else
        Serial.println("Concluído.\n");

    delay(5000);
}