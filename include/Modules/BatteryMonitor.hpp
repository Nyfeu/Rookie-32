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
        BatteryMonitor(int pin) : adcPin(pin) {
            maxBatteryVoltage = 8.0;   // Tensão máxima padrão
            minBatteryVoltage = 0.0;   // Tensão mínima padrão
        }

        void setMaxBatteryVoltage(float voltage) {
            maxBatteryVoltage = voltage;
        }

        void setMinBatteryVoltage(float voltage) {
            minBatteryVoltage = voltage;
        }
    
        // Ler a tensão real da bateria diretamente do ADC (em volts)
        float readBatteryVoltage() ;

        // Obter o nível de carga em porcentagem
        float getBatteryPercentage();
    
};

#endif /* _BATTERY_MONITOR_HPP */