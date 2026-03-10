#pragma once
#include <FrameworkCore.h>
namespace nam
{
	class Ecs;
	class Scene;
	class GameObject;

	class SceneManager final
	{
	private:
		Ecs* mp_ecs;
		UnMap<u32, Scene*> m_allCurrentScene;
		UnMap<size, Scene*> m_allCurrentScenesByTag;

		UnMap<u32, Scene*> m_allScene;
		UnMap<size, Scene*> m_allSceneByTag;

		UnMap<u32, GameObject*> m_allGameObjectInAllScene;
		uint32_t m_idNext;
	public:

		SceneManager();

		void Init();
		void Start();
		void CleanUpdate();
		void Destroy();

		void Reset();

		void AddCurrentScene(Scene* scene);
		void AddCurrentScene(u32 idScene);
		void AddCurrentScene(size sceneTag);

		void RemoveCurrentScene(Scene* scene);
		void RemoveCurrentScene(u32 idScene);
		void RemoveCurrentScene(size sceneTag);

		void SwitchCurrentScene(Scene* sceneClose, Scene* sceneOpen);
		void SwitchCurrentScene(u32 idSceneClose, u32 idSceneOpen);
		void SwitchCurrentScene(size sceneTag1, size sceneTag2);

		Scene* CreateScene(size sceneTag);
		void DestroyScene(Scene* scene);

	private:

		void SetActiveScene(Scene* scene, bool active);
		void SetActiveScene(u32 idScene, bool active);

		void SetActiveAllScene(bool active);

		void DestroyAllScene();

		void IncreaseIdNext();

	public:

		Scene* GetSceneByTag(size sceneTag);
		Scene* GetScene(u32 idScene);
		GameObject* GetGameObjectInGame(Entity& entity);
		GameObject* GetGameObjectInGame(u32 idEntity);

		const UnMap<u32, Scene*>& GetAllScene() const;

		const UnMap<u32, GameObject*>& GetAllGameObjectInAllScene() const;

		const UnMap<u32, Scene*>& GetCurrentScenes() const;
		const UnMap<size, Scene*>& GetCurrentScenesByTag() const;

		void SetEcs(Ecs* ecs);

		~SceneManager();

	private:
		friend class Scene;
	};
}

