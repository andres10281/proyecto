#include <iostream>
#include <malloc.h>

using namespace std;

struct nodoArbol {
    char nombreEmpresa[25];
    int codigoRNT;
    int year;
    int mes;
    int dia;
    nodoArbol *izq;
    nodoArbol *der;
};

nodoArbol *raizC = NULL, *raizF = NULL, *aux, *aux2;


int posicionarRNT(nodoArbol *aux, nodoArbol *aux2) {
    if (aux->codigoRNT < aux2->codigoRNT) {
        if (aux2->izq == NULL) {
            aux2->izq = aux;
            return 1;
        } else {
            return posicionarRNT(aux, aux2->izq);
        }
    } else {
        if (aux2->der == NULL) {
            aux2->der = aux;
            return 1;
        } else {
            return posicionarRNT(aux, aux2->der);
        }
    }
}


int posicionarFecha(nodoArbol *aux, nodoArbol *aux2) {
    if (aux->year < aux2->year) {
        if (aux2->izq != NULL) {
            return posicionarFecha(aux, aux2->izq);
        } else {
            aux2->izq = aux;
            return 1;
        }
    } else if (aux->year > aux2->year) {
        if (aux2->der != NULL) {
            return posicionarFecha(aux, aux2->der);
        } else {
            aux2->der = aux;
            return 1;
        }
    } else {
        if (aux->mes < aux2->mes) {
            if (aux2->izq != NULL) {
                return posicionarFecha(aux, aux2->izq);
            } else {
                aux2->izq = aux;
                return 1;
            }
        } else if (aux->mes > aux2->mes) {
            if (aux2->der != NULL) {
                return posicionarFecha(aux, aux2->der);
            } else {
                aux2->der = aux;
                return 1;
            }
        } else {
            if (aux->dia < aux2->dia) {
                if (aux2->izq != NULL) {
                    return posicionarFecha(aux, aux2->izq);
                } else {
                    aux2->izq = aux;
                    return 1;
                }
            } else if (aux->dia > aux2->dia) {
                if (aux2->der != NULL) {
                    return posicionarFecha(aux, aux2->der);
                } else {
                    aux2->der = aux;
                    return 1;
                }
            }
        }
    }
    return -1;
}


int eliminarNodoPrincipal(nodoArbol* &raiz, int codigoRNT) {
    if (raiz == NULL) {
        return -1;
    }
    if (codigoRNT < raiz->codigoRNT) {
        return eliminarNodoPrincipal(raiz->izq, codigoRNT);
    } else if (codigoRNT > raiz->codigoRNT) {
        return eliminarNodoPrincipal(raiz->der, codigoRNT);
    } else {
        if (raiz->izq == NULL) {
            nodoArbol* temp = raiz->der;
            delete raiz;
            raiz = temp;
            return 1;
        } else if (raiz->der == NULL) {
            nodoArbol* temp = raiz->izq;
            delete raiz;
            raiz = temp;
            return 1;
        }
        nodoArbol* temp = raiz->der;
        while (temp->izq != NULL) {
            temp = temp->izq;
        }
        raiz->codigoRNT = temp->codigoRNT;
        return eliminarNodoPrincipal(raiz->der, temp->codigoRNT);
    }
}


int eliminarNodoEspejoSubarbol(nodoArbol* &raiz, int year, int mes, int dia) {
    if (raiz == NULL) {
        return -1;
    }
    if (year < raiz->year) {
        return eliminarNodoEspejoSubarbol(raiz->izq, year, mes, dia);
    } else if (year > raiz->year) {
        return eliminarNodoEspejoSubarbol(raiz->der, year, mes, dia);
    } else {
        if (mes < raiz->mes) {
            return eliminarNodoEspejoSubarbol(raiz->izq, year, mes, dia);
        } else if (mes > raiz->mes) {
            return eliminarNodoEspejoSubarbol(raiz->der, year, mes, dia);
        } else {
            if (dia < raiz->dia) {
                return eliminarNodoEspejoSubarbol(raiz->izq, year, mes, dia);
            } else if (dia > raiz->dia) {
                return eliminarNodoEspejoSubarbol(raiz->der, year, mes, dia);
            } else {
                if (raiz->izq == NULL) {
                    nodoArbol* temp = raiz->der;
                    delete raiz;
                    raiz = temp;
                    return 1;
                } else if (raiz->der == NULL) {
                    nodoArbol* temp = raiz->izq;
                    delete raiz;
                    raiz = temp;
                    return 1;
                }
                nodoArbol* temp = raiz->der;
                while (temp->izq != NULL) {
                    temp = temp->izq;
                }
                raiz->codigoRNT = temp->codigoRNT;
                return eliminarNodoEspejoSubarbol(raiz->der, temp->year, temp->mes, temp->dia);
            }
        }
    }
    return -1;
}


void registrar() {
    aux = ((struct nodoArbol *) malloc (sizeof(struct nodoArbol)));
    cout << "Ingrese el nombre de la empresa: " << endl;
    cin >> aux->nombreEmpresa;
    cout << "Ingrese el codigo RNT: " << endl;
    cin >> aux->codigoRNT;
    cout << "Ingrese el year: ";
    cin >> aux->year;
    cout << "Ingrese el mes: ";
    cin >> aux->mes;
    cout << "Ingrese el dia: ";
    cin >> aux->dia;
    aux->izq = NULL;
    aux->der = NULL;
    if (!raizC) {
        raizC = aux;
    } else {
        aux2 = raizC;
        posicionarRNT(aux, aux2);
    }

    if (!raizF) {
        raizF = (struct nodoArbol*)malloc(sizeof(struct nodoArbol)); 
        *raizF = *aux; 
        raizF->izq = NULL;
        raizF->der = NULL;
    } else{
        aux2 = raizF;
        posicionarFecha(aux, aux2);
    }
}


void recorridoPreOrden(nodoArbol* nodo, string lado) {
    if (nodo == NULL) {
        return;
    } else {
        cout << "Moviendo hacia " << lado << ": " << nodo->codigoRNT << " " << nodo->nombreEmpresa << " " << nodo->year << "/" << nodo->mes << "/" << nodo->dia << endl;
        recorridoPreOrden(nodo->izq, "izquierdo");
        recorridoPreOrden(nodo->der, "derecho");
    }
}


void recorridoInOrden(nodoArbol* nodo, string lado) {
    if (nodo == NULL) {
        return;
    } else {
        recorridoInOrden(nodo->izq, "izquierdo");
        cout << "Moviendo hacia " << lado << ": " << nodo->codigoRNT << " " << nodo->nombreEmpresa << " " << nodo->year << "/" << nodo->mes << "/" << nodo->dia << endl;
        recorridoInOrden(nodo->der, "derecho");
    }
}


void recorridoPostOrden(nodoArbol* nodo, string lado) {
    if (nodo == NULL) {
        return;
    } else {
        recorridoPostOrden(nodo->izq, "izquierdo");
        recorridoPostOrden(nodo->der, "derecho");
        cout << "Moviendo hacia " << lado << ": " << nodo->codigoRNT << " " << nodo->nombreEmpresa << " " << nodo->year << "/" << nodo->mes << "/" << nodo->dia << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "1. Registrar una empresa" << endl;
        cout << "2. Recorrer árbol principal" << endl;
        cout << "3. Recorrer sub-árbol de fecha" << endl;
        cout << "4. Eliminar nodo del árbol principal" << endl;
        cout << "5. Eliminar nodo espejo del sub-árbol de fecha" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrar();
                break;
            case 2: {
                int subopcion;
                cout << "Recorrer árbol principal:" << endl;
                cout << "1. Recorrer preorden" << endl;
                cout << "2. Recorrer inorden" << endl;
                cout << "3. Recorrer posorden" << endl;
                cout << "Ingrese su opción: ";
                cin >> subopcion;
                switch (subopcion) {
                    case 1:
                        cout << "Recorrido preorden en árbol principal:" << endl;
                        recorridoPreOrden(raizC, "arbol principal");
                        break;
                    case 2:
                        cout << "Recorrido inorden en árbol principal:" << endl;
                        recorridoInOrden(raizC, "arbol principal");
                        break;
                    case 3:
                        cout << "Recorrido posorden en árbol principal:" << endl;
                        recorridoPostOrden(raizC, "arbol principal");
                        break;
                    default:
                        cout << "Opción no válida. Intente de nuevo." << endl;
                        break;
                }
                break;
            }
            case 3: {
                int subopcion;
                cout << "Recorrer sub-árbol de fecha:" << endl;
                cout << "1. Recorrer preorden" << endl;
                cout << "2. Recorrer inorden" << endl;
                cout << "3. Recorrer posorden" << endl;
                cout << "Ingrese su opción: ";
                cin >> subopcion;
                switch (subopcion) {
                    case 1:
                        cout << "Recorrido preorden en sub-árbol de fecha:" << endl;
                        recorridoPreOrden(raizF, "sub-arbol de fecha");
                        break;
                    case 2:
                        cout << "Recorrido inorden en sub-árbol de fecha:" << endl;
                        recorridoInOrden(raizF, "sub-arbol de fecha");
                        break;
                    case 3:
                        cout << "Recorrido posorden en sub-árbol de fecha:" << endl;
                        recorridoPostOrden(raizF, "sub-arbol de fecha");
                        break;
                    default:
                        cout << "Opción no válida. Intente de nuevo." << endl;
                        break;
                }
                break;
            }
            case 4: {
                int codigo;
                cout << "Ingrese el código RNT del nodo a eliminar: ";
                cin >> codigo;
                int resultado = eliminarNodoPrincipal(raizC, codigo);
                if (resultado == -1)
                    cout << "No se encontró el nodo con el código RNT especificado." << endl;
                else
                    cout << "Nodo eliminado exitosamente del árbol principal." << endl;
                break;
            }
            case 5: {
                int year, mes, dia;
                cout << "Ingrese la fecha (año, mes, día) del nodo espejo a eliminar: ";
                cin >> year >> mes >> dia;
                int resultado = eliminarNodoEspejoSubarbol(raizF, year, mes, dia);
                if (resultado == -1)
                    cout << "No se encontró el nodo espejo con la fecha especificada." << endl;
                else
                    cout << "Nodo espejo eliminado exitosamente del sub-árbol de fecha." << endl;
                break;
            }
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}




