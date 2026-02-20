#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>  // Para manejo de archivos
#include<string>   // Para leer cadenas
#include<sstream>  // Para partir cadenas por comas
#include<queue>
#include <algorithm>

struct Nodo{
    int dato;
    Nodo *der;
    Nodo *izq;
};

// Prototipos
void menu();
Nodo *crearNodo(int);
void insertarNodo(Nodo *&, int);
void mostrarArbol(Nodo *, int);
bool buscarNodo(Nodo *, int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);

// Funciones para archivos
void guardarArbol(Nodo *, std::ofstream &); // Auxiliar recursiva
void guardarCSV(Nodo *);                    // Función principal de guardado
void cargarCSV(Nodo *&);                    // Función de carga

Nodo *arbol = NULL;

int main(){
    menu();
    return 0;
}

// --- Función de menú ---
void menu(){
    int dato, opcion, contador = 0;
    do{
        system("clear"); // Limpiar pantalla en Linux

        std::cout << "\t:.. MENU ARBOL BINARIO ..:." << std::endl;
        std::cout << "1. Insertar un nuevo nodo" << std::endl;
        std::cout << "2. Mostrar el arbol completo (Grafico)" << std::endl;
        std::cout << "3. Buscar un nodo" << std::endl;
        std::cout << "4. Recorrido Pre-Orden" << std::endl;
        std::cout << "5. Recorrido In-Orden" << std::endl;
        std::cout << "6. Recorrido Post-Orden" << std::endl;
        std::cout << "7. Guardar arbol en CSV" << std::endl;
        std::cout << "8. Cargar arbol desde CSV" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch(opcion){
            case 1: 
                std::cout << "\n Digite un numero: ";
                std::cin >> dato;
                insertarNodo(arbol, dato);
                std::cout << "\n";
                break;
            case 2: 
                std::cout << "\nMostrando el arbol completo:\n\n";
                mostrarArbol(arbol, contador);
                std::cout << "\n";
                break;
            case 3:
                std::cout << "\n Digite el numero a buscar: ";
                std::cin >> dato;
                if(buscarNodo(arbol, dato)){
                    std::cout << "\nEl nodo " << dato << " SI ha sido encontrado en el arbol.\n";
                } else {
                    std::cout << "\nEl nodo NO existe.\n";
                }
                break;
            case 4:
                std::cout << "\nRecorrido Pre-Orden: ";
                preOrden(arbol);
                std::cout << "\n";
                break;
            case 5:
                std::cout << "\nRecorrido In-Orden: ";
                inOrden(arbol);
                std::cout << "\n";
                break;
            case 6:
                std::cout << "\nRecorrido Post-Orden: ";
                postOrden(arbol);
                std::cout << "\n";
                break;
            case 7:
                guardarCSV(arbol);
                break;
            case 8:
                cargarCSV(arbol);
                break;
        }
        
        if(opcion != 9){
            std::cout << "\nPresione Enter para continuar...";
            std::cin.ignore();
            std::cin.get();
        }

    }while (opcion != 9);    
}

// Función para crear un nodo
Nodo *crearNodo(int n){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo -> dato = n;
    nuevo_nodo -> der = NULL;
    nuevo_nodo -> izq = NULL;
    return nuevo_nodo;
}

// Función para insertar elementos (lógica BST)
void insertarNodo(Nodo *&arbol, int n){
    if (arbol == NULL){ 
        Nodo *nuevo_nodo = crearNodo(n);
        arbol = nuevo_nodo;
    }else{ 
        int valorRaiz = arbol -> dato;
        if (n < valorRaiz){ 
            insertarNodo(arbol -> izq, n);
        }else{ 
            insertarNodo(arbol -> der, n);
        }        
    }
}

// Función para mostrar el árbol gráficamente (acostado)
void mostrarArbol(Nodo *arbol, int cont){
    if (arbol == NULL){ 
        return;
    }else{
        mostrarArbol(arbol -> der, cont+1);
        for (int i = 0; i < cont; i++){
            std::cout << "   ";
        }
        std::cout << arbol -> dato << std::endl;
        mostrarArbol(arbol -> izq, cont+1);
    }
}

// Función para buscar nodo
bool buscarNodo(Nodo *arbol, int n){
    if(arbol == NULL){
        return false;
    }
    else if(arbol->dato == n){
        return true;
    }
    else if(n < arbol->dato){
        return buscarNodo(arbol->izq, n);
    }
    else{
        return buscarNodo(arbol->der, n);
    }
}

bool searchNode(Node *arbol, int key){
    bool present = false;

    while (root != nulltpr){
        
    }
    
}


// Funciones para recorridos del árbol
void preOrden(Nodo *arbol){ // Raíz - Izq - Der
    if(arbol == NULL) return;
    std::cout << arbol->dato << " - ";
    preOrden(arbol->izq);
    preOrden(arbol->der);
}

void inOrden(Nodo *arbol){ // Izq - Raíz - Der
    if(arbol == NULL) return;
    inOrden(arbol->izq);
    std::cout << arbol->dato << " - ";
    inOrden(arbol->der);
}

void postOrden(Nodo *arbol){ // Izq - Der - Raíz
    if(arbol == NULL) return;
    postOrden(arbol->izq);
    postOrden(arbol->der);
    std::cout << arbol->dato << " - ";
}

// Función para serializar (guardar a CSV)
// Usamos Pre-Orden para guardar porque facilita la reconstrucción
void guardarArbol(Nodo *arbol, std::ofstream &archivo){
    if(arbol == NULL) return;
    
    archivo << arbol->dato << ","; // Escribimos dato y coma
    guardarArbol(arbol->izq, archivo);
    guardarArbol(arbol->der, archivo);
}

void guardarCSV(Nodo *arbol){
    std::ofstream archivo;
    archivo.open("arbol.csv", std::ios::out); // Crea o sobrescribe

    if(archivo.fail()){
        std::cout << "No se pudo abrir el archivo para guardar.";
        return;
    }

    guardarArbol(arbol, archivo);
    archivo.close();
    std::cout << "\nArbol guardado exitosamente en 'arbol.csv'";
}

// Función para deserializar (cargar de CSV)
void cargarCSV(Nodo *&arbol){
    std::ifstream archivo;
    archivo.open("arbol.csv", std::ios::in);

    if(archivo.fail()){
        std::cout << "No se encontro el archivo 'arbol.csv'";
        return;
    }

    std::string linea;
    std::string valorStr;
    
    // Leemos toda la linea del CSV
    while(getline(archivo, linea)){
        std::stringstream ss(linea); // Convertimos la linea en stream para partirla
        
        while(getline(ss, valorStr, ',')){ // Partimos por comas
            if(!valorStr.empty()){
                int valor = std::stoi(valorStr); // Convertir string a int
                insertarNodo(arbol, valor);      // Insertamos usando la lógica existente
            }
        }
    }
    
    archivo.close();
    std::cout << "\nArbol cargado correctamente desde el archivo.";
}

queue<Node> q
q.push(node)
while (!q.empty)
{
    current q.front -> q.pop
    print(current -> value)
    if (current ->left!=null)
    {
        q.push(current -> left)
    }
    if (current -> right != NULL)
    {
        q.push(current ->right)
    }
}

void levelOrderTraversal(Node* root) { //distancia
    if (root == nullptr) {
        return;
    }
    queue<Node*> q;

    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();                   

        // Imprimir
        cout << current->value << " ";

        // Meter hijos a la cola
        if (current->left != nullptr) {
            q.push(current->left);
        }

        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

using namespace std;

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    // Calculamos la altura de cada subárbol y sumamos 1 (la raíz)
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    
    return max(leftHeight, rightHeight) + 1;
}

// 2. Función recursiva para imprimir los nodos de un nivel específico
void printGivenLevel(Node* root, int level) {
    if (root == nullptr) {
        return;
    }
    
    // Si llegamos al nivel objetivo, imprimimos el valor
    if (level == 1) {
        cout << root->value << " ";
    } 
    // Si aún no llegamos, bajamos un nivel hacia los hijos
    else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

// 3. Función principal que unifica todo
void levelOrderTraversal(Node* root) {
    int height = getHeight(root);
    
    // Llamamos a la función recursiva para cada nivel del árbol
    for (int i = 1; i <= height; i++) {
        printGivenLevel(root, i);
    }
}

//tarea: serializar y deserializar
//tarea: hacer el while de ciclo a una funcion recursiva, funcion levelordertraversal