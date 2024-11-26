#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <queue>
#include <vector>
#include <iostream>

// Функция генерации графа с использованием списков смежности
void generateAdjacencyList(std::vector<std::vector<int>>& adjList, int N) {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    // Генерация списка смежности
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int edge = rand() % 2;
            if (edge == 1) {
                adjList[i].push_back(j);
                adjList[j].push_back(i); // Для неориентированного графа
            }
        }
    }
}

// Функция вывода списка смежности
void printAdjacencyList(const std::vector<std::vector<int>>& adjList, int N) {
    printf("Список смежности:\n");
    for (int i = 0; i < N; i++) {
        printf("Вершина %d: ", i+1);
        for (int j : adjList[i]) {
            printf("%d ", j+1);
        }
        printf("\n");
    }
}

// Процедура поиска кратчайших расстояний от вершины v
void BFS(const std::vector<std::vector<int>>& adjList, int N, int v, std::vector<int>& DIST) {
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
        for (int neighbor : adjList[node]) {
            if (DIST[neighbor] == -1) {
                // Если сосед ещё не посещён, добавляем в очередь
                Q.push(neighbor);
                DIST[neighbor] = DIST[node] + 1;  // Обновляем расстояние
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

    // Создание списка смежности
    std::vector<std::vector<int>> adjList(N);

    // Генерация графа
    generateAdjacencyList(adjList, N);

    // Вывод списка смежности
    printAdjacencyList(adjList, N);

    // Ввод исходной вершины для поиска расстояний
    int startVertex;
    printf("Введите исходную вершину для поиска расстояний: ");
    scanf("%d", &startVertex);
    startVertex = startVertex - 1;

    // Вектор для хранения расстояний
    std::vector<int> DIST;

    // Выполняем поиск в ширину (BFS)
    BFS(adjList, N, startVertex, DIST);

    // Выводим результат в нужном формате
    printf("DIST = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}
