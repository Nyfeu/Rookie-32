# Rookie-32 🪖 [IN PROGRESS]

[![PlatformIO](https://img.shields.io/badge/Platform-ESP32S-00878F?logo=espressif)](https://platformio.org/)
[![FreeRTOS](https://img.shields.io/badge/OS-FreeRTOS-003366?logo=freertos&logoColor=white)](https://www.freertos.org/)
[![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino)](https://www.arduino.cc/)
[![App](https://img.shields.io/badge/App-Flutter-02569B?logo=flutter)](https://flutter.dev)

O Rookie-32 é um robô de esteiras, desenvolvido para explorar ambientes, transmitir imagens via câmera e interagir  com expressões animadas em um display OLED. 
Controlado por um app customizado via Wi-Fi, ele combina diversão e tecnologia.

### Destaques:

🤖 Movimento com esteiras (futuro canhão para "batalhas").
📸 Transmissão de vídeo em tempo real via câmera.
😊 OLED com emojis dinâmicos.
🔊 Buzzer para sons - estilo R2-D2.
📱 App Android/iOS para controle remoto e visualização da câmera.

## Componentes Principais 🛠

Hardware
- Microcontrolador: ESP32-S
- Câmera: OV7670
- Display: OLED 128x64 (I2C)
- Motores: 2x Motores DC com esteiras
- Buzzer: Piezoelétrico
- Fonte: Pack Li-Ion 8.4V recarregável

Software
- Plafatorma: PlatformIO (Arduino Framework)
- Sistema operacional: FreeRTOS

App: desenvolvido em Flutter.

## Como Usar 🎮

Controle pelo App:
- Conecte-se ao robô via Bluetooth/Wi-Fi.
- Use o joystick virtual para movimentação.
- Toque nos botões para ativar sons e mudar emojis.

## Próximos Passos 🚀

- Implementar o modo batalha com controle de um canhão.
- Acionamento do canhão via visão computacional.

