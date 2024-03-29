#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "VisualServer.h"
#include <iostream>

namespace eng {
class Node;
}

class AnyScript
{
public:
    template <typename T>
    AnyScript(T x) : ptr(new Content<T>(std::move(x))) {}

    AnyScript(const AnyScript &from) = delete;
    AnyScript(AnyScript &&other) noexcept: ptr(std::move(other.ptr)) {
        // std::cout << "Move constructor AnyScript" << std::endl;

    }

    AnyScript &operator=(const AnyScript &x) = delete;

    AnyScript &operator=(AnyScript &&) noexcept = default;


    void process(float delta) {
        ptr->process(delta);
    }

    void draw(eng::VisualServer* server) const {
        ptr->draw(server);
    }

    void set_owner(eng::Node* owner) {
        ptr->set_owner(owner);
    }

private:
    struct BaseContent {
        virtual ~BaseContent() = default;

        virtual void process(float delta) = 0;
        virtual void draw(eng::VisualServer* server) const = 0;
        virtual void set_owner(eng::Node* owner) = 0;
    };

    template <typename T>
    struct Content : BaseContent {
        Content(T x) : object(std::move(x)) {}
        Content(const Content &) noexcept = default;

        void process(float delta) {
            object.process(delta);
        }

        void draw(eng::VisualServer* server) const {
            object.draw(server);
        }
        void set_owner(eng::Node* owner) {
            object.set_owner(owner);
        }

        T object;
    };

    std::unique_ptr<BaseContent> ptr;
};

