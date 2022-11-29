/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Stav Ben Shushan
Date: 31/05/2022
File: Data struct - Knight Tour
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <assert.h>/* assert */
#include <time.h>  /* time_t, time */

#include "ktour.h"
#include "bit_array.h"

#define OUT_OF_RANGE (9)
#define NUM_OF_MOVES (8)
#define FULL_BORD (64)
#define MAX_TIME (10)
#define TWO_FIRST_ROWS (15)
#define FIRST_ROW (7)
#define TWO_LAST_ROWS (48)
#define LAST_ROW (56)
#define ROW_LEN (8)
#define FIRST_SQAUER (0)
#define LAST_SQAUER (63)

static int RecKnightTour(int current_position, bit_arr_t board, int *tour);

static int UpRight(int cur_pos);
static int UpLeft(int cur_pos);
static int RightUp(int cur_pos);
static int RightDown(int cur_pos);
static int DownRight(int cur_pos);
static int DownLeft(int cur_pos);
static int LeftUp(int cur_pos);
static int LeftDown(int cur_pos);

static int CheckUpFirst(int cur_pos);
static int CheckUpSecond(int cur_pos);
static int CheckRightFirst(int cur_pos);
static int CheckRightSecond(int cur_pos);
static int CheckDownFirst(int cur_pos);
static int CheckDownSecond(int cur_pos);
static int CheckLeftFirst(int cur_pos);
static int CheckLeftSecond(int cur_pos);

static void SetPriorityLUT(int cur_pos, bit_arr_t board, size_t *priority_lut);
static size_t CountPosibleMoves(int cur_pos, bit_arr_t board);
static size_t GetSmallestIndex(size_t *priority_lut);

typedef int (*move_lut_t)(int cur_pos);

static time_t g_start_time = 0;

static const move_lut_t g_move_lut[NUM_OF_MOVES] = {
    &DownRight, &RightDown, &RightUp, &UpRight,
    &UpLeft, &LeftUp, &LeftDown, &DownLeft};

enum Moves
{
    UP_FIRST = -16,
    DOWN_FIRST = 16,
    LEFT_FIRST = -2,
    RIGHT_FIRST = 2,

    UP_SECONG = -8,
    DOWN_SECOND = 8,
    LEFT_SECOND = -1,
    RIGHT_SECOND = 1,

    UNLEGAL_MOVE = -1
};

enum Legal
{
    LEGAL = 0,
    UNLEGAL
};

enum Status
{
    SUCCESS = 0,
    FAIL
};

enum Bit_Status
{
    BIT_OFF = 0,
    BIT_ON
};

int KnightTour(int start_index, int *buffer)
{
    bit_arr_t bit_arr = 0;

    assert(FIRST_SQAUER <= start_index);
    assert(LAST_SQAUER >= start_index);
    assert(NULL != buffer);

    g_start_time = time(NULL);

    return RecKnightTour(start_index, bit_arr, buffer);
}

static int RecKnightTour(int cur_pos, bit_arr_t board, int *tour)
{
    size_t i = 0;
    int next_move = 0;
    size_t smallest_index = 0;
    size_t priority_lut[NUM_OF_MOVES] = {0};

    if ((FULL_BORD - 1) == BitArrCountOn(board))
    {
        *tour = cur_pos;
        return SUCCESS;
    }

    if ((g_start_time + MAX_TIME) < time(NULL))
    {
        return FAIL;
    }

    SetPriorityLUT(cur_pos, board, priority_lut);

    for (i = 0; i < NUM_OF_MOVES; ++i)
    {
        smallest_index = GetSmallestIndex(priority_lut);

        if (OUT_OF_RANGE == smallest_index)
        {
            break;
        }

        next_move = (*g_move_lut[smallest_index])(cur_pos);
        if ((UNLEGAL_MOVE == next_move) ||
            (BIT_ON == BitArrGetBitVal(board, next_move)))
        {
            continue;
        }
        else if (SUCCESS == RecKnightTour(next_move,
                                          BitArrSetBitOn(board, cur_pos), tour + 1))
        {
            *tour = cur_pos;
            return SUCCESS;
        }
    }

    return FAIL;
}

/* ~~~~~~~~~~ Warnsdorff’s algorithm ~~~~~~~~~~ */

static void SetPriorityLUT(int cur_pos, bit_arr_t board, size_t *priority_lut)
{
    size_t i = 0;
    int next_move = 0;

    assert(NULL != priority_lut);
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    for (i = 0; i < NUM_OF_MOVES; ++i)
    {
        next_move = (*g_move_lut[i])(cur_pos);
        if ((UNLEGAL_MOVE == next_move) ||
            (BIT_ON == BitArrGetBitVal(board, next_move)))
        {
            priority_lut[i] = OUT_OF_RANGE;
        }
        else
        {
            priority_lut[i] = CountPosibleMoves(next_move,
                                                BitArrSetBitOn(board, cur_pos));
        }
    }
}

static size_t CountPosibleMoves(int cur_pos, bit_arr_t board)
{
    int next_move = 0;
    size_t i = 0;
    size_t max_moves_posible = NUM_OF_MOVES;

    for (i = 0; i < NUM_OF_MOVES; ++i)
    {
        next_move = (*g_move_lut[i])(cur_pos);
        if (UNLEGAL_MOVE == next_move)
        {
            --max_moves_posible;
        }
        else if (BIT_ON == BitArrGetBitVal(board, next_move))
        {
            --max_moves_posible;
        }
    }

    return max_moves_posible;
}

static size_t GetSmallestIndex(size_t *priority_lut)
{
    size_t i = 0;
    size_t min_index = 0;

    assert(NULL != priority_lut);

    for (i = 0; i < NUM_OF_MOVES; ++i)
    {
        if (priority_lut[min_index] > priority_lut[i])
        {
            min_index = i;
        }
    }

    priority_lut[min_index] = OUT_OF_RANGE;
    return min_index;
}

/* ~~~~~~~~~~ Moves ~~~~~~~~~~ */

static int UpRight(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckUpFirst(cur_pos) ||
        UNLEGAL == CheckRightSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + UP_FIRST + RIGHT_SECOND;
}

static int UpLeft(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckUpFirst(cur_pos) ||
        UNLEGAL == CheckLeftSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + UP_FIRST + LEFT_SECOND;
}

static int RightUp(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckRightFirst(cur_pos) ||
        UNLEGAL == CheckUpSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + RIGHT_FIRST + UP_SECONG;
}

static int RightDown(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckRightFirst(cur_pos) ||
        UNLEGAL == CheckDownSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + RIGHT_FIRST + DOWN_SECOND;
}

static int DownRight(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckDownFirst(cur_pos) ||
        UNLEGAL == CheckRightSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + DOWN_FIRST + RIGHT_SECOND;
}

static int DownLeft(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckDownFirst(cur_pos) ||
        UNLEGAL == CheckLeftSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + DOWN_FIRST + LEFT_SECOND;
}

static int LeftUp(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if (UNLEGAL == CheckLeftFirst(cur_pos) ||
        UNLEGAL == CheckUpSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + LEFT_FIRST + UP_SECONG;
}

static int LeftDown(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(63 >= cur_pos);

    if (UNLEGAL == CheckLeftFirst(cur_pos) ||
        UNLEGAL == CheckDownSecond(cur_pos))
    {
        return UNLEGAL_MOVE;
    }

    return cur_pos + LEFT_FIRST + DOWN_SECOND;
}

/* ~~~~~~~~~~ Legality Check ~~~~~~~~~~ */

static int CheckUpFirst(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return (TWO_FIRST_ROWS < cur_pos) ? LEGAL : UNLEGAL;
}

static int CheckUpSecond(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return (FIRST_ROW < cur_pos) ? LEGAL : UNLEGAL;
}

static int CheckRightFirst(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if ((((cur_pos + 2) % ROW_LEN) == 0) || (((cur_pos + 1) % ROW_LEN) == 0))
    {
        return UNLEGAL;
    }
    else
    {
        return LEGAL;
    }
}

static int CheckRightSecond(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return (((cur_pos + 1) % ROW_LEN) != 0) ? LEGAL : UNLEGAL;
}

static int CheckDownFirst(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return (TWO_LAST_ROWS > cur_pos) ? LEGAL : UNLEGAL;
}

static int CheckDownSecond(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return (LAST_ROW > cur_pos) ? LEGAL : UNLEGAL;
}

static int CheckLeftFirst(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    if ((((cur_pos - 1) % ROW_LEN) == 0) || ((cur_pos % ROW_LEN) == 0))
    {
        return UNLEGAL;
    }
    else
    {
        return LEGAL;
    }
}

static int CheckLeftSecond(int cur_pos)
{
    assert(FIRST_SQAUER <= cur_pos);
    assert(LAST_SQAUER >= cur_pos);

    return ((cur_pos % ROW_LEN) != 0) ? LEGAL : UNLEGAL;
}
