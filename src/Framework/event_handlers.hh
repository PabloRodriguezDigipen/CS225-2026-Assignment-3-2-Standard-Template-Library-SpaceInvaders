#pragma once

#include "event.hh"
#include <vector>

/// <summary>
/// Interface for all custom Event Handling classes
/// </summary>
class IEventHandler
{
public:
    //Method that recieves and processes the event in the handler
    virtual void call(Event* event) = 0;
};

/// <summary>
/// Template class for all custom Event Handlers
/// </summary>
/// <typeparam name="T">T typedef of the obejct interested in the event</typeparam>
/// <typeparam name="EVT">EVT type of the event</typeparam>
template<typename T, typename EVT>
class EventHandler : public IEventHandler
{
protected:
    // typedef of the function pointer that process the event
    typedef void (T::* ActionMethod)(EVT*);
    // Object itereste din the event
    T* object;
    // Function pointer to the action processing the event
    ActionMethod method;
public:
    // Default constructor for the class
    EventHandler(T* object, ActionMethod method) : object(object), method(method) {}

    //Especific implementaton of the cal method from the interface
    void call(Event* event) override {
        EVT* specific_event = dynamic_cast<EVT*>(event);
        if (specific_event != nullptr)
            (object->*method)(specific_event);
    }
};


class EventManager
{
    std::vector<IEventHandler*> listeners;
public:
    void registerEventHandler(IEventHandler* handler) {
        listeners.push_back(handler);
    }

    IEventHandler* getEventHandlerAt(int index) {
        return listeners[index];
    }

    void notifyEvent(Event* event) {
        for (auto* listener : listeners)
            listener->call(event);
    }

    virtual void update() = 0;
};
