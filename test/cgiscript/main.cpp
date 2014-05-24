#include <iostream> 
#include <fcgi_stdio.h> 
#include <stdlib.h> 

char *path_name;

int main() 
{
	int count = 0;
	while(FCGI_Accept() >= 0){
		printf("Content-type: text/html\r\n\r\n");
		path_name =  getenv( "SCRIPT_FILENAME" ); 
		printf("FastCGI Hello! %s",path_name);
	}
	return 0;
}
