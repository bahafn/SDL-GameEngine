#include <iostream>
#include <SDL3/SDL.h>

#include "gameObject/Transform.hpp"
#include "renderer/Renderer.hpp"
#include "utils/Vector.hpp"

// int main() {
//     SDL_Window* mWindow = SDL_CreateWindow("Test", 500, 500, SDL_WINDOW_FULLSCREEN);
//     const auto renderer = new Renderer(mWindow);
//
//     const Vector pos = {200, 200};
//     const Vector size = {50, 50};
//
//     auto *rect = new SDL_FRect(pos.x, pos.y, size.x, size.y);
//
//     renderer->render_image("C:/Users/HP/Pictures/Screenshots/Screenshot 2025-02-05 115244.png", rect);
//     renderer->present();
//
//     SDL_Delay(2000);
//
//     free(rect);
//
//     SDL_DestroyWindow(mWindow);
//     SDL_Quit();
//
//     SDL_Quit();
//     return 0;
// }

// int main() {
//     auto transform = std::make_shared<Transform>(Vector(10, 10), Vector(1, 1), 20);
//     auto transform2 = new Transform(Vector(10, 10), Vector(1, 1), 0, transform);
//
//     transform->set_position(Vector(100, 100));
//     transform->set_scale(Vector(2, 2));
//     transform->set_rotation(90);
//
//     std::cout << "local position: " << transform2->get_local_position() << "\n";
//     std::cout << "(global) position: " << transform2->get_position() << "\n";
//     std::cout << "local scale: " << transform2->get_local_scale() << "\n";
//     std::cout << "(global) scale: " << transform2->get_scale() << "\n";
//     std::cout << "local rotation: " << transform2->get_local_rotation() << "\n\n";
//     std::cout << "(global) rotation: " << transform2->get_rotation() << "\n\n";
//
//     transform2->set_position(Vector(100, 100));
//     transform2->set_local_scale(Vector(2, 2));
//     transform2->set_local_rotation(90);
//
//     std::cout << "local position: " << transform2->get_local_position() << "\n";
//     std::cout << "(global) position: " << transform2->get_position() << "\n";
//     std::cout << "local scale: " << transform2->get_local_scale() << "\n";
//     std::cout << "(global) scale: " << transform2->get_scale() << "\n";
//     std::cout << "local rotation: " << transform2->get_local_rotation() << "\n\n";
//     std::cout << "(global) rotation: " << transform2->get_rotation() << "\n\n";
//
//     transform->set_position(Vector(0, 0));
//     transform->set_scale(Vector(1, 1));
//     transform->set_rotation(0);
//
//     std::cout << "local position: " << transform2->get_local_position() << "\n";
//     std::cout << "(global) position: " << transform2->get_position() << "\n";
//     std::cout << "local scale: " << transform2->get_local_scale() << "\n";
//     std::cout << "(global) scale: " << transform2->get_scale() << "\n";
//     std::cout << "local rotation: " << transform2->get_local_rotation() << "\n\n";
//     std::cout << "(global) rotation: " << transform2->get_rotation() << "\n\n";
// }

int main() {
    auto grand_parent = std::make_shared<Transform>(Vector(10, 10), Vector(2, 2), 90);
    auto parent = std::make_shared<Transform>(Vector(10, 10), Vector(2, 2), 45, grand_parent);
    auto child = std::make_shared<Transform>(Vector(10, 10), Vector(2, 2), 45, parent);

    std::cout << "position: " << child->get_position() << std::endl;
    std::cout << "rotation: " << child->get_rotation() << std::endl;
    std::cout << "scale: " << child->get_scale() << std::endl;

    std::cout << "local position: " << child->get_local_position() << std::endl;
    std::cout << "local rotation: " << child->get_local_rotation() << std::endl;
    std::cout << "local scale: " << child->get_local_scale() << std::endl;

    std::cout << child->is_child_of(parent) << std::endl;
}
