#include <bits/stdc++.h>
#include <termios.h>//LIBERIA DE LINUX PARA USAR GETCH().
#include <unistd.h>
#include <stdio.h>
#include <string>
//#include<conio.h>

using namespace std;

int tam = 101;
//Funcion para trabajar en linux con getch(), debido a que no esta presente en sus librerias
int getch (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
//Funcion para trabajar en linux con getch(), debido a que no esta presente en sus librerias
int getche (void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

struct Banco{
    int cedula;
    string email;
    int celular;
    string clave;
    double saldo;
};
bool validarClave (string clave){
    int longitud, i;
    bool aux = true;
    longitud = clave.size();
    for (i = 0; i < longitud; i++){
    	// Si clave no esta en ascii de los numeros 0 a 9, la clave no es numerica.
	    if (clave[i] < 48 || clave[i] > 57){ 
		    aux = false;
            break;
	    }
    }
    return aux;
}

string capturarClave (){
    int contarLetras;
    bool comprobar = true, respuesta;
    char letra;
    string clave;
    cout << "INGRESE UNA CLAVE PARA LA CUENTA: ";
    contarLetras = 1;
    //Recibe la tecla enter del teclado como char, se arreglo bug que no permitia agregar mas caracteres( la contrasena ha de ser 4 numeros)
    //al recibir enter como char solo capturaba 3 y el enter
    //Dando un error en la linea 48 y 74, ya que la funcion validar clave va del ascii entre 48 y 57 (numeros del 0 al 9) asi que retorna t=true
    //(por lo tanto la linea 75 no se cumple).
    cin.ignore();
    do{
        //En linux usar getch() y descomentar las primeras 2 funciones, ya que son funciones definidas para usar la funcion getch().Descomentar en las lineas 11 hasta la 33 para usar esta funcion.
	letra = getch(); //Este man es tan rapido que captura el enter con char en la contrasena, produciendo un error en la validacion de la linea 48 y 74.
	//Se arreglo el error mencionado en los ultimos comentarios agregando cin.ignore en la linea 64.
	//Dia 11:07/10/12/2022 ya funciona.
	cout << "*";
	clave += letra;
	contarLetras++;
	if (contarLetras == 5){
	    comprobar = validarClave(clave);
	    if (comprobar == false){
	        contarLetras = 1;
	        system("cls");
		cout<<"\n";
            	cout << "CARACTER PROHIBIDO.\n";
        	cout << "!VERIFICA QUE LOS DATOS SEAN CORRECTOS!.\n";
       	        cout << "DIGITE NUEVAMENTE SU CONTRASENA : ";
	        clave = "";
	        cout << "\n";
		}
	}
    }while (contarLetras <= 4 || comprobar == false);
    return clave;
}

int guardar (Banco cliente[], int tam){
    for (int i = 0; i < tam; i++){
        if (cliente[i].cedula == 0 && cliente[i].email.empty() && cliente[i].celular == 0 && cliente[i].clave.empty() && cliente[i].saldo == 0){
            return i;
        }
    }
    return 100;
}

bool validarCedula (Banco cliente[], int tam, int ced){
    for (int i = 0; i < tam; i++){
        if (cliente[i].cedula == ced){
            return true;
        }
    }
    return false;
}

void consignacion (Banco cliente[], int tam, int ced){
    bool cedulaExiste = validarCedula (cliente, tam, ced);
    if (cedulaExiste == true){
        double dineroConsignado = 0;
        string persona = "";
        system ("cls");
        cin.ignore();
        cout << "CONSIGNACIONES.\n";
        cout << "INGRESE SU NOMBRE.\n~";
        fflush(stdin);
        getline (cin, persona);
        //Mostrar el nombre de la persona que consigna en mayuscula
        for(int i = 0; i < persona.size(); i++){
        	persona[i] = toupper(persona[i]);
		}
        cout << "INGRESE EL MONTO A CONSIGNAR.\n~";
        cin >> dineroConsignado;
        if (dineroConsignado >= 5000){           
            for (int i = 0; i < tam; i++){
                if (cliente[i].cedula == ced){
                    cliente[i].saldo += dineroConsignado;
                    break;
                }
            }
            cout << "EL DINERO SE HA CONSIGNADO.\nGRACIAS " << persona << " POR EL DINERO.\n";
        }
        else {
            cout << "EL MONTO MINIMO ES DE $5.000.\n";
            cout << "NO PUEDE CONSIGNAR DINERO. INTENTE NUEVAMENTE.\n";
        }
    }
    else {
        cout << "LA CUENTA NO ESTA EN NUESTRO SISTEMA.\n";
    }
}
//Funcion exclusiva para ver los datos guardados en la estructura
void verClientes (Banco cliente[], int tam){
    system("cls");
    cout << "A VER QUE HAY GUARDADO.\n";
    for (int i = 0; i < tam; i++){
        int cedula = 0; 
        cedula = cliente[i].cedula;
        if (cedula != 0){                             
            cout << "\nCliente # " << i+1 << "\n";
            cout << cliente[i].cedula << "\n";
            cout << fixed;
            cout << setprecision(2) << cliente[i].celular << "\n";
            cout << cliente[i].clave<< "\n";
            cout << cliente[i].email << "\n";
            cout << "SALDO DE LA CUENTA: " << cliente[i].saldo<< "\n";
        }
        else{
            cout << "\nINGRESE MAS CLIENTES. ( # DE ESPACIOS DISPONIBLES :" << tam-i << ")\n";
            break; // Break para romper fors esta brutal.
        }
    }
    cin.get();
}

void crearCuenta (Banco cliente[], int tam){ 
//mmm no esta guardando datos en la struct.
//Dia 9:09/10/10/2022 ya funciona.
    system("cls");
    cout << "GRACIAS POR ELEGIRNOS.\n";
    cout << "COMPLETE EL FORMULARIO PARA CREAR UNA CUENTA.\n";  
    //Dato guarda la posicion de la estructura donde el cliente no existe, posteriormente creara la cuenta del cliente en esa posicion de la estructura
    int dato = guardar(cliente, tam);
    int cedula = 0;   
	//Valida si la posicion que retorna la funcion guardar es mayor a 0 y menor que 100, ya que solo pueden existir 100 cuentas y no pueden ser menores a 0, ni mayores a 100          
        if (dato >= 0 && dato < tam){    
            cout << "INGRESE EL NUMERO DE CEDULA: ";
            cin >> cedula;
            if (!validarCedula(cliente, tam, cedula)){
                cliente[dato].cedula = cedula; 
                cout << "\nINGRESE SU EMAIL: ";
                cin >> cliente[dato].email;
                cout << "\nINGRESE SU CELULAR: ";
                cin >> cliente[dato].celular;
                cout << "\n";
                cliente[dato].clave = capturarClave();           
                cout << "\n";
                cliente[dato].saldo = 0;
            }else{
                for (int i = 0; i < tam; i++){
                    if (cliente[i].cedula == cedula){
                        cout << "EL USUARIO CON LA CEDULA: " << cliente[i].cedula << " YA TIENE UNA CUENTA.\n";
                        cin.ignore();
                        break;
                    }
                }
                return;
            }
        cout << "\nLA CUENTA SE HA CREADO.\n";
    }    
}

void menu(){
    int opcion = 0;
    Banco cliente[tam];
    do{
        system("cls");
            cout << "MENU BANCO.\n";
            cout << "1. CREACION DE UNA CUENTA.\n";
            cout << "2. CONSIGNACIONES.\n";
            cout << "3. CONSULTAS DE SALDO.\n";
            cout << "4. RETIROS.\n";
            cout << "5. INSCRIBIR PAGOS.\n";
            cout << "6. PAGOS.\n";
            cout << "7. CANCELACION DE LA CUENTA.\n";
            cout << "8. SALIR.\n";
            cout << "~  QUE DESEA HACER? :";
            cin >> opcion;  //Validar no ingresar letras.Aun falta que no se pueda ingresar letras 14/01/2023
        switch (opcion){
            case 1:{
                system("cls");
                int opc = 0;
                cout << "1. CREAR CUENTA.\n";
                cout << "2. VER CLIENTES.\n";
                cin >> opc;
                switch (opc){
                case 1:{
                    crearCuenta (cliente, tam);
                    break;
                }
                case 2:{
                    verClientes (cliente, tam);
                    break;
                }
                default:
                    system("cls");
                    cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                     cin.ignore();
                    // cin.get();
                    // return menu();
                    break;
                }
                cin.ignore();
                break;
            }
            case 2:{
                system("cls");
                // Funciona mostrando los datos de la struct banco en la posicion 0. SIRVE COMO TEST
                // cout << cliente->cedula << "\n" << cliente->celular << "\n" << cliente->clave << "\n" << cliente->email << "\n" << cliente->saldo << "\n";
                int ced = 0;
                cout << "INGRESE EL NUMERO DE CEDULA A LA CUAL VA A CONSIGNAR.\n~";
                cin >> ced;
                consignacion (cliente, tam, ced);
                cin.get();
                cin.ignore();
                break;
            }
            case 3:{
                system("clear");
                cin.ignore();
                break;
            }
            case 4:{
                system("clear");
                cin.ignore();
                break;
            }
            case 5:{
                system("clear");
                cin.ignore();
                break;
            }
            case 6:{
                system("clear");
                cin.ignore();
                break;
            }
            case 7:{
                system("clear");
                cin.ignore();
                break;
            }
            case 8:{
                system("clear");
                cout << "SALIENDO....\n";
                exit(0);
                break;
            }
            default:{
                system("cls");
                cout << "NINGUNA OPCION DISPONIBLE FUE SELECCIONADA.\n";
                cin.ignore();
                return menu();
                break;
            }
        }
    }while (opcion >= 1 && opcion < 9);
}

//Blanquear Estructura en todas sus posiciones
void datosClean (){
    Banco cliente[tam];
    for (int k = 0; k < tam; k++){ 
        cliente[k].cedula = 0;
        cliente[k].celular = 0;
        cliente[k].clave = "";
        cliente[k].email = "";
        cliente[k].saldo = 0;
    }  
}

int main (){
    datosClean ();
    menu ();
    cin.ignore();
    return 0;
}
