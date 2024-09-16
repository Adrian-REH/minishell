#include <stdio.h>
#include <sys/stat.h>
       #include <unistd.h>

#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SHEBANG "#!"

int execute_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE];
    int line_number = 0;
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        // Eliminar el salto de línea al final
        line[ft_chr(line, "\n")] = 0;

        if (line_number == 1 && strncmp(line, "#!", 2) == 0) {
            continue;
        }

    }

    fclose(file);
    return 0;
}

int main(int  argc, char **argv, char **env)
{
    struct stat path_stat;
	char *args[] = {argv[1], NULL};
		if (execve(args[0], args, env) == -1)
	if (stat(argv[1], &path_stat) == 0)
	{
		printf("STR %s is to dir  %d\n",argv[1], S_ISDIR(path_stat.st_mode));
		printf("STR %s is to file %d\n",argv[1], S_ISREG(path_stat.st_mode));

	}
	else
	{
		printf("File %s does not exist\n", argv[0]);
	}

}