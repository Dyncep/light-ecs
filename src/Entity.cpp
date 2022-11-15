#include "ECS/Entity.hpp"

namespace Dyncep::ECS {
Entity::Entity() = default;

[[nodiscard]] bool Entity::isActive() const noexcept { return this->is_active; }

void Entity::initialize() {
  /** initialize each component using fore loop **/
  std::for_each(std::begin(components), std::end(components),
                [](auto &c) { c->initialize(); });
}

void Entity::update() {
  /** update each component using fore loop **/
  std::for_each(std::begin(components), std::end(components),
                [](auto &c) { c->update(); });
}

void Entity::render() {
  /** render each component using fore loop **/
  std::for_each(std::begin(components), std::end(components),
                [](auto &c) { c->render(); });
}

void Entity::destroy() noexcept { is_active = false; }

} // namespace Dyncep::ECS
