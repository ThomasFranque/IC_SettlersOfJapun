#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 32
typedef struct UNIT { 
/**Estrutura da unidade do mapa, primeira posicao de cada array � uma letra, o resto um numero*/
	char Building;
	char Material;
	char E;
}UNIT;

typedef struct{
	UNIT *grid; /**Isto innicializa um apontador que contem UNITS*/
	unsigned int xdim;
	unsigned int ydim;
	char E[MAX];
} MAP_CONFIG;

void print_unit(){
    int rows = 5, columns = 5;

    /* Iterate over each row */
    for(int i=1; i<=rows; i++)
    {
        /* Iterate over each column */
        for(int j=1; j<=columns; j++)
        {
            if(i==1 || i==rows || j==1 || j==columns)
            {
                /* Print star for 1st and last row, column */
                printf("*");
            }
            else
            {
                printf("X");
            }
        }
        /* Move to the next line */
        printf("\n");
    }
}


void print_map(MAP_CONFIG *config){
	int xdim = config->xdim;
	int ydim = config->ydim;
	for (int i = 0; i < xdim; i++){
		for(int j = 0; i< ydim; j++);
			print_unit();
		printf("\n");
	}
}

FILE *openFile(char *nome, char *mode) {
	FILE *f;
	printf("Opening file %s\n", nome);
	f = fopen(nome, mode);

	if (f == NULL) {
		fprintf(stderr, "*** It was not possible to open the file %s.", nome);
		exit(1);	
	}
	return f;
}

void set_config_val(MAP_CONFIG *config, const char *key, char *val) {
	/**
	Esta funcao atribui a uma estrutura CONFIG o valor x e y do board
	@param config = estrutura tipo MAP_CONFIG para xdim e ydim
	@param Key = palavra chave do que se le da INI
	@param val = valor que se vai atribuir a chave correspondente na estrutura
	*/

	if (strcmp(key,"xdim")== 0){
		config->xdim = 4;
	}
	else if (strcmp(key, "ydim") == 0){
		config->ydim = atoi(val);
	}
	else if (strcmp(key, "E")== 0){
		strcpy(config->E, val);
	}
}

MAP_CONFIG read_config(FILE *f) {
	/**
	Esta funcao e onde de facto os valores vao ser atribuidos e procurados, quando se quer ler um ficheiro INI so e necessario
	chamar esta funcao com as estruturas pedidas.
	@param config = estrutura tipo MAP_CONFIG para xdim e ydim
	@param map_unit = Uma estrutura tipo UNIT para guardar os valores das 4 direcoes a volta lidas da INI
	@param f = ficheiro INI de onde se vao ler os valores para atribuir as estruturas passadas a funcao
	*/
	MAP_CONFIG config;
	char str[MAX];
	char *token;
	const char *delim = "=\n";
	char varname[MAX];
	char value[MAX];

	while (1) {
		fgets(str, MAX, f);
		if(feof(f)!= 0) break;
		if (strchr(str, ';'))
			;
		else if (strchr(str, '=')) 
		{
			token = strtok(str, delim);
			strcpy(varname, token);
			printf("%s\n", varname);
			token = strtok(NULL, delim);
			strcpy(value, token);
			printf("%s\n", value);
			set_config_val(&config, varname, value);
		}
	}
	
	fclose(f);
	return config;
}

int main(int argc, char **argv) {
	MAP_CONFIG map;
	FILE *f;
	char *filename;
	for (int i = 0; i < argc; i++)
		printf("Parametro %d: %s\n", i, argv[i]);
	if (argc >= 2) {
		filename = argv[1];
	}
	else {
		printf("A abrir o ficheiro de base...\n"); /**abre ficheiro standard se nao for oferecido como argumento um ficheiro*/
		filename = "mapa.ini";
	}

	f = openFile(filename, "r"); /**abre ficheiro atraves de funcao*/
	/**RETIRAR TODA A INFORMACAO DO FICHEIRO AQUI*/
	map = read_config(f);
	printf("%d %d", map.xdim, map.ydim);
	printf("%s", map.E);
	map.grid = calloc(map.xdim * map.ydim, sizeof(UNIT)); /**Isto aloca a grid com as estruturas UNIT la dentro*/
	getchar();
	return 0;
}
