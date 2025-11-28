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
#define HOR_FILE "horarios.txt" 
// Verifica si existe el archivo maestro, si no, lo crea y carga la nómina inicial predeterminada
void inicializarEmpleados();
void inicializarHorarios();
// Autentifica al usuario comparando las credenciales con el archivo; la contraseña el el ID
int login();
void menu();

void menuEmpleados();
void mostrarEmpleados();
void agregarEmpleado();
void buscarEmpleado();
void eliminarEmpleado();
void modificarEmpleado(); 

void menuHorarios();
void mostrarHorarios();
void agregarHorario();
void modificarHorario();
void eliminarHorario();

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
void mostrarTurnos();

int empleadoExiste(int num);

int main() {
    inicializarEmpleados();
    inicializarHorarios(); 

    printf("\nBienvenido al sistema de enfermeria del Hospital General Siglo XXI\n");
 // Es un bucle que impide el acceso al menú hasta que la autentificación sea exitosa
    while (!login()) {
        printf("\nContrasena o usuario incorrecto. Intente nuevamente.\n");
    }

    menu();
    return 0;
}

void inicializarEmpleados() {
    FILE *f = fopen(EMP_FILE, "r");
    if (f) { fclose(f); return; }
//Abre el archivo para agregar el nuevo registro sin borrar los ya existentes
    f = fopen(EMP_FILE, "w");
    fprintf(f, "10000001|Carlos|Ramirez|Administrador|Matutino\n");
    fprintf(f, "10000002|Lucia|Torres|Enfermera|Matutino\n");
    fclose(f);
}

void inicializarHorarios() {
    FILE *f = fopen(HOR_FILE, "r");
    if (f) { fclose(f); return; }

    f = fopen(HOR_FILE, "w");
    fprintf(f, "1|Matutino|07:00|15:00\n");
    fprintf(f, "2|Vespertino|14:00|22:00\n");
    fprintf(f, "3|Nocturno|22:00|07:00\n");
    fclose(f);
}

int login() {
    char usuario[50], nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    char pass[20], numStr[20];
    int num;

    printf("\nUsuario: "); scanf("%s", usuario);
    printf("Contrasena: "); scanf("%s", pass);

    FILE *f = fopen(EMP_FILE, "r");
    if (!f) return 0;

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
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Empleados (Altas, Bajas y Edicion)\n");
        printf("2. Asistencias\n");
        printf("3. Gestion de Horarios (Configuracion)\n");
        printf("4. Vacaciones\n");
        printf("5. Permisos\n");
        printf("6. Reportes\n");
        printf("0. Salir\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) menuEmpleados();
        if (op == 2) menuAsistencias();
        if (op == 3) menuHorarios();
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
        printf("5. Modificar informacion de empleado\n");
        printf("0. Volver al menu principal\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) mostrarEmpleados();
        if (op == 2) agregarEmpleado();
        if (op == 3) buscarEmpleado();
        if (op == 4) eliminarEmpleado();
        if (op == 5) modificarEmpleado();

    } while (op != 0);
}

void mostrarEmpleados() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num;

    printf("\n%-15s %-20s %-20s %-20s %-15s\n", "NUMERO EMP", "NOMBRE", "APELLIDO", "CARGO", "TURNO");
    printf("-------------------------------------------------------------------------------------------\n");

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);
        printf("%-15d %-20s %-20s %-20s %-15s\n", num, nombre, apellido, cargo, turno);
    }
    fclose(f);
}

void agregarEmpleado() {
    FILE *f = fopen(EMP_FILE, "a");
    int num;
    char nombre[50], apellido[50], cargo[50], turno[50];

    printf("\nNumero de empleado (8 digitos): "); scanf("%d", &num);
    printf("Nombre: "); scanf("%s", nombre);
    printf("Apellido: "); scanf("%s", apellido);
    printf("Cargo: "); scanf("%s", cargo);
    printf("Turno Asignado (ej. Matutino): "); scanf("%s", turno);

    fprintf(f, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
    fclose(f);
}

void buscarEmpleado() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300], search[50];
    int num;

    printf("\nIngrese nombre a buscar: "); scanf("%s", search);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);
        if (strcmp(nombre, search) == 0) {
            printf("\nEncontrado: %d %s %s (%s)\n", num, nombre, apellido, cargo);
            fclose(f); return;
        }
    }
    printf("\nEmpleado no encontrado.\n");
    fclose(f);
}

void eliminarEmpleado() {
    FILE *f = fopen(EMP_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    char linea[300], nombre[50], apellido[50], cargo[50], turno[50];
    int num, elim, encontrado = 0;

    printf("\nNumero de empleado a eliminar: "); scanf("%d", &elim);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);
        if (num != elim) fprintf(temp, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
        else encontrado = 1;
    }

    fclose(f); fclose(temp);
    remove(EMP_FILE); rename("temp.txt", EMP_FILE);

    if (encontrado) printf("\nEmpleado eliminado.\n");
    else printf("\nEmpleado no encontrado.\n");
}

void modificarEmpleado() {
    FILE *f = fopen(EMP_FILE, "r");
    FILE *temp = fopen("temp_edit.txt", "w");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num, target, opcionMod, encontrado = 0;

    if (!f || !temp) return;

    printf("\nIngrese el Numero de empleado a modificar: ");
    scanf("%d", &target);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);

        if (num == target) {
            encontrado = 1;
            printf("\n--- Datos Actuales ---\n");
            printf("1. Nombre: %s\n2. Apellido: %s\n3. Cargo: %s\n4. Turno: %s\n", nombre, apellido, cargo, turno);
            printf("Que dato desea corregir? (0 para cancelar): ");
            scanf("%d", &opcionMod);

            switch (opcionMod) {
                case 1: printf("Nuevo Nombre: "); scanf("%s", nombre); break;
                case 2: printf("Nuevo Apellido: "); scanf("%s", apellido); break;
                case 3: printf("Nuevo Cargo: "); scanf("%s", cargo); break;
                case 4: printf("Nuevo Turno: "); scanf("%s", turno); break;
            }
        }
        fprintf(temp, "%08d|%s|%s|%s|%s\n", num, nombre, apellido, cargo, turno);
    }

    fclose(f); fclose(temp);
    remove(EMP_FILE); rename("temp_edit.txt", EMP_FILE);

    if (encontrado) printf("\nInformacion actualizada.\n");
    else printf("\nEmpleado no encontrado.\n");
}

void menuHorarios() {
    int op;
    do {
        printf("\n--- GESTION DE HORARIOS Y TURNOS ---\n");
        printf("1. Ver lista de horarios configurados\n");
        printf("2. Crear nuevo horario (Turno)\n");
        printf("3. Editar horario existente\n");
        printf("4. Eliminar horario\n");
        printf("0. Volver al menu principal\nOpcion: ");
        scanf("%d", &op);

        if (op == 1) mostrarHorarios();
        if (op == 2) agregarHorario();
        if (op == 3) modificarHorario();
        if (op == 4) eliminarHorario();

    } while (op != 0);
}

void mostrarHorarios() {
    FILE *f = fopen(HOR_FILE, "r");
    char linea[300], nombre[50], inicio[10], fin[10];
    int id;

    printf("\n%-5s %-20s %-10s %-10s\n", "ID", "TURNO", "INICIO", "FIN");
    printf("--------------------------------------------------\n");

    while (f && fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^\n]", &id, nombre, inicio, fin);
        printf("%-5d %-20s %-10s %-10s\n", id, nombre, inicio, fin);
    }
    if (f) fclose(f);
}

void agregarHorario() {
    FILE *f = fopen(HOR_FILE, "a");
    int id;
    char nombre[50], inicio[10], fin[10];

    printf("\nIngrese ID unico para el turno: "); scanf("%d", &id);
    printf("Nombre del turno: "); scanf("%s", nombre);
    printf("Hora inicio (HH:MM): "); scanf("%s", inicio);
    printf("Hora fin (HH:MM): "); scanf("%s", fin);

    fprintf(f, "%d|%s|%s|%s\n", id, nombre, inicio, fin);
    printf("\nHorario creado.\n");
    fclose(f);
}

void modificarHorario() {
    FILE *f = fopen(HOR_FILE, "r");
    FILE *temp = fopen("temp_hor.txt", "w");
    char linea[300], nombre[50], inicio[10], fin[10];
    int id, target, op, encontrado = 0;

    if (!f || !temp) return;
    mostrarHorarios();
    printf("\nID del horario a modificar: "); scanf("%d", &target);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^\n]", &id, nombre, inicio, fin);
        if (id == target) {
            encontrado = 1;
            printf("1. Cambiar horas\n2. Cambiar nombre\nOpcion: "); scanf("%d", &op);
            if (op == 1) {
                printf("Nueva inicio: "); scanf("%s", inicio);
                printf("Nueva fin: "); scanf("%s", fin);
            } else if (op == 2) {
                printf("Nuevo nombre: "); scanf("%s", nombre);
            }
        }
        fprintf(temp, "%d|%s|%s|%s\n", id, nombre, inicio, fin);
    }
    fclose(f); fclose(temp);
    remove(HOR_FILE); rename("temp_hor.txt", HOR_FILE);
    if (encontrado) printf("\nHorario actualizado.\n");
}

void eliminarHorario() {
    FILE *f = fopen(HOR_FILE, "r");
    FILE *temp = fopen("temp_hor.txt", "w");
    char linea[300], nombre[50], inicio[10], fin[10];
    int id, target, encontrado = 0;

    if (!f || !temp) return;
    mostrarHorarios();
    printf("\nID del horario a eliminar: "); scanf("%d", &target);

    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^\n]", &id, nombre, inicio, fin);
        if (id != target) fprintf(temp, "%d|%s|%s|%s\n", id, nombre, inicio, fin);
        else encontrado = 1;
    }
    fclose(f); fclose(temp);
    remove(HOR_FILE); rename("temp_hor.txt", HOR_FILE);
    if (encontrado) printf("\nHorario eliminado.\n");
}

void menuAsistencias() {
    int op;
    do {
        printf("\n--- ASISTENCIAS ---\n");
        printf("1. Registrar asistencia\n2. Consultar asistencias\n0. Volver\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) registrarAsistencia();
        if (op == 2) consultarAsistencias();
    } while (op != 0);
}

void registrarAsistencia() {
    FILE *f = fopen(ASIS_FILE, "a");
    int num;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nNumero de empleado: "); scanf("%d", &num);
    fprintf(f, "%08d|%04d-%02d-%02d|%02d:%02d\n", num, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
    printf("\nAsistencia registrada.\n");
    fclose(f);
}

void consultarAsistencias() {
    FILE *f = fopen(ASIS_FILE, "r");
    char linea[300];
    printf("\n%-15s %-15s %-10s\n", "EMP", "FECHA", "HORA");
    printf("--------------------------------------\n");
    while (f && fgets(linea, 300, f)) printf("%s", linea);
    if (f) fclose(f);
}

void menuVacaciones() {
    int op;
    do {
        printf("\n--- VACACIONES ---\n");
        printf("1. Registrar\n2. Consultar\n3. Constancia\n0. Volver\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) registrarVacaciones();
        if (op == 2) consultarVacaciones();
        if (op == 3) constanciaVacaciones();
    } while (op != 0);
}

void registrarVacaciones() {
    FILE *f = fopen(VAC_FILE, "a");
    int num; char ini[20], fin[20];
    printf("\nNumero de empleado: "); scanf("%d", &num);
    printf("Inicio (YYYY-MM-DD): "); scanf("%s", ini);
    printf("Fin (YYYY-MM-DD): "); scanf("%s", fin);
    fprintf(f, "%08d|%s|%s\n", num, ini, fin);
    printf("\nVacaciones registradas.\n");
    fclose(f);
}

void consultarVacaciones() {
    FILE *f = fopen(VAC_FILE, "r");
    char linea[300];
    while (f && fgets(linea, 300, f)) printf("%s", linea);
    if (f) fclose(f);
}

void constanciaVacaciones() {
    int num; char ini[20], fin[20];
    printf("\nNumero de empleado: "); scanf("%d", &num);
    printf("Inicio: "); scanf("%s", ini);
    printf("Fin: "); scanf("%s", fin);
    printf("\n=== CONSTANCIA DE VACACIONES ===\nEmpleado: %08d\nPeriodo: %s a %s\n", num, ini, fin);
}

void menuPermisos() {
    int op;
    do {
        printf("\n--- PERMISOS ---\n");
        printf("1. Registrar\n2. Consultar\n3. Eliminar\n0. Volver\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) registrarPermiso();
        if (op == 2) consultarPermisos();
        if (op == 3) eliminarPermiso();
    } while (op != 0);
}

void registrarPermiso() {
    FILE *f = fopen(PER_FILE, "a");
    int num; char fecha[20], motivo[200];
    while (1) {
        printf("\nNumero de empleado: "); scanf("%d", &num);
        if (empleadoExiste(num)) break;
        printf("Empleado no existe.\n");
    }
    printf("Fecha: "); scanf("%s", fecha);
    printf("Motivo: "); scanf("%s", motivo);
    fprintf(f, "%08d|%s|%s\n", num, fecha, motivo);
    printf("\nPermiso registrado.\n");
    fclose(f);
}

void consultarPermisos() {
    FILE *f = fopen(PER_FILE, "r");
    char linea[300];
    while (f && fgets(linea, 300, f)) printf("%s", linea);
    if (f) fclose(f);
}

void eliminarPermiso() {
    FILE *f = fopen(PER_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    char linea[300], fecha[20], motivo[200];
    int num, target, encontrado = 0;
    printf("\nEmpleado a eliminar permiso: "); scanf("%d", &target);
    while (f && fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^\n]", &num, fecha, motivo);
        if (num != target) fprintf(temp, "%08d|%s|%s\n", num, fecha, motivo);
        else encontrado = 1;
    }
    fclose(f); fclose(temp);
    remove(PER_FILE); rename("temp.txt", PER_FILE);
    if (encontrado) printf("\nPermiso eliminado.\n");
}

void menuReportes() {
    int op;
    do {
        printf("\n--- REPORTES ---\n");
        printf("1. Crear reporte\n2. Consultar reportes\n3. Reporte completo\n");
        printf("4. Ver lista de empleados por turno\n");
        printf("0. Volver\nOpcion: ");
        scanf("%d", &op);
        if (op == 1) crearReporte();
        if (op == 2) consultarReportes();
        if (op == 3) reporteCompleto();
        if (op == 4) mostrarTurnos();
    } while (op != 0);
}

void crearReporte() {
    FILE *f = fopen(REP_FILE, "a");
    int num; char desc[200];
    printf("\nNumero de empleado: "); scanf("%d", &num);
    printf("Descripcion: "); scanf("%s", desc);
    fprintf(f, "%08d|%s\n", num, desc);
    fclose(f);
}

void consultarReportes() {
    FILE *f = fopen(REP_FILE, "r");
    char linea[300];
    while (f && fgets(linea, 300, f)) printf("%s", linea);
    if (f) fclose(f);
}

void reporteCompleto() {
    int target; char linea[300];
    printf("\nNumero de empleado: "); scanf("%d", &target);
    if (!empleadoExiste(target)) { printf("No existe.\n"); return; }
    
    printf("\n=== REPORTE %08d ===\n", target);
    FILE *f = fopen(EMP_FILE, "r");
    while (f && fgets(linea, 300, f)) {
        int num; char n[50], a[50], c[50], t[50];
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, n, a, c, t);
        if (num == target) printf("Datos: %s %s, %s, %s\n", n, a, c, t);
    }
    if (f) fclose(f);
}

void mostrarTurnos() {
    FILE *f = fopen(EMP_FILE, "r");
    char nombre[50], apellido[50], cargo[50], turno[50], linea[300];
    int num;
    printf("\n%-15s %-20s %-20s\n", "NOMBRE", "CARGO", "TURNO");
    printf("------------------------------------------------------\n");
    while (fgets(linea, 300, f)) {
        sscanf(linea, "%d|%[^|]|%[^|]|%[^|]|%[^\n]", &num, nombre, apellido, cargo, turno);
        printf("%-20s %-20s %-20s\n", nombre, cargo, turno);
    }
    fclose(f);
}

int empleadoExiste(int num) {
    FILE *f = fopen(EMP_FILE, "r");
    char linea[300]; int n;
    while (f && fgets(linea, 300, f)) {
        sscanf(linea, "%d", &n);
        if (n == num) { fclose(f); return 1; }
    }
    if (f) fclose(f);
    return 0;
}
