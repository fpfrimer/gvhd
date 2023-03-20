#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

bool is_valid_name(const char *name) {
    if (!isalpha(name[0])) {
        return false;
    }

    for (unsigned int i = 1; i < strlen(name); i++) {
        if (!isalnum(name[i]) && name[i] != '_') {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <nome_entidade> <nome_arquitetura> [port_1 port_2 ...]\n", argv[0]);
        return 1;
    }

    const char *entity_name = argv[1];
    const char *arch_name = argv[2];

    if (!is_valid_name(entity_name)) {
        printf("Erro: Nome da entidade inválido\n");
        return 1;
    }

    if (!is_valid_name(arch_name)) {
        printf("Erro: Nome da arquitetura inválido\n");
        return 1;
    }

    char template_file[256];
    snprintf(template_file, sizeof(template_file), "%s.vhd", entity_name);

    FILE *file = fopen(template_file, "w");
    if (!file) {
        printf("Erro ao criar arquivo: %s\n", template_file);
        return 1;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char datetime_str[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(file, "-- arquivo gerado: %s\n", template_file);
    fprintf(file, "-- entidade: %s\n", entity_name);
    fprintf(file, "-- arquitetura: %s\n", arch_name);
    fprintf(file, "-- data e hora de criação: %s\n\n", datetime_str);

    fprintf(file, "library ieee;\n");
    fprintf(file, "use ieee.std_logic_1164.all;\n");
    fprintf(file, "use ieee.numeric_std.all;\n\n");

    fprintf(file, "entity %s is\n", entity_name);
    fprintf(file, "    port (\n");

    for (int i = 3; i < argc; i++) {
        if (!is_valid_name(argv[i])) {
            printf("Aviso: Nome de port inválido '%s'\n", argv[i]);
            continue;
        }

        fprintf(file, "        %s : -- insira o modo e tipo do sinal aqui;\n", argv[i]);
    }

    fprintf(file, "    );\n");
    fprintf(file, "end entity %s;\n\n", entity_name);

    fprintf(file, "architecture %s of %s is\n", arch_name, entity_name);
    fprintf(file, "    -- declare suas variáveis e componentes internos aqui\n");
    fprintf(file, "begin\n");
    fprintf(file, "    -- escreva sua descrição de arquitetura aqui\n");
    fprintf(file, "end architecture %s;\n", arch_name);

    fclose(file);

    printf("Arquivo VHDL gerado: %s\n", template_file);
    return 0;
}
