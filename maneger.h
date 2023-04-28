#pragma once
void Init();
void Updete();
void Draw();
void Delete();
void Debug();

enum SCENE {
	title_scene,
	game_scene,
	end_scene
};

static int gamescene;