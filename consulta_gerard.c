#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;

	char consulta [80];
	char num[3];
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd", 0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

	printf ("Dame numero de partida: "); 
	scanf ("%s", num);
	sprintf(consulta, "SELECT jugadores.username FROM (jugadores,partidas,registro) WHERE partidas.id = %d AND partidas.id = registro.id_p AND jugadores.id = registro.id_j;",atoi(num));
	
	err=mysql_query (conn,consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

	resultado = mysql_store_result (conn);

	row = mysql_fetch_row (resultado);

	
	int i = 1;
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf ("Jugadores de la partida %s:\n", num);
		while (row !=NULL) {
			printf ("Jugador %d: %s\n", i, row[0]);
			row = mysql_fetch_row (resultado);
			i++;
	}
		
		
		
		mysql_close (conn);
		exit(0);
}
