/*
 * ---------------------------------------------------
 * testData.cpp
 *
 * Author: Thomas Choquet <semoir.dense-0h@icloud.com>
 * Date: 2025/03/01 20:16:49
 * ---------------------------------------------------
 */

#include "UtilsCPP_test.hpp"
#include <cassert>
#include <climits>

namespace utl::test
{

template<>
const unsigned char getTestData<unsigned char>(unsigned int index)
{
    static unsigned char datas[] = {
        'a', 'l', 'd', 'p', 'A', '$', 75, 128, UCHAR_MAX, 0 
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const int getTestData<int>(unsigned int index)
{
    static int datas[] = {
        6574, 5498, 4834, -3187, 8027,
        -4423, -9333, INT_MAX, INT_MIN, 0
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const double getTestData<double>(unsigned int index)
{
    static double datas[] = {
        1356.2635, 133542.897, -9876.1345, 932.1458, -3982.83674,
        -2589.5326, 75285.468, 987646972424.0, 0.000000000012, 0
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const unsigned long long getTestData<unsigned long long>(unsigned int index)
{
    static unsigned long long datas[] = {
        14746527416314757120ul, 14065381139728564224ul,
        14932322341420531712ul, 4284239288033345536ul,
        8171696784159014912ul,  11115991861653667840ul,
        17594450617462423552ul, 3647834969964806144ul, 
        0, ULLONG_MAX
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const std_string getTestData<std_string>(unsigned int index)
{
    static std_string datas[] = {
        "pMKUgW7S9F", "nFarXR9Ezw",
        "MMP6Niu52u", "cKgU23bmjh",
        "0rbLgatkP5", "vJq4HwKtpT",
        "6UPG3M217m", "私はトーマス", 
        "",           "aeluhvzpijzenrifujzerhhtbzieuthgzirecbzerchzeourgfzebcruztvufzoyebrvouzebrvozbetuzbrugybchjbzhbgzrcaeocevczervc"
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const std_vector_of_int getTestData<std_vector_of_int>(unsigned int index)
{
    static std_vector_of_int datas[] = {
        {1, 2, 3},
        {3976, 97865, 80967584, 36457, 20385},
        {18934, 8034, 32445, 834},
        {2156, 906734, 9732},
        {12467, 8563},
        {974, 0, 13, INT_MAX},
        {INT_MIN, -864, -874},
        {43634655},
        {2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732, 2156, 906734, 9732},
        {}
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

template<>
const std_vector_of_strings getTestData<std_vector_of_strings>(unsigned int index)
{
    static std_vector_of_strings datas[] = {
        {"g7lS11rVtW53wvbVA1o7Ye7odQueWwtg", "GmTjf3PwgD8qpPt2c1oyIKkrteSmK7yZ", "Ff5jZpHi03N7607RcvuXfB7F0Zuwspd6"},
        {"uVNOMoDIVm", "XKSsW4J8ZF", "PFK6r5QsV1", "bGBOEKHQvj", "HZqUedyCrv"},
        {"X6JrTkf1fN", "ZUZwaEQPP8", "rgFm2jmpkG", "jjn2WnrE2M"},
        {"QTZFOdiouo", "T3toUoW6aH", "gYzwqLHEFi"},
        {"8FPmf4U6UD", "3kHmKsuJqs"},
        {"SCr7Xcufpb", "", "a", "NHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9iNHnA04um9i"},
        {"VUOQ5nWkRo", "c1WKEXZqgJ", "8dcrOQ6mS5"},
        {"PRykq7yEMw"},
        {"6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0", "6i6HicLAjQ", "hWTfn9jgAf", "yF7E27OEfB", "vnsX6OpFr0"},
        {}
    };

    assert(index < sizeof(datas) / sizeof(datas[0]));
    return datas[index];
}

}
