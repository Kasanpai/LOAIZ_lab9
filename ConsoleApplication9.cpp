
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <vector>

// Функция генерации матрицы смежности
void generateAdjacencyMatrix(int** matrix, int N) {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Генерация матрицы смежности
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // С вероятностью 0.5 устанавливаем ребро между вершинами
            int edge = rand() % 2;
            matrix[i][j] = edge;
            matrix[j][i] = edge;  // Для неориентированного графа симметрично
        }
    }

    // Диагональные элементы должны быть равны 0 (нет петель)
    for (int i = 0; i < N; i++) {
        matrix[i][i] = 0;
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

// Процедура поиска кратчайших расстояний от вершины v
void BFS(int** matrix, int N, int v, std::vector<int>& DIST) {
    // Инициализируем вектор расстояний как -1 (не посещены)
    DIST.assign(N, -1);

    // Используем очередь для обхода графа
    std::queue<int> Q;
    Q.push(v);  // Добавляем начальную вершину
    DIST[v] = 0;  // Расстояние до самой себя равно 0

    // Пока очередь не пуста, продолжаем обход
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        // Обрабатываем всех соседей текущей вершины
        for (int i = 0; i < N; i++) {
            if (matrix[node][i] == 1 && DIST[i] == -1) {
                // Если сосед ещё не посещён, добавляем в очередь
                Q.push(i);
                DIST[i] = DIST[node] + 1;  // Обновляем расстояние
            }
        }
    }
}

// Основная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    printf("Введите количество вершин в графе: ");
    scanf("%d", &N);

    // Выделение памяти для матрицы смежности
    int** adjacencyMatrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adjacencyMatrix[i] = (int*)malloc(N * sizeof(int));
    }

    // Генерация матрицы смежности
    generateAdjacencyMatrix(adjacencyMatrix, N);

    // Вывод матрицы смежности
    printAdjacencyMatrix(adjacencyMatrix, N);

    // Ввод исходной вершины для поиска расстояний
    int startVertex;
    printf("Введите исходную вершину для поиска расстояний: ");
    scanf("%d", &startVertex);
    startVertex = startVertex - 1;
    // Вектор для хранения расстояний
    std::vector<int> DIST;

    // Выполняем поиск в ширину (BFS)
    BFS(adjacencyMatrix, N, startVertex, DIST);

    // Выводим результат
    printf("Расстояния от вершины %d до всех других вершин:\n", startVertex + 1);
    for (int i = 0; i < N; i++) {
        printf("До вершины %d: %d\n", i + 1, DIST[i]);
    }

    printf("DIST = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);

    return 0;
}