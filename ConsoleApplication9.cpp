
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <iostream>
#include <chrono>  // Для измерения времени

using namespace std;

// Структура для представления вершины в списке смежности
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Функция для добавления вершины в список смежности
void addEdge(Node** adjList, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Функция генерации матрицы смежности
void generateAdjacencyMatrix(int** matrix, int N) {
    srand((unsigned int)time(NULL)); // Инициализация генератора случайных чисел

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2; // Генерация ребра с вероятностью 0.5
            matrix[i][j] = edge;
            matrix[j][i] = edge; // Симметрично для неориентированного графа
        }
        matrix[i][i] = 0; // Диагональные элементы равны 0
    }
}

// Функция вывода матрицы смежности
void printAdjacencyMatrix(int** matrix, int N) {
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для генерации списка смежности
void generateAdjacencyList(Node** adjList, int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrix[i][j] == 1) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = j;
                newNode->next = adjList[i];
                adjList[i] = newNode;

                newNode = (Node*)malloc(sizeof(Node));
                newNode->vertex = i;
                newNode->next = adjList[j];
                adjList[j] = newNode;
            }
        }
    }
}

// Функция для вывода списка смежности
void printAdjacencyList(Node** adjList, int N) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("Вершина %d: ", i);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


// Функция поиска кратчайших расстояний с помощью BFS
void BFSmatx(int** matrix, int N, int v, int* DIST) {
    for (int i = 0; i < N; i++) DIST[i] = -1; // Инициализация расстояний
    int* queue = (int*)malloc(N * sizeof(int)); // Очередь
    int front = 0, back = 0;

    queue[back++] = v;
    DIST[v] = 0;

    while (front < back) {
        int node = queue[front++];
        for (int i = 0; i < N; i++) {
            if (matrix[node][i] == 1 && DIST[i] == -1) {
                queue[back++] = i;
                DIST[i] = DIST[node] + 1;
            }
        }
    }
    free(queue);
}

// Функция поиска кратчайших расстояний с помощью DFS
void DFSmatx(int** matrix, int N, int v, int* DIST) {
    for (int i = 0; i < N; i++) {
        DIST[i] = -1; // Инициализация расстояний как -1
    }

    int* stack = (int*)malloc(N * sizeof(int)); // Создаём стек
    int top = -1; // Индекс вершины стека

    stack[++top] = v; // Добавляем стартовую вершину в стек
    DIST[v] = 0; // Расстояние до стартовой вершины равно 0

    while (top >= 0) {
        int node = stack[top--]; // Берём вершину из стека

        for (int i = 0; i < N; i++) {
            if (matrix[node][i] == 1 && DIST[i] == -1) { // Если есть связь и вершина ещё не посещена
                stack[++top] = i; // Добавляем вершину в стек
                DIST[i] = DIST[node] + 1; // Обновляем расстояние
            }
        }
    }

    free(stack); // Освобождаем память
}

// Процедура поиска кратчайших расстояний от вершины с использованием BFS
void BFS(int startVertex, Node** adjList, int N, int* DIST) {
    queue<int> q;
    q.push(startVertex);
    DIST[startVertex] = 0;  // Расстояние до начальной вершины всегда 0

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Обрабатываем всех соседей текущей вершины
        Node* temp = adjList[current];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (DIST[neighbor] == -1) { // Если вершина ещё не была посещена
                DIST[neighbor] = DIST[current] + 1;
                q.push(neighbor);
            }
            temp = temp->next;
        }
    }
}

// Процедура поиска расстояний от вершины с использованием DFS
void DFS(int node, Node** adjList, int* DIST, int currentDist, bool* visited, int N) {
    // Если текущий путь короче, чем ранее найденный, обновляем расстояние
    if (DIST[node] == -1 || currentDist < DIST[node]) {
        DIST[node] = currentDist;
    }

    visited[node] = true; // Отмечаем вершину как посещенную

    // Обрабатываем всех соседей текущей вершины
    Node* temp = adjList[node];
    while (temp != NULL) {
        int neighbor = temp->vertex;
        if (!visited[neighbor]) {  // Если сосед ещё не был посещён
            DFS(neighbor, adjList, DIST, currentDist + 1, visited, N);
        }
        temp = temp->next;
    }

    visited[node] = false; // Размечаем вершину как не посещенную после обработки
}






int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    // Создание и инициализация матрицы смежности
    int** adjacencyMatrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adjacencyMatrix[i] = (int*)malloc(N * sizeof(int));
    }


    // Создание списка смежности
    Node** adjList = (Node**)malloc(N * sizeof(Node*));
    for (int i = 0; i < N; i++) {
        adjList[i] = NULL;
    }

    generateAdjacencyMatrix(adjacencyMatrix, N);

    // Ввод исходной вершины для поиска расстояний
    int startVertex;
    printf("Введите исходную вершину для поиска расстояний: ");
    scanf("%d", &startVertex);


    // Вывод матрицы смежности
    printf("Матрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    generateAdjacencyList(adjList, adjacencyMatrix, N);
    // Вывод списка смежности
    printAdjacencyList(adjList, N);

    // Массив для хранения расстояний
    int* DIST = (int*)malloc(N * sizeof(int));

    // BFS

    auto startTime1 = chrono::high_resolution_clock::now();
    BFSmatx(adjacencyMatrix, N, startVertex, DIST);
    auto endTime1 = chrono::high_resolution_clock::now();
    chrono::duration<double> dfsMDuration1 = endTime1 - startTime1;

    printf("DIST (BFS) = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
    printf("Время выполнения BFS: %f секунд\n", dfsMDuration1.count());
    // DFS
    auto startTime2 = chrono::high_resolution_clock::now();
    DFSmatx(adjacencyMatrix, N, startVertex, DIST);
    auto endTime2 = chrono::high_resolution_clock::now();
    chrono::duration<double> dfsMDuration2 = endTime2 - startTime2;

    printf("DIST (DFS) = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST[i]);
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
    printf("Время выполнения DFS: %f секунд\n", dfsMDuration2.count());
    // Очистка памяти
    for (int i = 0; i < N; i++) {
        free(adjacencyMatrix[i]);
    }





    // Массив для хранения расстояний для BFS
    int* DIST_BFS = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        DIST_BFS[i] = -1;  // Инициализация всех расстояний как -1
    }

    // Измерение времени для BFS
    auto startTime = chrono::high_resolution_clock::now();
    BFS(startVertex, adjList, N, DIST_BFS);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> bfsDuration = endTime - startTime;

    // Выводим результат BFS
    printf("DIST (BFS) = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST_BFS[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Время выполнения BFS: %f секунд\n", bfsDuration.count());

    // Массив для хранения расстояний для DFS
    int* DIST_DFS = (int*)malloc(N * sizeof(int));
    bool* visited = (bool*)malloc(N * sizeof(bool));
    for (int i = 0; i < N; i++) {
        DIST_DFS[i] = -1;  // Инициализация всех расстояний как -1
        visited[i] = false; // Инициализация массива посещённых вершин
    }

    // Измерение времени для DFS
    auto startTime4 = chrono::high_resolution_clock::now();
    DFS(startVertex, adjList, DIST_DFS, 0, visited, N);
    auto endTime4 = chrono::high_resolution_clock::now();
    chrono::duration<double> dfsDuration4 = endTime4 - startTime4;

    // Выводим результат DFS
    printf("DIST (DFS) = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST_DFS[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Время выполнения DFS: %f секунд\n", dfsDuration4.count());

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        Node* temp = adjList[i];
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }

    free(adjList);

    free(DIST_BFS);
    free(DIST_DFS);
    free(visited);

    return 0;
}