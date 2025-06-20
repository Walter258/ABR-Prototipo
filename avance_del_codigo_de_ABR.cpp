#include <iostream>
#include <string>
using namespace std;

struct Persona {
    string nombre;
    string fechaNacimiento;
    string id;
    string genero;
    string rol;
    string lugarNacimiento;

    Persona* izquierda;
    Persona* derecha;
};

// Crear nuevo nodo
Persona* crearNodo(string nombre, string fecha, string id, string genero, string rol, string lugar) {
    Persona* nuevo = new Persona();
    nuevo->nombre = nombre;
    nuevo->fechaNacimiento = fecha;
    nuevo->id = id;
    nuevo->genero = genero;
    nuevo->rol = rol;
    nuevo->lugarNacimiento = lugar;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

// Insertar nodo (por nombre)
Persona* insertar(Persona* raiz, Persona* nuevo) {
    if (raiz == NULL) {
        return nuevo;
    }
    if (nuevo->nombre < raiz->nombre) {
        raiz->izquierda = insertar(raiz->izquierda, nuevo);
    } else {
        raiz->derecha = insertar(raiz->derecha, nuevo);
    }
    return raiz;
}

// Buscar por nombre
Persona* buscar(Persona* raiz, string nombre) {
    if (raiz == NULL || raiz->nombre == nombre) {
        return raiz;
    }
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

// Nodo con valor mínimo
Persona* minimoNodo(Persona* nodo) {
    Persona* actual = nodo;
    while (actual && actual->izquierda != NULL)
        actual = actual->izquierda;
    return actual;
}

// Eliminar nodo
Persona* eliminar(Persona* raiz, string nombre) {
    if (raiz == NULL) return raiz;

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
        if (raiz->izquierda == NULL) {
            Persona* temp = raiz->derecha;
            delete raiz;
            return temp;
        } else if (raiz->derecha == NULL) {
            Persona* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        Persona* temp = minimoNodo(raiz->derecha);
        raiz->nombre = temp->nombre;
        raiz->fechaNacimiento = temp->fechaNacimiento;
        raiz->id = temp->id;
        raiz->genero = temp->genero;
        raiz->rol = temp->rol;
        raiz->lugarNacimiento = temp->lugarNacimiento;
        raiz->derecha = eliminar(raiz->derecha, temp->nombre);
    }
    return raiz;
}

// Recorridos
void inOrder(Persona* raiz) {
    if (raiz != NULL) {
        inOrder(raiz->izquierda);
        cout << raiz->nombre << " - " << raiz->fechaNacimiento << endl;
        inOrder(raiz->derecha);
    }
}

void preOrder(Persona* raiz) {
    if (raiz != NULL) {
        cout << raiz->nombre << " - " << raiz->fechaNacimiento << endl;
        preOrder(raiz->izquierda);
        preOrder(raiz->derecha);
    }
}

void postOrder(Persona* raiz) {
    if (raiz != NULL) {
        postOrder(raiz->izquierda);
        postOrder(raiz->derecha);
        cout << raiz->nombre << " - " << raiz->fechaNacimiento << endl;
    }
}

// Simular recorrido por niveles sin <queue>
void recorridoPorNivel(Persona* raiz) {
    if (raiz == NULL) return;

    Persona* cola[100];
    int inicio = 0, fin = 0;
    cola[fin++] = raiz;

    while (inicio < fin) {
        Persona* actual = cola[inicio++];
        cout << actual->nombre << " - " << actual->rol << endl;

        if (actual->izquierda != NULL)
            cola[fin++] = actual->izquierda;
        if (actual->derecha != NULL)
            cola[fin++] = actual->derecha;
    }
}

// Programa principal
int main() {
    Persona* raiz = NULL;

    raiz = insertar(raiz, crearNodo("Carlos Torres", "1975-04-10", "001", "M", "Padre", "Lima"));
    raiz = insertar(raiz, crearNodo("Ana Torres", "2001-09-15", "002", "F", "Hija", "Lima"));
    raiz = insertar(raiz, crearNodo("Luis Torres", "1999-03-05", "003", "M", "Hijo", "Lima"));
    raiz = insertar(raiz, crearNodo("Sofia Torres", "2023-05-30", "004", "F", "Nieta", "Huancayo"));

    cout << "=== Recorrido InOrder ===\n";
    inOrder(raiz);

    cout << "\n=== Recorrido PreOrder ===\n";
    preOrder(raiz);

    cout << "\n=== Recorrido PostOrder ===\n";
    postOrder(raiz);

    cout << "\n=== Recorrido por Nivel (simulado) ===\n";
    recorridoPorNivel(raiz);

    return 0;
}
