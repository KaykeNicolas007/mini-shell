# Mini-Shell

Um interpretador de comandos (shell) simples, escrito em C para Linux, feito como projeto de estudo de **Sistemas Operacionais**. Ele lê o que o usuário digita, separa o comando e seus argumentos e pede ao sistema operacional que execute o programa correspondente.

## Motivação

A ideia de criar este interpretador de comandos surgiu ao ler o capítulo 1 do livro _Sistemas Operacionais Modernos_, do Andrew Stuart Tanenbaum. Com isso, pensei em trazer conceitos como **chamadas de sistema** e **processos** para algo mais prático e próximo da minha realidade. Portanto, utilizei o próprio código de exemplo de um shell em C apresentado pelo Tanenbaum no capítulo 1 e resolvi implementá-lo de fato, entendendo cada etapa.

## Funcionalidades

- Prompt colorido (`mini-shell: `) que aguarda a digitação de um comando
- Execução de qualquer programa do sistema com argumentos (`ls -la`, `pwd`, `cat arquivo`...), usando a variável de ambiente `PATH`
- Execução de programas locais informando o caminho (`./execDemo a b c`)
- Tratamento de linha vazia
- Encerramento com `Ctrl+D` (fim de entrada, EOF)
- Mensagens de erro claras quando o comando não existe ou o `fork()` falha

## Compilação e uso

Requisitos: Linux (ou WSL) e `gcc`.

```bash
gcc mini-shell.c -o mini-shell
./mini-shell
```

Exemplo de sessão, usando o programa auxiliar `execDemo` (veja mais abaixo):

```
mini-shell: ./execDemo a b c
Token: c
Token: b
Token: a
Fim da execução.
mini-shell: ls -la
...
mini-shell: ^D
```

## Funcionamento do `mini-shell.c`

O shell repete, indefinidamente, o ciclo clássico **ler → interpretar → executar**:

```
          ┌──────────────────────────────────────────────┐
          ▼                                              │
   type_prompt() ──► fgets() ──► tokenize() ──► execute() ──► free()
   (mostra prompt)   (lê linha)  (separa em     (fork + execvp
                                  argumentos)    + waitpid)
```

| Etapa       | Função / chamada            | O que acontece                                                                                                           | Conceito de SO                            |
| ----------- | --------------------------- | ------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------- |
| Prompt      | `printf` + `fflush(stdout)` | Mostra o prompt e força a saída imediata, antes de bloquear esperando a entrada                                          | Buffer de saída padrão                    |
| Leitura     | `fgets`                     | Lê a linha inteira (até 1024 caracteres). Retorna `NULL` em EOF, o que encerra o loop                                    | Entrada padrão (`stdin`)                  |
| Tokenização | `strtok` + `malloc`         | Corta a linha nos espaços e guarda o endereço de cada pedaço num vetor dinâmico de até 64 ponteiros, terminado em `NULL` | Formato `argv[]` que todo processo recebe |
| Criação     | `fork()`                    | Duplica o processo: o filho recebe `0` e o pai recebe o PID do filho                                                     | Criação de processos                      |
| Execução    | `execvp()`                  | No filho, substitui a imagem do processo pelo programa pedido, procurando-o no `PATH`                                    | Chamada de sistema `exec`                 |
| Espera      | `waitpid()`                 | O pai fica bloqueado até o filho terminar                                                                                | Sincronização entre pai e filho           |

### Decisões de projeto

- **Buffer fixo de 1024 caracteres:** escolhido pela simplicidade na primeira versão. A leitura dinâmica fica como evolução futura.
- **`strtok` altera a string original:** ele coloca um `'\0'` no lugar de cada separador. Por isso cada token já é uma string válida dentro do próprio buffer, e basta guardar o endereço de onde cada um começa, sem copiar nada.
- **Vetor terminado em `NULL`:** é o formato que o `execvp` exige para saber onde acabam os argumentos.
- **`fork` antes do `execvp`:** como o `execvp` substitui o processo inteiro, chamá-lo direto no shell o destruiria depois do primeiro comando. O filho é quem "se sacrifica".
- **`exit(EXIT_FAILURE)` após o `execvp`:** o `execvp` só retorna quando falha. Sem esse `exit`, o filho (uma cópia do shell) continuaria dentro do loop e passaria a competir com o pai pela entrada do teclado.
- **`free` do vetor de tokens a cada comando**, para evitar vazamento de memória.

## Comandos criados

Alguns comandos foram criados para entender ainda melhor, e de forma mais aprofundada, conteúdos subsequentes do livro.

### `execDemo.c`

Programa auxiliar simples, usado como alvo para testar o shell: ele imprime os argumentos que recebe. Ao ser executado pelo mini-shell, serve de demonstração de como um processo pode ser clonado (com `fork()`) e ter sua imagem de núcleo trocada (com `execvp()`).

```bash
gcc execDemo.c -o execDemo
```

### `copiarArquivos.c`

Uma tentativa de compreender melhor o capítulo 4, **Sistemas de Arquivos**. Utiliza as chamadas de sistema `open`, `read`, `write` e `close`.

```bash
gcc copiarArquivos.c -o copiarArquivos
./copiarArquivos <origem> <destino>
```

## Limitações conhecidas

- Não há comandos internos (_builtins_): `cd` e `exit` ainda não existem. Para sair, use `Ctrl+D`.
- Sem redirecionamento (`>`, `<`), pipes (`|`) e execução em segundo plano (`&`).
- Sem tratamento de sinais: `Ctrl+C` encerra o shell inteiro.
- Sem suporte a aspas: `echo "a b"` é separado em dois argumentos.
- Linhas com mais de 1024 caracteres são truncadas, e o excedente é lido como se fosse o próximo comando.
- O limite de 64 argumentos ainda não é verificado.

## Próximos passos

- [ ] Comandos internos `cd` e `exit` (precisam rodar no processo do shell, e não em um filho, porque um filho não consegue alterar o diretório atual do pai)
- [ ] Comando próprio de listagem de arquivos (com `opendir`, `readdir` e `closedir`)
- [ ] Redirecionamento de entrada e saída (`open` + `dup2`)
- [ ] Execução em segundo plano com `&`
- [ ] Pipes (`pipe` + `dup2` + dois `fork`)
- [ ] Tratamento de sinais (`SIGINT`) para que `Ctrl+C` interrompa só o processo filho
- [ ] Leitura de linha com alocação dinâmica, sem limite fixo

## Estrutura do repositório

```
.
├── mini-shell.c       # o interpretador de comandos
├── execDemo.c         # programa auxiliar para testar fork/execvp
├── copiarArquivos.c   # cópia de arquivos com chamadas de sistema
└── README.md
```

## Referências

- TANENBAUM, A. S.; BOS, H. _Sistemas Operacionais Modernos_. Capítulo 1 (introdução e chamadas de sistema), capítulo 2 (processos) e capítulo 4 (sistemas de arquivos).
