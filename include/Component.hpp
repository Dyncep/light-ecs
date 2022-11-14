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
   * @brief default constructor, abstract class anyways
   */
  Component() = default;

  /**
   * @brief abstract initialize function for each component
   */
  virtual void initialize() = 0;

  /**
   * @brief abstract update function for each component
   */
  virtual void update() = 0;

  /**
   * @brief abstract render function for each component
   */
  virtual void render() = 0;

  /**
   * @brief virtual destructor, since every component may generate different
   * stuff to be cleaned up
   */
  virtual ~Component();

private:
  /**
   * @entity the entity parent of this component
   */
  Entity *entity = nullptr;
};

} // namespace Dyncep::ECS

#endif
