#ifndef DYNCEP_ECS_MANAGER_HPP
#define DYNCEP_ECS_MANAGER_HPP

#include "Entity.hpp"

namespace Dyncep::ECS {

class Manager {
public:
  /**
   * @brief constructor
   */
  Manager();

  /**
   * @brief invoke the update function for each entity
   */
  virtual void update();

  /**
   * @brief invoke the render function for each entity
   */
  virtual void render();

  /**
   * @brief remove inactive entities
   */
  virtual void clean();

  /**
   * @brief add an entity to the manager and a reference to it
   *
   * @return &Entity
   */
  virtual Entity &addEntity();

  /**
   * @brief virtual destructor
   */
  virtual ~Manager() = default;

private:
  /**
   * @entities the vector for the actual entities
   */
  std::vector<std::unique_ptr<Entity>> entities{};
};

} // namespace Dyncep::ECS

#endif
