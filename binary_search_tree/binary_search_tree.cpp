#include <iostream>
#include <vector>

bool binary_search_tree(int val, std::vector<int> &array)
{
    int left{0};
    int right{static_cast<int>(array.size() - 1)};

    while (left <= right) {
        int mid{(left + right) / 2};

        if(array[mid] == val)
            return true;

        left = (val >= array[mid])?(mid + 1):left;
        right = (val < array[mid])?(mid - 1):right;

    }

    return (array[left] == val);
}

int binary_search_treeV2(int val, std::vector<int> &array)
{
    int length{static_cast<int>(array.size())};
    auto iter = array.begin();

    while (length > 1) {
        int half{length / 2};
        length -= half;

        __builtin_prefetch(&iter[length  / 2 - 1]);// left middle
        __builtin_prefetch(&iter[half + length  / 2 - 1]);//right middle

        iter += (iter[half - 1] < val) * half;//cmov
    }

    return *iter;
}

int main (int argc, char *argv[])
{
    std::vector<int> array;
    array.reserve(101);

    for(int i = 0; i < 101; ++i)
    {
        array.push_back(i);
    }

    int val{10};

    if(binary_search_tree(val, array))
    {
        std::cout << "found !" << std::endl;
    }

    if(val == binary_search_treeV2(val, array))
    {
        std::cout << "found !" << std::endl;
    }

    return 0;
}
