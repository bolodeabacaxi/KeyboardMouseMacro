# Arduino Macro: Automação de Teclado e Mouse (MMORPG)

Este repositório contém um script para Arduino Leonardo que automatiza a interação com o teclado e o mouse. O código simula pressionamentos de teclas e movimentos do mouse, com controle de tempo e pausas entre as ações. O processo é ativado por um botão físico conectado ao pino 13 do Arduino.


## Funcionalidades

- **Pressionamento de Teclas**: As teclas '1', '2' e '3' são pressionadas em sequência com intervalos aleatórios entre cada pressionamento.
- **Movimento do Mouse**: O mouse se move da direita para a esquerda, com cliques e movimentações programadas.
- **Ativação por Botão**: O código começa a rodar quando um botão conectado ao pino 13 do Arduino Leonardo é pressionado.
- **Controle de Seta Direita**: A seta direita do teclado é pressionada por um tempo determinado, seguida de uma pausa antes de reiniciar o ciclo.

## Como Funciona

1. **Início**: O código começa a rodar quando o botão no pino 13 é pressionado.
2. **Teclas e Mouse**: A cada ciclo, o Arduino simula o pressionamento das teclas '1', '2', '3' e move o mouse conforme programado.
3. **Pausa e Reinício**: O ciclo de ação é interrompido por uma pausa, após o que ele se reinicia.

## Requisitos

- **Placa**: Arduino Leonardo
- **Bibliotecas**: `Keyboard.h` e `Mouse.h`
- **Botão**: Conecte um botão ao pino 13 para iniciar o processo.

## Como Usar

1. Faça o upload do código para o seu Arduino Leonardo.
2. Conecte o botão ao pino 13 (com resistor de pull-down ou pull-up).
3. Ao pressionar o botão, o script começará a simular os pressionamentos de teclas e movimentos de mouse automaticamente.

## Personalização

Você pode ajustar o código para modificar os tempos de espera, as teclas a serem pressionadas e os movimentos do mouse, de acordo com sua necessidade.

## Contribuições

Sinta-se à vontade para enviar pull requests, relatar problemas ou sugerir melhorias!

