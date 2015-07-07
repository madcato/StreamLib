========================================================================
       CONSOLE APPLICATION : WebServer
========================================================================

Este es un servidor de aplicaciones simple con interfaz web.

Indice
-------------------------------
1. Configuración
	1.1 webapp.conf
	1.2 controllers.conf
	1.3 DB
2. Esquema directorios
3. Ampliación de funcionalidades
	3.1 Ficheros plantilla
4. Control de la aplicación
---------------------------------

1. Configuración

1.1 webapp.conf
	Este archivo deberá encontrarse en el directorio ./conf
	Sus variables son:
		
	server_ip = localhost	// Bind IP
	server_port = 7777		// Bind port
	control_port = 9999		// Bind control port. Puerto de control de la apliacion, ver 4. Control de la apliación.
	base_path = .\web		// Base path donde están ubicados los ficheros html a servir.


	log_file = .\log\webapp.log		// fichero de log
	#log_format = date time c-ip cs-mehtod cs-uri cs-bodylength x-status sc-serverMsg-s
	log_format = date time c-ip cs-mehtod cs-uri x-status	// formato de log

	#error log
	error_file = .\log\errors.log	// fichero de errores
	#error_level = LOG_ALL | ~LOG_TRACE
	error_level = LOG_ALL		// nivel de errores a mostrar

	#controller configuration archive
	controller_conf_file=.\conf\controllers.conf	// fichero de controladores dinámicos
	include_path=.\includes\			// path de includes
	
1.2 controllers.conf
	En este archivo se dan de alta todas aquellas clases dinámicas que el servidor WebApp creará y le asignará una ruta web.
	De tal manera que cuando algún cliente web acceda a esa URL el servidor redigirá la petición a la clase dinámica.
	
	Ejemplo:
	ArtList=/ArtList	// Todas las peticiones dirigidas hacia http://localhost:7777/ArtList llegarán a la clase ArtList
						
						
1.3 DB
	Al iniciar la aplicación deberá indicarse en el primer parámetro de entrada una cadena de conexión a base de datos que será usada de manera global por todos los controladores.

2. Esquema directorios
	El único directorio no configurable es el de configuración. Deberá llamarse "conf" y estar dentro del direcotrio donde se ejecute la aplicación web.
	Aparte de este directorio se necesitan al menos otros tres: uno para ficheros de inclusión, otro para los logs y un tercero que servirá de base para los ficheros estáticos de la aplicación web como ficheros html e imágenes.

3. Ampliación de funcionalidades
	Para incluir nuevas funcionalidades al servidor web hay que crear controladores dinámicos. Estos controladores son clases genéricas C++ que deben heredar de la clase GenericController e implementar los métodos "classId" y "executeQuery".
	Cuando el servidor reciba una petición dirigida a un determinado controlador, invocará al método "executeQuery" pasando como parámetro todas las variables que hayan sido enviadas con la petición web(POST y GET indistintamente).
	Esta función deberá devolver una estructura de respuesta que será enviada al cliente web. En caso de que la petición sea incorrecta o exista algún problema en la ejecución se podrá devolver alguna respuesta preestablecida, ver método constructNotFoundResponse. 
	IMPORTANTE: Para que la aplicación web pueda instanciar objetos de los controladores, se deberá incluir la siguiente macro en el archivo de implementación del controlador: REGISTER_CLASS(ClassName);
	
3.1 Ficheros plantilla
	Los ficheros plantilla permiten generar cómodamente código HTML donde devolver el resultado del procesamiento de la peticiones.
	Para conocer su funcionamiento ver la documentación de la clase HTMLTPage de la librería Stream.
	
4. Control de la aplicación
	La aplicación web abre un puerto de control cuyo número es configurable en el archivo WebApp.conf.
	Este puerto es accesible usando un cliente Telnet cualquiera. Responde a los siguientes comandos:
	- SHUTDOWN	Finaliza la aplicación.
	- RESTART	Reinicia todo el proceso de inicialización.
	- NOOP		No hace nada.