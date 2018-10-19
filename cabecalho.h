// Checa se tem algum jogo salvo
int isJogoSalvo();

// Passa um char e checa se eh uma letra
int isLetra(char);

// Conta as letras da palavra sorteada
int contarLetras(char *);

// Deixa o char em maiusculo para uma melhor comparacao
char maiuscula(char);

// Comeca um novo jogo
char* comecaNovo();

// Traduz as letras da palavra para _
char* traduzir_nome(char *);

// Desenha o stickman de acordo com as chances
char* desenhaStickman();


// Salva o progresso da partida
void salvarProgresso();

// Cria o arquivo dos paises e enche ele
void criaArquivoPaises();

// Limpa os ponteiros
void limpaBuffer(char *, int);

// Malloc nas variaveis globais
void startaVariaveis();


// Retorna a palavra traduzida com _
char* getForca();

// Retorna a palavra sorteada
char* getPalavra();

// Retorna os erros
char* getErros();

// Retorna as chances
int getChances();

// Retorna a quantidade de letras na palavra
int getQtdeLetras();

void diminuiChances();
