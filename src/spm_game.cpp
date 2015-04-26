/* Space Marine - Edsel Apostol, Copyright 2013 */

#include "spm_defines.h"
#include "spm_game.h"
#include "spm_surface.h"
#include "spm_camera.h"
#include "spm_timer.h"
#include "spm_enemy.h"
#include "spm_static.h"
#include "spm_pickup.h"
#include "spm_collision.h"
#include "spm_bitmap_font.h"
#include "spm_soundfx.h"
#include <string>
#include <iostream>

Game::Game()
{
    m_ScreenFlags = SDL_HWSURFACE | SDL_DOUBLEBUF; // | SDL_FULLSCREEN;
    m_quit = false;
    m_Frame = 0;
    m_DeltaTime = 0.0;

    SDL_Init(SDL_INIT_EVERYTHING);

	// init SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096))
	{
		fprintf(stderr, "SDL_Mixer Error: %s\n", Mix_GetError());
		exit(1);
	}

	srand(SDL_GetTicks()); // init RNG seed

    m_pScreen = SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, SCR_BPP, m_ScreenFlags);
    m_pBackground = Surface::OnLoad("images/tilebg.png");

	//TODO: add dynamic loading of sprites from file

	BitmapFont::GameFont.Load("images/font.png", 16, 16);

    Player::Marine.Load("images/zombie.png", 3, 4, 3, 5);

	Camera::GameCam.Update(Player::Marine.m_Position); // hack, to let enemies spawn out of the screen at init

	Bullet* bullet = new Bullet();
	bullet->Load("images/bullet.png", 1, 1, 1, 1);
	Player::Marine.SetBullet(*bullet);

	for(int i = 0; i < NUM_STATIC; ++i) {
        Static* temp_ent = new Static();
        temp_ent->Load("images/building.png", 1, 1, 1, 1);
    }

	Pickup* temp_pickup = new Pickup(-1, 10, 5000);
	temp_pickup->Load("images/pickupspeed.png", 1, 1, 1, 1);
	for(int i = 0; i < NUM_PICKUPS/2; ++i) {
        new Pickup(*temp_pickup);
    }

	temp_pickup = new Pickup(10, -1, 5000);
	temp_pickup->Load("images/pickuplife.png", 1, 1, 1, 1);
	for(int i = 0; i < NUM_PICKUPS/2; ++i) {
        new Pickup(*temp_pickup);
    }

	Enemy* temp_ent = new Enemy(2, 5, 750, MovementSpeedVector/2);
	temp_ent->Load("images/spiders1.png", 3, 4, 12, 5);
	for(int i = 0; i < NUM_ENEMIES/3; ++i) {
        new Enemy(*temp_ent);
    }

	temp_ent = new Enemy(3, 10, 1000, MovementSpeedVector/4);
	temp_ent->Load("images/spiders2.png", 4, 4, 16, 4);
	for(int i = 0; i < NUM_ENEMIES/3; ++i) {
		new Enemy(*temp_ent);   
    }

	temp_ent = new Enemy(1, 1, 300, MovementSpeedVector);
	temp_ent->Load("images/spiders3.png", 6, 4, 16, 10);
	for(int i = 0; i < NUM_ENEMIES/3; ++i) {
        new Enemy(*temp_ent);
    }

	SoundFX::GameSoundsList = new SoundFX[SoundFX::SND_MAX];
	SoundFX::GameSoundsList[SoundFX::SND_BG].Load("sounds/gt2_harppen.ogg");
	SoundFX::GameSoundsList[SoundFX::SND_HIT].Load("sounds/Hic.wav");
	SoundFX::GameSoundsList[SoundFX::SND_BG].Play(-1, -1);
	
	m_LoopTime.Start();
    m_Fps.Start();
    m_FpsCap.Start();
}

Game::~Game()
{
    Entity::EntityList.clear();
	delete[] SoundFX::GameSoundsList;
	Mix_CloseAudio();
    SDL_Quit();
}

void Game::DisplayFPS()
{
    ++m_Frame;
    double time = m_Fps.GetTicks();
    if (time > 1000) {
        char buff[255];
        sprintf(buff, "SpaceMarine FPS: %0.2f", (float)m_Frame / (float)(time / 1000 ));
        SDL_WM_SetCaption( buff, NULL );
        m_Fps.Start();
        m_Frame = 0;
    }
}

void Game::LimitFPS()
{
    double time = ( 1000.f / FRAME_RATE ) - m_FpsCap.GetTicks();
    if (time > 0) SDL_Delay(time);
    m_FpsCap.Start();
}

int Game::Run()
{
    while(!m_quit) {
        HandleInput();
        Update();
        Render();
        //LimitFPS();
        DisplayFPS();
    }
    return 0;
}

void Game::HandleInput()
{
    while(SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT) {
            m_quit = true;
            break;
        }
        if (m_Event.type == SDL_KEYDOWN) {
            if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                m_quit = true;
        }
		Player::Marine.HandleInput(m_Event);
    }
}

void Game::Update()
{
    m_DeltaTime = (m_LoopTime.GetTicks()) / 1000.f;
    m_LoopTime.Start();

    for(int i = 0; i < Entity::EntityList.size(); ++i) {
        if(!Entity::EntityList[i]) continue;
		if(!Entity::EntityList[i]->m_Active) continue;
        Entity::EntityList[i]->Update(m_DeltaTime);
    }

    Camera::GameCam.Update(Player::Marine.m_Position);
}

void Game::Render()
{
    // tile the background surface for the whole level, draw only those in collision with the camera
    for (int idx_w = 0; idx_w <= (LVL_WIDTH/m_pBackground->w); ++idx_w) {
        for (int idx_h = 0; idx_h <= (LVL_HEIGHT/m_pBackground->h); ++idx_h) {
            SDL_Rect bgBox, coll;

            bgBox.x = m_pBackground->w*idx_w;
            bgBox.y = m_pBackground->h*idx_h;
            bgBox.w = m_pBackground->w;
            bgBox.h = m_pBackground->h;

            coll = Entity::Intersection(bgBox, Camera::GameCam.m_Rect);

            if (coll.w == 0 && coll.h == 0) {
                continue;
            }
            Surface::OnDraw(m_pScreen, m_pBackground, coll.x-Camera::GameCam.m_Rect.x, coll.y-Camera::GameCam.m_Rect.y, coll.x-bgBox.x, coll.y-bgBox.y, coll.w, coll.h);
        }
    }

	for(int i = 0; i < Entity::EntityList.size(); ++i) {
        if(!Entity::EntityList[i]) continue;
        if(!Entity::EntityList[i]->m_Active) continue;
        Entity::EntityList[i]->Render(m_pScreen);
    }

	char buff[255];
	sprintf(buff, "HP: %d            Score: %d", Player::Marine.m_Hp,  Player::Marine.GetScore());
	std::string str = buff;
	BitmapFont::GameFont.RenderString(m_pScreen, str, 32, 0);

	if (!Player::Marine.m_Active) {
		std::string str = "Game Over!!!!";
		BitmapFont::GameFont.RenderString(m_pScreen, str, SCR_WIDTH/2 - ((str.size()/2) * 32), SCR_HEIGHT/2 - 16);
	}

    SDL_Flip(m_pScreen);
}

int main(int argc, char* args[])
{
    Game game;
    return game.Run();
}
