#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Abrir el archivo grande en modo solo lectura
    int fd = open("./minishell_tester/test_files/infile_big", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Redirigir el archivo a la entrada estándar (STDIN_FILENO)
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Error en dup2");
        close(fd);
        return 1;
    }

    // Cerrar el descriptor original, ya que no lo necesitamos más
    close(fd);

    // Ejecutar el comando grep "hi"
    char *args[] = {"grep", "--binary-files=text", "hi", NULL};
    char *envp[] = {NULL}; // Entorno vacío si no necesitas uno especial

    if (execve("/bin/grep", args, envp) == -1)
    {
        perror("Error al ejecutar grep");
        return 1;
    }

    return 0; // No se llegará a este punto si execve es exitoso
}
