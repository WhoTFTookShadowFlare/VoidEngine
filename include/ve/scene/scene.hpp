#pragma once

#include "ve/scene/game_object.hpp"
#include <memory>
#include <map>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;
	class Scene final {
		map<string, shared_ptr<GameObject>> objects = {};
	public:

		shared_ptr<GameObject>& operator[](string);

		vector<shared_ptr<GameObject>> getObjects();

		void draw(double delta);
	};
}

