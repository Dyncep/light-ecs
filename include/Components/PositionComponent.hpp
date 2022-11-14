#ifndef DYNCEP_ECS_COMPONENTS_POSITION_COMPONENT_HPP
#define DYNCEP_ECS_COMPONENTS_POSITION_COMPONENT_HPP

#include "Component.hpp"

namespace {
/** @brief example of a component
 */
class PositionComponent : public Component {
public:
  /**
   * @brief retrieve the x position of the component
   *
   * @return int
   */
  [[nodiscard]] int x() const noexcept { return this->x_position; }

  /**
   * @brief retrieve the y position of the component
   *
   * @return int
   */
  [[nodiscard]] int y() const noexcept { return this->y_position; }

  void initialize() override {
    this->x_position = 0;
    this->y_position = 0;
  }

  void update() override {
    /**
     * do whatever u want with your position component here in order to update,
     * check for collision, whatever ur game/application needs
     **/
    this->x_position += this->y_position;
  }

  void render() override {
    /**
     * same as above
     **/
  }

private:
  /**
   * @x_position the x position of the component
   */
  int x_position = 0;

  /**
   * @y_position the y position of the component
   */
  int y_position = 0;
};
} // namespace Dyncep::ECS::Components

#endif
