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

void my_mv(const char *arxiu, const char *nom_o_lloc){
	int fd = open(arxiu,O_RDONLY);
	int fd2 = open(nom_o_lloc, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU );
	int num;
	char buf[1024];
	if (fd == -1) {
		perror("Error: No es pot obrir l'arxiu.\n");
		close(fd2);
		return;
	} 
	if (fd2 == -1){
		perror("Error en el creat");
		close(fd2);
		return;
	}
	while((num = read(fd,buf,3)) > 0) {
		if (write(fd2,buf,num) < 0) {
			perror("Error en el write");
			close(fd);
			close(fd2);
			return;
		}
	}
	close(fd);
	close(fd2);

	if (unlink(arxiu) < 0) {
		perror("Error en esborrar l'arxiu original");
		return;
	}

	printf("L'arxiu s'ha mogut correctament.\n");
			
}

int main(){
	char arxiu[100];
	printf("Introdueix el nom de l'arxiu: ");
	scanf("%s",arxiu);

	int ln;
	printf("Introdueix el nombre de linies que vols llegir: ");
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

