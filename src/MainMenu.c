#include "raylib.h"
#include "stdio.h"

#include "MainMenu.h"
#include "Button.h"
#include "Constants.h"
#include "SceneManager.h"

// Características do texto
const int TITLE_FONT_SIZE = 60;

// Variáveis dos botões
Button playButton;
Button exitButton;
Button creditsButton;

// Características dos botões
const float BUTTON_WIDTH = 200;
const float BUTTON_HEIGHT = 50;
const float BUTTON_SPACING = 20;
const int FONT_SIZE = 30;

Color btn_color = { 255, 255, 255, 60 };
Color btn_hover_color = { 255, 255, 255, 255 };

Texture2D main_menu;


void MainMenu_Init(void) {
    main_menu = LoadTexture("backgrounds/main_menu.png");

    // Calcula a posição central dos botões
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float totalHeight = (BUTTON_HEIGHT * 2) + BUTTON_SPACING;
    float startY = (screenHeight - totalHeight) / 2;

    // Inicializa o botão Play
    playButton = (Button){
        .bounds = {
            .x = (screenWidth - BUTTON_WIDTH) / 2,
            .y = startY,
            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT
        },
        .text = "JOGAR",
        .font_size = FONT_SIZE,
        .color = btn_color,
        .hover_color = btn_hover_color
    };

    // Inicializa o botão Exit
    exitButton = (Button){
        .bounds = {
            .x = (screenWidth - BUTTON_WIDTH) / 2,
            .y = startY + 4* (BUTTON_HEIGHT + BUTTON_SPACING),
            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT
        },
        .text = "SAIR",
        .font_size = FONT_SIZE,
        .color = btn_color,
        .hover_color = btn_hover_color
    };

    creditsButton = (Button) {
    .bounds = {
        .x = (screenWidth - BUTTON_WIDTH) / 2,
        .y = startY + 1 * (BUTTON_HEIGHT + BUTTON_SPACING),
        .width = BUTTON_WIDTH,
        .height = BUTTON_HEIGHT
    },
    .text = "CREDITOS",
    .font_size = FONT_SIZE,
    .color = btn_color,
    .hover_color = btn_hover_color
    };

}

void MainMenu_Update(void) {

    bool game = CheckCollisionPointRec(GetMousePosition(), playButton.bounds);
    bool exit = CheckCollisionPointRec(GetMousePosition(), exitButton.bounds);
    bool credits = CheckCollisionPointRec(GetMousePosition(), creditsButton.bounds);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (game) SceneManager_ChangeScene(SCENEREFERENCE_GAME);
        //else if (exit) ChangeScene(EXIT);
        //else if (credits) ChangeScene(CREDITS);
    }
}

void DrawMainMenuBackground(void) {
    Rectangle source = { 0.0f, 0.0f, (float)main_menu.width, (float)main_menu.height };
    Rectangle destination = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
    Vector2 offset = { 0 };
    float rotation = 0.0f;
    Color color = { 255, 255, 255, 90 };
    DrawTexturePro(main_menu, source, destination, offset, rotation, color);
}

void MainMenu_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawMainMenuBackground();
    int titleWidth = MeasureText(CONSTANTS_GAME_TITLE, TITLE_FONT_SIZE);
    
    DrawText(CONSTANTS_GAME_TITLE, (GetScreenWidth() - titleWidth) / 2, 100, FONT_SIZE * 2, WHITE);
    Button_Draw(&playButton);
	Button_Draw(&exitButton);
    Button_Draw(&creditsButton);

    EndDrawing();
}

void MainMenu_Unload(void) {
    UnloadTexture(main_menu);
}