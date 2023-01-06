#include <vector>   // vector
#include <iostream> // cout

#define FAIL_MAX (100000000)

using namespace std;

int JumpGame(vector<int> nums);

static int ReqJump(vector<int> &nums, size_t target_index, size_t cur_index,
                   size_t *best_jump, size_t cur_jump);

int main()
{
    vector<int> vec1;

    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(1);
    vec1.push_back(1);
    vec1.push_back(4);

    cout << "best vec1 jump is: " << JumpGame(vec1) << endl;

    vector<int> vec2;

    vec2.push_back(3);
    vec2.push_back(2);
    vec2.push_back(0);
    vec2.push_back(4);
    vec2.push_back(0);
    vec2.push_back(0);
    vec2.push_back(1);
    vec2.push_back(4);

    cout << "best vec2 jump is: " << JumpGame(vec2) << endl;

    //[ 5, 9, 3, 2, 1, 0, 2, 3, 3, 1, 0, 0 ]

    vector<int> vec3;

    vec3.push_back(5);
    vec3.push_back(9);
    vec3.push_back(3);
    vec3.push_back(2);
    vec3.push_back(1);
    vec3.push_back(0);
    vec3.push_back(2);
    vec3.push_back(3);
    vec3.push_back(4);
    vec3.push_back(1);
    vec3.push_back(0);
    vec3.push_back(0);
    vec3.push_back(0);

    cout << "best vec3 jump is: " << JumpGame(vec3) << endl;

    return 0;
}

int JumpGame(vector<int> nums)
{
    if (1 == nums.size())
    {
        return 0;
    }
    size_t best_jump = FAIL_MAX;

    size_t target = nums.size();
    return ReqJump(nums, target, 0, &best_jump, 0);
}

static int ReqJump(vector<int> &nums, size_t target_index, size_t cur_index,
                   size_t *best_jump, size_t cur_jump)
{
    if (cur_jump >= *best_jump)
    {
        return FAIL_MAX;
    }

    if (target_index <= cur_index + nums[cur_index] + 1)
    {
        // cout << "target_index: " << target_index << endl;
        // cout << "cur_index: " << cur_index << endl;
        // cout << "nums[cur_index]: " << nums[cur_index] << endl;

        *best_jump = cur_jump;

        return 1;
    }

    size_t best_retval = 0;

    for (size_t i = 1; i <= static_cast<size_t>(nums[cur_index]); ++i)
    {
        if (cur_jump >= *best_jump)
        {
            return FAIL_MAX;
        }

        if (0 == nums[cur_index + i])
        {
            continue;
        }

        size_t temp_retval = ReqJump(nums, target_index, cur_index + i, best_jump, cur_jump + 1);

        if (0 == temp_retval)
        {
            continue;
        }

        if (0 == best_retval)
        {
            best_retval = temp_retval;
        }
        else if (temp_retval < best_retval)
        {
            best_retval = temp_retval;
        }
    }

    if (0 == best_retval)
    {
        return FAIL_MAX;
    }

    return best_retval + 1;
}