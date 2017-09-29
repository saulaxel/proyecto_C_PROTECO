/**
 * Universidad Nacional Autonoma de MExico
 * IngenierIa en computaciOn
 * Ingeniero MartInez Ortiz SaUl Axel
 * Base de datos de tienda
 * PROTECO, generación 33
 * Fecha: 30/09/16
 * DescripciOn: Sistema para el manejo de las bases de datos de
 *  una tienda de discos compactos ya sea por el administrador
 *  o por los vendedores.
 **/

// InclusiOn de informaciOn requerida
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#   define CLEAR "cls"
#   include <locale.h>
    setlocale(LC_ALL, "Spanish_Mexico");
#elif __unix__
#   define CLEAR "clear"
#else
#   define CLEAR "" // No pos si asI esta la cosa mejor no hagas nada
#endif // _WIN32

#define LONG_NOMBRE_PERSONA 60
#define ARCHIVO_USUARIOS "mis_usuarios.txt"
#define ARCHIVO_DISCOS "mis_discos.txt"

#ifndef NDEBUG
#   define z(s, c)                                                       \
    printf("%s %s\n%s %s\n",s->cuenta,c->cuenta,s->contrasena,c->contrasena)
#else
#   define z(s, c)
#endif

// Estructura que simula booleanos
typedef enum { falso, verdadero } Booleano;

// Estructura para los usuarios
#define NOM_ADMIN "admin"
#define CONTRA_ADMIN "admin"
#define LONGITUD_CUENTA 30
#define LONGITUD_CONTRASENA 16
#define MAX_USUARIOS 100

typedef struct usuario Usuario;
struct usuario
{
    unsigned char cuenta[LONGITUD_CUENTA+1];
    unsigned char contrasena[LONGITUD_CONTRASENA+1];
    unsigned char nombre_usuario[LONG_NOMBRE_PERSONA+1];
    int           edad;
    int           numero_compras;

    struct usuario *siguiente;
    struct usuario *anterior;
};

static Usuario admin = {
    .cuenta         = NOM_ADMIN,
    .contrasena     = CONTRA_ADMIN,
    .nombre_usuario = "Martínez Ortiz Saúl Axel",
    .edad           = 20,
    .numero_compras = 0,
    .siguiente      = NULL,
    .anterior       = NULL
};

typedef struct listaUsuarios ListaUsuarios;
struct listaUsuarios
{
    Usuario *primero;
    Usuario *ultimo;

    unsigned short num_usuarios;
};

// Estructura para los discos
#define LONG_NOMBRE_DISCO 100
#define MAX_DISCOS 1000

typedef struct disco Disco;
struct disco
{
    unsigned char nombre_artista[LONG_NOMBRE_PERSONA+1];
    unsigned char nombre_disco[LONG_NOMBRE_DISCO+1];
    float         precio;
    int           anio_lanzamiento;
    int           numero_compras;

    struct disco *anterior;
    struct disco *siguiente;
};

typedef struct listaDiscos ListaDiscos;
struct listaDiscos
{
    Disco *primero;
    Disco *ultimo;

    unsigned short num_discos;
};

// Prototipos de funciOn

/**
 * FunciOn menu: apuntador a estructura Usuario -> vacio
 * DescripciOn: Desglosa las opciones para que el
 *  usuario sepa de donde elejir
 **/
void menu(Usuario *usr);

/**
 * FunciOn establecerUsuario: apuntador a cadena,
 apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Manda a llamar a la funciOn que lee los usuarios de la
 * base de datos. En caso de no haber base de datos este la crea
 * con los datos de administrador.
 **/
Usuario * establecerUsuario(ListaUsuarios *misUsuarios);

/**
 * FunciOn leerBD_Usuarios: apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Lee la lista de usuarios del archivo
 *  base de datos y los guarda en la lista de usuarios recibida
 **/
void leerBD_Usuarios(ListaUsuarios *misUsuarios);

/**
 * FunciOn escribirBD_Usuarios: apuntador estructura ListaUsuarios -> vacio
 * DescripciOn: Escribe los datos de ListaUsuarios en el archivo
 *  usado como base de datos
 **/
void escribirBD_Usuarios(ListaUsuarios *misUsuarios);

/**
 * FunciOn mostrarUsuarios: vacio -> vacio
 * DescipciOn: Imprime a pantalla los datos del archivo que representa
 *  nuestra base de datos de usuarios
 **/
void mostrarUsuarios(void);

/**
 * FunciOn mostrarUsuariosInversa: apuntador a estructura ListaUsuarios -> vacio
 * Descripción: Imprime a pantalla los datos de los usuarios en orden
 *  inverso al alfabEtico
 */
void mostrarUsuariosInversa(ListaUsuarios *misUsuarios);

/**
 * FunciOn verPerfil: apuntador a estructura Usuario -> vacio
 * DescripciOn: Despliega los datos del usuario actual
 */
void verPerfil(Usuario *usr);

/**
 * FunciOn modificarInfo: apuntador a estructura Usuario -> vacio
 * DescripciOn: Permite al usuario cambiar alguno de sus datos
 */
void modificarInfo(Usuario *usr);

/**
 * FunciOn cambiarUsuario: estructura Usuario, estructura ListaUsuarios -> vacio
 * DescripciOn: Permite al usuario intentar cambiarse a otro
 *  usuario registrado.
 **/
void cambiarUsuario(Usuario *usr, ListaUsuarios *misUsuarios);

/**
 * FunciOn leerDatosUsuario: apuntador a cadena,apuntador a cadena -> vacio
 * DescipciOn: Recibe dos apuntadores a cadena (usr y contra) en los
 *  que almacenarA los datos que pide desde consola
 **/
void leerDatosUsuario(unsigned char *usr, unsigned char *contra);

/**
 * FunciOn existeUsuario: estructura Usuario,
 estructura ListaUsuarios -> estructura Booleano
 * DescripciOn: Pide al usuario sus datos y los comprueba con la
 *  base de datos actual para devolver si el usuario se encuentra
 *  o no registrado
 **/
Booleano existeUsuario(Usuario *usr, ListaUsuarios *misUsuarios);

/**
 * FunciOn crearUsuario: vacio -> apuntador a Usuario
 * DescripciOn: Crea un usuario nuevo por medio de memoria dinAmica
 *  e inicializa sus datos con informaciOn pedida desde la consola
 **/
Usuario * crearUsuario(void);

/**
 * FunciOn agregarUsuario: apuntador a estructura Usuario,
 *             apuntador a estructura ListaUsuarios ->
 *             enumeraciOn Booleano
 * DescripciOn: Recibe un usuario nuevo y lo almacena en la lista
 *  de usuarios si no existe su cuenta
 **/
Booleano agregarUsuario(Usuario *usr, ListaUsuarios *misUsuarios);

/**
 * FunciOn eliminarUsuario: apuntador a estructura Usuario,
 *              apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida
 *  sobre las cuentas de los usuarios y en la primera coincidencia
 *  eliminarA el usuario actual de la lista y de la memoria
 *  regresando a la funciOn que lo llamo verdadero, o falso al no
 *  encontrar ninguna concidencia
 + PS: No elimina al administrador(por ello lo recibe)
 **/
void eliminarUsuario(Usuario *adm, ListaUsuarios *misUsuarios);

/**
 * FunciOn leerBD_Discos: estructura ListaDiscos -> vacio
 * DescripciOn: Consulta el archivo base de datos de discos
 *  y guarda su informaciOn en una lista de usuarios
 **/
void leerBD_Discos(ListaDiscos *misDiscos);

/**
 * FunciOn escribirBD_Discos: esctuctura ListaDiscos -> vacio
 * DescripciOn: Escribe los datos de la lista de discos en
 *  el archivo de base de datos de discos sobreescribiendola
 *  en cada ocaciOn
 **/
void escribirBD_Discos(ListaDiscos *misDiscos);

/**
 * FunciOn mostrarDiscos: vacio -> vacio
 * DescripciOn: Imprime en pantalla los datos de la base de
 *  datos de los discos
 **/
void mostrarDiscos(void);

/**
 * FunciOn mostrarDiscosInversa: apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Imprime en pantalla los discos en orden
 *  inverso al alfabetico.
 */
void mostrarDiscosInversa(ListaDiscos *misDiscos);

/**
 * FunciOn buscarDisco: apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Imprime los datos de un disco buscado por
 *  medio de su nombre.
 */
void buscarDisco(ListaDiscos *misDiscos);

/**
 * FunciOn comprarDisco: apuntador a usuarios,
 *  apuntador a estructura ListaUsuarios -> vacio
 * DescripciOn: Permite al usuario comprar un disco
 */
void comprarDisco(Usuario *usr, ListaDiscos *misDiscos);

/**
 * FunciOn editarDisco: apuntador a estructura ListaDiscos, vacio
 * DescripciON: Permite al usuario modificar un dato de un disco
 */
void editarDisco(ListaDiscos *misDiscos);

/**
 * FunciOn crearDisco: vacio -> apuntador a Disco
 * DescripciOn: Se encarga de instanciar un nuevo disco por
 *  medio de memoria dinAmica e inicializado con datos pedidos
 *  por consola para al final regresar una referencia al mismo.
 **/
Disco * crearDisco(void);

/**
 * FunciOn agregarDisco: apuntador a estrucutra Disco,
 *              estructura ListaDiscos -> enumeraciOn Booleano
 * DescripciOn: Recibe un nuevo disco y lo almacena en la
 *  lista especificada como argumento
 **/
Booleano agregarDisco(Disco * nvo, ListaDiscos *misDiscos);

/**
 * FunciOn eliminarDisco: apuntador a cadena,
 *                           estructura ListaDiscos -> vacio
 * DescripciOn: Hace una busqueda lineal de la cadena recibida en
 *  comparaciOn con los nombres de los discos, borrando el disco
 *  coincidente y regresando verdadero en el proceso, o de lo contrario
 *  regresando falso al no encontrar coincidencias.
 **/
void eliminarDisco(Usuario *adm, ListaDiscos *misDiscos);

/**
 * FunciOn leerLinea: cadena -> vacio
 * DescripciOn: Lee una lInea y la guarda en el arreglo de
 *  caracteres cuya direcciOn se recibe como parAmetro. Si el
 *  argumento es NULL, solamente limpia el buffer
 **/
void leerLinea(char * buff);

int main(void)
{
    ListaDiscos misDiscos = { NULL, NULL, 0 };
    ListaUsuarios misUsuarios = { NULL, NULL, 0 };
    short opcion = 0;
    Usuario *usr;

    system(CLEAR);
    // Recuperar los datos de la base de datos
    leerBD_Usuarios(&misUsuarios);
    leerBD_Discos(&misDiscos);
    printf("\n\t_____________________________________________\n");
    printf("\tLas bases de datos se han leido correctamente\n\n");
    // Si la base de datos de usuarios esta vacia --> La aplicacion no
    // ha sido usada
    usr = establecerUsuario(&misUsuarios);

    do {
        system(CLEAR);
        printf("Usuario: %s \n\n", usr->cuenta);
        short opcion_maxima;

        if ( strcmp(usr->cuenta, admin.cuenta) == 0 )
        {
            opcion_maxima = 16;
        }
        else
        {
            opcion_maxima = 7;
        }

        printf("Ingrese la opción deseada\n");
        menu(usr);

        do {
            printf("> ");
            scanf("%hd",&opcion);
            leerLinea(NULL);
        } while ( opcion < 1 || opcion > opcion_maxima );

        if ( opcion == opcion_maxima )
            opcion = 16;

        switch ( opcion )
        {
            case 1:
                mostrarDiscos();
                break;

            case 2:
                buscarDisco(&misDiscos);
                break;

            case 3:
                comprarDisco(usr, &misDiscos);
                break;

            case 4:
                verPerfil(usr);
                break;

            case 5:
                modificarInfo(usr);
                escribirBD_Usuarios(&misUsuarios);
                break;

            case 6:
                cambiarUsuario(usr, &misUsuarios);
                break;

            case 7:
                mostrarUsuarios();
                break;

            case 8:
                mostrarUsuariosInversa(&misUsuarios);
                break;

            case 9:
                mostrarDiscos();
                break;

            case 10:
                mostrarDiscosInversa(&misDiscos);
                break;

            case 11:
                if ( misUsuarios.num_usuarios < MAX_USUARIOS )
                {
                    if ( agregarUsuario(crearUsuario(), &misUsuarios) )
                    {
                        printf("Hay un total de %d usuario(s)\n",
                                misUsuarios.num_usuarios);
                        escribirBD_Usuarios(&misUsuarios);
                    }
                }
                else
                {
                    printf("Lo sentimos, se ha alcanzado el máximo número\n");
                    printf("de usuarios\n");
                }

                leerLinea(NULL);
                break;

            case 12:
                if ( misUsuarios.num_usuarios >= 1 )
                    eliminarUsuario(usr, &misUsuarios);
                break;

            case 13:
                if ( misDiscos.num_discos < MAX_DISCOS )
                {
                    if ( agregarDisco(crearDisco(), &misDiscos) )
                    {
                        printf("Hay un total de %d disco(s)\n",
                                misDiscos.num_discos);
                        escribirBD_Discos(&misDiscos);
                    }
                }
                else
                {
                    printf("Lo sentimos, se ha alcanzado el máximo número\n");
                    printf("de discos\n");
                }
                leerLinea(NULL);
                break;

            case 14:
                if ( misDiscos.num_discos >= 1 )
                    eliminarDisco(usr, &misDiscos);
                break;

            case 15:
                editarDisco(&misDiscos);
                break;

            case 16:
                printf("Esperamos volver a verl@ pronto\n");
                leerLinea(NULL);
                escribirBD_Usuarios(&misUsuarios);
                escribirBD_Discos(&misDiscos);
                leerLinea(NULL);
        }
    } while ( opcion != 16 );


    leerLinea(NULL);
    return 0;
}

// Contenido de la funciOn "menu"
void menu(Usuario *usr)
{
    printf("\t 1) Mostrar discos\n");
    printf("\t 2) Buscar disco\n");
    printf("\t 3) Comprar disco\n");
    printf("\t 4) Ver perfil de usuario\n");
    printf("\t 5) Modificar info\n");
    printf("\t 6) Cambiar de usuario\n");
    if ( strcmp(usr->cuenta, admin.cuenta) == 0 )
    {
        printf("\t 7) Mostrar usuarios ordenados\n");
        printf("\t 8) Mostrar usuarios a la inversa\n");
        printf("\t 9) Mostrar discos ordenados\n");
        printf("\t 10) Mostrar discos a la inversa\n");
        printf("\t 11) Agregar usuario\n");
        printf("\t 12) Eliminar usuario\n");
        printf("\t 13) Agregar discos\n");
        printf("\t 14) Eliminar disco\n");
        printf("\t 15) Editar disco\n");
        printf("\t 16) Salir\n");
    }
    else
    {
        printf("\t 7) Salír\n");
    }
}

// Contenido de la funciOn "establecerUsuario"
Usuario * establecerUsuario(ListaUsuarios *misUsuarios)
{
    Usuario *usr;
    Booleano datosCorrectos = falso;
    int opcion;
    unsigned char cuenta[60], contrasena[60];


    while ( !datosCorrectos )
    {
        opcion = -1;
        printf("Seleccione una opción:\n");
        printf("\t1. Ingresar con una cuenta existente.\n");
        printf("\t2. Salir.\n");

        while ( opcion < 1 || opcion > 2 )
        {
            printf("> ");
            scanf("%d", &opcion);
            leerLinea(NULL);
        }

        if ( opcion == 1 )
        {
            printf("Ingrese sus datos de usuario:\n");
            leerDatosUsuario(cuenta, contrasena);
            usr = (Usuario *) malloc(sizeof(Usuario));
            strcpy(usr->cuenta, cuenta);
            strcpy(usr->contrasena, contrasena);

            if ( existeUsuario(usr, misUsuarios) )
            {
                datosCorrectos = verdadero;
                free(usr);
                Booleano a = falso;
                usr = misUsuarios->primero;

                for (int i = 1; i<=misUsuarios->num_usuarios && !a; ++i)
                {
                    if ( strcmp(cuenta, usr->cuenta) == 0 )
                    {
                        a = verdadero;
                    }
                    else
                    {
                        usr = usr->siguiente;
                    }
                }
                printf("Bienvenid@ %s\n",usr->cuenta);
            }
            else
            {
                printf("Cuenta o contraseña incorrectas\n");
            }
        }
        else
        {
            printf("Vuelva pronto\n");
            leerLinea(NULL);
            exit(0);
        }
    }

    leerLinea(NULL);
    return usr;

}

// Contenido de la funciOn "leerBD_Usuarios"
void leerBD_Usuarios(ListaUsuarios *misUsuarios)
{
    FILE *ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"r");
    Usuario *nvo;

    printf("Leyendo la base de datos de usuarios...\n");
    leerLinea(NULL);

    if ( ap_BD_usuarios )
    {

        while( !feof(ap_BD_usuarios) )
        {
            nvo = (Usuario*) malloc(sizeof(Usuario));
            fscanf(ap_BD_usuarios,"%[^\t]\t",nvo->cuenta);
            fscanf(ap_BD_usuarios,"%[^\t]\t",nvo->contrasena);
            fscanf(ap_BD_usuarios,"%[^\t]\t",nvo->nombre_usuario);
            fscanf(ap_BD_usuarios,"%d\t",&(nvo->edad));
            fscanf(ap_BD_usuarios,"%d\t\n",&(nvo->numero_compras));
            //printf("Se ha leido un usuario\n");
            //printf("Sus datos son %s %s\n",nvo->cuenta,nvo->contrasena);
            agregarUsuario(nvo, misUsuarios);
        }

        //printf("La base de datos se  de usuarios ha leido completamente\n");
        //printf("Sus datos son\n");

        //int i;
        //Usuario *aux = misUsuarios->primero;
        //for( i = 1; i <= misUsuarios->num_usuarios; ++i ){
        //printf("%d %s %s\n", i, aux->cuenta, aux->contrasena);
        //aux = aux->siguiente;
        //}

        fclose(ap_BD_usuarios);
    }
    else
    {
        agregarUsuario(&admin,misUsuarios);
    }

    // Se escriben los datos justo despuEs de leerlos para evitar problemas
    // causados por escribir en el archivo de usuarios directamente, es decir
    // para evitar:
    //  - Usuarios mal ordenados
    //  - Usuarios repetidos
    //  - etc
    escribirBD_Usuarios(misUsuarios);
}

// Contenido de la funciON "escribirBD_Usuarios"
void escribirBD_Usuarios(ListaUsuarios *misUsuarios)
{
    FILE *ap_BD_usuarios;
    Usuario *aux = misUsuarios->primero;

    if (aux != NULL)
    {
        ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"w");
        for (int i = 1; i <= misUsuarios->num_usuarios; ++i)
        {
            fprintf(ap_BD_usuarios,"%s\t%s\t%s\t%d\t%d\t\n",
                    aux->cuenta,aux->contrasena,
                    aux->nombre_usuario,
                    aux->edad, aux->numero_compras);
            aux = aux->siguiente;
        }

        fclose(ap_BD_usuarios);
    }
}

// Contenido de la funciOn "mostrarUsuarios"
void mostrarUsuarios(void)
{
    FILE *ap_BD_usuarios = fopen(ARCHIVO_USUARIOS,"r");
    unsigned char cadena[LONGITUD_CUENTA+1];
    int entero;
    int i = 1;

    if ( ap_BD_usuarios )
    {

        while ( !feof(ap_BD_usuarios) )
        {
            printf("%2d",i);
            fscanf(ap_BD_usuarios,"%[^\t]\t",cadena);
            printf("\tUsuario: %s\n",cadena);
            fscanf(ap_BD_usuarios,"%[^\t]\t",cadena);
            printf("\tContraseña: %s\n",cadena);
            fscanf(ap_BD_usuarios,"%[^\t]\t",cadena);
            printf("\tNombre de usuario: %s\n",cadena);
            fscanf(ap_BD_usuarios,"%d\t",&entero);
            printf("\tEdad: %d\n",entero);
            fscanf(ap_BD_usuarios,"%d\t\n",&entero);
            printf("\tDiscos comprados: %d\t\n",entero);
            ++i;
        }

        fclose(ap_BD_usuarios);
    }
    else
    {
        printf("Parece que no hay usuarios registrados\n");
    }
    leerLinea(NULL);
}

// Contenido de la funciON "mostrarUsuariosInversa"
void mostrarUsuariosInversa(ListaUsuarios *misUsuarios)
{
    Usuario *apt;
    int i,j;
    j = misUsuarios->num_usuarios;
    apt = misUsuarios->ultimo;
    if ( apt )
    {
        for (i = j; i >= 1; --i)
        {
            printf("%2d",j - i + 1);
            printf("\tUsuario: %s\n",apt->cuenta);
            printf("\tContraseña: %s\n",apt->contrasena);
            printf("\tNombre de usuario: %s\n",apt->nombre_usuario);
            printf("\tEdad: %d\n",apt->edad);
            printf("\tDiscos comprados: %d\t\n",apt->numero_compras);
            apt = apt->anterior;
        }
    }
    else
    {
        printf("Parece que no hay usuarios registrados\n");
    }
    leerLinea(NULL);
}

// Contenido de la funciOn "verPerfil"
void verPerfil(Usuario *usr)
{
    printf("\tUsuario: %s\n",usr->cuenta);
    printf("\tContraseña: %s\n",usr->contrasena);
    printf("\tNombre de usuario: %s\n",usr->nombre_usuario);
    printf("\tEdad: %d\n",usr->edad);
    printf("\tDiscos comprados: %d\t\n",usr->numero_compras);
    leerLinea(NULL);
}

// Contenido de la funciOn "modificarInfo"
void modificarInfo(Usuario *usr)
{
    short opcion;
    if ( strcmp(usr->cuenta, admin.cuenta) == 0 )
    {
        printf("No puedes modificar los datos del administrador\n");
        leerLinea(NULL);
        return;
    }

    printf("Elija la información que desea modificar\n");
    printf("\t1) Contraseña\n");
    printf("\t2) Nombre\n");
    printf("\t3) Edad\n");

    do {
        scanf("%hd",&opcion);
        leerLinea(NULL);
    } while( opcion < 1 || opcion > 3 );
    leerLinea(NULL);

    if ( opcion == 1 )
    {
        printf("Ingrese su nueva contraseña\n");
        printf("> ");
        scanf("%s",usr->contrasena);
        leerLinea(NULL);
    }
    else if ( opcion == 2 )
    {
        printf("Ingrese su nuevo nombre\n");
        printf("> ");
        scanf("%[^\n]",usr->nombre_usuario);
    }
    else
    {
        printf("Ingrese su nueva edad\n");
        do {
            printf("> ");
            scanf("%d",&(usr->edad) );
            leerLinea(NULL);
        } while ( usr->edad < 0 || usr->edad > 200 );
    }

    printf("Cambios realizados satisfactoriamente2\n");
    leerLinea(NULL);
}

// Contenido de la funciOn "cambiarUsuario"
void cambiarUsuario(Usuario *usr, ListaUsuarios *misUsuarios)
{
    Usuario *nuevoUsuario = (Usuario *) malloc(sizeof(Usuario));
    Usuario *aux = misUsuarios->primero;
    Booleano cambio = falso;
    int i;

    leerDatosUsuario(nuevoUsuario->cuenta,nuevoUsuario->contrasena);
    if ( strcmp(nuevoUsuario->cuenta, usr->cuenta) != 0 )
    {
        for ( i = 1; i <= misUsuarios->num_usuarios; ++i)
        {
            if (
                    strcmp(nuevoUsuario->cuenta, aux->cuenta) == 0 &&
                    strcmp(nuevoUsuario->contrasena, aux->contrasena) == 0
               )
            {
                strcpy(usr->cuenta,nuevoUsuario->cuenta);
                strcpy(usr->contrasena,nuevoUsuario->contrasena);
                cambio = verdadero;
            }
            aux = aux->siguiente;
        }
    }

    if ( cambio )
        printf("Cambio de usuario correctamente realizado\n");
    else
        printf("El cambio de usuario ha fallado\n");

    leerLinea(NULL);
}

// Contenido de la funciOn "leerDatosUsuario"
void leerDatosUsuario(unsigned char *cta, unsigned char *contra)
{

    printf("Ingrese la cuenta: ");
    scanf("%30s",cta);
    leerLinea(NULL);
    fflush(stdin);

    printf("Ingrese la contraseña: ");
    scanf("%16s",contra);
    leerLinea(NULL);
    fflush(stdin);
    putchar('\n');
}

// Contenido de la funciOn "existeUsuario"
Booleano existeUsuario(Usuario *usr, ListaUsuarios *misUsuarios)
{
    Usuario *aux = misUsuarios->primero;

    for (int i = 1; i <= misUsuarios->num_usuarios ; ++i )
    {
        //printf("Comparando con el usuario %d\n", i);
        //printf("Las cuentas son: %s %s\n", usr->cuenta, aux->cuenta);
        //printf("El resultado es: %d\n", strcmp(usr->cuenta, aux->cuenta) );

        //printf("Las contraseñas son: %s %s\n",
        //  usr->contrasena,
        //  aux->contrasena);
        //printf("El resultado es: %d\n",
        //  strcmp(usr->contrasena, aux->contrasena) );
        //if( strcmp(usr->contrasena, aux->contrasena) ){
        //    printf("No hay correspondencia\n");
        //}else{
        //    printf("Hay correspondencia\n");
        //}

        if (
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
Usuario * crearUsuario(void)
{
    Usuario *aux;

    aux = (Usuario *) malloc(sizeof(Usuario));
    aux->siguiente = NULL;
    aux->anterior = NULL;
    aux->numero_compras = 0;

    leerDatosUsuario(aux->cuenta, aux->contrasena);
    leerLinea(NULL);
    printf("Ingrese el nombre completo del usuario:\n");
    scanf("%[^\n]",aux->nombre_usuario);
    leerLinea(NULL);

    do {
        printf("Ingrese la edad del usuario: \n");
        scanf("%d",&aux->edad);
        //printf("%d\n",aux->edad);
        leerLinea(NULL);
    } while ( aux->edad <= 0 );

    return aux;
}

// Contenido de la funciOn "agregarUsuario"
Booleano agregarUsuario(Usuario *nvo, ListaUsuarios *misUsuarios)
{
    Usuario *apt;
    Usuario *aux;
    Booleano a = falso; // Bandera para remediar la estupidez humana
    apt = misUsuarios->primero;

    if ( apt == NULL )
    {
        misUsuarios->primero = nvo;
        misUsuarios->ultimo = nvo;
        ++misUsuarios->num_usuarios;
        return verdadero;
    }
    // Primer caso, si el nuevo usuario va acomodado en la primera
    //  posición
    if ( strcmp(nvo->cuenta, apt->cuenta) < 0 )
    {
        nvo->siguiente = apt;
        apt->anterior = nvo;
        misUsuarios->primero = nvo;
    }
    else
    {
        // Segundo caso, se recorren posiciones hasta encontrar el
        //  lugar que le corresponde al usuario
        for (int i = 1; i <= misUsuarios->num_usuarios && !a; ++i)
        {
            //Si se llega a la posiciOn del usuario

            if(
                    strcmp(nvo->cuenta, apt->cuenta) > 0 &&
                    apt->siguiente == NULL || ( apt->siguiente != NULL &&
                        strcmp(nvo->cuenta, apt->siguiente->cuenta) < 0)
              )
            {
                aux = apt->siguiente;
                nvo->anterior = apt;
                apt->siguiente = nvo;
                if ( aux )
                {
                    nvo->siguiente = aux;
                    aux->anterior = nvo;
                }
                else
                {
                    misUsuarios->ultimo = nvo;
                }
                a = verdadero;
            }
            else if (strcmp(apt->cuenta, nvo->cuenta) == 0 )
            {
                printf("Lo sentimos, el nombre de usuario ya está ocupado\n");
                leerLinea(NULL);
                return falso;
            }
            apt = apt->siguiente;
        }
    }
    ++misUsuarios->num_usuarios;
    printf("Usuario añadido correctamente\n");
    leerLinea(NULL);
    return verdadero;
}

// Contenido de la funciOn "eliminarUsuario"
void eliminarUsuario(Usuario *adm, ListaUsuarios *misUsuarios)
{
    Usuario *aux = (Usuario *) malloc(sizeof(Usuario));
    Usuario *elim = (Usuario *) malloc(sizeof(Usuario));

    printf("Indique el usuario que desea borrar\n");
    leerDatosUsuario(elim->cuenta, elim->contrasena);

    if (
            strcmp(elim->cuenta, adm->cuenta) == 0 &&
            strcmp(elim->contrasena, adm->contrasena) == 0
       )
    {
        printf("No te puedes eliminar a ti mismo\n");
        leerLinea(NULL);
        return;
    }

    free(aux);
    aux = misUsuarios->primero;
    for(int i = 1; i <= misUsuarios->num_usuarios; ++i)
    {
        if (
                strcmp(elim->cuenta, aux->cuenta) == 0 &&
                strcmp(elim->contrasena, aux->contrasena) == 0
           )
        {
            if (
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

            leerLinea(NULL);
            return;
        }
        aux = aux->siguiente;
    }
    leerLinea(NULL);
}

// Contenido de la funciOn "leerBD_Discos"
void leerBD_Discos( ListaDiscos *misDiscos )
{
    FILE *ap_BD_discos = fopen(ARCHIVO_DISCOS,"r");
    Disco *nvo;

    printf("Leyendo la base de datos de discos...\n");
    leerLinea(NULL);

    if( ap_BD_discos )
    {

        while( !feof(ap_BD_discos) )
        {
            nvo = (Disco*) malloc(sizeof(Disco));
            fscanf(ap_BD_discos,"%[^\t]\t",nvo->nombre_artista);
            fscanf(ap_BD_discos,"%[^\t]\t",nvo->nombre_disco);
            fscanf(ap_BD_discos,"%f\t",&nvo->precio);
            fscanf(ap_BD_discos,"%d\t",&nvo->anio_lanzamiento);
            fscanf(ap_BD_discos,"%d\t\n",&nvo->numero_compras);

            //printf("Se ha leido un discos\n");
            //printf(
            //"Sus datos son:\n%s\n%s\n%.2f %d %d\n",
            //nvo->nombre_artista,nvo->nombre_disco,
            //nvo->precio, nvo->anio_lanzamiento,
            //nvo->numero_compras
            //);
            agregarDisco(nvo, misDiscos);
        }

        //printf("La base de datos de discos se ha leido completamente\n");
        //printf("Sus datos son\n");

    }
    else
    {
        printf("No hay discos guardados\n");
    }


    // Se escriben los datos justo despuEs de leerlos para evitar problemas
    // causados por escribir en el archivo de discos directamente, es decir
    // para evitar:
    //  - Discos mal ordenados
    //  - Discos repetidos
    //  - Etc
    escribirBD_Discos(misDiscos);
    leerLinea(NULL);
}

// Contenido de la funciOn "escribirBD_Discos"
void escribirBD_Discos(ListaDiscos *misDiscos)
{
    FILE *ap_BD_discos;
    Disco *aux = misDiscos->primero;
    //printf("Escribiendo discos\n");
    //aux = misDiscos->primero;
    //for(i=1;i<=misDiscos->num_discos;++i){
    //printf("%d %s %s %f %d %d\n",
    //i, aux->nombre_artista,
    //aux->nombre_disco,
    //aux->precio,
    //aux->anio_lanzamiento,
    //aux->numero_compras
    //);
    //aux = aux->siguiente;
    //}
    //aux = misDiscos->primero;
    if ( aux )
    {
        ap_BD_discos = fopen(ARCHIVO_DISCOS, "w");
        for(int i = 1; i <= misDiscos->num_discos; ++i)
        {
            fprintf(ap_BD_discos,"%s\t%s\t%f\t%d\t%d\t\n",
                    aux->nombre_artista, aux->nombre_disco,
                    aux->precio, aux->anio_lanzamiento,
                    aux->numero_compras);

            aux = aux->siguiente;
        }

        fclose(ap_BD_discos);
    }
}

// Contenido de la funciOn "mostrarDiscos"
void mostrarDiscos(void)
{
    FILE *ap_BD_discos = fopen(ARCHIVO_DISCOS,"r");
    unsigned char cadena[LONG_NOMBRE_DISCO+1];
    unsigned int entero;
    float flotante;

    int i = 1;

    if( ap_BD_discos )
    {

        while( !feof(ap_BD_discos) )
        {
            printf("%2d",i);
            fscanf(ap_BD_discos,"%[^\t]\t",cadena);
            printf("\tArtista:  %s\n",cadena);
            fscanf(ap_BD_discos,"%[^\t]\t",cadena);
            printf("\tNombre del disco: %s\n",cadena);
            fscanf(ap_BD_discos,"%f\t",&flotante);
            printf("\tCosto: %.2f\n",flotante);
            fscanf(ap_BD_discos,"%d\t",&entero);
            printf("\tAño de lanzamiento: %d\n",entero);
            fscanf(ap_BD_discos,"%d\t",&entero);
            printf("\tUnidades compradas: %d\n",entero);
            ++i;
        }
        putchar('\n');

        fclose(ap_BD_discos);
    }
    else
    {
        printf("Parece que no hay discos registrados\n");
    }
    leerLinea(NULL);
}

// Contenido de la funciON "mostrarDiscosInversa"
void mostrarDiscosInversa(ListaDiscos *misDiscos)
{
    Disco *apt;
    int j;
    Booleano a = falso;
    j = misDiscos->num_discos;
    apt = misDiscos->ultimo;
    if ( apt )
    {
        for(int i = j; i >= 1; --i)
        {
            printf("%2d",j - i + 1);
            printf("\tArtista: %s\n",apt->nombre_artista);
            printf("\tNombre del disco: %s\n",apt->nombre_disco);
            printf("\tCosto: %f\n",apt->precio);
            printf("\tAño de lanzamiento: %d\n",apt->anio_lanzamiento);
            printf("\tDiscos comprados: %d\t\n",apt->numero_compras);
            apt = apt->anterior;
        }
    }
    else
    {
        printf("Parece que no hay discos en la base de datos\n");
    }
    leerLinea(NULL);
}

// Contenido de la FunciOn "buscar disco"
void buscarDisco(ListaDiscos *misDiscos)
{
    unsigned char cadena[60];
    Disco *apt;
    int j;
    Booleano a = falso;
    leerLinea(NULL);
    printf("Ingrese el disco que desea buscar\n");
    scanf("%[^\n]",cadena);

    j = misDiscos->num_discos;
    apt = misDiscos->primero;
    for (int i = 1; i <= j && !a; ++i)
    {
        if ( strcmp(apt->nombre_disco, cadena) == 0 )
        {
            printf("%2d",j - i + 1);
            printf("\tArtista: %s\n",apt->nombre_artista);
            printf("\tNombre del disco: %s\n",apt->nombre_disco);
            printf("\tCosto: %f\n",apt->precio);
            printf("\tAño de lanzamiento: %d\n",apt->anio_lanzamiento);
            printf("\tDiscos comprados: %d\t\n",apt->numero_compras);
            a = verdadero;
        }
        ++i;
        apt = apt->siguiente;
    }

    if ( !a )
        printf("No se pudo encontrar el disco\n");

    leerLinea(NULL);
}

// Contenido de la FunciOn "comprarDisco"
void comprarDisco(Usuario *usr,ListaDiscos *misDiscos)
{
    unsigned char cadena[60];
    Disco *apt;
    int j;
    Booleano a = falso;

    leerLinea(NULL);

    printf("Ingrese el disco que desea comprar\n");
    scanf("%[^\n]",cadena);

    j = misDiscos->num_discos;
    apt = misDiscos->primero;
    for (int i = 1; i <= j && !a; ++i)
    {
        if ( strcmp(apt->nombre_disco, cadena) == 0 )
        {
            printf("\tHas comprado el disco: %s\n",apt->nombre_disco);
            ++apt->numero_compras;
            a = verdadero;
            ++usr->numero_compras;
        }
        apt = apt->siguiente;
    }

    if ( !a ) {
        printf("no se pudo encontrar el disco\n");
    }
    leerLinea(NULL);
}

// Contenido de la funciOn editarDisco
void editarDisco(ListaDiscos *misDiscos)
{
    Booleano a = falso;
    unsigned char cadena[60];
    int opcion = -1;
    Disco *apt;

    leerLinea(NULL);
    printf("Ingrese el nombre del disco que desea editar\n> ");
    scanf("%[^\n]", cadena);

    apt = misDiscos->primero;
    for (int i = 1; i <= misDiscos->num_discos && !a; ++i)
    {
        if( strcmp(apt->nombre_disco, cadena) == 0 )
        {
            printf("Seleccióne la opción que desea modificar\n");
            printf("\t1. Precio\n\t2. Número de compras\n");
            do {
                printf("> ");
                scanf("%d",&opcion);
                leerLinea(NULL);
            } while( opcion < 1 || opcion > 2 );

            if ( opcion == 1 )
            {
                printf("Ingrese el nuevo precio\n");
                do {
                    printf("> ");
                    scanf("%f",&(apt->precio) );
                    leerLinea(NULL);
                } while( apt->precio < 0 );
            }
            else
            {
                printf("Ingrese el nuevo número de compras\n");
                do {
                    printf("> ");
                    scanf("%d",&(apt->numero_compras) );
                    leerLinea(NULL);
                } while( apt->numero_compras < 0 );
            }
            leerLinea(NULL);
            a = verdadero;
        }
        apt = apt->siguiente;
    }
    escribirBD_Discos(misDiscos);
}

// Contenido de la funciOn "crearDisco"
Disco * crearDisco(void)
{
    Disco *aux;

    aux = (Disco *) malloc(sizeof(Disco));
    aux->siguiente = NULL;
    aux->anterior = NULL;

    leerLinea(NULL);
    printf("Ingrese el nombre del artista: \n");
    scanf("%60[^\n]",aux->nombre_artista);
    //printf("%s\n",aux->nombre_artista);
    leerLinea(NULL);

    printf("Ingrese el titulo del disco: \n");
    scanf("%100[^\n]",aux->nombre_disco);
    //printf("%s\n",aux->nombre_disco);
    leerLinea(NULL);

    do {
        printf("Ingrese el costo del disco: \n");
        scanf("%f",&aux->precio);
        //printf("%f\n",aux->precio);
        leerLinea(NULL);
    } while( aux->precio <= 0 );

    do {
        printf("Ingrese el año de lanzamiento del disco (min 1900): \n");
        scanf("%d",&aux->anio_lanzamiento);
        //printf("%d\n",aux->anio_lanzamiento);
        leerLinea(NULL);
    } while( aux->anio_lanzamiento < 1900 );

    do {
        printf("Ingrese el número de ejemplares comprados: \n");
        scanf("%d",&aux->numero_compras);
        //printf("%d\n",aux->numero_compras);
        leerLinea(NULL);
    } while( aux->precio < 0 );

    return aux;
}

// Contenido de la funciOn "agregarDisco"
Booleano agregarDisco(Disco * nvo, ListaDiscos *misDiscos)
{
    Disco *apt;
    Disco *aux;
    Booleano a = falso; // Bandera para remediar la estupidez humana

    apt = misDiscos->primero;
    if ( apt == NULL )
    {
        misDiscos->primero = nvo;
        misDiscos->ultimo = nvo;
        ++misDiscos->num_discos;
        return verdadero;
    }

    // Primer caso, si el nuevo disco va acomodado en la primera
    //  posiciOn
    if ( strcmp(nvo->nombre_disco, apt->nombre_disco) < 0 )
    {
        nvo->siguiente = apt;
        apt->anterior = nvo;
        misDiscos->primero = nvo;
    }
    else
    {
        // Segundo caso, se recorren posiciones hasta encontrar el
        //  lugar que le corresponde al usuario
        for (int i = 1; i <= misDiscos->num_discos && !a; ++i)
        {
            //Si se llega a la posiciOn del usuario

            if (
                    strcmp(nvo->nombre_disco, apt->nombre_disco) > 0 &&
                    apt->siguiente == NULL || ( apt->siguiente != NULL &&
                        strcmp(nvo->nombre_disco, apt->siguiente->nombre_disco) < 0)
               )
            {
                aux = apt->siguiente;
                nvo->anterior = apt;
                apt->siguiente = nvo;
                if ( aux )
                {
                    nvo->siguiente = aux;
                    aux->anterior = nvo;
                }
                else
                {
                    misDiscos->ultimo = nvo;
                }
                a = verdadero;
            }
            else if ( strcmp(apt->nombre_disco, nvo->nombre_disco) == 0 )
            {
                printf("Lo sentimos, el disco ya existe en la base de datos\n");
                leerLinea(NULL);
                return falso;
            }
            apt = apt->siguiente;
        }
    }
    ++misDiscos->num_discos;
    printf("Disco añadido correctamente\n");
    leerLinea(NULL);
    return verdadero;
}

// Contenido de la funciOn "eliminarDiscos"
void eliminarDisco(Usuario *adm, ListaDiscos *misDiscos)
{
    Usuario *usr = (Usuario *) malloc(sizeof(Usuario));
    Disco *elim = (Disco *) malloc(sizeof(Disco));
    Disco *aux;

    printf("Indique el disco que desea borrar\n");
    leerLinea(NULL);
    scanf("%100[^\n]",elim->nombre_disco);

    aux = misDiscos->primero;
    for(int i = 1; i <= misDiscos->num_discos; ++i)
    {
        if ( strcmp( elim->nombre_disco, aux->nombre_disco ) == 0 )
        {
            if (
                    misDiscos->primero != aux &&
                    misDiscos->ultimo != aux
               )
            {
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
            }
            else if ( misDiscos->num_discos == 1 )
            {
                misDiscos->primero = NULL;
                misDiscos->ultimo = NULL;
            }
            else if ( misDiscos->primero == aux )
            {
                aux->siguiente->anterior = NULL;
                misDiscos->primero = misDiscos->primero->siguiente;
            }
            else // Si es el Ultimo
            {
                aux->anterior->siguiente = NULL;
                misDiscos->ultimo = aux->anterior;
            }

            free(elim);
            --misDiscos->num_discos;
            escribirBD_Discos(misDiscos);
            printf("Se ha eliminado un disco correctamente\n");
            leerLinea(NULL);
            return;
        }
        aux = aux->siguiente;
    }

    leerLinea(NULL);
}

void leerLinea(char * buff)
{
    char cadena[100];

    if ( buff == NULL )
        scanf("%[^\n]", cadena);
    else
        scanf("%[^\n]", buff);
}
