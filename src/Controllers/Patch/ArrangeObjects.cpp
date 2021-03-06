// (c) 2017 Alex Nadzharov
// License: GPL3

#include "ArrangeObjects.h"
#include "UIObjects/UIObject.hpp"

#include "math.h"

#include "PdPatchViewController.hpp"

ArrangeObjects::ArrangeObjects()
{
}

void ArrangeObjects::alignLeft(objectVec* v)
{
    int x = 32768; //big enough lol

    for (auto obj : *v) {
        if (x > obj->x)
            x = obj->x;
    }
    for (auto obj : *v) {
        obj->x = x;
    }
}

void ArrangeObjects::alignRight(objectVec* v)
{
    int x = 0;

    for (auto obj : *v) {
        if (x < obj->x)
            x = obj->x;
    }
    for (auto obj : *v) {
        obj->x = x;
    }
}

void ArrangeObjects::alignBottom(objectVec* v)

{
    int y = 0;

    for (auto obj : *v) {
        if (y < obj->y)
            y = obj->y;
    }
    for (auto obj : *v) {
        obj->y = y;
    }
}

void ArrangeObjects::alignTop(objectVec* v)
{
    int y = 32768; //big enough lol

    for (auto obj : *v) {
        if (y > obj->y)
            y = obj->y;
    }
    for (auto obj : *v) {
        obj->y = y;
    }
}

void ArrangeObjects::alignCenter(objectVec* v)
{
    int x = 0; //big enough lol
    int c = 0;

    for (auto obj : *v) {
        //if (x > obj->x)
        x += obj->x;
        c++;
    }

    if (c == 0)
        return;

    x = x / c;

    for (auto obj : *v) {
        obj->x = x;
    }
}

void ArrangeObjects::distributeHorizontal(objectVec* v)
{

    int min_x = 32768; //big enough lol

    for (auto obj : *v) {
        if (min_x > obj->y)
            min_x = obj->y;
    }

    int max_x = 0;

    for (auto obj : *v) {
        if (max_x < obj->y)
            max_x = obj->y;
    }

    int i = 0;

    for (auto obj : *v) {

        int nx = floor(float(i) / float(v->size()) * float(max_x - min_x) + min_x);

        obj->x = nx;
        i++;
    }
}

void ArrangeObjects::distributeVertical(objectVec* v)
{

    int min_y = 32768; //big enough lol

    for (auto obj : *v) {
        if (min_y > obj->y)
            min_y = obj->y;
    }

    int max_y = 0;

    for (auto obj : *v) {
        if (max_y < obj->y)
            max_y = obj->y;
    }

    int i = 0;

    for (auto obj : *v) {

        int ny = floor(float(i) / float(v->size()) * float(max_y - min_y) + min_y);

        obj->y = ny;
        i++;
    }
}

// new
void ArrangeObjects::alignToGrid(objectVec* v, int gridSize){}
void ArrangeObjects::tidyUp(objectVec* v){}

// ---

void ArrangeMenuActions::_arrangeLeftAction()
{
    if (!_controller) return;
    ArrangeObjects::alignLeft(&_controller->data.objects);
}

void ArrangeMenuActions::_arrangeCenterAction()
{
    if (!_controller) return;
    ArrangeObjects::alignCenter(&_controller->data.objects);
};

void ArrangeMenuActions::_arrangeRightAction()
{
    if (!_controller) return;
    ArrangeObjects::alignRight(&_controller->data.objects);
};

void ArrangeMenuActions::_arrangeTopAction()
{
    if (!_controller) return;
    ArrangeObjects::alignTop(&_controller->data.objects);
};

void ArrangeMenuActions::_arrangeBottomAction()
{
    if (!_controller) return;
    ArrangeObjects::alignBottom(&_controller->data.objects);
};

void ArrangeMenuActions::_arrangeDHAction()
{
    if (!_controller) return;
}

void ArrangeMenuActions::_arrangeDVAction()
{
    if (!_controller) return;
}
