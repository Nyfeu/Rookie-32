# Rookie-32 🪖

![Espressif](https://img.shields.io/badge/espressif-E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white)
[![FreeRTOS](https://img.shields.io/badge/FreeRTOS-7DC847?style=for-the-badge)](https://www.freertos.org/)
![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Flutter](https://img.shields.io/badge/Flutter-%2302569B.svg?style=for-the-badge&logo=Flutter&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-%23222.svg?style=for-the-badge&logo=platformio&logoColor=%23f5822a)

## Integrantes do Grupo 

| Nome | R.A. |
| ---- | ---- |
| André Solano F. R. Maiolini | 19.02012-0 |
| Durval Consorti Soranz de Barros Santos | 22.01097-0 |
| Leonardo Roberto Amadio | 22.01300-8 |

## Apresentação do Projeto

O Rookie-32 consiste em um carrinho robótico controlado remotamente via Bluetooth, utilizando um aplicativo móvel para navegação e interação. O Rookie-32 conta com motores controlados por pontes H e esteiras, garantindo mobilidade eficiente. Para evitar colisões, um sensor ultrassônico (HC-SR04) detecta obstáculos no caminho.

Além disso, o sistema emite alertas sonoros através de um buzzer de 3.3V, seja para informar eventos importantes durante a navegação, quanto para dar ao sistema uma personalidade amigável. A interface visual do carrinho inclui um display OLED, que exibe animações de olhos que mudam a cada requisição, tornando a interação mais dinâmica. O sistema também pode capturar imagens utilizando um segundo microcontrolador (ESP32-CAM), ampliando as possibilidades de monitoramento e visão remota.

Para garantir o funcionamento adequado dos componentes eletrônicos, o sistema emprega um circuito de alimentação (com LM7805) para ajustar os níveis de sinal entre os módulos. O nível de bateria pode ser monitorado e exibido no display OLED e no aplicativo móvel, permitindo ao usuário acompanhar o tempo de operação do carrinho.

O ESP32S NodeMCU ESP-12 é responsável pelo processamento das informações e comunicação via Bluetooth. O design do sistema prioriza modularidade, permitindo futuras expansões e aprimoramentos na funcionalidade do carrinho.

### Destaques:

- 🤖 Movimento com esteiras
- 📸 Transmissão de vídeo em tempo real via câmera Wi-Fi
- 😊 OLED com emojis dinâmicos
- 🔊 Buzzer para sons - estilo R2-D2.
- 📱 App Android/iOS para controle remoto e visualização da câmera

## Requisitos do Sistema 📝

| ID | Requisito | Tipo |
| --- | --- | --- |
| UR-01 | O sistema deve utilizar um regulador de tensão para garantir alimentação estável dos componentes. | Obrigatório |
| UR-02 | O Rookie-32 deve ser controlado remotamente via aplicativo móvel por Bluetooth. | Obrigatório |
| UR-03 | O controle dos motores deve ser feito através das pontes H, que são controladas pelo GPIOs do ESP32S NodeMCU ESP-12. | Obrigatório |
| UR-04 | O sistema deve possuir verificação do nível de bateria via ADC e transmitido para o aplicativo. | Obrigatório |
| UR-05 | O sistema deve possuir um sensor ultrassônico (HC-SR04) para evitar colisões. | Obrigatório |
| UR-06 | O carrinho deve emitir efeitos sonoros através de um buzzer de 3.3V. | Obrigatório |
| UR-07 | O sistema deve ser capaz de realizar a captura de imagens via ESP32-CAM via Wi-Fi.. | Desejável |
| UR-08 | O sistema deve minimizar a quantidade de pinos utilizados para posterior atualização. | Desejável |
| UR-09 | O sistema deve exibir animações de olhos no carrinho, mudando a cada requisição, utilizando displays OLED. | Desejável |
| UR-10 | O sistema deve possuir verificação direta pelo do nível de bateria por meio de display físico. | Desejável |
| UR-11 | Alcance do streaming de vídeo capturado. | Desejável |

## Componentes Principais 🛠

Hardware
- Microcontrolador: ESP32S NodeMCU ESP-12 e ESP32-CAM
- Display: OLED 128x64 (I2C)
- Motores: 2x Motores DC com esteiras
- Buzzer: Piezoelétrico
- Fonte: Pack Li-Ion 8.4V recarregável
- Sensor de Proximidade: HC-SR04

Software
- Plafatorma: PlatformIO (Arduino Framework)
- Sistema operacional de tempo real (RTOS): FreeRTOS

App: desenvolvido em linguagem Dart (framework Flutter).

## Diagrama de Blocos 🧊

![Diagrama de blocos feito via draw.io](./diagrama%20de%20blocos.png)

## Como Usar 🎮

Controle pelo App:
- Conecte-se ao robô via Bluetooth/Wi-Fi utilizando o aplicativo móvel 📲.
- Use o joystick virtual para movimentação 🕹️.
- Toque nos botões para ativar sons e mudar emojis 👀.
- Ligue/desligue a lanterna utilizando o botão toggle 🔦.

## Custos do Protótipo 💵

| Componente                 | Preço    | 
| -------------------------- | -------- |
| Ponte H L298n              | R$ 17,96 |
| Sensor HC-Sr04             | R$ 17,00 |
| ESP32S NodeMcu ESP-12      | R$ 47,40 |
| ESP32-CAM                  | R$ 59,90 |
| Buzzer 5V                  | R$ 2,48  |
| Motor DC 3-6V TTL (2x)     | R$ 15,00 |
| Display OLED 0.96"         | R$ 27,80 |
| Regulador de Tensão LM7805 | R$ 2,50  |
| Módulo Display de Bateria  | R$ 10,00 |
| Pack Bateria Li-Íon (8.4V) | R$ 40,00 |
| Filamento ABS (1 kg)       | R$ 67,26 |
| **Total**                  | **R$ 307,24** |

## Documentação do Código com Doxygen 📄

Para garantir a clareza e facilitar a manutenção e futuras colaborações no projeto Rookie-32, toda a base de código foi documentada utilizando o Doxygen. O Doxygen é uma ferramenta padrão de fato para gerar documentação a partir de código-fonte documentado.

### Como funciona:

- Comentários Estruturados: O código será anotado com comentários especiais formatados para o Doxygen, descrevendo funções, variáveis, estruturas e módulos.
- Geração Automática: A partir desses comentários, o Doxygen pode gerar documentação em diversos formatos, como HTML, LaTeX, RTF, XML e man pages.

Para visualizar a documentação completa, basta acessar `docs/html/index.html`

---

