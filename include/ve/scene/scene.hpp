#pragma once

#include "ve/scene/game_object.hpp"
#include <memory>
#include <map>
#include <vector>
#include <string>

namespace VoidEngine::Scene {
	using namespace std;
	class Scene final : public enable_shared_from_this<Scene> {
		map<string, shared_ptr<GameObject>> objects = {};
	public:
		std::shared_ptr<GameObject> getObject(string name);
		void setObject(string name, std::shared_ptr<GameObject> obj);

		vector<shared_ptr<GameObject>> getObjects();

		void draw(double delta);
	};
}
