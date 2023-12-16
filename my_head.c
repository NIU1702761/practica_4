#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void my_head(const char *arxiu, int ln) {
         int fd = open(arxiu, O_RDONLY);
         if (fd == -1) {
                perror("Error: No es pot obrir l'arxiu.");
                return;
        }
        if (ln <= 0) {
                perror("Error: El nombre de línies ha de ser major que zero.");
                close(fd);
                return;

         } else {
                char c;
                int n_ln = 0;

                while (read(fd, &c,1) != 0 && n_ln < ln) {
                        printf("%c", c);
                        if (c == '\n') {
                                n_ln ++;
                         }
                }
        }
    close(fd);
}
int main(){
        char arxiu[100];
        printf("Introdueix el nom de l'arxiu: ");
        scanf("%s",arxiu);

        int ln;
        printf("Introdueix el nombre de linies que vols llegir: \n");
        scanf("%d",&ln);

        my_head(arxiu, ln);
	
	return 0;
	}

