#ifndef DYNCEP_ECS_ENTITY_HPP
#define DYNCEP_ECS_ENTITY_HPP

#include "Component.hpp"
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

namespace Dyncep::ECS {

/** the maximum amount of allowed components for an entity **/
constexpr const size_t MAX_COMPONENTS = 64;

/**
 * using alias size_t as an identifier for components in order to
 * fetch a desired component from an entity
 */
using ComponentID = size_t;

/**
 * using alias bitset as a storage container for boolean values (1 || 0), which
 * is later used to check if an entity has a component
 */
using ComponentBitset = std::bitset<MAX_COMPONENTS>;

/**
 * using alias array as a raw pointer storage container for the actual
 * components, which is later used to retrieve components by their given
 * ComponentID
 */
using ComponentArray = std::array<Component *, MAX_COMPONENTS>;

/**
 * @brief get a component id
 * static variable always incrementing on function invokation
 *
 * @return ComponentID
 */
inline ComponentID getComponentID() {
  static ComponentID c{};
  return c++;
}

/**
 * @brief retrieve the component id for a specific type of component
 * since the compiler generates a function for each component type,
 * every component or rather component type will have it's own id using this
 * method
 *
 * @tparam T - the type of the desired component
 * @return ComponentID
 */
template <typename T> inline ComponentID getComponentTypeID() noexcept {
  static ComponentID type_id = getComponentID();
  return type_id;
}

/**
 * @brief the actual entity class used which owns various components and handles
 * them
 */
class Entity {
public:
  /**
   * @brief constructor
   */
  Entity();

  /**
   * @brief getter method for the is_active boolean flag
   * used in order to check whether the entity is still active or should be
   * deleted
   *
   * e.g. is_active would be set to false if a game entity like the player dies
   * and should therefore be removed from the system
   *
   * @return bool
   */
  [[nodiscard]] bool isActive() const noexcept;

  /**
   * @brief invoke the initialize function for every component this entity
   * manages
   */
  virtual void initialize();

  /**
   * @brief invoke the update function for every component this entity manages
   */
  virtual void update();

  /**
   * @brief invoke the render function for every component this entity manages
   */
  virtual void render();

  /**
   * @brief destroy the entity by setting the is_active flag to false and
   * therefore wait to be cleaned up
   */
  virtual void destroy() noexcept;

  /**
   * @brief check for the existence of a component with a given type
   *
   * @tparam CompnoentType - the type of the component to check for existence
   * @return bool
   */
  template <typename ComponentType> bool hasComponent() const {
    return this->component_bitset[getComponentTypeID<ComponentType>()];
  }

  /**
   * @brief add a component to the entity
   *
   * @tparam ComponentType - the type of the component to add
   * @tparam TArgs - arguments for the construction of the component
   * @return T& - reference to the newly created component
   */
  template <typename ComponentType, typename... TArgs>
  ComponentType &addComponent(TArgs &&...args) {
    /** create new unique pointer **/
    auto c = std::make_unique<ComponentType>(std::forward<TArgs>(args)...);

    /** fetch raw pointer to return reference **/
    auto *p = c.get();

    /** set this as parent entity to component **/
    p->setEntity(this);

    /** add to containers **/
    components.push_back(std::move(c));
    component_array[getComponentTypeID<ComponentType>()] = p;
    component_bitset[getComponentTypeID<ComponentType>()] = 1;

    /** initialize component **/
    p->initialize();
    return *p;
  }

  /**
   * @brief retrieve the reference to a component managed by this entity
   *
   * designed to be used like so:
   * entity.getComponent<SizeComponent>().setWidth(100);
   *
   * @tparam ComponentType - the type of component to fetch
   * @return ComponentType& - reference to the component
   */
  template <typename ComponentType> ComponentType &getComponent() {
    return *static_cast<ComponentType *>(
        component_array[getComponentTypeID<ComponentType>()]);
  }

private:
  /**
   * @is_active whether or not this entity is active
   * should be removed from the system if the boolean flag equals false
   */
  bool is_active = true;

  /**
   * @components the vector which contains the actual unique pointer of each
   * component
   */
  std::vector<std::unique_ptr<Component>> components{};

  /**
   * @component_array the component array which contains raw pointers of each
   * component with the index being the component type id
   * used to fetch components from the entity
   *
   * e.g. auto *c = component_array[getComponentTypeID<T>()];
   */
  ComponentArray component_array{};

  /**
   * @component_bitset the component bitset which contains 1's or 0's in order
   * to scan an entity for the existence of a component
   *
   * e.g. bool exists = component_bitset[getComponentTypeID<T>()];
   */
  ComponentBitset component_bitset{};
};

} // namespace Dyncep::ECS

#endif
