/**
 * @file MotorController.hpp
 * @brief Definição da classe MotorController para controlar motores DC.
 */

#ifndef _MOTOR_CONTROLLER_HPP
#define _MOTOR_CONTROLLER_HPP

#include <Arduino.h>
#include "Aplic.hpp"

/**
 * @class MotorController
 * @brief Gerencia o controle de dois motores DC conectados via uma ponte H.
 *
 * Esta classe permite controlar a movimentação de um robô ou veículo
 * com dois motores (esquerdo e direito) conectados a pinos GPIO específicos.
 * Ela oferece métodos para mover para frente, para trás, virar e parar,
 * além de uma função para lidar com comandos de joystick (x, y).
 */
class MotorController {
private:

  int in1A, in2A, in1B, in2B;   ///< Pinos GPIO para controle da ponte H dos motores.
  const float DEAD_ZONE = 0.2;  ///< Zona morta para comandos de joystick, para evitar movimentos acidentais.

  /**
   * @brief Move ambos os motores para que o robô se mova para frente.
   * @details Define os estados dos pinos da ponte H para movimentação para frente.
   */
  void moverFrente();

  /**
   * @brief Move ambos os motores para que o robô se mova para trás.
   * @details Define os estados dos pinos da ponte H para movimentação para trás.
   */
  void moverTras();

  /**
   * @brief Move os motores para que o robô vire para a esquerda.
   * @details Define os estados dos pinos da ponte H para virar à esquerda.
   */
  void virarEsquerda();

  /**
   * @brief Move os motores para que o robô vire para a direita.
   * @details Define os estados dos pinos da ponte H para virar à direita.
   */
  void virarDireita();

public:

  /**
   * @brief Construtor da classe MotorController.
   * @param _in1A Pino de controle IN1 para o motor A.
   * @param _in2A Pino de controle IN2 para o motor A.
   * @param _in1B Pino de controle IN1 para o motor B.
   * @param _in2B Pino de controle IN2 para o motor B.
   */
  MotorController(int _in1A, int _in2A, int _in1B, int _in2B);

  /**
   * @brief Para todos os motores, definindo todos os pinos de controle para LOW.
   */
  void pararTodos();

  /**
   * @brief Inicializa os pinos GPIO como OUTPUT e define o estado inicial como LOW (parado).
   * @details Deve ser chamado no setup() do Arduino.
   */
  void begin();

  /**
   * @brief Lida com os comandos de movimentação baseados em valores X e Y (joystick-like).
   * @details Interpreta os valores X e Y para determinar a direção do movimento (frente, trás, esquerda, direita)
   * e chama a função de movimentação correspondente. Possui uma zona morta (`DEAD_ZONE`) para evitar movimentos indesejados.
   * @param x Valor do eixo X (horizontal) do comando de movimentação.
   * @param y Valor do eixo Y (vertical) do comando de movimentação.
   */
  void handle(float x, float y);

};

#endif /* _MOTOR_CONTROLLER_HPP */
