#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include <chrono>  // Для измерения времени

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
        printf("Вершина %d: ", i);
        for (int j : adjList[i]) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

// Процедура поиска расстояний от вершины с использованием DFS
void DFS(int node, const std::vector<std::vector<int>>& adjList, std::vector<int>& DIST, int currentDist, std::vector<bool>& visited) {
    // Если текущий путь короче, чем ранее найденный, обновляем расстояние
    if (DIST[node] == -1 || currentDist < DIST[node]) {
        DIST[node] = currentDist;
    }

    visited[node] = true; // Отмечаем вершину как посещенную

    // Обрабатываем всех соседей текущей вершины
    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {  // Если сосед ещё не был посещён
            DFS(neighbor, adjList, DIST, currentDist + 1, visited);
        }
    }

    visited[node] = false; // Размечаем вершину как не посещенную после обработки
}

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

    // Вектор для хранения расстояний для DFS
    std::vector<int> DIST_DFS(N, -1); // Инициализация всех расстояний как -1
    std::vector<bool> visited(N, false); // Вектор для отслеживания посещённых вершин

    // Измерение времени для DFS
    auto startTime = std::chrono::high_resolution_clock::now();
    DFS(startVertex, adjList, DIST_DFS, 0, visited);
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dfsDuration = endTime - startTime;

    // Выводим результат DFS
    printf("DIST (DFS) = [");
    for (int i = 0; i < N; i++) {
        printf("%d", DIST_DFS[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Время выполнения DFS: %f секунд\n", dfsDuration.count());

    return 0;
}
