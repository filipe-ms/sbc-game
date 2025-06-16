// File: GameUnitMovement.c
#include "GameUnitMovement.h"

#include "GameUnit.h"
#include "Constants.h"
#include "GameCamera.h"
#include "GameUI.h"
#include "GenList.h"
#include "GameMap.h"

#include "raylib.h"
#include "raymath.h"

#include <stdbool.h>
#include <stdio.h>


#include "GameUnitSelection.h" // Isso aqui tem que sair daqui depois

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

static Unit_Direction GetDirectionFromVectors(Vector2 currentPos, Vector2 nextWaypoint) {
	Vector2 moveVector = Vector2Subtract(nextWaypoint, currentPos);

	if (fabsf(moveVector.x) > fabsf(moveVector.y)) {
		if (moveVector.x > 0) return GAMEUNIT_DIRECTION_RIGHT;
		else return GAMEUNIT_DIRECTION_LEFT;
	}
	else {
		if (moveVector.y > 0) return GAMEUNIT_DIRECTION_DOWN;
		else return GAMEUNIT_DIRECTION_UP;
	}
}

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
	if (pos.x >= 0 && pos.x < CONSTANTS_MAP_WIDTH && 
		pos.y >= 0 && pos.y < CONSTANTS_MAP_HEIGHT) {
		return UnitGrid[(int)pos.x][(int)pos.y].isWalkable;
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
static void ReconstructPath(GameUnit* unit, PathNode* endNode) {
	// Limpa o caminho antigo, se existir.
	if (unit->PositionalData.Path) {
		List_Destroy(unit->PositionalData.Path);
	}
	unit->PositionalData.Path = List_Create(sizeof(Vector2));

	PathNode* current = endNode;
	while (current != NULL) {
		if (!List_Add(unit->PositionalData.Path, &current->position)) return;
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
void GameUnitMovement_BuildPath(GameUnit* unit, Vector2 destination) {
	if (!unit) return;

	// Limpa dados de movimento anteriores.
	if (unit->PositionalData.Path) {
		List_Destroy(unit->PositionalData.Path);
		unit->PositionalData.Path = NULL;
	}
	unit->PositionalData.NextWaypoint = (Vector2){ -1, -1 };

	if (!IsValidGridPosition(destination)) return;

	unit->PositionalData.FinalDestination = destination;

	Vector2 startGridPos = {
		floorf(unit->PositionalData.Position->x / CONSTANTS_TILE_SIZE_F),
		floorf(unit->PositionalData.Position->y / CONSTANTS_TILE_SIZE_F)
	};

	List* openList = List_Create(sizeof(PathNode));
	List* closedList = List_Create(sizeof(PathNode));

	// Configura o nó inicial.
	PathNode startNode;
	startNode.position = startGridPos;
	startNode.g_cost = 0;
	startNode.h_cost = CalculateHeuristic(startNode.position, unit->PositionalData.FinalDestination);
	startNode.f_cost = startNode.g_cost + (startNode.h_cost * heuristicNoise);
	startNode.parent = NULL;

	List_AddWithFn(openList, &startNode, CompareByFCostFn);

	while (openList->size > 0) {
		// O melhor nó é sempre o primeiro, pois a lista está ordenada pelo f_cost.
		PathNode bestNodeData = *(PathNode*)List_GetByIndex(openList, 0);
		List_RemoveFirst(openList);

		// Move o melhor nó da lista aberta para a fechada.
		List_AddLast(closedList, &bestNodeData);

		// Obtém um ponteiro estável para o nó que acabamos de adicionar na lista fechada.
		PathNode* currentNodeInClosedList = (PathNode*)closedList->tail->data;

		// Se chegamos ao destino, reconstrói o caminho e finaliza.
		if (currentNodeInClosedList->position.x == unit->PositionalData.FinalDestination.x && currentNodeInClosedList->position.y == unit->PositionalData.FinalDestination.y) {
			ReconstructPath(unit, currentNodeInClosedList);
			// Define o primeiro waypoint.
			Vector2* firstWaypoint = (Vector2*)List_GetByIndex(unit->PositionalData.Path, 0);
			if (firstWaypoint) {
				unit->PositionalData.NextWaypoint = GetGameGridToWorld(*firstWaypoint);
			}
			List_Destroy(openList);
			List_Destroy(closedList);
			return;
		}

		// Analisa os vizinhos (Cima, Baixo, Esquerda, Direita).
		Vector2 neighbors[4] = {
			{currentNodeInClosedList->position.x, currentNodeInClosedList->position.y - 1},
			{currentNodeInClosedList->position.x, currentNodeInClosedList->position.y + 1},
			{currentNodeInClosedList->position.x - 1, currentNodeInClosedList->position.y},
			{currentNodeInClosedList->position.x + 1, currentNodeInClosedList->position.y}
		};

		ShuffleNeighbors(neighbors, 4);

		for (int i = 0; i < 4; i++) {
			Vector2 neighborPos = neighbors[i];

			if (!IsValidGridPosition(neighborPos) || FindNodeInList(closedList, neighborPos)) {
				continue;
			}

			int tentative_g_cost = currentNodeInClosedList->g_cost + 1;
			PathNode* neighborInOpenList = FindNodeInList(openList, neighborPos);

			if (neighborInOpenList != NULL && tentative_g_cost >= neighborInOpenList->g_cost) {
				continue;
			}

			if (neighborInOpenList != NULL) {
				List_RemoveWithFn(openList, &neighborPos, FindByPositionFn);
			}

			PathNode newNeighborNode;
			newNeighborNode.parent = currentNodeInClosedList;
			newNeighborNode.position = neighborPos;
			newNeighborNode.g_cost = tentative_g_cost;
			newNeighborNode.h_cost = CalculateHeuristic(neighborPos, unit->PositionalData.FinalDestination);
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
void GameUnitMovement_Unload(GameUnit* unit) {
	if (unit->PositionalData.Path) {
		List_Destroy(unit->PositionalData.Path);
		unit->PositionalData.Path = NULL;
	}
}

static void GameUnitMovement_MovementUpdate(GameUnit* unit) {
	if (!unit || 
		!unit->PositionalData.Path || 
		unit->PositionalData.Path->size == 0 || 
		unit->PositionalData.NextWaypoint.x == -1) {
		if (unit && unit->Unit.Action == GAMEUNIT_ACTION_WALK) {
			Unit_ChangeAction(&unit->Unit, GAMEUNIT_ACTION_IDLE);
		}
		return;
	}

	if (unit->Unit.Action != GAMEUNIT_ACTION_WALK) {
		Unit_ChangeAction(&unit->Unit, GAMEUNIT_ACTION_WALK);
	}

	Unit_Direction newDirection = GetDirectionFromVectors(*unit->PositionalData.Position, unit->PositionalData.NextWaypoint);
	if (unit->Unit.Direction != newDirection) {
		Unit_ChangeDirection(&unit->Unit, newDirection);
	}

	float movementSpeed = 500.0f; // Velocidade da unidade.
	float displacement = movementSpeed * GetFrameTime();

	// Se a unidade ainda não chegou ao próximo waypoint, move-se na direção dele.
	if (Vector2DistanceSqr(*unit->PositionalData.Position, unit->PositionalData.NextWaypoint) > displacement * displacement) {
		float angle = atan2f(unit->PositionalData.NextWaypoint.y - unit->PositionalData.Position->y, unit->PositionalData.NextWaypoint.x - unit->PositionalData.Position->x);
		unit->PositionalData.Position->x += cosf(angle) * displacement;
		unit->PositionalData.Position->y += sinf(angle) * displacement;
	}
	else {
		// Se chegou ao waypoint, atualiza a posição para ser exatamente a do waypoint.
		*unit->PositionalData.Position = unit->PositionalData.NextWaypoint;
		List_RemoveFirst(unit->PositionalData.Path);

		// Se ainda há caminho a percorrer, define o próximo waypoint.
		if (unit->PositionalData.Path->size > 0) {
			Vector2* nextGridPosPtr = (Vector2*)List_GetByIndex(unit->PositionalData.Path, 0);
			if (nextGridPosPtr) {
				unit->PositionalData.NextWaypoint = GetGameGridToWorld(*nextGridPosPtr);
			}
		}
		else {
			// Se o caminho terminou, limpa os dados de movimento.
			unit->PositionalData.NextWaypoint = (Vector2){ -1, -1 };
			unit->PositionalData.FinalDestination = (Vector2){ -1, -1 };
			List_Destroy(unit->PositionalData.Path);
			unit->PositionalData.Path = NULL;
		}
	}
}

void GameUnitMovement_HandleInput(GameUnit* unit) {
	if (unit && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Vector2 endGridPos = GetMouseToGameGrid();
		GameUnitMovement_BuildPath(unit, endGridPos);
	}
}

void GameUnitMovement_Update(GameUnit* unit) {
	if (!unit) return;

	GameUnitMovement_HandleInput(unit);
	GameUnitMovement_MovementUpdate(unit);
}
