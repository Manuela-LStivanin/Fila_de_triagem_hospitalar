# Integrantes:
* Henry Afonso Fiorentin Tres - 208487
* Manuela Larissa Stivanin - 210542

## Trabalho: Simulação de Atendimento hospitalar

Este programa em C++ simula o funcionamento de um serviço de triagem/atendimento com filas por prioridade. Ele permite registrar chegadas de pacientes, realizar atendimentos seguindo a ordem de prioridade, consultar o estado atual das filas e, ao final, gerar um relatório com estatísticas.

### Prioridades

O programa usa 4 filas de prioridade, identificadas por um caractere:

- `V` — Vermelho (mais urgente)
- `A` — Amarelo
- `D` — Verde
- `B` — Branco (menos urgente)

> Observação: o código aceita as letras em maiúsculas ou minúsculas (converte para maiúscula internamente).

O programa roda em modo interativo e apresenta um menu com as opções:

- `C` — Chegada de um paciente (entrada: senha prioridade hora min)
- `A` — Realizar um atendimento (entrada: hora min)
- `D` — Exibir informações sobre o estado atual das filas
- `Q` — Encerrar e mostrar relatório final

### Formato das entradas

- Para `C` (chegada): informe quatro tokens (senha, prioridade, hora e minuto) separados por espaço ou newline. Ex.:

```
100 V 13 05
```

- Para `A` (atendimento): informe hora e minuto do atendimento. Ex.: `14 05`.

### Exemplo de sessão (entrada/saída simplificada)

Entrada (sequência de comandos e dados):

```
C
100 V 13 05
C
101 A 13 10
D
A
14 00
D
Q
```

Saída esperada (resumida):

- Mensagens de menu e confirmação das operações
- Linhas com o estado atual das filas quando `D` for selecionado, no formato:

```
V:<tamanhoV> A:<tamanhoA> D:<tamanhoD> B:<tamanhoB> | Atendidos: <total>
```

- Ao encerrar com `Q`, é exibido o relatório final com:
  - Total atendidos
  - Total por prioridade (V, A, D, B)
  - Pico de lotação (maior soma de filas observada)
  - Espera máxima em minutos

### Mensagens especiais

- Se um atendimento (`A`) for solicitado e não houver pacientes, o programa imprime o horário do atendimento seguido de "Sem pacientes aguardando atendimento." (com minuto formatado com dois dígitos quando necessário).


Se quiser, eu posso:

- adicionar exemplos de arquivos de entrada usados para testes automatizados;
- criar um script PowerShell `build.ps1` para compilar automaticamente;
- ou compilar o programa aqui para verificar se gera warnings/erros.
