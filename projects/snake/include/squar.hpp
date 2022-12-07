/*******************************************************************************
- Name: Daniel Jenudi
- Date: 06.12.22
- Project: Snake
*******************************************************************************/

#ifndef __SQUAR_H__
#define __SQUAR_H__

#include <cstdlib> // size_t
#include <string>

#include "raylib.h"

#define SQUAR_SIDE (150)

enum Squar_Content
{
    NOTHING = 0,
    GROW_TOKEN,
    SNAKE
};

class Squar
{
public:
    Squar(size_t x = 0, size_t y = 0, size_t width = SQUAR_SIDE, size_t height = SQUAR_SIDE);
    void Draw(Color color);
    void SetLocation(size_t x, size_t y);
    size_t GetLocationX();
    size_t GetLocationY();
    Squar_Content GetContent();
    void SetContent(Squar_Content new_content);

private:
    Rectangle m_rec;
    Squar_Content m_content;
};

#endif /*__SQUAR_H__*/