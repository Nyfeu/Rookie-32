#ifndef _BATTERY_MONITOR_HPP
#define _BATTERY_MONITOR_HPP

#include "Arduino.h"

class BatteryMonitor {
    private:

        int adcPin;
        float maxBatteryVoltage;       // Tensão máxima esperada (ex: 8.0V)
        float minBatteryVoltage;       // Tensão mínima esperada (ex: 0.0V)
    
    public:
    
        // Construtor
        BatteryMonitor(int pin) {
            adcPin = pin;
        }

        void setMaxBatteryVoltage(float voltage) {
            maxBatteryVoltage = voltage;
        }

        void setMinBatteryVoltage(float voltage) {
            minBatteryVoltage = voltage;
        }
    
        // Ler a tensão real da bateria diretamente do ADC (em volts)
        float readBatteryVoltage() {
            int millivolts = analogReadMilliVolts(adcPin); // Retorna milivolts
            return millivolts / 1000.0;                    // Converter para volts
        }

        // Obter o nível de carga em porcentagem
        float getBatteryPercentage() {

            float voltage = readBatteryVoltage();

            if (voltage > maxBatteryVoltage) voltage = maxBatteryVoltage;      // Limitar a tensão máxima
            else if (voltage < minBatteryVoltage) voltage = minBatteryVoltage; // Limitar a tensão mínima

            return ((voltage - minBatteryVoltage) / (maxBatteryVoltage - minBatteryVoltage)) * 100.0;

        }
    
};

#endif /* _BATTERY_MONITOR_HPP */