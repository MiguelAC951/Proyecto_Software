#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Centraliza los nombres de los archivos para facilitar cambios y evitar errores de escritura
#define EMP_FILE "empleados.txt"
#define ASIS_FILE "asistencias.txt"
#define VAC_FILE "vacaciones.txt"
#define PER_FILE "permisos.txt"
#define REP_FILE "reportes.txt"

// Verifica si existe el archivo maestro, si no, lo crea y carga la nómina inicial predeterminada
void inicializarEmpleados();

// Autentifica al usuario comparando las credenciales con el archivo; la contraseña el el ID
int login();
void menu();

void menuEmpleados();
void mostrarEmpleados();
void agregarEmpleado();
void buscarEmpleado();
void eliminarEmpleado();

void menuAsistencias();
void registrarAsistencia();
void consultarAsistencias();

void menuVacaciones();
void registrarVacaciones();
void consultarVacaciones();
void constanciaVacaciones();

void menuPermisos();
void registrarPermiso();
void consultarPermisos();
void eliminarPermiso();

void menuReportes();
void crearReporte();
void consultarReportes();
void reporteCompleto();

void menuTurnos();
void mostrarTurnos();
void modificarTurno();

int empleadoExiste(int num);

int main() {
    inicializarEmpleados();

    printf("\nBienvenido al sistema de enfermería del Hospital General Siglo XXI\n");

    // Es un bucle que impide el acceso al menú hasta que la autentificación sea exitosa
    while (!login()) {
        printf("\nContraseña o usuario incorrecto. Intente nuevamente.\n");
    }

    menu();
    return 0;
}

void inicializarEmpleados() {
    FILE *f = fopen(EMP_FILE, "r");
    if (f) {
        fclose(f);
        return;
    }

    //Abre el archivo para agregar el nuevo registro sin borrar los ya existentes
    f = fopen(EMP_FILE, "w");
    fprintf(f, "10000001|Carlos|Ramirez|Administrador|Matutino\n");
    fprintf(f, "10000002|Lucia|Torres|Enfermera|Matutino\n");
    fprintf(f, "10000003|Maria|Sanchez|Enfermera|Matutino\n");
    fprintf(f, "10000004|Fernanda|Lopez|Enfermera|Vespertino\n");
    fprintf(f, "10000005|Andrea|Medina|Enfermera|Vespertino\n");
    fprintf(f, "10000006|Claudia|Rojas|Enfermera|Vespertino\n");
    fprintf(f, "10000007|Diana|Morales|Enfermera|Nocturno\n");
    fprintf(f, "10000008|Paola|Fernandez|Enfermera|Nocturno\n");
    fprintf(f, "10000009|Karina|Vega|Enfermera|Nocturno\n");
    fclose(f);
}

int login() {
    char usuario[50], nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    char pass[20], numStr[20];
    int num;

    printf("\nUsuario: ");
    scanf("%s", usuario);
    printf("Contraseña: ");
    scanf("%s", pass);

    FILE *f = fopen(EMP_FILE, "r");
    if (!f) return 0;

// Itera linea por linea y separa los campos delimitados por ´|´para mostrarlos en una formato tabular    
    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);
        sprintf(numStr, "%08d", num);
        if (strcmp(usuario, nombre) == 0 && strcmp(pass, numStr) == 0) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

void menu() {
    int op;
    // Mantiene al usuario dentro del módulo de empleados permitiendo relizar muchas operaciones hasta que elija regresar
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Empleados\n");
        printf("2. Asistencias\n");
        printf("3. Turnos\n");
        printf("4. Vacaciones\n");
        printf("5. Permisos\n");
        printf("6. Reportes\n");
        printf("0. Salir\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) menuEmpleados();
        if (op == 2) menuAsistencias();
        if (op == 3) menuTurnos();
        if (op == 4) menuVacaciones();
        if (op == 5) menuPermisos();
        if (op == 6) menuReportes();

    } while (op != 0);
}

void menuEmpleados() {
    int op;
    do {
        printf("\n--- GESTION DE EMPLEADOS ---\n");
        printf("1. Mostrar empleados\n");
        printf("2. Agregar empleado\n");
        printf("3. Buscar empleado\n");
        printf("4. Eliminar empleado\n");
        printf("0. Volver al menú principal\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) mostrarEmpleados();
        if (op == 2) agregarEmpleado();
        if (op == 3) buscarEmpleado();
        if (op == 4) eliminarEmpleado();

    } while (op != 0);
}

void mostrarEmpleados() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num;

    printf("\n%-15s %-20s %-20s %-20s %-15s\n",
           "NUMERO EMP", "NOMBRE", "APELLIDO", "CARGO", "TURNO");
    printf("-------------------------------------------------------------------------------------------\n");

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);
        printf("%-15d %-20s %-20s %-20s %-15s\n",
               num, nombre, apellido, cargo, turno);
    }

    fclose(f);
}

void agregarEmpleado() {
    FILE *f = fopen(EMP_FILE, "a");
    int num;
    char nombre[50], apellido[50], cargo[50], turno[50];

    printf("\nNumero de empleado (8 digitos): ");
    scanf("%d", &num);
    printf("Nombre: ");
    scanf("%s", nombre);
    printf("Apellido: ");
    scanf("%s", apellido);
    printf("Cargo: ");
    scanf("%s", cargo);
    printf("Turno: ");
    scanf("%s", turno);

    fprintf(f, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
    fclose(f);
}

void buscarEmpleado() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300], search[50];
    int num;

    printf("\nIngrese nombre a buscar: ");
    scanf("%s", search);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);
        if (strcmp(nombre, search) == 0) {
            printf("\n%-15s %-20s %-20s %-20s %-15s\n",
                   "NUMERO EMP", "NOMBRE", "APELLIDO", "CARGO", "TURNO");
            printf("%-15d %-20s %-20s %-20s %-15s\n",
                   num, nombre, apellido, cargo, turno);
            fclose(f);
            return;
        }
    }

    printf("\nEmpleado no encontrado.\n");
    fclose(f);
}
// Realiza una baja lógica, copia todos los registros a uno temporal, excluyendo al objetivo, despues renombra el archivo
void eliminarEmpleado() {
    FILE *f = fopen(EMP_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num, elim;
    int encontrado = 0;

    printf("\nNumero de empleado a eliminar: ");
    scanf("%d", &elim);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);
        if (num != elim) {
            fprintf(temp, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
        } else {
            encontrado = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove(EMP_FILE);
    rename("temp.txt", EMP_FILE);

    if (encontrado) printf("\nEmpleado eliminado.\n");
    else printf("\nEmpleado no encontrado.\n");
}

void menuAsistencias() {
    int op;
    do {
        printf("\n--- ASISTENCIAS ---\n");
        printf("1. Registrar asistencia\n");
        printf("2. Consultar asistencias\n");
        printf("0. Volver al menú anterior\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) registrarAsistencia();
        if (op == 2) consultarAsistencias();

    } while (op != 0);
}

void registrarAsistencia() {
    FILE *f = fopen(ASIS_FILE, "a");
    int num;

    // Captura la fecha y hora actual del sistema para registrar el momento exacto del fichaje
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nNumero de empleado: ");
    scanf("%d", &num);

    fprintf(f, "%08d|%04d-%02d-%02d|%02d:%02d\n",
            num, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min);

    printf("\nAsistencia registrada.\n");
    fclose(f);
}

void consultarAsistencias() {
    FILE *f = fopen(ASIS_FILE, "r");
    char linea[300];

    printf("\n%-15s %-15s %-10s\n", "EMP", "FECHA", "HORA");
    printf("--------------------------------------\n");

    while (f && fgets(linea, 300, f)) {
        printf("%s", linea);
    }

    if (f) fclose(f);
}

void menuTurnos() {
    int op;
    do {
        printf("\n--- TURNOS ---\n");
        printf("1. Mostrar turnos\n");
        printf("2. Modificar turno\n");
        printf("0. Volver al menú anterior\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) mostrarTurnos();
        if (op == 2) modificarTurno();

    } while (op != 0);
}

void mostrarTurnos() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num;

    printf("\n%-15s %-20s %-20s %-20s\n",
           "NUMERO EMP", "NOMBRE", "CARGO", "TURNO");
    printf("--------------------------------------------------------------------\n");

    //Recorre el archivo y reescribe el registro, haciendo que coincida con el nuevo dato, sin tocar lo demás
    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);
        printf("%-15d %-20s %-20s %-20s\n",
               num, nombre, cargo, turno);
    }

    fclose(f);
}

void modificarTurno() {
    int target;
    char newTurno[50], linea[300];
    char nombre[50], apellido[50], cargo[50], turno[50];
    int num;

    printf("\nNumero de empleado: ");
    scanf("%d", &target);

    if (!empleadoExiste(target)) {
        printf("\nEmpleado no existe.\n");
        return;
    }

    printf("Nuevo turno: ");
    scanf("%s", newTurno);

    FILE *f = fopen(EMP_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);

        if (num == target)
            fprintf(tmp, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, newTurno);
        else
            fprintf(tmp, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
    }

    fclose(f);
    fclose(tmp);
    remove(EMP_FILE);
    rename("temp.txt", EMP_FILE);

    printf("\nTurno modificado.\n");
}

void menuVacaciones() {
    int op;
    do {
        printf("\n--- VACACIONES ---\n");
        printf("1. Registrar vacaciones\n");
        printf("2. Consultar vacaciones\n");
        printf("3. Generar constancia\n");
        printf("0. Volver al menú anterior\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) registrarVacaciones();
        if (op == 2) consultarVacaciones();
        if (op == 3) constanciaVacaciones();

    } while (op != 0);
}

void registrarVacaciones() {
    FILE *f = fopen(VAC_FILE, "a");
    int num;
    char ini[20], fin[20];

    printf("\nNumero de empleado: ");
    scanf("%d", &num);
    printf("Fecha inicio (YYYY-MM-DD): ");
    scanf("%s", ini);
    printf("Fecha fin (YYYY-MM-DD): ");
    scanf("%s", fin);

    fprintf(f, "%08d|%s|%s\n", num, ini, fin);
    printf("\nVacaciones registradas.\n");

    fclose(f);
}

void consultarVacaciones() {
    FILE *f = fopen(VAC_FILE, "r");
    char linea[300];

    printf("\n%-15s %-12s %-12s\n", "EMP", "INICIO", "FIN");
    printf("----------------------------------\n");

    while (f && fgets(linea, 300, f)) {
        printf("%s", linea);
    }

    if (f) fclose(f);
}

void constanciaVacaciones() {
    int num;
    char ini[20], fin[20];

    printf("\nNumero de empleado: ");
    scanf("%d", &num);
    printf("Fecha inicio: ");
    scanf("%s", ini);
    printf("Fecha fin: ");
    scanf("%s", fin);
// Genera una salida a la pantalla simulando un documento oficial para validación visual
    printf("\n=== CONSTANCIA DE VACACIONES ===\n");
    printf("Empleado: %08d\n", num);
    printf("Periodo: %s a %s\n", ini, fin);
}

void menuPermisos() {
    int op;
    do {
        printf("\n--- PERMISOS ---\n");
        printf("1. Registrar permiso\n");
        printf("2. Consultar permisos\n");
        printf("3. Eliminar permiso\n");
        printf("0. Volver al menú anterior\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) registrarPermiso();
        if (op == 2) consultarPermisos();
        if (op == 3) eliminarPermiso();

    } while (op != 0);
}

// Función auxiliar para validar si un ID es real antes de permitir operacoines importantes
int empleadoExiste(int num) {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int n;
    while (f && fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &n, nombre, apellido, cargo, turno);
        if (n == num) {
            fclose(f);
            return 1;
        }
    }
    if (f) fclose(f);
    return 0;
}

void registrarPermiso() {
    FILE *f = fopen(PER_FILE, "a");
    int num;
    char fecha[20], motivo[200];

    while (1) {
        printf("\nNumero de empleado: ");
        scanf("%d", &num);

        if (!empleadoExiste(num)) {
            printf("\nEl empleado no existe. Intente nuevamente.\n");
            continue;
        }
        break;
    }

    printf("Fecha: ");
    scanf("%s", fecha);
    printf("Motivo: ");
    scanf("%s", motivo);

    fprintf(f, "%08d|%s|%s\n", num, fecha, motivo);
    printf("\nPermiso registrado.\n");

    fclose(f);
}

void consultarPermisos() {
    FILE *f = fopen(PER_FILE, "r");
    char linea[300];

    printf("\n%-15s %-12s %-30s\n", "EMP", "FECHA", "MOTIVO");
    printf("-------------------------------------------------------\n");

    while (f && fgets(linea, 300, f)) {
        printf("%s", linea);
    }

    if (f) fclose(f);
}

void eliminarPermiso() {
    FILE *f = fopen(PER_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");
    char linea[300];
    int num, target;
    char fecha[20], motivo[200];
    int encontrado = 0;

    printf("\nNumero de empleado cuyo permiso desea eliminar: ");
    scanf("%d", &target);

    while (f && fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^\n]", &num, fecha, motivo);

        if (num != target) {
            fprintf(tmp, "%08d|%s|%s\n", num, fecha, motivo);
        } else {
            encontrado = 1;
        }
    }

    fclose(f);
    fclose(tmp);
    remove(PER_FILE);
    rename("temp.txt", PER_FILE);

    if (encontrado) printf("\nPermiso eliminado.\n");
    else printf("\nNo existen permisos para ese empleado.\n");
}

void menuReportes() {
    int op;
    do {
        printf("\n--- REPORTES ---\n");
        printf("1. Crear reporte\n");
        printf("2. Consultar reportes\n");
        printf("3. Reporte completo\n");
        printf("0. Volver al menú anterior\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) crearReporte();
        if (op == 2) consultarReportes();
        if (op == 3) reporteCompleto();

    } while (op != 0);
}

void crearReporte() {
    FILE *f = fopen(REP_FILE, "a");
    int num;
    char desc[200];

    printf("\nNumero de empleado: ");
    scanf("%d", &num);
    printf("Descripcion: ");
    scanf("%s", desc);

    fprintf(f, "%08d|%s\n", num, desc);
    printf("\nReporte creado.\n");

    fclose(f);
}

void consultarReportes() {
    FILE *f = fopen(REP_FILE, "r");
    char linea[300];

    printf("\n%-15s %-50s\n", "EMP", "DESCRIPCION");
    printf("------------------------------------------------------\n");

    while (f && fgets(linea, 300, f)) {
        printf("%s", linea);
    }

    if (f) fclose(f);
}

// Cruza la información de todos los archivos para generar un historial integral del empleado
void reporteCompleto() {
    int target;
    char linea[300];

    printf("\nNumero de empleado: ");
    scanf("%d", &target);

    if (!empleadoExiste(target)) {
        printf("\nEmpleado no existe.\n");
        return;
    }

    printf("\n=== REPORTE COMPLETO DEL EMPLEADO %08d ===\n", target);

    FILE *f;

    printf("\n--- DATOS PERSONALES ---\n");
    f = fopen(EMP_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num;
        char nombre[50], apellido[50], cargo[50], turno[50];
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]",
               &num, nombre, apellido, cargo, turno);
        if (num == target)
            printf("Nombre: %s %s\nCargo: %s\nTurno: %s\n",
                   nombre, apellido, cargo, turno);
    }
    if (f) fclose(f);

    printf("\n--- ASISTENCIAS ---\n");
    f = fopen(ASIS_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num;
        char fecha[20], hora[20];
        sscanf(linea, "%d|%[^|]|%[^\n]", &num, fecha, hora);
        if (num == target)
            printf("%s %s\n", fecha, hora);
    }
    if (f) fclose(f);

    printf("\n--- VACACIONES ---\n");
    f = fopen(VAC_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num;
        char ini[20], fin[20];
        sscanf(linea, "%d|%[^|]|%[^\n]", &num, ini, fin);
        if (num == target)
            printf("%s a %s\n", ini, fin);
    }
    if (f) fclose(f);

    printf("\n--- PERMISOS ---\n");
    f = fopen(PER_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num;
        char fecha[20], motivo[200];
        sscanf(linea, "%d|%[^|]|%[^\n]", &num, fecha, motivo);
        if (num == target)
            printf("%s Motivo: %s\n", fecha, motivo);
    }
    if (f) fclose(f);

    printf("\n--- REPORTES ADMINISTRATIVOS ---\n");
    f = fopen(REP_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num;
        char desc[200];
        sscanf(linea, "%d|%[^\n]", &num, desc);
        if (num == target)
            printf("%s\n", desc);
    }
    if (f) fclose(f);
}
