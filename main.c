/*
	Bibliotecas utilizadas
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/*
	Essa função recebe como entrada o nome de um arquivo de entrada e o nome de um
	arquivo de saída. A função faz a leitura binária e imprime cada bit em forma
	de texto no arquivo de saída. O arquivo de saída terá o tamanho 8 vezes maior
	que o arquivo de entrada, pois cada bit será convertido para um caractere que possui
	o tamanho de 1 byte.
*/
void printBinaryCharacters(const char *name_input_file, const char *name_output_file) {
	FILE *input_file = fopen(name_input_file, "rb");
	FILE *output_file = fopen(name_output_file, "w");

	if (input_file == NULL || output_file == NULL) {
	printf("Erro ao abrir o arquivo\n");
	exit(1);
	}

	fseek(input_file, 0, SEEK_END);
	uint32_t file_size = ftell(input_file);
	rewind(input_file);

	unsigned char *file_data = (unsigned char*) malloc(file_size * sizeof(unsigned char));
	fread(file_data, sizeof(unsigned char), file_size, input_file);

	for (uint32_t i = 0; i < file_size; i++) {
	for (char j = 7; j >= 0; j--) {
		fprintf(output_file, "%d", (file_data[i] >> j) & 1);
	}
	}

	fclose(input_file);
	fclose(output_file);
	free(file_data);
}

/*
	Essa função verifica se o arquivo de entra é um arquivo de texto
	com apenas caracteres "0"s e/ou "1"s. Caso a função encontre algum 
	caractere diferente, o programa é finalizado e a mensagem de conteúdo
	inválido é apresentado.
*/
uint32_t checkValidContent(const char *name_input_file) {
	FILE *input_file = fopen(name_input_file, "r");

	if (input_file == NULL) {
	printf("Erro ao abrir o arquivo\n");
	exit(1);
	}

	fseek(input_file, 0, SEEK_END);
	uint32_t file_size = ftell(input_file);
	rewind(input_file);

	char *file_data = (char*) malloc(file_size * sizeof(char));
	fread(file_data, sizeof(char), file_size, input_file);

	for (uint32_t i = 0; i < file_size; i++) {
	if (file_data[i] != '0' && file_data[i] != '1') {
		fclose(input_file);
		free(file_data);
		printf("O conteúdo do arquivo não é válido\n");
		exit(1);
	}
	}

	fclose(input_file);
	free(file_data);
	return file_size;
}

/*
	Caso o arquivo de entrada tenha apenas caracteres "0"s e/ou "1"s,
	cada caractere é convertido para um bit, de forma de uma sequencia
	de oito caracteres forma uma sequencia binária de um byte que é
	gravado no arquivo de saída.
*/
void convertBitsToFile(const char *name_input_file, const char *name_output_file) {
	uint32_t file_size = checkValidContent(name_input_file);

	FILE *input_file = fopen(name_input_file, "r");
	FILE *output_file = fopen(name_output_file, "wb");

	if (input_file == NULL || output_file == NULL) {
	printf("Erro ao abrir o arquivo\n");
	exit(1);
	}

	uint32_t binary_data_size = (file_size + 7) / 8;
	unsigned char *binary_data = (unsigned char*) malloc(binary_data_size * sizeof(unsigned char));

	uint32_t binary_data_index = 0;
	char file_data[9];
	file_data[8] = '\0';

	while (fscanf(input_file, "%8s", file_data) == 1) {
	unsigned char numero = 0;
	for (char i = 0; i < 8; i++) {
		if (file_data[i] == '1') {
		numero |= (1 << (7 - i));
		}
	}
	binary_data[binary_data_index++] = numero;
	}

	fwrite(binary_data, sizeof(unsigned char), binary_data_size, output_file);
	fclose(input_file);
	fclose(output_file);
	free(binary_data);
	printf("Arquivo convertido com sucesso\n");
}


int main(int argc, char *argv[]) {
	if (argc != 4) {
	printf("\nUso para imprimir binário: %s -b <name__arquivo_entrada> <name__arquivo_saída> \n", argv[0]);
	printf("Uso para converter para arquivo: %s -f <name__arquivo_entrada> <name__arquivo_saída> \n\n", argv[0]);
	return 1;
	}

	char *name_input_file = argv[2];
	char *name_output_file = argv[3];
	char *flag = argv[1];

	/*
		O parâmetro "-b" é usado para imprimir os bits de um arquivo de entrada em um arquivo de saída,
		enquanto que o parâmetro "-f" é usado para pegar um arquivo com uma sequência de caracteres
		"0"s e/ou "1"s e converter essa sequência para binário. Como cada sequência de 8 caracteres
		formam 1 byte, o arquivo de saída será um binário com tamanho 8 vezes menor.
	*/
	if ((strcmp(flag, "-b") != 0) && (strcmp(flag, "-f") != 0)) {
	printf("\nUso para imprimir binário: %s -b <name__arquivo_entrada> <name__arquivo_saída> \n", argv[0]);
	printf("Uso para converter para arquivo: %s -f <name__arquivo_entrada> <name__arquivo_saída> \n\n", argv[0]);
	return 1;
	}

	if (strcmp(flag, "-b") == 0)
	{
	printBinaryCharacters(name_input_file, name_output_file);
	}

	if (strcmp(flag, "-f") == 0)
	{
	convertBitsToFile(name_input_file, name_output_file);
	}

	return 0;
}