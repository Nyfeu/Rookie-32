//----------------------------------------------------------------------------------
//      Inclusões

#include "Aplic.hpp"

//----------------------------------------------------------------------------------
//      Setup

/**
 * @brief Rotina para inicialização do HW e das tarefas (tasks) do sistema.
 */

void setup() {

    initHW();                // Inicializa o HW (Sensores, comunicação etc.)
    createFreeRTOSTasks();   // Inicializa as tarefas (tasks) do sistema e o WDT.
    
}

//----------------------------------------------------------------------------------
//      Main Loop

/**
 * @brief A loopTask não foi utilizada.
 */

void loop() {}
