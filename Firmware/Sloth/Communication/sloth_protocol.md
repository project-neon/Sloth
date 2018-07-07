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

|Comando | OPCODE | TAG| Descrição|
| -----  | ------ | ------ | --- |
| Increment | 0x21 | SLOTH_OPCODE_INC | Incrementa uma variável utilizada no controle (KP, KI, KD, etc) |
| Decrement | 0x22 | SLOTH_OPCODE_DEC | Decrementa a mesma coisa|
| Set | 0x23 | SLOTH_OPCODE_SET | Define um valor específico para as variáveis utilizadas no controle |
| Full config | 0x24 | SLOTH_OPCODE_CONFIG | Define um conjunto de valores: kp, ki e kd ao mesmo tempo |
| Start | 0x25 | SLOTH_OPCODE_START | Inicia algum ciclo no robô |
| Stop | 0x26 | SLOTH_OPCODE_STOP | Para o que o robô está fazendo |
| Save | 0x27 | SLOTH_OPCODE_SAVE | Salva os parâmetros do PID na EEPROM |

## Definições de Payloads

### Sloth Control Var

Os comandos: Increment, Decrement e Set possuem um payload determinado "variable", uma estrutura de dados que possui um código pra variável e um valor, que define qual variável ele irá modificar. Atualmente, há uma lista com as seguintes variáveis identificadas na lista a seguir:

| Variável | Código | Tag |
| -------  |  ----- | --- |
| KP 	| 0x21 | SLOT_VAR_KP |
| KI 	| 0x22 | SLOT_VAR_KI |
| KD 	| 0x23 | SLOT_VAR_KD |

Exemplos de comandos codificados

| Comando | Byte array | obs|
| ----    | ---- | -- |
| Inc KP | 0x02 0x21 0x21 | Observe que o campo "value" não é preenchido/transmitido |
| Dec KP | 0x02 0x22 0x21 | Observe que o campo "value" não é preenchido/transmitido |
| Dec KD | 0x02 0x22 0x23 | Observe que o campo "value" não é preenchido/transmitido |
| Set KI | 0x06 0x23 0x22 0x00 0x00 0x25 0x31 | Depois temos que ver como fica o endian disso aqui! |
| Set KD | 0x06 0x23 0x23 0x00 0x00 0x02 0x15 | Depois temos que ver como fica o endian disso aqui! |

### Config

O comando de configuração receve uma estrutura de dados do tipo "slot_config_t" que possui valores definidos para kp, ki e kd.

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