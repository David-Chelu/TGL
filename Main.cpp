#include "Source/TGL.h"
#include "Test/TGL.h"

int main()
{
    TGL::Test::test_TGL
        tests;
    
    TGL::Test::test_tglVector
        testVector(tests);
    

    tests.DisplayValues();
    tests.Run();


    return 0;
}
