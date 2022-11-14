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
  void update();

  /**
   * @brief invoke the render function for each entity
   */
  void render();

  /**
   * @brief remove inactive entities
   */
  void clean();

  /**
   * @brief add an entity to the manager and a reference to it
   *
   * @return &Entity
   */
  Entity &addEntity();

private:
  /**
   * @entities the vector for the actual entities
   */
  std::vector<std::unique_ptr<Entity>> entities{};
};

} // namespace Dyncep::ECS

#endif
