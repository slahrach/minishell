# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>


int	main(int argc, char **argv, char **envp)
{
    char 	*ff;
    int 	fd1;
    int 	fd0;
    int 	fd11;
    int 	fd00;

    fd11 = open("testout", O_WRONLY | O_CREAT);
    fd00 = open("testFailed", O_RDONLY | O_CREAT);
    ff = "";
    fd1 = dup(1);
    fd0 = dup(0);
    dup2(fd11, 1);
    dup2(fd00, 0);
    while (ff)
    {
        ff = readline("fff : ");
        printf("%s\n", ff);
    }
    dup2(fd1, 1);
    dup2(fd0, 0);
    return 0;
}