/**
 * @file BluetoothHandler.hpp
 * @brief Definição da classe BluetoothHandler para gerenciar a comunicação Bluetooth.
 */

#ifndef _BLUETOOTH_HANDLER_HPP
#define _BLUETOOTH_HANDLER_HPP

#include <Arduino.h>
#include <BluetoothSerial.h>
#include "Emotion.hpp"
#include "Aplic.hpp"

/**
 * @class BluetoothHandler
 * @brief Gerencia a comunicação Bluetooth, incluindo o tratamento de comandos e callbacks.
 *
 * Esta classe abstrai a complexidade da comunicação Bluetooth 
 * para o ESP32. Ela configura o módulo Bluetooth, gerencia a conexão com clientes,
 * e processa comandos recebidos para controlar o robô, como movimentação, emissão de sons
 * e consulta do nível da bateria. Também permite configurar callbacks para eventos específicos,
 * como a reprodução de sons em resposta a certos comandos.
 */
class BluetoothHandler {

    public:
    
        /**
         * @brief Construtor da classe BluetoothHandler.
         */
        BluetoothHandler();

        /**
         * @brief Inicia a comunicação Bluetooth.
         * @param deviceName O nome do dispositivo Bluetooth a ser anunciado (padrão é "ESP32_BT").
         */
        void begin(const String& deviceName = "ESP32_BT");

        /**
         * @brief Lida com as requisições de clientes Bluetooth pendentes.
         * @details Deve ser chamada periodicamente no loop principal ou em uma tarefa FreeRTOS
         * para processar os dados recebidos via Bluetooth.
         */
        void handleClient();

        /**
         * @brief Define uma função de callback para ser chamada ao receber um comando de som.
         * @param cb Ponteiro para a função de callback que aceita um parâmetro `Emotion`.
         */
        void setSoundCallback(void (*cb)(Emotion)) {
            soundCallback = cb;
        }

    private:

        BluetoothSerial _btSerial;      ///< Instância da classe para o Serial Bluetooth.
        void (*soundCallback)(Emotion); ///< Ponteiro para a função de callback de som.

        /**
         * @brief Lida com comandos de movimentação recebidos via Bluetooth (ex: "/move?x=...&y=...").
         * @param cmd A string do comando recebido.
         */
        void onMoveCommand(const String& cmd);

        /**
         * @brief Lida com comandos de som recebidos via Bluetooth (ex: "/sound?name=...").
         * @param cmd A string do comando recebido.
         */
        void onSoundCommand(const String& cmd);

        /**
         * @brief Lida com comandos desconhecidos recebidos via Bluetooth.
         * @param cmd A string do comando desconhecido.
         */
        void onUnknownCommand(const String& cmd);

        /**
         * @brief Lida com comandos de consulta de bateria recebidos via Bluetooth (ex: "/battery").
         * @details Envia a porcentagem da bateria de volta para o cliente Bluetooth.
         */
        void onBatteryCommand();

        // Funções auxiliares

        /**
         * @brief Extrai o valor de um parâmetro de uma string de consulta.
         * @param input A string de entrada contendo a consulta (ex: "x=10&y=20").
         * @param key A chave do parâmetro a ser extraído (ex: "x" ou "y").
         * @return O valor do parâmetro como um float. Retorna 0.0 se o parâmetro não for encontrado.
         */
        float extractParam(const String& input, const String& key);

        /**
         * @brief Converte uma string que representa uma emoção para o tipo de enumeração `Emotion` correspondente.
         * @param emotionStr A string da emoção (ex: "happiness", "sadness").
         * @return O valor da enumeração `Emotion` correspondente, ou `ERROR` se a string não for reconhecida.
         */
        Emotion getEmotionFromString(const String& emotionStr);

};

#endif /* _BLUETOOTH_HANDLER_HPP */
