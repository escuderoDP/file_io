#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint64_t get_file_size(const char *file_name)
{
	FILE *p_input_file;
	size_t file_size;
	p_input_file = fopen(file_name, "rb");
	if (p_input_file == NULL)
	{
		printf("Não foi possível abrir arquivo de entrada <%s>.\n", file_name);
		exit(1);
	}
	fseek(p_input_file, 0, SEEK_END);
	file_size = ftell(p_input_file);
	fseek(p_input_file, 0, SEEK_SET);
	fclose(p_input_file);

	return file_size;
}

void ler_arquivo_para_vetor(const char *file_name, uint64_t *file_blocks,
			    size_t file_size)
{
    FILE *p_file_input;
    int res;

    p_file_input = fopen(file_name, "rb");
    if (p_file_input == NULL) {
        printf("Não foi possível abrir arquivo de entrada <%s>.\n", file_name);
        exit(1);
    }

    res = fread(file_blocks, 1, file_size, p_file_input);

    fclose(p_file_input);

}

void escreve_vetor_para_arquivo(const char *file_name, uint64_t *file_blocks, size_t file_size)
{
    FILE *p_file_output;

    p_file_output = fopen(file_name, "wb");
    if (p_file_output == NULL) {
        printf("Não foi possível abrir arquivo de saída <%s>.\n", file_name);
        exit(1);
    }

    fwrite(file_blocks, 1, file_size, p_file_output);

    fclose(p_file_output);
}

int main(int argc, char const *argv[])
{
	const char *input_file_name;
	const char *output_file_name;
	uint64_t file_size;
	uint64_t *file_blocks;
	int i;
	//char output[60]; 
	input_file_name = argv[1];
	//output = argv[1];
	uint64_t size_output_file_name = strlen(argv[1]);
	char output[size_output_file_name + 6];

	for(i = 0; i < size_output_file_name; i++)
	{
		output[i] = argv[1][i];
	}
	output[size_output_file_name] = "\0";
	printf("Name output file = %s \n", output);
	strcat(output, "_bits");

	output_file_name = output;
	printf("Name output file = %s \n", output);

	file_size = get_file_size(input_file_name);
	printf("File Size = %lu \n", file_size);

	//if (strcmp(argv[1], "-c") == 0) {

		file_blocks = malloc(file_size);

		ler_arquivo_para_vetor(input_file_name, file_blocks, file_size);

		//escreve_vetor_para_arquivo(output_file_name, file_blocks, file_size);


		exit(1);
	//}

	return 0;
}