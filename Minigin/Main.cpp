#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include <memory>
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("background.tga");
	auto transform = go->AddComponent<dae::Transform>();
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::RenderComponent>("logo.tga");
	transform = go->AddComponent<dae::Transform>();
	transform->SetLocalPosition({ 216, 180,0 });
	scene.Add(go);

	SDL_Color white{ 255,255,255 };
	go = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent<dae::RenderComponent>();
	go->AddComponent<dae::Transform>();
	auto text = go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font,white);
	text->Initialise();
	text->SetPosition(80, 20);
	scene.Add(go);

	SDL_Color yellow{ 255,255,0 };
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::Transform>();
	auto fps = go->AddComponent<dae::FPSComponent>();
	go->AddComponent<dae::RenderComponent>();
	text = go->AddComponent<dae::TextComponent>("0", font, yellow);

	fps->Initialise();
	text->Initialise();

	scene.Add(go);

	const float radiusPacman{ 50.f };
	const float rotSpeedPacman{ 3.3f };
	auto pacman = std::make_shared<dae::GameObject>();
	pacman->AddComponent<dae::Transform>();
	auto pacmanRenderComp = pacman->AddComponent<dae::RenderComponent>("pacman.png");
	pacmanRenderComp->SetPosition(350.f, 350.f);
	pacman->AddComponent<dae::RotationComponent>(radiusPacman, rotSpeedPacman);
	scene.Add(pacman);


	const float radiusGhost{ 50.f };
	const float rotSpeedGhost{ 1.f };

	auto ghost = std::make_shared<dae::GameObject>();
	ghost->AddComponent<dae::Transform>();
	ghost->AddComponent<dae::RenderComponent>("ghost1.png");
	ghost->AddComponent<dae::RotationComponent>(radiusGhost, rotSpeedGhost);
	ghost->SetParent(pacman.get(), false);
	scene.Add(ghost);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}