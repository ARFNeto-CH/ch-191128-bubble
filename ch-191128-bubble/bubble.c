#define			_CRT_SECURE_NO_WARNINGS

#define		_preto_            0
#define		_azul_             1
#define		_verde_            2
#define		_ciano_            3
#define		_vermelho_         4
#define		_magenta_          5
#define		_marron_           6
#define		_cinza_claro_      7
#define		_cinza_escuro_     8
#define		_azul_claro_       9
#define		_verde_claro_     10
#define		_ciano_claro_     11
#define		_vermelho_claro_  12
#define		_magenta_claro_   13
#define		_amarelo_         14
#define		_branco_          15

#define textcolor_2( letras,  fundo)       \
    SetConsoleTextAttribute(	           \
        GetStdHandle(STD_OUTPUT_HANDLE),   \
        (letras|(fundo<<4))	               \
    )

#define		_intervalo_		20
#define		fundo_menor		_amarelo_
#define		fundo_maior		_ciano_claro_
#define		fundo_fixo		_ciano_claro_ 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int*	arruma_um_vetor(int);	// cria os vetores de teste

int		bubbleUp_sort(int[], int);	// bolha
int		bubble_sort(int[], int);	// ancora
int		bubbleUp_sort_A(int[], int);// versao animada bolha
int		bubble_sort_A(int[], int);	// versao animada ancora

// funcoes auxiliares para a animacao
int		mostra_o_fixo_V(int, int, int[], int, int, int);
int		mostra_o_par_V(int, int, int[], int, int, int, int);
int		mostra_o_vetor(int[], int);
int		mostra_o_vetor_UP(int, int, int[], int, int);
int		mostra_o_vetor_V(int, int, int[], int);
int		mostra_status(char*,int,int);

int		cls(); // versao windows
void	gotoYX(HANDLE, int, int); // afinal com linha e coluna
void	text_color(HANDLE, int, int); // usando o handle passado

//	os testes
void	teste_down(int);		// normal
void	teste_down_A(int, int, int, int);	// animado normal
void	teste_up(int);			// bolha sobe
void	teste_up_A(int, int, int);	// animado bolha

int		intervalo = _intervalo_;	// pura preguica

int main(int argc, char** argv)
{
	char	c;
	int		linha = 3;
	int		coluna = 8;
	int		m = 64; // tamanho do vetor para os testes simples
	int		n = 10;
	char	mensagem[40];
	time_t	hora;

	if (argc > 1)
	{	// linha de comando bubble N intervalo
		n = atoi(argv[1]);
		if (n > 32 || n < 2) n = 16;	// entre 2 e 32 apenas
		if (argc > 2)
		{
			intervalo = atoi(argv[2]);
			if (intervalo > 200 || intervalo < 10) intervalo = 0;	// entre 160 e 2000 ms
		};
	};	// end if

	// teste 1 de 4

	cls();
	printf("\n\nUsando o bubble sort convencional\n");
	printf("(vetor de %d numeros inteiros positivos gerados aleatoriamente)\n", m);
	printf("[Tecle ENTER]");
	c = getc(stdin);
	teste_down(m);
	printf("[Tecle ENTER]");
	c = getc(stdin);

	// teste 2 de 4

	cls();
	printf("\n\nUsando o bubble sort no sentido das bolhas :)\n");
	printf("(vetor de %d numeros inteiros positivos gerados aleatoriamente)\n", m);
	printf("[Tecle ENTER]");
	c = getc(stdin);
	teste_up(m);
	printf("[Tecle ENTER]");
	c = getc(stdin);

	// teste 3 de 4

	cls();
	printf("\n\nUsando o bubble sort convencional, mas com o algoritmo animado)\n");
	printf("(vetor de %d numeros inteiros positivos gerados aleatoriamente)\n", n);
	if (intervalo == 0)
	{
		printf("Animacao passo a passo: segue com ENTER\n");
	}
	else
	{
		printf("Intervalo na animacao de %dms aprox.\n", 10 * intervalo);
	};	// if
	printf("[Tecle ENTER]");
	c = getc(stdin);
	teste_down_A(linha, coluna, n, intervalo);
	printf("[Tecle ENTER]");
	c = getc(stdin);

	// teste 4 de 4

	cls();
	printf("\n\nUsando o bubble sort no sentido das bolhas :) com o algoritmo animado)\n");
	printf("(vetor de %d numeros inteiros positivos gerados aleatoriamente)\n", n);
	if (intervalo == 0)
	{
		printf("Animacao passo a passo: segue com ENTER\n");
	}
	else
	{
		printf("Intervalo na animacao de %dms aprox.\n", 10 * intervalo);
	};	// if
	printf("[Tecle ENTER]");
	c = getc(stdin);
	teste_up_A(linha, coluna, n, intervalo);
	printf("[Tecle ENTER]");
	c = getc(stdin);

	return 0;
}	// main()


int*	arruma_um_vetor(int quantos)
{
	if (quantos < 1) return NULL;	// errado
	int* vetor = (int*)malloc(sizeof(int) * quantos);
	if (vetor == NULL) return NULL;	// nao conseguiu alocar
	int salvo;
	int total = quantos;
	for (int i = 0; i < quantos; i = i + 1) vetor[i] = i; // numera todos
	for (int i = 0; i < quantos - 2; i = i + 1)
	{
		int prox = rand() % total;
		salvo = vetor[i];
		vetor[i] = vetor[i + prox];
		vetor[i + prox] = salvo;
		total = total - 1;
	}
	return vetor;
};	// arruma_um_vetor()


int		bubbleUp_sort(int vetor[], int N)
{
	int passo, elemento, temp;
	for (passo = 0; passo < N - 1; passo = passo + 1)
	{
		int mudou_algo = 0;	// se nao muda nada no passo ja terminou
		for (elemento = N - 1; elemento > passo; elemento = elemento - 1)
		{
			if (vetor[elemento] < vetor[elemento - 1])
			{
				temp = vetor[elemento];
				vetor[elemento] = vetor[elemento - 1];
				vetor[elemento - 1] = temp;
				mudou_algo = 1;
			}	// if
		}	// for
		if (mudou_algo == 0)
			return passo + 1;	// economizou uns passos
	}	// for
	return passo + 1;
};


int		bubble_sort(int vetor[], int N)
{
	int passo, elemento, temp;
	for (passo = 0; passo < N - 1; passo = passo + 1)
	{
		int mudou_algo = 0;	// se nao muda nada no passo ja terminou
		for (elemento = 0; elemento < (N - 1 - passo); elemento = elemento + 1)
		{
			if (vetor[elemento] > vetor[elemento + 1])
			{
				temp = vetor[elemento];
				vetor[elemento] = vetor[elemento + 1];
				vetor[elemento + 1] = temp;
				mudou_algo = 1;
			}	// if
		}	// for
		if (mudou_algo == 0)
			return passo + 1;	// economizou uns passos
	}	// for
	return passo + 1;
};


int		bubbleUp_sort_A(int vetor[], int N)
{
	int passo, elemento, temp;
	char mensagem[40];

	for (passo = 0; passo < N - 1; passo = passo + 1)
	{
		// no inicio mostra os ja fixos
		for (int i = 0; i < passo; i += 1)
		{
			mostra_o_fixo_V(3, 8, vetor, N, passo, fundo_fixo);
		}	// for
		mostra_o_vetor_UP(3, 8, vetor, N - passo, passo);
		sprintf(mensagem, "Inicio do passo %02d", passo);
		mostra_status(mensagem, intervalo, N);

		int mudou_algo = 0;	// se nao muda nada no passo ja terminou
		for (elemento = N - 1; elemento > passo; elemento = elemento - 1)
		{
			mostra_o_par_V(3, 8, vetor, N, elemento-1, fundo_menor, fundo_menor);
			sprintf(mensagem, "Comparando (%d,%d)", vetor[elemento-1], vetor[elemento]);
			mostra_status(mensagem, intervalo, N);
			if (vetor[elemento] < vetor[elemento - 1])
			{
				mostra_o_par_V(3, 8, vetor, N, elemento-1, fundo_menor, fundo_maior);
				temp = vetor[elemento];
				vetor[elemento] = vetor[elemento - 1];
				vetor[elemento - 1] = temp;
				mudou_algo = 1;
			}
			else
			{
				mostra_o_par_V(3, 8, vetor, N, elemento-1, fundo_maior, fundo_menor);
				// no swap
			}// if
			mostra_status("", intervalo, N);
			mostra_o_vetor_UP(3, 8, vetor, N - passo, passo);
		}	// for
		if (mudou_algo == 0)
		{	// termina a animacao e retorna
			for (int i = passo; i <= N-1; i = i + 1)
			{
				mostra_o_fixo_V(3, 8, vetor, N, i, fundo_fixo);
			}
			return passo + 1;	// economizou uns passos
		}
		// em (passo) esta um elemento classificado
		mostra_o_fixo_V(3, 8, vetor, N, passo, fundo_fixo);
	}	// for
	return passo + 1;
};	// bubbleUP_sort_A()


int		bubble_sort_A(int vetor[], int N)
{
	int passo, elemento, temp;
	char mensagem[40];

	for (passo = 0; passo < N - 1; passo = passo + 1)
	{
		mostra_o_vetor_V(3, 8, vetor, N - passo);
		sprintf(mensagem, "Inicio do passo %02d", passo);
		mostra_status(mensagem, intervalo, N);

		int mudou_algo = 0;	// se nao muda nada no passo ja terminou
		for (elemento = 0; elemento < (N - 1 - passo); elemento = elemento + 1)
		{
			mostra_o_par_V(3, 8, vetor, N, elemento, fundo_menor, fundo_menor);
			sprintf(mensagem, "Comparando (%d,%d)", vetor[elemento], vetor[elemento + 1]);
			mostra_status(mensagem, intervalo, N);
			if (vetor[elemento] > vetor[elemento + 1])
			{
				mostra_o_par_V(3, 8, vetor, N, elemento, fundo_maior, fundo_menor);
				temp = vetor[elemento];
				vetor[elemento] = vetor[elemento + 1];
				vetor[elemento + 1] = temp;
				mudou_algo = 1;
			}
			else
			{
				mostra_o_par_V(3, 8, vetor, N, elemento, fundo_menor, fundo_maior);
				// no swap
			}// if
			mostra_status("", intervalo, N);
			//mostra_o_par_V(3, 8, vetor, N, elemento, _branco_, _branco_);
			mostra_o_vetor_V(3, 8, vetor, N - passo);
		}	// for
		if (mudou_algo == 0)
		{	// termina a animacao e retorna
			for (int i = N - passo - 1; i >= 0; i -= 1)
			{
				mostra_o_fixo_V(3, 8, vetor, N, i, fundo_fixo);
			}
			return passo + 1;	// economizou uns passos
		}
		// em (N-1-passo) esta um elemento classificado
		mostra_o_fixo_V(3, 8, vetor, N, N - 1 - passo, fundo_fixo);
	}	// for
	return passo + 1;
};	// bubble_sort_A()


int		mostra_o_fixo_V(
	int linha, int coluna,
	int v[], int N,
	int pos, int cor_a
)
{
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoYX(H, linha + 2 + pos, coluna);
	text_color(H, _preto_, cor_a);
	printf("   %02d   ", v[pos]);
	text_color(H, _branco_, _preto_);
	return 0;
}	// end mostra_o_fixo_V()


int		mostra_o_par_V(
	int linha, int coluna,
	int v[], int N,
	int pos, int cor_a, int cor_b
)
{
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoYX(H, linha + 2 + pos, coluna);
	text_color(H, _preto_, cor_a);
	printf("   %02d   ", v[pos]);
	gotoYX(H, linha + 2 + pos + 1, coluna);
	text_color(H, _preto_, cor_b);
	printf("   %02d   ", v[pos + 1]);
	text_color(H, _branco_, _preto_);
	return 0;
}



int		mostra_o_vetor(int v[], int N)
{
	printf("\nVetor com %02d elementos\n\n", N);
	for (int i = 0; i < N; i += 1)
	{
		printf(" %02d ", v[i]);
		if (i % 10 == 9) printf("\n");
	};
	printf("\n\n");
	return 0;
};


int		mostra_o_vetor_UP(int linha, int coluna, int v[], int N, int passo)
{
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	text_color(H, _branco_, _preto_);
	gotoYX(H, linha, coluna);
	printf("A classificar: %02d elementos", N);
	for (int i = 0; i < N; i += 1)
	{
		gotoYX(H, linha + 2 + i + passo, coluna);
		printf("   %02d   ", v[passo+i]);
	};
	return 0;
};


int		mostra_o_vetor_V(int linha, int coluna, int v[], int N)
{
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	text_color(H, _branco_, _preto_);
	gotoYX(H, linha, coluna);
	printf("A classificar: %02d elementos", N);
	for (int i = 0; i < N; i += 1)
	{
		gotoYX(H, linha + 2 + i, coluna);
		printf("   %02d   ", v[i]);
	};
	return 0;
};


int		mostra_status(char* mensagem, int tempo, int N)
{
	gotoYX(GetStdHandle(STD_OUTPUT_HANDLE), N+6, 0);
	printf("%s [Tecle ENTER]", mensagem);
	if (tempo == 0)
	{
		char c = getc(stdin);
	}
	else
	{
		for(int i = 0; i<10; i+=1)
			Sleep(tempo);
	}
	gotoYX(GetStdHandle(STD_OUTPUT_HANDLE), N+6, 0);
	printf("                                                   ");
	return 0;
};


int	cls()
{	// limpa a tela no windows, no oficial
	CONSOLE_SCREEN_BUFFER_INFO		info;
	HANDLE		H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD		origem = { 0,0 };
	int			total;
	if (H == INVALID_HANDLE_VALUE) return -1;
	GetConsoleScreenBufferInfo(H, &info);
	int r = FillConsoleOutputCharacter(H, (TCHAR) ' ', 
		info.dwSize.X * info.dwSize.Y,
		origem, &total);
	int s = FillConsoleOutputAttribute(
		H, info.wAttributes, 
		info.dwSize.X * info.dwSize.Y,
		origem, &total);
	SetConsoleCursorPosition(H, origem);
	return 0;
};	// end cls()


void	gotoYX(HANDLE console, int x, int y)
{
	static COORD	 coord;
	coord.X = y; coord.Y = x;
	SetConsoleCursorPosition(console, coord);
	return;
};	// gotoXY


void	text_color(HANDLE Console, int letras, int fundo)
{
	SetConsoleTextAttribute(Console, letras | (fundo << 4));
}	// text_color

// ==================== testes ====================

void	teste_down(int n)
{
	time_t	hora;
	srand((unsigned int)time(&hora));
	int* v = arruma_um_vetor(n);

	cls();
	mostra_o_vetor(v, n);
	int passos = bubble_sort(v, n);
	printf("(up) %02d elementos classificados em %d passos", n, passos);
	mostra_o_vetor(v, n);
	return;
};	// teste_down()


void	teste_down_A(int linha, int coluna, int n, int intervalo)
{
	char	mensagem[40];
	time_t	hora;
	srand((unsigned int)time(&hora));
	int* v = arruma_um_vetor(n);

	cls();
	mostra_o_vetor_V(linha, coluna, v, n);
	sprintf(mensagem, "%02d elementos a classificar", n);
	mostra_status(mensagem, 0, n);

	int passos = bubble_sort_A(v, n);

	sprintf(mensagem, "%02d elementos classificados em %d passos", n, passos);
	mostra_status(mensagem, 0, n);

	return;
};	// teste_down_A()


void	teste_up(int n)
{
	time_t	hora;
	srand((unsigned int)time(&hora));
	int* v = arruma_um_vetor(n);

	cls();
	mostra_o_vetor(v, n);
	int passos = bubbleUp_sort(v, n);
	printf("(up) %02d elementos classificados em %d passos", n, passos);
	mostra_o_vetor(v, n);
	return;
};	// teste_up()


void	teste_up_A(int linha, int coluna, int n, int intervalo)
{
	char	mensagem[40];
	time_t	hora;
	srand((unsigned int)time(&hora));
	int* v = arruma_um_vetor(n);

	cls();
	mostra_o_vetor_V(linha, coluna, v, n);
	sprintf(mensagem, "%02d elementos a classificar", n);
	mostra_status(mensagem, 0, n);

	int passos = bubbleUp_sort_A(v, n);

	sprintf(mensagem, "%02d elementos classificados em %d passos", n, passos);
	mostra_status(mensagem, 0, n);

	return;
};	// teste_up_A()
