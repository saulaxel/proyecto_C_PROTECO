/**
 * MartInez Ortiz SaUl Axel
 * PROTECO generaciOn 33, curso de Bases de Datos
 * Tarea n: RealizaciOn de una base de datos sencilla en c
 **/

// InclusiOn de informaciOn requerida
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
	#define CLEAR "cls"
	#include <locale.h>
	setlocale(LC_ALL,"Spanish_Mexico");
#elif __unix__
	#define CLEAR "clear"
#else
	#define CLEAR "" // No pos si asI esta la cosa mejor no hagas nada
#endif // _WIN32

#define LONG_NOMBRE_PERSONA 60
#define ARCHIVO_USUARIOS "mis_usuarios.txt"
#define ARCHIVO_DISCOS "mis_discos.txt"

#define z(s,c) printf("%s %s\n%s %s\n",s->cuenta,c->cuenta,s->contrasena,c->contrasena)
// Estructura que simula booleanos
enum booleano { falso, verdadero };
typedef enum booleano Booleano;

// Estructura para los usuarios
#define CTA_ADMIN "admin"
#define CONTRA_ADMIN "admin"
#define LONGITUD_CUENTA 30
#define LONGITUD_CONTRASENA 16
#define MAX_USUARIOS 5
struct usuario{
	unsigned char cuenta[LONGITUD_CUENTA+1];
	unsigned char contrasena[LONGITUD_CONTRASENA+1];
	unsigned char nombre_usuario[LONG_NOMBRE_PERSONA+1];
	struct usuario *siguiente;
	struct usuario *anterior;
};
typedef struct usuario Usuario;

struct listaUsuarios{
	Usuario *primero;
	Usuario *ultimo;
	unsigned short num_usuarios;
};
typedef struct listaUsuarios ListaUsuarios;

// Estructura para los discos
#define LONG_NOMBRE_DISCO 100
#define MAX_DISCOS 1000
struct disco{
	unsigned char nombre_artista[LONG_NOMBRE_PERSONA+1];
	unsigned char nombre_disco[LONG_NOMBRE_DISCO+1];
	float precio;
	int anio_lanzamiento;
	int numero_compras;
	struct disco *anterior;
	struct disco *siguiente;
};
typedef struct disco Disco;

struct listaDiscos{
	Disco *primero;
	Disco  *ultimo;
	unsigned short num_discos;
};
typedef struct listaDiscos ListaDiscos;

// Prototipos de funciOn

/**
 * FunciOn menu: vacio -> vacio
 * DescripciOn: Desglosa las opciones para que el 
 *  usuario sepa de donde elejir
 **/
void menu( void );

/**
 * FunciOn establecerUsuariosIniciales: apuntador a cadena,
				        apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Manda a llamar a la funciOn que lee los usuarios de la 
 * base de datos. En caso de no haber base de datos este la crea
 * con los datos de administrador.
 **/
void establecerUsuariosIniciales( Usuario *usr, ListaUsuarios *misUsuarios );

/**
 * FunciOn leerBD_Usuarios: apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Lee la lista de usuarios del archivo
 *  base de datos y los guarda en la lista de usuarios recibida
 **/
void leerBD_Usuarios( ListaUsuarios *misUsuarios );

/**
 * FunciOn escribirBD_Usuarios: apuntador estructura ListaUsuarios -> vacio
 * DescripciOn: Escribe los datos de ListaUsuarios en el archivo
 *  usado como base de datos
 **/
void escribirBD_Usuarios( ListaUsuarios *misUsuarios );

/**
 * FunciOn mostrarUsuarios: vacio -> vacio
 * DescipciOn: Imprime a pantalla los datos del archivo que representa
 *  nuestra base de datos de usuarios
 **/
void mostrarUsuarios( void );

/**
 * FunciOn cambiarUsuario: estructura Usuario, estructura ListaUsuarios -> vacio
 * DescripciOn: Permite al usuario intentar cambiarse a otro
 *  usuario registrado.
 **/
void cambiarUsuario( Usuario *usr, ListaUsuarios *misUsuarios );

/**
 * FunciOn leerDatosUsuario: apuntador a cadena,apuntador a cadena -> vacio
 * DescipciOn: Recibe dos apuntadores a cadena (usr y contra) en los 
 *  que almacenarA los datos que pide desde consola
**/
void leerDatosUsuario( unsigned char *usr, unsigned char *contra);

/**
 * FunciOn existeUsuario: estructura Usuario,
                             estructura ListaUsuarios -> estructura Booleano
 * DescripciOn: Pide al usuario sus datos y los comprueba con la
 *  base de datos actual para devolver si el usuario se encuentra
 *  o no registrado
 **/
Booleano existeUsuario( Usuario *usr, ListaUsuarios *misUsuarios);
 
/**
 * FunciOn crearUsuario: vacio -> apuntador a Usuario
 * DescripciOn: Crea un usuario nuevo por medio de memoria dinAmica
 *  e inicializa sus datos con informaciOn pedida desde la consola 
 **/
Usuario * crearUsuario( void );

/**
 * FunciOn agregarUsuario: apuntador a estructura Usuario, 
 * 			   apuntador a estructura ListaUsuarios ->  
 *			   enumeraciOn Booleano
 * DescripciOn: Recibe un usuario nuevo y lo almacena en la lista 
 *  de usuarios si no existe su cuenta
 **/
Booleano agregarUsuario( Usuario *usr, ListaUsuarios *misUsuarios );

/**
 * FunciOn eliminarUsuario: apuntador a estructura Usuario,
 * 			    apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida
 *  sobre las cuentas de los usuarios y en la primera coincidencia
 *  eliminarA el usuario actual de la lista y de la memoria 
 *  regresando a la funciOn que lo llamo verdadero, o falso al no
 *  encontrar ninguna concidencia
 + PS: No elimina al administrador(por ello lo recibe)
 **/
void eliminarUsuario( Usuario *adm, ListaUsuarios *misUsuarios );

/**
 * FunciOn leerBD_Discos: estructura ListaDiscos -> vacio
 * DescripciOn: Consulta el archivo base de datos de discos
 *  y guarda su informaciOn en una lista de usuarios
 **/
void leerBD_Discos( ListaDiscos *misDiscos );

/**
 * FunciOn escribirBD_Discos: esctuctura ListaDiscos -> vacio
 * DescripciOn: Escribe los datos de la lista de discos en 
 *  el archivo de base de datos de discos sobreescribiendola
 *  en cada ocaciOn
 **/
void escribirBD_Discos( ListaDiscos *misDiscos );

/**
 * FunciOn mostrarDiscos: vacio -> vacio
 * DescripciOn: Imprime en pantalla los datos de la base de 
 *  datos de los discos
 **/
void mostrarDiscos( void );

/**
 * FunciOn crearDisco: vacio -> apuntador a Disco
 * DescripciOn: Se encarga de instanciar un nuevo disco por 
 *  medio de memoria dinAmica e inicializado con datos pedidos
 *  por consola para al final regresar una referencia al mismo.
 **/
Disco * crearDisco(void);

/**
 * FunciOn agregarDisco: apuntador a estrucutra Disco,
 *   	         	    estructura ListaDiscos 
 *			    -> enumeraciOn Booleano 
 * DescripciOn: Recibe un nuevo disco y lo almacena en la
 *  lista especificada como argumento
 **/
Booleano agregarDisco( Disco * nvo, ListaDiscos *misDiscos );

/**
 * FunciOn eliminarDisco: apuntador a cadena,
 *                           estructura ListaDiscos -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida en 
 *  comparaciOn con los nombres de los discos, borrando el disco
 *  coincidente y regresando verdadero en el proceso, o de lo contrario 
 *  regresando falso al no encontrar coincidencias.
 **/
void eliminarDisco( Usuario *adm, ListaDiscos *misDiscos );

/**
 * FunciOn leerLinea: vacio -> vacio
 * DescripciOn: Limpia el buffer leyendo una linea
 **/
void leerLinea( void );

int main(void){
    ListaDiscos misDiscos = { NULL, NULL, 0 };
    ListaUsuarios misUsuarios = { NULL, NULL, 0 };
    short condicion = 0;
    Usuario admin = { CTA_ADMIN, CONTRA_ADMIN, "Martínez Ortiz Saúl Axel", NULL, NULL };
    
    system(CLEAR);
    // Recuperar los datos de la base de datos
    leerBD_Usuarios( &misUsuarios );
    leerBD_Discos( &misDiscos );
    printf("\n\t_____________________________________________\n");
    printf("\tLas bases de datos se han leido correctamente\n\n");
    // Si la base de datos de usuarios esta vacia --> La aplicacion no
    // ha sido usada
    establecerUsuariosIniciales( &administrador, &misUsuarios );

    do{
	system(CLEAR);
	printf("Usuario: %s \n\n", administrador.cuenta);

	printf("Ingrese la opción deseada\n");	
	menu();
	scanf("%hd",&condicion);

	switch( condicion ){
	    case 1:
		mostrarUsuarios();
	    break;

	    case 2:
		mostrarDiscos();
	    break;

	    case 3:
		if( misUsuarios.num_usuarios < MAX_USUARIOS ){
		    if( agregarUsuario( crearUsuario(), &misUsuarios ) ){
			printf("Hay un total de %d usuario(s)\n",
				misUsuarios.num_usuarios);
			 
			escribirBD_Usuarios( &misUsuarios );
		    }
		}else{
		    printf("Lo sentimos, se ha alcanzado el máximo número\n");
		    printf("de usuarios\n");
		    getchar();
		}
		getchar();
	    break;

	    case 4:
		if( misUsuarios.num_usuarios >= 1 ){
		    eliminarUsuario( &administrador, &misUsuarios );
		}
	    break;

	    case 5:
		if( misDiscos.num_discos < MAX_DISCOS ){
		    if( agregarDisco( crearDisco(), &misDiscos ) ){
			printf("Hay un total de %d disco(s)\n",
				misDiscos.num_discos);
			escribirBD_Discos( &misDiscos );
			}
		}else{
			printf("Lo sentimos, se ha alcanzado el máximo número\n");
			printf("de discos\n");
			getchar();
		}
		getchar();
	    break;

	    case 6:
		if( misDiscos.num_discos >= 1 ){
		    eliminarDisco( &administrador, &misDiscos );
		}
	    break;
	    
	    case 7:
		cambiarUsuario( &administrador, &misUsuarios );
	    break;

	    case 8:
		printf("Esperamos volver a verlo pronto\n");
		leerLinea();
		getchar();
	    break;

	    default:
		printf("Error, opción no valida\n");
		leerLinea();
		getchar();
	    break;
	}
    }while ( condicion != 8 );


    getchar();
    return 0;
}

// Contenido de la funciOn "menu"
void menu(){
    printf("\t 1) Mostrar usuarios guardados\n");
    printf("\t 2) Mostrar discos guardados\n");
    printf("\t 3) Agregar usuario\n");
    printf("\t 4) Eliminar usuario\n");
    printf("\t 5) Agregar discos\n");
    printf("\t 6) Eliminar disco\n");
    printf("\t 7) Cambiar de usuario\n");
    printf("\t 8) Salir\n");
}

// Contenido de la funciOn "establecerUsuariosIniciales"
void establecerUsuariosIniciales( Usuario *usr, ListaUsuarios *misUsuarios ){

    if( misUsuarios->num_usuarios == 0 ){
	printf("Usted será el primer usuario\n");
    }
    
    leerDatosUsuario( usr->cuenta, usr->contrasena);

    if( misUsuarios->num_usuarios == 0){
	if( agregarUsuario( usr, misUsuarios ) ){
	    escribirBD_Usuarios( misUsuarios );	
	    printf("Felicidades %s, ahora puedes administrar una\n",usr->cuenta);
	    printf("base de datos\n");
	    getchar();
	}
    }else{
	if( existeUsuario( usr, misUsuarios ) == falso ){

	    printf("Lo sentimos, el nombre de usuario o contraseña\n");
	    printf("no son validos, pida al administrador que le de\n");
	    printf("acceso\n");

	    getchar();
	    exit(0);

	}
    }	
}

// Contenido de la funciOn "leerBD_Usuarios"
void leerBD_Usuarios( ListaUsuarios *misUsuarios ){
    FILE *ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"r");
    Usuario *nvo;

    printf("Leyendo la base de datos de usuarios...\n");
    getchar();

    if( ap_BD_usuarios ){

	while( !feof(ap_BD_usuarios) ){
	    nvo = (Usuario*) malloc( sizeof(Usuario) );
	    fscanf(ap_BD_usuarios,"%30[^\t]\t",nvo->cuenta);
	    fscanf(ap_BD_usuarios,"%16[^\t]\n",nvo->contrasena);
	    printf("Se ha leido un usuario\n");
	    printf("Sus datos son %s %s\n",nvo->cuenta,nvo->contrasena);
	    agregarUsuario( nvo, misUsuarios );
	}

	printf("La base de datos se  de usuarios ha leido completamente\n");
	printf("Sus datos son\n");

	int i;
	Usuario *aux = misUsuarios->primero;
	for( i = 1; i <= misUsuarios->num_usuarios; ++i ){
	    printf("%d %s %s\n", i, aux->cuenta, aux->contrasena); 
	    aux = aux->siguiente;
	}
	
	// Se escriben los datos justo despuEs de leerlos para evitar problemas
	// causados por escribir en el archivo de usuarios directamente, es decir
	// para evitar:
	//  - Usuarios mal ordenados
	//  - Usuarios repetidos
	//  - etc
	fclose(ap_BD_usuarios);
    }
    
    escribirBD_Usuarios( misUsuarios );
    getchar();
}

// Contenido de la funciON "escribirBD_Usuarios"
void escribirBD_Usuarios( ListaUsuarios *misUsuarios ){
    FILE *ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"w");
    Usuario *aux = misUsuarios->primero;
    int i;

    for( i = 1; i <= misUsuarios->num_usuarios; ++i){
	fprintf(ap_BD_usuarios,"%s\t%s\t\n",aux->cuenta,aux->contrasena);
	aux = aux->siguiente;
    }
    
    fclose(ap_BD_usuarios);
}

// Contenido de la funciOn "mostrarUsuarios"
void mostrarUsuarios( void ){
    FILE *ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"r");
    unsigned char cadena[LONGITUD_CUENTA+1];
    int i = 1;

    if( ap_BD_usuarios ){
	
	while( !feof(ap_BD_usuarios) ){
	    printf("%2d",i);
	    fscanf(ap_BD_usuarios,"%30[^\t]\t",cadena);
	    printf("\t%30s",cadena);
	    fscanf(ap_BD_usuarios,"%16[^\t]\n",cadena);
	    printf("\t%16s\n",cadena);
	    ++i;
	}
	putchar('\n');

	fclose(ap_BD_usuarios);
    }else{
	printf("Parece que no hay usuarios registrados\n");
    }
    getchar();
    getchar();
}

// Contenido de la funciOn "cambiarUsuario"
void cambiarUsuario( Usuario *usr, ListaUsuarios *misUsuarios ){
    Usuario *nuevoUsuario = (Usuario *) malloc(sizeof(Usuario));
    Usuario *aux = misUsuarios->primero;
    Booleano cambio = falso;
    int i;

    leerDatosUsuario(nuevoUsuario->cuenta,nuevoUsuario->contrasena);

    for( i = 1; i <= misUsuarios->num_usuarios; ++i){
	if( 
	    nuevoUsuario->cuenta == aux->cuenta == 0 &&
	    nuevoUsuario->contrasena == aux->contrasena == 0
	  )
	{
	    strcpy(usr->cuenta,nuevoUsuario->cuenta);
	    strcpy(usr->contrasena,nuevoUsuario->contrasena);
	    cambio = verdadero;
	}
	aux = aux->siguiente;
    }

    if(cambio){
	printf("Cambio de usuario correctamente realizado\n"); 
    }else{
	printf("El cambio de usuario ha fallado\n");
    }

    getchar();
    getchar();
}

// Contenido de la funciOn "leerDatosUsuario"
void leerDatosUsuario( unsigned char *cta, unsigned char *contra){

    printf("Ingrese la cuenta: ");
    scanf("%30s",cta);
    leerLinea();
    fflush(stdin);

    printf("Ingrese la contraseña: ");
    scanf("%16s",contra);
    leerLinea();
    fflush(stdin);
    putchar('\n');
}

// Contenido de la funciOn "existeUsuario"
Booleano existeUsuario( Usuario *usr, ListaUsuarios *misUsuarios ){
    Usuario *aux = misUsuarios->primero;
    int i;

    for( i = 1; i <= misUsuarios->num_usuarios ; ++i ){
	//printf("Comparando con el usuario %d\n", i);
	//printf("Las cuentas son: %s %s\n", usr->cuenta, aux->cuenta);
	//printf("El resultado es: %d\n", strcmp(usr->cuenta, aux->cuenta) );
	
	//printf("Las contraseñas son: %s %s\n", 
	//	usr->contrasena,
	//	aux->contrasena);
	//printf("El resultado es: %d\n", 
    	//	strcmp(usr->contrasena, aux->contrasena) );
	//if( strcmp(usr->contrasena, aux->contrasena) ){
	//    printf("No hay correspondencia\n");
	//}else{
	//    printf("Hay correspondencia\n");    
	//}

	if( 
	    strcmp( aux->cuenta, usr->cuenta ) == 0 &&
	    strcmp( aux->contrasena, usr->contrasena ) == 0
	  )
	{
	    return verdadero;	    
	}
	aux = aux->siguiente;
    }
    return falso;
}

// Contenido de la funciOn "crearUsuario"
Usuario * crearUsuario( void ){
    Usuario *aux;
    
    aux = (Usuario *) malloc( sizeof(Usuario) );
    aux->siguiente = NULL;
    aux->anterior = NULL;

    leerDatosUsuario( aux->cuenta, aux->contrasena );

    return aux;
}

// Contenido de la funciOn "agregarUsuario"
Booleano agregarUsuario( Usuario *nvo, ListaUsuarios *misUsuarios ){
    Usuario *apt = misUsuarios->primero;
    Usuario *aux;
    int i;
    int compara;
    
    for( i = 1; i <= misUsuarios->num_usuarios ; ++i ){
	if( // Si se llega a la posiciOn del usuario 
	    strcmp(nva->cuenta, apt->cuenta) > 0 
	  )
	{
	    aux = apt->siguiente;
	    if( aux ){
		nvo->anterior = apt;
		nvo->siguiente = aux;
		aux->anterior = nvo;
	    }else{
		
	    }

	}else if( strcmp( apt->cuenta, nvo->cuenta ) == 0 ){
	    printf("Lo sentimos, el nombre de usuario ya está ocupado\n");
	    getchar();
	    return falso;
	}
	apt = apt->siguiente;
    }

    }else{
	if( misUsuarios->num_usuarios != 0 ){
	    misUsuarios->ultimo->siguiente = nvo;
	    nvo->anterior = misUsuarios->ultimo;
	    misUsuarios->ultimo = nvo;
	}else{
	    misUsuarios->primero = misUsuarios->ultimo = nvo;    
	}
	
	++misUsuarios->num_usuarios;
	printf("Usuario añadido correctamente\n");
	getchar();
	return verdadero;	
    }
}

// Contenido de la funciOn "eliminarUsuario"
void eliminarUsuario( Usuario *adm, ListaUsuarios *misUsuarios ){
    Usuario *aux = (Usuario *) malloc( sizeof(Usuario) );
    Usuario *elim = (Usuario *) malloc( sizeof(Usuario) );

    printf("A continuación confirme sus datos de administrador\n");
    printf("(igualmente no le basta con una su cuenta para borrar\n");
    printf("a un usuario, también requerirá la contraseña del\n");
    printf("usuario a borrar\n");
    leerDatosUsuario( aux->cuenta, aux->contrasena );

    if( 
	strcmp(adm->cuenta,aux->cuenta) != 0 || 
	strcmp(adm->contrasena,aux->contrasena) != 0
      )
    {
	free(aux);
	printf("Cuenta o contraseña incorrectas\n");
	getchar();
	getchar();
    }
    else
    {
	printf("Ahora indique el usuario que desea borrar\n");
	leerDatosUsuario( elim->cuenta, elim->contrasena );
	if( 
	    strcmp( elim->cuenta, adm->cuenta ) == 0 &&
	    strcmp( elim->contrasena, adm->contrasena ) == 0
	  )
	{
	    printf("No te puedes eliminar a ti mismo\n");
	    getchar();
	    getchar();
	    return;
	}

	int i;
	free(aux);
	aux = misUsuarios->primero;
	for( i = 1; i <= misUsuarios->num_usuarios; ++i){
	    printf("hola %d ",i);
	    if( 
		strcmp( elim->cuenta, aux->cuenta ) == 0 &&
		strcmp( elim->contrasena, aux->contrasena ) == 0
	      )
	    {
		if( 
		    misUsuarios->primero != aux &&
		    misUsuarios->ultimo != aux
		  )
		{
		    aux->anterior->siguiente = aux->siguiente;
		    aux->siguiente->anterior = aux->anterior;
		}
		else if( misUsuarios->primero == aux )
		{
		    aux->siguiente->anterior = NULL; 
		    misUsuarios->primero = misUsuarios->primero->siguiente;
		}
		else // Si es el ultimo
		{
		    aux->anterior->siguiente = NULL;
		    misUsuarios->ultimo = misUsuarios->ultimo->anterior;
		}

		free(elim);
		--misUsuarios->num_usuarios;
		escribirBD_Usuarios( misUsuarios );
		printf("Se ha eliminado un usuario correctamente\n");
		getchar();
		getchar();
		return;
	    } 
	    aux = aux->siguiente;
	}
	getchar();
	getchar();
    }
}

// Contenido de la funciOn "leerBD_Discos"
void leerBD_Discos( ListaDiscos *misDiscos ){
    FILE *ap_BD_discos = fopen(ARCHIVO_DISCOS,"r");
    Disco *nvo;

    printf("Leyendo la base de datos de discos...\n");
    getchar();

    if( ap_BD_discos ){

        while( !feof(ap_BD_discos) ){
            nvo = (Disco*) malloc( sizeof(Disco) );
            fscanf(ap_BD_discos,"%60[^\t]\t",nvo->nombre_artista);
	    fscanf(ap_BD_discos,"%100[^\t]\t",nvo->nombre_disco);
	    fscanf(ap_BD_discos,"%f\t",&nvo->precio);
	    fscanf(ap_BD_discos,"%d\t",&nvo->anio_lanzamiento);
	    fscanf(ap_BD_discos,"%d\t\n",&nvo->numero_compras);

            printf("Se ha leido un discos\n");
	    printf(
		    "Sus datos son:\n%s\n%s\n%.2f %d %d\n",
		    nvo->nombre_artista,nvo->nombre_disco,
		    nvo->precio, nvo->anio_lanzamiento,
		    nvo->numero_compras
		  );
	    agregarDisco( nvo, misDiscos );
	}

	printf("La base de datos de discos se ha leido completamente\n");
	printf("Sus datos son\n");

    }else{
	printf("No hay discos guardados\n");
    }

	
    // Se escriben los datos justo despuEs de leerlos para evitar problemas
    // causados por escribir en el archivo de discos directamente, es decir
    // para evitar:
    //  - Discos mal ordenados
    //  - Discos repetidos
    //	- Etc
    escribirBD_Discos( misDiscos );
    getchar();
}

// Contenido de la funciOn "escribirBD_Discos"
void escribirBD_Discos( ListaDiscos *misDiscos ){
    FILE *ap_BD_discos = fopen(ARCHIVO_DISCOS,"w");
    Disco *aux = misDiscos->primero;
    int i;

    for( i = 1; i <= misDiscos->num_discos; ++i){
	fprintf( 
		 ap_BD_discos,"%s\t%s\t%.2f\t%2d\t%d\t\n",
		 aux->nombre_artista,aux->nombre_disco,
		 aux->precio,aux->anio_lanzamiento,
		 aux->numero_compras
	       );
	aux = aux->siguiente;
    }
    
    fclose(ap_BD_discos);
}

// Contenido de la funciOn "mostrarDiscos"
void mostrarDiscos( void ){
    FILE *ap_BD_discos = fopen(ARCHIVO_DISCOS,"r");
    unsigned char cadena[LONG_NOMBRE_DISCO+1];
    unsigned int entero;
    float flotante;

    int i = 1;

    if( ap_BD_discos ){
	
	while( !feof(ap_BD_discos) ){
	    printf("%2d",i);
	    fscanf(ap_BD_discos,"%30[^\t]\n",cadena);
	    printf("\t%30s",cadena);
	    fscanf(ap_BD_discos,"%d\t",&entero);
	    printf("\t%10d",entero);
	    fscanf(ap_BD_discos,"%f\t\n",&flotante);
	    printf("\t%.2f\n",flotante);
	    ++i;
	}
	putchar('\n');

	fclose(ap_BD_discos);
    }else{
	printf("Parece que no hay discos registrados\n");
    }
    getchar();
    getchar();
}

// Contenido de la funciON "nuevoDiscos"
Disco * crearDisco(void){
    Disco *aux;
    
    aux = (Disco *) malloc( sizeof(Disco) );
    aux->siguiente = NULL;
    aux->anterior = NULL;

    printf("Ingrese el nombre del artista: \n");
    scanf("%60[^\n]",aux->nombre_artista);
    leerLinea();
    
    printf("Ingrese el titulo del disco: \n");
    scanf("%100[^\n]",aux->nombre_disco);
    leerLinea();

    do{
	printf("Ingrese el costo del disco: \n");	
	scanf("%f",&aux->precio);
    }while( aux->precio <= 0 );

    do{
	printf("Ingrese el año de lanzamiento del disco: \n");
	scanf("%d",&aux->anio_lanzamiento);
    }while( aux->anio_lanzamiento < 1900 );

    do{
	printf("Ingrese el número de ejemplares comprados: \n");
	scanf("%d",&aux->numero_compras);
    }while( aux->precio < 0 );
    
    return aux;
}

// Contenido de la funciON "agregarDisco"
Booleano agregarDisco( Disco * nvo, ListaDiscos *misDiscos ){
    Disco *apt = misDiscos->primero;
    Booleano existente = falso;
    int i;
    
    for( i = 1; i <= misDiscos->num_discos ; ++i ){
	if( strcmp( apt->nombre_disco, nvo->nombre_disco ) == 0 ){
	    existente = verdadero;
	}
	apt = apt->siguiente;
    }

    if( existente ){
	printf("Lo sentimos, el nombre de disco ya esta ocupado\n");	
	getchar();
	return falso;
    }else{
	if( misDiscos->num_discos != 0 ){
	    misDiscos->ultimo->siguiente = nvo;
	    nvo->anterior = misDiscos->ultimo;
	    misDiscos->ultimo = nvo;
	}else{
	    misDiscos->primero = misDiscos->ultimo = nvo;    
	}
	
	++misDiscos->num_discos;
	printf("disco añadido correctamente\n");
	getchar();
	return verdadero;	
    }
}

// Contenido de la funciOn "eliminarDiscos"
void eliminarDisco( Usuario *adm, ListaDiscos *misDiscos ){
    Usuario *usr = (Usuario *) malloc( sizeof(Usuario) );
    Disco *elim = (Disco *) malloc( sizeof(Disco) );
    Disco *aux;

    printf("A continuación confirme sus datos de administrador\n");
    leerDatosUsuario( usr->cuenta, usr->contrasena );

    if( 
	strcmp(adm->cuenta,usr->cuenta) != 0 || 
	strcmp(adm->contrasena,usr->contrasena) != 0
      )
    {
	printf("Cuenta o contraseña incorrectas\n");
	free(usr);
	getchar();
	getchar();
    }
    else
    {
	printf("Ahora indique el disco que desea borrar\n");
	scanf("%100[^\n]",elim->nombre_disco);

	int i;
	free(usr);
	aux = misDiscos->primero;
	for( i = 1; i <= misDiscos->num_discos; ++i){
	    if( strcmp( elim->nombre_disco, aux->nombre_disco ) == 0 ){
		if( 
		    misDiscos->primero != aux &&
		    misDiscos->ultimo != aux
		  )
		{
		    aux->anterior->siguiente = aux->siguiente;
		    aux->siguiente->anterior = aux->anterior;
		}
		else if( misDiscos->num_discos == 0 )
		{
		    misDiscos = NULL;
		    misDiscos->ultimo = NULL;
		}
		else if( misDiscos->primero == aux )
		{
		    aux->siguiente->anterior = NULL; 
		    misDiscos->primero = misDiscos->primero->siguiente;
		}
		else // Si es el ultimo
		{
		    aux->anterior->siguiente = NULL;
		    misDiscos->ultimo = aux->anterior;
		}

		free(elim);
		--misDiscos->num_discos;
		escribirBD_Discos( misDiscos );
		printf("Se ha eliminado un disco correctamente\n");
		getchar();
		getchar();
		return;
	    } 
	    aux = aux->siguiente;
	}
	getchar();
	getchar();
    }
}

// Contenido de la funciOn "leerLinea"
void leerLinea( void ){
    char cadena[100];
    scanf("%[^\n]",cadena);
}
