# Projeto com RTOS

## Componentes

- FreeRTOS 4.3.5
- DHT22
- LCD SSD1306
- ESP32 WROOM-32 38 pinos

## Descrição

A ideia é utilizar os componentes para formar um sistema de umidificação inteligente.

O DHT22 é responsável por obter os valores de temperatura e umidade do ambiente.

O LCD é responsável por mostrar informações como:
- Temperatura Atual
- Umidade Atual
- Hora Atual
- Status do Sistema (Ligado/Desligado)

O ESP32 é responsável por controlar o sistema de umidificação,
que consiste em controlar um LED que representa a umidificação.
