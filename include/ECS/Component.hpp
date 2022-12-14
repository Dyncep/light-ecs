#ifndef DYNCEP_ECS_COMPONENT_HPP
#define DYNCEP_ECS_COMPONENT_HPP

namespace Dyncep::ECS {

/**
 * @brief forward declaration for the Entity class
 */
class Entity;

/**
 * @brief the actual component class used which should is owned by an Entity in
 * all cases
 */
class Component {
public:
  /**
   * @brief default constructor
   */
  Component() = default;

  /**
   * @brief virtual initialize function for each component
   */
  virtual void initialize() {}

  /**
   * @brief virtual update function for each component
   */
  virtual void update() {}

  /**
   * @brief virtual render function for each component
   */
  virtual void render() {}

  /**
   * @brief set the entity of the component
   *
   * @param Entity*
   */
  void setEntity(Entity *entity) { this->entity = entity; }

  /**
   * @brief getter method for the entity of the component
   *
   * @return Entity*
   */
  Entity *getEntity() { return this->entity; }

  /**
   * @brief virtual destructor, since every component may generate different
   * stuff to be cleaned up
   */
  virtual ~Component() {}

protected:
  /**
   * @entity the entity parent of this component
   */
  Entity *entity = nullptr;
};

} // namespace Dyncep::ECS

#endif
