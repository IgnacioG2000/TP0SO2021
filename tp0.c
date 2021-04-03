/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();


	//Loggear "soy un log"
	log_info(logger,"Soy un log");


	config = leer_config();

	//asignar valor de config a la variable valor
	valor = config_get_string_value(config,"CLAVE");

	//Loggear valor de config
	log_info(logger,valor);

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//crear conexion
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	
	conexion = crear_conexion(ip,puerto);

	//enviar CLAVE al servirdor
	enviar_mensaje(valor,conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	t_log* logger = log_create("tp0.log","Inicio TP0",1,LOG_LEVEL_INFO);
	if(logger == NULL) 
		exit(1);
	else 
		return logger;
}

t_config* leer_config(void)
{
	t_config* config = config_create("tp0.config");

	return config;
}

void leer_consola(t_log* logger)
{
	char* leido = readline(">");

	//El primero te lo dejo de yapa
	while(strcmp(leido,"")!= 0) {
		log_info(logger,leido);
		free(leido);
		leido = readline(">");
	}

	free(leido); // Para liberar cadena vacia
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();
	
	while(strcmp(leido,"")!= 0){
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		leido = readline(">");
	}

	free(leido);

	enviar_paquete(paquete,conexion);

	eliminar_paquete(paquete);

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
