/**
 * MartInez Ortiz SaUl Axel
 * PROTECO generaciOn 33, curso de Bases de Datos
 * Tarea n: RealizaciOn de una base de datos sencilla en c
 **/

// Incluir informaciOn requerida
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

#define ARCHIVO_USUARIOS "mis_usuarios.txt"
#define ARCHIVO_PRODUCTOS "mis_productos.txt"

#define z(s,c) printf("%s %s\n%s %s\n",s->cuenta,c->cuenta,s->contrasena,c->contrasena)
// Estructura que simula booleanos
enum booleano { falso, verdadero };
typedef enum booleano Booleano;

// Estructura para los usuarios
#define LONGITUD_CUENTA 30
#define LONGITUD_CONTRASENA 16
#define MAX_USUARIOS 5
struct usuario{
	unsigned char cuenta[LONGITUD_CUENTA+1];
	unsigned char contrasena[LONGITUD_CONTRASENA+1];
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

// Estructura para los productos
#define LONG_NOMBRE_PRODUCTO 30
#define MAX_PRODUCTOS 20
struct producto{
	unsigned char nombre[LONG_NOMBRE_PRODUCTO+1];
	int cantidad;
	float precio;
	struct producto *anterior;
	struct producto *siguiente;
};
typedef struct producto Producto;

struct listaProductos{
	Producto *primero;
	Producto *ultimo;
	unsigned short num_productos;
};
typedef struct listaProductos ListaProductos;

// Prototipos de funciOn

/**
 * FunciOn menu: vacio -> vacio
 * DescripciOn: Desglosa las opciones para que el 
 *  usuario sepa de donde elejir
 **/
void menu( void );

/**
 * FunciOn establecerUsuariosIniciales: apuntador a cadena,
				        estructura ListaUsuarios -> vacio
 * DescripciOn: Permite al usuario ingresar usuarios 
 * iniciales antes de solicitar datos para el ingreso
 **/
void establecerUsuariosIniciales( Usuario *usr, ListaUsuarios *misUsuarios );

/**
 * FunciOn leerBD_Usuarios: estructura ListaUsuarios -> vacio
 * DescripciOn: Lee la lista de usuarios del archivo
 *  base de datos y los guarda en la lista de usuarios recibida
 **/
void leerBD_Usuarios( ListaUsuarios *misUsuarios );

/**
 * FunciOn escribirBD_Usuarios: estructura ListaUsuarios -> vacio
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
 * FunciOn comprobarUsuario: estructura Usuario,
                             estructura ListaUsuarios -> estructura Booleano
 * DescripciOn: Pide al usuario sus datos y los comprueba con la
 *  base de datos actual para devolver si el usuario se encuentra
 *  o no registrado
 **/
Booleano comprobarUsuario( Usuario *usr, ListaUsuarios *misUsuarios);
 
/**
 * FunciOn crearUsuario: vacio -> apuntador a Usuario
 * DescripciOn: Crea un usuario nuevo por medio de memoria dinAmica
 *  e inicializa sus datos con informaciOn pedida desde la consola 
 **/
Usuario * crearUsuario( void );

/**
 * FunciOn agregarUsuario: apuntador estructura Usuario, 
 * 			   estructura ListaUsuarios ->  
 *			   enumeraciOn Booleano
 * DescripciOn: Recibe un usuario nuevo y lo almacena en la lista 
 *  especificada
 **/
Booleano agregarUsuario( Usuario *usr, ListaUsuarios *misUsuarios );

/**
 * FunciOn eliminarUsuario: estructura Usuario,
 * 			    estructura ListaUsuarios -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida
 *  sobre las cuentas de los usuarios y en la primera coincidencia
 *  eliminarA el usuario actual de la lista y de la memoria 
 *  regresando a la funciOn que lo llamo verdadero, o falso al no
 *  encontrar ninguna concidencia
 **/
void eliminarUsuario( Usuario *adm, ListaUsuarios *misUsuarios );

/**
 * FunciOn leerBD_Productos: estructura ListaProductos -> vacio
 * DescripciOn: Consulta el archivo base de datos de productos
 *  y guarda su informaciOn en una lista de usuarios
 **/
void leerBD_Productos( ListaProductos *misProductos );

/**
 * FunciOn escribirBD_Productos: esctuctura ListaProductos -> vacio
 * DescripciOn: Escribe los datos de la lista de productos en 
 *  el archivo de base de datos de productos sobreescribiendola
 *  en cada ocaciOn
 **/
void escribirBD_Productos( ListaProductos *misProductos );

/**
 * FunciOn mostrarProductos: vacio -> vacio
 * DescripciOn: Imprime en pantalla los datos de la base de 
 *  datos de los productos
 **/
void mostrarProductos( void );

/**
 * FunciOn crearProducto: vacio -> apuntador a Producto
 * DescripciOn: Se encarga de instanciar un nuevo producto por 
 *  medio de memoria dinAmica e inicializado con datos pedidos
 *  por consola para al final regresar una referencia al mismo.
 **/
Producto * crearProducto(void);

/**
 * FunciOn agregarProducto: apuntador a estrucutra Producto,
 *   	         	    estructura ListaProductos 
 *			    -> enumeraciOn Booleano 
 * DescripciOn: Recibe un nuevo producto y lo almacena en la
 *  lista especificada como argumento
 **/
Booleano agregarProducto( Producto * nvo, ListaProductos *misProductos);

/**
 * FunciOn eliminarProducto: apuntador a cadena,
 *                           estructura ListaProductos -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida en 
 *  comparaciOn con los nombres de los productos, borrando el producto
 *  coincidente y regresando verdadero en el proceso, o de lo contrario 
 *  regresando falso al no encontrar coincidencias.
 **/
void eliminarProducto( Usuario *adm, ListaProductos *misProductos );

/**
 * FunciOn leerLinea: vacio -> vacio
 * DescripciOn: Limpia el buffer leyendo una linea
 **/
void leerLinea( void );

int main(void){
    ListaProductos misProductos = { NULL, NULL, 0 };
    ListaUsuarios misUsuarios = { NULL, NULL, 0 };
    short condicion = 0;
    Usuario administrador = { {0}, {0}, NULL, NULL };
    
    system(CLEAR);
    // Recuperar los datos de la base de datos
    leerBD_Usuarios( &misUsuarios );
    leerBD_Productos( &misProductos );
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
		mostrarProductos();
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
		if( misProductos.num_productos < MAX_PRODUCTOS ){
		    if( agregarProducto( crearProducto(), &misProductos ) ){
			printf("Hay un total de %d producto(s)\n",
				misProductos.num_productos);
			escribirBD_Productos( &misProductos );
			}
		}else{
			printf("Lo sentimos, se ha alcanzado el máximo número\n");
			printf("de productos\n");
			getchar();
		}
		getchar();
	    break;

	    case 6:
		if( misProductos.num_productos >= 1 ){
		    eliminarProducto( &administrador, &misProductos );
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
    printf("\t 2) Mostrar productos guardados\n");
    printf("\t 3) Agregar usuario\n");
    printf("\t 4) Eliminar usuario\n");
    printf("\t 5) Agregar producto\n");
    printf("\t 6) Eliminar producto\n");
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
	if( comprobarUsuario( usr, misUsuarios ) == falso ){

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

	fclose(ap_BD_usuarios);
    }else{
	printf("No hay usuarios guardados\n");
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

// Contenido de la funciOn "comprobarUsuario"
Booleano comprobarUsuario( Usuario *usr, ListaUsuarios *misUsuarios ){
    Usuario *aux = misUsuarios->primero;
    int i;

    for( i = 1; i <= misUsuarios->num_usuarios ; ++i ){
	printf("Comparando con el usuario %d\n", i);
	//printf("Las cuentas son: %s %s\n", usr->cuenta, aux->cuenta);
	//printf("El resultado es: %d\n", strcmp(usr->cuenta, aux->cuenta) );
	
	//printf("Las contraseñas son: %s %s\n", 
	//	usr->contrasena,
	//	aux->contrasena);
	//printf("El resultado es: %d\n", 
    	//	strcmp(usr->contrasena, aux->contrasena) );
	if( strcmp(usr->contrasena, aux->contrasena) ){
	    printf("No hay correspondencia\n");
	}else{
	    printf("Hay correspondencia\n");    
	}

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
    Booleano existente = falso;
    int i;
    
    for( i = 1; i <= misUsuarios->num_usuarios ; ++i ){
	if( strcmp( apt->cuenta, nvo->cuenta ) == 0 ){
	    existente = verdadero;
	}
	apt = apt->siguiente;
    }

    if( existente ){
	printf("Lo sentimos, el nombre de usuario ya esta ocupado\n");	
	getchar();
	return falso;
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

// Contenido de la funciOn "leerBD_Productos"
void leerBD_Productos( ListaProductos *misProductos ){
    FILE *ap_BD_productos = fopen(ARCHIVO_PRODUCTOS,"r");
    Producto *nvo;

    printf("Leyendo la base de datos de productos...\n");
    getchar();

    if( ap_BD_productos ){

        while( !feof(ap_BD_productos) ){
            nvo = (Producto*) malloc( sizeof(Producto) );
            fscanf(ap_BD_productos,"%30[^\t]\t",nvo->nombre);
	    fscanf(ap_BD_productos,"%d\t",&nvo->cantidad);
	    fscanf(ap_BD_productos,"%f\t\n",&nvo->precio);

            printf("Se ha leido un producto\n");
	    printf("Sus datos son %s %d %.2f\n",nvo->nombre,nvo->cantidad,nvo->precio);
	    agregarProducto( nvo, misProductos );
	}

	printf("La base de datos de productos se ha leido completamente\n");
	printf("Sus datos son\n");

	int i;
	Producto *aux = misProductos->primero;
	for( i = 1; i <= misProductos->num_productos; ++i ){
	    printf("%d %s %d %.2f\n", i, aux->nombre, aux->cantidad, aux->precio); 
	    aux = aux->siguiente;
	}

	fclose(ap_BD_productos);
    }else{
	printf("No hay productos guardados\n");
    }

    escribirBD_Productos( misProductos );
    getchar();
}

// Contenido de la funciOn "escribirBD_Productos"
void escribirBD_Productos( ListaProductos *misProductos ){
    FILE *ap_BD_productos = fopen(ARCHIVO_PRODUCTOS,"w");
    Producto *aux = misProductos->primero;
    int i;

    for( i = 1; i <= misProductos->num_productos; ++i){
	fprintf(ap_BD_productos,"%s\t%d\t%.2f\t\n",aux->nombre,aux->cantidad, aux->precio);
	aux = aux->siguiente;
    }
    
    fclose(ap_BD_productos);
}

// Contenido de la funciOn "mostrarProductos"
void mostrarProductos( void ){
    FILE *ap_BD_productos = fopen(ARCHIVO_PRODUCTOS,"r");
    unsigned char cadena[LONG_NOMBRE_PRODUCTO+1];
    unsigned int entero;
    float flotante;

    int i = 1;

    if( ap_BD_productos ){
	
	while( !feof(ap_BD_productos) ){
	    printf("%2d",i);
	    fscanf(ap_BD_productos,"%30[^\t]\n",cadena);
	    printf("\t%30s",cadena);
	    fscanf(ap_BD_productos,"%d\t",&entero);
	    printf("\t%10d",entero);
	    fscanf(ap_BD_productos,"%f\t\n",&flotante);
	    printf("\t%.2f\n",flotante);
	    ++i;
	}
	putchar('\n');

	fclose(ap_BD_productos);
    }else{
	printf("Parece que no hay productos registrados\n");
    }
    getchar();
    getchar();
}

// Contenido de la funciON "nuevoProducto"
Producto * crearProducto(void){
    Producto *aux;
    
    aux = (Producto *) malloc( sizeof(Producto) );
    aux->siguiente = NULL;
    aux->anterior = NULL;

    printf("Ingrese el nombre: \n");
    scanf("%30s",aux->nombre);
    leerLinea();
    fflush(stdin);
    
    do{
	printf("Ingrese la cantidad de ejemplares del producto\n");
	scanf("%d",&aux->cantidad);
    }while( aux->cantidad < 0 );

    do{
	printf("Ingrese el costo del producto\n");
	scanf("%f",&aux->precio);
	fflush(stdin);
    }while( aux->precio <= 0 );
    return aux;
}

// Contenido de la funciON "agregarProducto"
Booleano agregarProducto( Producto * nvo, ListaProductos *misProductos){
    Producto *apt = misProductos->primero;
    Booleano existente = falso;
    int i;
    
    for( i = 1; i <= misProductos->num_productos ; ++i ){
	if( strcmp( apt->nombre, nvo->nombre ) == 0 ){
	    existente = verdadero;
	}
	apt = apt->siguiente;
    }

    if( existente ){
	printf("Lo sentimos, el nombre de producto ya esta ocupado\n");	
	getchar();
	return falso;
    }else{
	if( misProductos->num_productos != 0 ){
	    misProductos->ultimo->siguiente = nvo;
	    nvo->anterior = misProductos->ultimo;
	    misProductos->ultimo = nvo;
	}else{
	    misProductos->primero = misProductos->ultimo = nvo;    
	}
	
	++misProductos->num_productos;
	printf("producto añadido correctamente\n");
	getchar();
	return verdadero;	
    }
}

// Contenido de la funciOn "eliminarProducto"
void eliminarProducto( Usuario *adm, ListaProductos *misProductos ){
    Usuario *usr = (Usuario *) malloc( sizeof(Usuario) );
    Producto *elim = (Producto *) malloc( sizeof(Producto) );
    Producto *aux;

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
	printf("Ahora indique el producto que desea borrar\n");
	scanf("%30s",elim->nombre);

	int i;
	free(usr);
	aux = misProductos->primero;
	for( i = 1; i <= misProductos->num_productos; ++i){
	    if( strcmp( elim->nombre, aux->nombre ) == 0 ){
		if( 
		    misProductos->primero != aux &&
		    misProductos->ultimo != aux
		  )
		{
		    aux->anterior->siguiente = aux->siguiente;
		    aux->siguiente->anterior = aux->anterior;
		}
		else if( misProductos->num_productos == 0 )
		{
		    misProductos->primero = NULL;
		    misProductos->ultimo = NULL;
		}
		else if( misProductos->primero == aux )
		{
		    aux->siguiente->anterior = NULL; 
		    misProductos->primero = misProductos->primero->siguiente;
		}
		else // Si es el ultimo
		{
		    aux->anterior->siguiente = NULL;
		    misProductos->ultimo = misProductos->ultimo->anterior;
		}

		free(elim);
		--misProductos->num_productos;
		escribirBD_Productos( misProductos );
		printf("Se ha eliminado un producto correctamente\n");
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
