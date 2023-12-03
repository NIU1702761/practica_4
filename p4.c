#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define salt '\n'
void my_head(const char *arxiu, int ln) {
   	 int fd = open(arxiu, O_RDONLY);
   	 if (fd == -1) {
        	perror("Error: No es pot obrir l'arxiu.\n");
		close(fd);
       		//exit(EXIT_FAILURE)
		return;
    	}
	if (ln <= 0) {
        	perror("Error: El nombre de línies ha de ser major que zero.\n");
        	close(fd);
        	return;

   	 } else {
		char c;
	    	int n_ln = 0;
    		
    		while (read(fd, &c,1) != 0 && n_ln < ln) {
        		if (c == '\n') {
           			n_ln ++;
				printf("%c",c);		
       			 } else {
				printf("%c",c);
			}
    		}
	}
    close(fd);
}

void my_mv(const char *arxiu, const char *nom_o_lloc){
	int fd = open(arxiu,O_RDONLY);
	int fd2 = creat(nom_o_lloc,0666);
	int num;
	char buf[1024];
	if (fd == -1) {
		perror("Error: No es pot obrir l'arxiu.\n");
		close(fd);
		return;
	} else {
		if (fd2 < 0){
			perror("Error en el creat");
			close(fd);
			return;
		} else {
			while((num = read(fd,buf,3)) > 0) {
				if (write(fd2,buf,num) < 0) {
					perror("Error en el write");
					close(fd);
					close(fd2);
					return;
				}
			}
			if (unlink(arxiu) < 0) {
				perror("Error en esborrar l'arxiu original");
				return;
			}
			printf("L'arxiu s'ha mogut correctament.\n");
			
		}
	close(fd);
	close(fd2);
	
	}
}
int main(){
	char arxiu[100];
	printf("Introdueix el nom de l'arxiu:\n");
	scanf("%s",arxiu);

	int ln;
	printf("Introdueix el nombre de linies que vols llegir:\n");
        scanf("%d",&ln);

	my_head(arxiu, ln);

	char arxiu2[100];
	char nou_arxiu2[100];

	printf("Introdueix el nom de l'arxiu a moure: ");
	scanf("%s",arxiu2);

	printf("Introduiex el nom o la nova ubicació de l'arxiu: ");
	scanf("%s",nou_arxiu2);

	my_mv(arxiu2,nou_arxiu2);

    	return 0;
}

