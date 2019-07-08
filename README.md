# Projeto-Final_Microcontroladores
Projeto envolvendo os conhecimentos adquiridos na disciplina de microntroladores 2019/1.
O projeto consiste em utilizar um ATMega328p para ler um sensor e controlar um atuador via web usando um módulo Wi-Fi.

Os seguintes componentes foram utilizados:
-Módulo Wi-fi, ESP01.
-Sensor, RTC DS1302.
-Atuador, motor DC.

##ESP01
O ESP01 é um módulo wi-fi que usa um esp8266 para fazer a conexão com a internet.
Neste projeto utilizou-se o protocolo MQTT para comunicação do módulo com a internet e do ATMega com o módulo o  protocolo Modbus.
Como o ESP tem tensão de alimentação de 3,3 V é necessário atenção nas conexões com o ATMega328p que usa 5 V.

##RTC DS1302
O DS1302 é um RTC(Real Time Clock) que usa como padrão de comunicação três fios, um de clock, um de enable e um de dados(envio e recebimento).
O firmware foi feito em duas etapas:
-Uma construindo um código de uma comunicação de três fios onde ele faz a conversão dos dados para serial e lê dados seriais de uma entrada.
-Depois seguindo o padrão de transferência de dados descrito pelo [datasheet do fabricante do DS1302](https://datasheets.maximintegrated.com/en/ds/DS1302.pdf)
montou-se funções para escrita e leitura dos dados.

##Motor DC(Ventoinha de PC)
O motor é controlador por um PWM variável de 0 a 100% gerado pelo ATMega328p.
Como um simples PWM não é o suficiente para o acionamento do motor fez-se um driver de corrente com um transistor BD139.
