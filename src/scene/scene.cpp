#include "ve/scene/scene.hpp"
#include "ve/scene/game_object.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;

	std::shared_ptr<GameObject> Scene::getObject(string name) {
		return objects[name];
	}

	void Scene::setObject(string name, std::shared_ptr<GameObject> obj) {
		auto prev = getObject(name);
		if(prev != nullptr) {
			Events::ERemovedFromScene evt(shared_from_this(), prev);
			prev->onRemovedFromScene(evt);
		}

		objects[name] = obj;

		if(obj != nullptr) {
			Events::EAddedToScene evt(shared_from_this(), obj);
			obj->onAddedToScene(evt);
		}
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
