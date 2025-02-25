#ifndef RENDEREREXCEPTION_H
#define RENDEREREXCEPTION_H

#include <exception>
#include <string>

class RendererException final : public std::exception {
    std::string message;

public:
    explicit RendererException(const std::string &message);

    std::string getMessage();
};

#endif
