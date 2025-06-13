// MAIN_C

#include <stdio.h>
#include "raylib.h"
#include "resource_dir.h"

#include "SceneManager.h"
#include "Constants.h"
//#include "request.h"
#include "SpecificLists.h"
#include "GenList.h"

void Main_InitProgram(void); // Chamar tudo relativo à inicialização de arquivos necessários aqui
void Main_Cleanup(void);     // Liberar a memória de tudo aqui

int main(void) {
    Main_InitProgram();

    SceneManager_Init();
    SceneManager_ChangeScene(SCENEREFERENCE_GAME);
    SceneManager_LoopScene();
    
    Main_Cleanup();
    
    CloseWindow();

    return 0;
}

void Main_InitProgram(void) {
    // Inicializa o CURL
    /*if (InitRequestSystem() != 0) {
        fprintf(stderr, "ERRO: Falha ao inicializar o sistema de requisições.\n");
        return 1;
    }*/

	// Inicializa a janela da Raylib
    SetConfigFlags(
        (FLAG_VSYNC_HINT * CONSTANTS_VIDEO_SETTINGS_ENABLE_VSYNC) |
        (FLAG_WINDOW_HIGHDPI * CONSTANTS_VIDEO_SETTINGS_ENABLE_WINDOW_HIGHDPI) |
        (FLAG_FULLSCREEN_MODE * CONSTANTS_VIDEO_SETTINGS_ENABLE_FULLSCREEN)
    );

    InitWindow(
        CONSTANTS_VIDEO_SETTINGS_WIDTH_BUFFER,
        CONSTANTS_VIDEO_SETTINGS_HEIGHT_BUFFER,
        CONSTANTS_GAME_TITLE);

    if (!IsWindowReady()) {
        fprintf(stderr, "ERRO FATAL: Falha ao inicializar a janela Raylib.\n");
        Main_Cleanup();
        return;
    }

    SetTargetFPS(CONSTANTS_VIDEO_SETTINGS_TARGET_FPS);

    // Inicializa assets
    SearchAndSetResourceDir(CONSTANTS_RESOURCE_DIR);
	//LoadGameAssets();
}

void Main_Cleanup(void) {
    //CleanupRequestSystem();
	//UnloadGameAssets();
    printf("Aplicação encerrada normalmente.\n");
}