// File: GameUnitMovement.c
#include "GameUnitMovement.h"

#include "GameUnit.h"
#include "Constants.h"
#include "GameCamera.h"
#include "GameUI.h"
#include "GameUnitSelection.h"
#include "GenList.h"
#include "GameMap.h"

#include "raylib.h"
#include "raymath.h"

#include <stdbool.h>
#include <stdio.h>


// Estrutura e variáveis usadas pelo algoritmo A*

typedef struct PathNode {
    Vector2 position;
    int g_cost;
    int h_cost;
    int f_cost;
    struct PathNode* parent;
} PathNode;

const int heuristicNoise = 5;
const int tiebreakerNoise = 10;

List* PathList = NULL;

static Vector2 currentWaypoint;


// Funções de comparação

static int FindByPositionFn(void* context, void* data) {
    Vector2* targetPosition = (Vector2*)context;
    PathNode* node = (PathNode*)data;
    return (node->position.x == targetPosition->x && node->position.y == targetPosition->y);
}

static int CompareByFCostFn(void* data1, void* data2) {
    PathNode* node1 = (PathNode*)data1;
    PathNode* node2 = (PathNode*)data2;

    if (node1->f_cost < node2->f_cost) return -1;
    if (node1->f_cost > node2->f_cost) return 1;
    return 0;
}


// Outras funções auxiliares

// TODO: matar isso aqui quando as unidades ganharem autonomia.
static Vector2 GetMouseToGameGrid() { 
    Vector2 mousePos = GetMousePosition();
    Vector2 worldPos = GetScreenToWorld2D(mousePos, GameCamera);
    return (Vector2) {
        floorf(worldPos.x / CONSTANTS_TILE_SIZE_F),
            floorf(worldPos.y / CONSTANTS_TILE_SIZE_F)
    };
}

// TODO: Mapa deve cuidar de todos esses tipos de conversão.
static Vector2 GetGameGridToWorld(Vector2 gridPos) { 
    return (Vector2) {
        gridPos.x* CONSTANTS_TILE_SIZE_F,
            gridPos.y* CONSTANTS_TILE_SIZE_F
    };
}

// TODO: Essa função se encaixa melhor no Map.
static bool IsValidGridPosition(Vector2 pos) {
    if (pos.x >= 0 && pos.x < MAP_WIDTH && 
        pos.y >= 0 && pos.y < MAP_HEIGHT) {
        return GameMap.Grid[(int)pos.x][(int)pos.y].isWalkable;
    }
    return false;
}

static int CalculateHeuristic(Vector2 a, Vector2 b) {
    return abs(a.x - b.x) + abs(a.y - b.y) + GetRandomValue(0, tiebreakerNoise);
}

// Encontra um nó em uma lista usando a função de predicado, passando a posição como contexto.
static PathNode* FindNodeInList(List* list, Vector2 position) {
    if (!list) return NULL;
    return (PathNode*)List_FindWithFn(list, &position, FindByPositionFn);
}

// Reconstrói o caminho final a partir do nó de destino, revertendo a ordem.
static void ReconstructPath(PathNode* endNode) {
    if (PathList) List_Destroy(PathList);
    PathList = List_Create(sizeof(Vector2));

    PathNode* current = endNode;
    while (current != NULL) {
        if (!List_Add(PathList, &current->position)) return;
        current = current->parent;
    }
}

// Embaralha um array de vizinhos para criar caminhos diferentes (Fisher-Yates shuffle).
static void ShuffleNeighbors(Vector2 array[], int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            int j = GetRandomValue(0, i);
            Vector2 temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

// Implementação do A*
void GameUnitMovement_BuildPath(Vector2 start, Vector2 end) {
    if (PathList) {
        List_Destroy(PathList);
        PathList = NULL;
    }

    if (!IsValidGridPosition(start) || !IsValidGridPosition(end)) return;

    List* openList = List_Create(sizeof(PathNode));
    List* closedList = List_Create(sizeof(PathNode));

    // Configura o nó inicial
    PathNode startNode;

    startNode.position = start;
    startNode.g_cost = 0;
    startNode.h_cost = CalculateHeuristic(start, end);
    startNode.f_cost = startNode.g_cost + (startNode.h_cost * heuristicNoise);
    startNode.parent = NULL;

    List_AddWithFn(openList, &startNode, CompareByFCostFn);

    while (openList->size > 0) {
        // O melhor nó é sempre o primeiro, pois a lista está ordenada
        PathNode bestNodeData = *(PathNode*)List_GetByIndex(openList, 0);
        List_RemoveFirst(openList);

        // Move o melhor nó da lista aberta para a fechada
        List_AddLast(closedList, &bestNodeData);

        // Obtém um ponteiro estável para o nó que acabamos de adicionar na lista fechada
        PathNode* currentNodeInClosedList = (PathNode*)closedList->tail->data;

        // Se chegamos ao destino, reconstrói o caminho e finaliza
        if (currentNodeInClosedList->position.x == end.x && currentNodeInClosedList->position.y == end.y) {
            ReconstructPath(currentNodeInClosedList);
            List_Destroy(openList);
            List_Destroy(closedList);
            return;
        }

        // Analisa os vizinhos
        Vector2 neighbors[4] = {
            {currentNodeInClosedList->position.x, currentNodeInClosedList->position.y - 1}, // Up
            {currentNodeInClosedList->position.x, currentNodeInClosedList->position.y + 1}, // Down
            {currentNodeInClosedList->position.x - 1, currentNodeInClosedList->position.y}, // Left
            {currentNodeInClosedList->position.x + 1, currentNodeInClosedList->position.y}  // Right
        };

        ShuffleNeighbors(neighbors, 4);

        for (int i = 0; i < 4; i++) {
            Vector2 neighborPos = neighbors[i];

            // Ignora vizinho inválido ou já na lista fechada
            if (!IsValidGridPosition(neighborPos)) continue;
            if (FindNodeInList(closedList, neighborPos)) continue; 

            int tentative_g_cost = currentNodeInClosedList->g_cost + 1;
            PathNode* neighborInOpenList = FindNodeInList(openList, neighborPos);

            // Se o vizinho já está na openList com um custo maior, não faz nada
            if (neighborInOpenList != NULL && tentative_g_cost >= neighborInOpenList->g_cost) {
                continue;
            }

            // Se o vizinho estava na openList, removemos a versão antiga para adicionar a nova, com custo menor
            if (neighborInOpenList != NULL) {
                List_RemoveWithFn(openList, &neighborPos, FindByPositionFn);
            }

            // Cria o nó vizinho atualizado e o adiciona na openList
            PathNode newNeighborNode;
            newNeighborNode.parent = currentNodeInClosedList;
            newNeighborNode.position = neighborPos;
            newNeighborNode.g_cost = tentative_g_cost;
            newNeighborNode.h_cost = CalculateHeuristic(neighborPos, end);
            newNeighborNode.f_cost = newNeighborNode.g_cost + (newNeighborNode.h_cost * heuristicNoise);

            List_AddWithFn(openList, &newNeighborNode, CompareByFCostFn);
        }
    }

    // Se a openList esvaziar e não acharmos o caminho, limpa as listas.
    List_Destroy(openList);
    List_Destroy(closedList);
}


// Outras funções


// TODO: Descarrega a lista de movimentos de uma GameUnit
void GameUnitMovement_Unload(void) {
    if (PathList) {
        List_Destroy(PathList);
        PathList = NULL;
    }
}

void GameUnitMovement_Update(void) {
    GameUnit* unit = SelectedUnit;
    if (!unit || !PathList || PathList->size == 0) return;

    // Pega o próximo ponto do caminho
    Vector2* nextGridPosPtr = (Vector2*)List_GetByIndex(PathList, 0);
    if (!nextGridPosPtr) return;

    currentWaypoint = GetGameGridToWorld(*nextGridPosPtr);
    unit->Destination = currentWaypoint;
    float movementSpeed = 500.0f;
    float displacement = movementSpeed * GetFrameTime();

    // Move a unidade em direção ao ponto
    if (Vector2Distance(*unit->Position, unit->Destination) > displacement) {
        float angle = atan2f(unit->Destination.y - unit->Position->y, unit->Destination.x - unit->Position->x);
        unit->Position->x += cosf(angle) * displacement;
        unit->Position->y += sinf(angle) * displacement;
    }
    else {
        // Se chegou ao ponto, atualiza a posição e remove o ponto do caminho
        *unit->Position = unit->Destination;
        List_RemoveFirst(PathList);
    }
}

void GameUnitMovement_HandleInput(void) {
    if (SelectedUnit && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 startGridPos = {
            floorf(SelectedUnit->Position->x / CONSTANTS_TILE_SIZE_F),
            floorf(SelectedUnit->Position->y / CONSTANTS_TILE_SIZE_F)
        };
        Vector2 endGridPos = GetMouseToGameGrid();
        GameUnitMovement_BuildPath(startGridPos, endGridPos);
    }
}

void DEBUG_BigUpdate(void) {
    GameUnitMovement_HandleInput();
    GameUnitMovement_Update();
}
