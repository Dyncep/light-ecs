#include "Entity.hpp"

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

template <typename ComponentType> bool Entity::hasComponent() const {
  return this->component_bitset[getComponentTypeID<ComponentType>()];
}

template <typename ComponentType, typename... TArgs>
ComponentType &Entity::addComponent(TArgs &&...args) {
  /** create new unique pointer **/
  auto *c = std::make_unique<ComponentType>(std::forward<TArgs>(args)...);

  /** fetch raw pointer to return reference **/
  auto *p = c->get();

  /** set this as parent entity to component **/
  c->entity = this;

  /** add to containers **/
  components.push_back(std::move(c));
  component_array[getComponentTypeID<ComponentType>()] = p;
  component_bitset[getComponentTypeID<ComponentType>()] = 1;

  /** initialize component **/
  p->initialize();
  return p;
}

template <typename ComponentType> ComponentType &Entity::getComponent() {
  return *static_cast<ComponentType *>(
      component_array[getComponentTypeID<ComponentType>()]);
}

} // namespace Dyncep::ECS
