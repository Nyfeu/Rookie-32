/**
 * @file BatteryMonitor.hpp
 * @brief Definição da classe BatteryMonitor para monitoramento de bateria.
 */

#ifndef _BATTERY_MONITOR_HPP
#define _BATTERY_MONITOR_HPP

#include "Arduino.h"

/**
 * @class BatteryMonitor
 * @brief Gerencia a leitura e cálculo do nível de carga da bateria.
 *
 * Esta classe fornece funcionalidades para interagir com um pino ADC
 * para ler a tensão da bateria e converter essa leitura em uma porcentagem
 * de carga, com base em tensões mínima e máxima configuráveis.
 */

class BatteryMonitor {
    private:

        int adcPin;                    ///< Pino ADC conectado ao divisor de tensão da bateria
        float maxBatteryVoltage;       ///< Tensão máxima esperada da bateria (100% de carga) [V]
        float minBatteryVoltage;       ///< Tensão mínima esperada da bateria (0% de carga) [V]
    
    public:
    
        /**
         * @brief Construtor da classe BatteryMonitor.
         * @param pin O número do pino ADC ao qual o divisor de tensão da bateria está conectado.
         */
        BatteryMonitor(int pin) : adcPin(pin) {
            maxBatteryVoltage = 8.0;   // Tensão máxima padrão
            minBatteryVoltage = 0.0;   // Tensão mínima padrão
        }

        /**
         * @brief Define a tensão máxima da bateria para o cálculo da porcentagem.
         * @param voltage A tensão máxima em Volts que corresponde a 100% de carga.
         */
        void setMaxBatteryVoltage(float voltage) {
            maxBatteryVoltage = voltage;
        }

        /**
         * @brief Define a tensão mínima da bateria para o cálculo da porcentagem.
         * @param voltage A tensão mínima em Volts que corresponde a 0% de carga.
         */
        void setMinBatteryVoltage(float voltage) {
            minBatteryVoltage = voltage;
        }
    
        /**
         * @brief Lê a tensão real da bateria diretamente do ADC e a retorna em Volts.
         * @return A tensão da bateria em Volts.
         */
        float readBatteryVoltage() ;

        /**
         * @brief Calcula e retorna o nível de carga da bateria em porcentagem.
         * @details O cálculo é baseado na tensão lida do ADC e nas tensões mínima e máxima configuradas.
         * A função garante que a porcentagem fique entre 0% e 100%.
         * @return O nível de carga da bateria em porcentagem (0.0 a 100.0).
         */
        float getBatteryPercentage();
    
};

#endif /* _BATTERY_MONITOR_HPP */