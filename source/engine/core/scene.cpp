#include "scene.hpp"

Scene::Scene() {
    std::cout << "The Scene has been created.\n";
}

void Scene::start() { }

void Scene::update() { }

void Scene::render() { }

Scene::~Scene() {
    std::cout << "The Scene has been destroyed.\n";
}