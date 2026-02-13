#include "ve/scene/scene.hpp"
#include "ve/scene/game_object.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;

	shared_ptr<GameObject>& Scene::operator[](string name) {
		return objects[name];
	}

	vector<shared_ptr<GameObject>> Scene::getObjects() {
		vector<shared_ptr<GameObject>> objVec;

		for(auto obj = objects.begin(); obj != objects.end(); obj++) {
			objVec.push_back(obj->second);
		}

		return objVec;
	}

	void Scene::draw(double delta) {
		for(auto obj = objects.begin(); obj != objects.end(); obj++)
			obj->second->draw(delta);
	}
}

