#include "Modules/BatteryMonitor.hpp"

float BatteryMonitor::readBatteryVoltage() {
    int millivolts = analogReadMilliVolts(adcPin); // Retorna milivolts
    return millivolts / 1000.0;                    // Converter para volts
}

float BatteryMonitor::getBatteryPercentage() {

    float voltage = readBatteryVoltage();

    if (voltage > maxBatteryVoltage) voltage = maxBatteryVoltage;       // Limitar a tensão máxima
    else if (voltage < minBatteryVoltage) voltage = minBatteryVoltage; // Limitar a tensão mínima

    return ((voltage - minBatteryVoltage) / (maxBatteryVoltage - minBatteryVoltage)) * 100.0;

}