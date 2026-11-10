#include "entity.hh"           
       

Component* Entity::getComponent(const char* name) {
    for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); it++)
    {
        Component* component = *(it);
        if (strcmp(component->getName(), name) == 0)
            return component;
    }

    printf("No existe un componente con nombre %s!", name);
    return nullptr;
}

void Entity::attach(Component* component)
{
    component->setOwner(this);
    components.push_back(component);
}

Entity::~Entity() {
    for (Component* component : components) {
        delete component;
    }

    components.clear();
}