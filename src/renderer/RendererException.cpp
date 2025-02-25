#include "renderer/RendererException.hpp"

RendererException::RendererException(const std::string &message) {
    this->message = message;
}

std::string RendererException::getMessage() {
    return message;
}
