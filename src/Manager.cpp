#include "ECS/Manager.hpp"

namespace Dyncep::ECS {

Manager::Manager() = default;

void Manager::update() {
  std::for_each(std::begin(entities), std::end(entities),
                [](auto &e) { e->update(); });
}

void Manager::render() {
  std::for_each(std::begin(entities), std::end(entities),
                [](auto &e) { e->render(); });
}

void Manager::clean() {
  entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                [](const auto &p) { return !p->isActive(); }),
                 std::end(entities));
}

Entity &Manager::addEntity() {
  auto e = std::make_unique<Entity>();
  auto &i = *e;
  entities.push_back(std::move(e));
  return i;
}

} // namespace Dyncep::ECS
