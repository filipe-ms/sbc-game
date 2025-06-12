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
#include <stdlib.h>
#include <float.h>
#include <time.h>

//=====================================
// Estruturas e variáveis do Pathfinding A*
//=====================================

typedef struct PathNode {
    Vector2 position;
    float g_cost;
    float h_cost;
    float f_cost;
    struct PathNode* parent;
} PathNode;

List* PathList = NULL;
static Vector2 currentWaypoint;

//=====================================
// Funções Auxiliares (Grid, A*, Listas)
//=====================================

static Vector2 GetMouseToGameGrid() {
    Vector2 mousePos = GetMousePosition();
    Vector2 worldPos = GetScreenToWorld2D(mousePos, GameCamera);
    return (Vector2) {
        floorf(worldPos.x / CONSTANTS_TILE_SIZE_F),
            floorf(worldPos.y / CONSTANTS_TILE_SIZE_F)
    };
}

static Vector2 GetGameGridToWorld(Vector2 gridPos) {
    return (Vector2) {
        gridPos.x* CONSTANTS_TILE_SIZE_F,
            gridPos.y* CONSTANTS_TILE_SIZE_F
    };
}

static bool IsValidGridPosition(Vector2 pos) {
    if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT) {
        return GameMap.Grid[(int)pos.x][(int)pos.y].isWalkable;
    }
    return false;
}

// Adicionada uma pequena variação aleatória para tornar os caminhos menos previsíveis.
static float CalculateHeuristic(Vector2 a, Vector2 b) {
    float random_factor = (float)rand() / (float)RAND_MAX * 5.0f;
    return fabsf(a.x - b.x) + fabsf(a.y - b.y) + random_factor;
}

static PathNode* FindNodeInList(List* list, Vector2 position) {
    if (!list) return NULL;
    Node* current = list->head;
    while (current) {
        PathNode* p_node = (PathNode*)current->data;
        if (p_node->position.x == position.x && p_node->position.y == position.y) {
            return p_node;
        }
        current = current->next;
    }
    return NULL;
}

// Reconstrói o caminho final a partir do nó de destino
static void ReconstructPath(PathNode* endNode) {
    if (PathList) {
        List_Destroy(PathList);
    }
    PathList = List_Create(sizeof(Vector2));

    PathNode* current = endNode;
    while (current != NULL) {
        // Adiciona no início da lista para inverter a ordem
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) return; // Falha na alocação
        new_node->data = malloc(sizeof(Vector2));
        if (!new_node->data) { free(new_node); return; } // Falha na alocação

        *(Vector2*)new_node->data = current->position;
        new_node->next = PathList->head;
        PathList->head = new_node;
        if (!PathList->tail) {
            PathList->tail = new_node;
        }
        PathList->size++;

        current = current->parent;
    }
}

// IMPLEMENTADO: Função para embaralhar um array de vizinhos (Fisher-Yates shuffle)
static void ShuffleNeighbors(Vector2 array[], int n) {
    if (n > 1) {
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Vector2 temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

//=====================================
// Lógica Principal do A*
//=====================================

void GameUnitMovement_BuildPath(Vector2 start, Vector2 end) {
    // IMPORTANTE: Para uma aleatoriedade melhor, a função srand() deve ser chamada
    // apenas uma vez no início do seu programa (ex: na função main).
    // Estou deixando aqui para garantir que a funcionalidade do TODO seja atendida
    // de forma auto-contida neste arquivo.
    srand(time(NULL));

    if (PathList) {
        List_Destroy(PathList);
        PathList = NULL;
    }

    if (!IsValidGridPosition(start) || !IsValidGridPosition(end)) {
        return;
    }

    // MODIFICADO: O valor da heurística agora é uma variável local.
    // Você pode alterar este valor para testar diferentes comportamentos.
    // Valores mais altos farão o A* se comportar mais como uma busca gulosa (mais rápido, menos preciso).
    // Valores mais baixos o farão se comportar mais como Dijkstra (mais lento, mais preciso).
    // Exemplo com aleatoriedade: float heuristic_epsilon = 5.0f + ((float)rand() / (float)RAND_MAX * 2.0f); // Varia de 5.0 a 7.0
    float heuristic_epsilon = 5.0f + ((float)rand() / (float)RAND_MAX * 2.0f);

    List* openList = List_Create(sizeof(PathNode));
    List* closedList = List_Create(sizeof(PathNode));

    PathNode* startNode = (PathNode*)malloc(sizeof(PathNode));
    if (!startNode) return;

    startNode->position = start;
    startNode->g_cost = 0;
    startNode->h_cost = CalculateHeuristic(start, end);
    startNode->f_cost = startNode->g_cost + (startNode->h_cost * heuristic_epsilon);
    startNode->parent = NULL;

    List_Add(openList, startNode);
    free(startNode);

    while (openList->size > 0) {
        Node* bestNodeLink = openList->head;
        PathNode* bestNode = (PathNode*)bestNodeLink->data;
        Node* currentLink = openList->head->next;

        while (currentLink) {
            PathNode* currentNode = (PathNode*)currentLink->data;
            if (currentNode->f_cost < bestNode->f_cost) {
                bestNode = currentNode;
                bestNodeLink = currentLink;
            }
            currentLink = currentLink->next;
        }

        // Adiciona uma cópia do melhor nó para a lista fechada.
        List_Add(closedList, bestNode);
        // Pega um ponteiro estável para o nó que acabamos de adicionar na lista fechada.
        PathNode* currentNodeInClosedList = (PathNode*)closedList->tail->data;

        // Remove o nó original da lista aberta.
        List_Remove(openList, bestNode);

        // Verifica se chegou ao destino.
        if (currentNodeInClosedList->position.x == end.x && currentNodeInClosedList->position.y == end.y) {
            ReconstructPath(currentNodeInClosedList);
            List_Destroy(openList);
            List_Destroy(closedList);
            return;
        }

        // Analisa os vizinhos
        Vector2 neighbors[4] = {
            {currentNodeInClosedList->position.x, currentNodeInClosedList->position.y - 1},
            {currentNodeInClosedList->position.x, currentNodeInClosedList->position.y + 1},
            {currentNodeInClosedList->position.x - 1, currentNodeInClosedList->position.y},
            {currentNodeInClosedList->position.x + 1, currentNodeInClosedList->position.y}
        };

        // IMPLEMENTADO: Embaralha a ordem dos vizinhos para criar caminhos diferentes.
        ShuffleNeighbors(neighbors, 4);

        for (int i = 0; i < 4; i++) {
            Vector2 neighborPos = neighbors[i];

            if (!IsValidGridPosition(neighborPos) || FindNodeInList(closedList, neighborPos)) {
                continue;
            }

            float tentative_g_cost = currentNodeInClosedList->g_cost + 1;
            PathNode* neighborNode = FindNodeInList(openList, neighborPos);

            if (neighborNode == NULL || tentative_g_cost < neighborNode->g_cost) {
                if (neighborNode == NULL) {
                    neighborNode = malloc(sizeof(PathNode));
                    if (!neighborNode) return;

                    neighborNode->position = neighborPos;
                    neighborNode->h_cost = CalculateHeuristic(neighborPos, end);
                    List_Add(openList, neighborNode);
                    free(neighborNode);
                    neighborNode = (PathNode*)openList->tail->data;
                }

                neighborNode->parent = currentNodeInClosedList;
                neighborNode->g_cost = tentative_g_cost;
                neighborNode->f_cost = neighborNode->g_cost + (neighborNode->h_cost * heuristic_epsilon);
            }
        }
    }

    // Se o caminho não for encontrado, limpa as listas.
    List_Destroy(openList);
    List_Destroy(closedList);
}


//=====================================
// Funções de Gerenciamento e Update
//=====================================

void GameUnitMovement_Unload(void) {
    if (PathList) {
        List_Destroy(PathList);
        PathList = NULL;
    }
}

void GameUnitMovement_Update(void) {
    GameUnit* unit = SelectedUnit;
    if (!unit || !PathList || PathList->size == 0) return;

    Vector2* nextGridPosPtr = (Vector2*)List_Get(PathList, 0);
    if (!nextGridPosPtr) return;

    Vector2 nextGridPosValue = *nextGridPosPtr;

    currentWaypoint = GetGameGridToWorld(nextGridPosValue);
    unit->Destination = currentWaypoint;
    float movementSpeed = 500.0f;
    float displacement = movementSpeed * GetFrameTime();

    if (Vector2Distance(*unit->Position, unit->Destination) > displacement) {
        float angle = atan2f(unit->Destination.y - unit->Position->y, unit->Destination.x - unit->Position->x);
        unit->Position->x += cosf(angle) * displacement;
        unit->Position->y += sinf(angle) * displacement;
    }
    else {
        *unit->Position = unit->Destination;
        List_Remove(PathList, &nextGridPosValue);
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
