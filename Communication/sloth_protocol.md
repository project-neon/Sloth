# Protocolo de configuração do Sloth

## Estrutura base de comandos

Os comandos podem ter basicamente 5 componentes essenciais, listados abaixo

| Length | Command | Status | Payload | CRC|
| ------ | ------  | ------ |   ---   | -- |

- Length: Tamanho do pacote, assim sabemos quantos bytes devemos esperar na serial. É importante considerar que os bytes não chegarão de uma só vez.
- Command: O comando que será recebido e processado
- Status: O status é aplicável à resposta ao comando. É bom ter um ACK pra ter certeza que um comando foi recebido. Mas é dispensável, podemos fazer uma comunicação malha aberta
- Payload: Quando aplicável, o comando poderá possuir um payload, que são dados necessários para o funcionamento do comando (e.g. definição de um valor)
- CRC: Falhas de comunicação acontecem. Esse campo é dispensável a priori, mas talvez a gente precise caso a comunicação esteja muito ruim.

## Lista de comandos

|Comando | OPCODE | Descrição|
| -----  | ------ | ------ |
| Increment | | Incrementa uma variável utilizada no controle (KP, KI, KD, etc) |
| Decrement | | Decrementa a mesma coisa|
| Set | | Define um valor específico para as variáveis utilizadas no controle |
| Full config | | Define um conjunto de valores: kp, ki e kd ao mesmo tempo |
| Start | | Inicia algum ciclo no robô |
| Stop | | Para o que o robô está fazendo |

### Exemplo
Os comandos Increment e Decrement podem possuir o seguinte payload: KP, KI ou KD. Numa "metalinguagem" o comando ficaria algo do tipo (excluindo crc):

Requisição:
|2 | Increment | KP |
| -----  | ------ | ------ |

Resposta:
|2 | Increment | SUCCESS |
| -----  | ------ | ------ |


O comando Set poderia ter um conjunto de argumentos:

Requisição:
|4 | Set | KP Value | KI Value | KD Value |
| -----  | -- | ---- | --- | --- |

Resposta:
|2 | Set | SUCCESS |
| -----  | ------ | ------ |

No caso, tudo que vem depois do SET é o payload do comando.