#ifndef TGL_H_TEST
    #define TGL_H_TEST



#include <functional>



#define CLASS_ID(object) typeid(object).name()
#define TEST_CLASS_NAME(object) TGL::Test::className[CLASS_ID(object)]
#define TEST_CLASS_IDENTITY \
std::string("TGL::Test::")\
          + TEST_CLASS_NAME(*this)



namespace TGL
{
    namespace Test 
    {
        class test_TGL;
        class test_tglTest;
        class test_tglVector;

        bool
            testPassed;
        
        std::string
            testResult[2] = { "Failed", "Passed" },
            failDescription;
        
        unsigned
            currentExpect,
            indentSize = 3;
        
        void
            ResetData();
        
        std::string
            TestPassedText(bool testPassed = TGL::Test::testPassed);
    }
}



#include "TGL.cpp"

#include "test_tglTest.h"
#include "test_TGL.h"
#include "test_tglVector.h"

namespace TGL
{
    namespace Test
    {
        std::map<const std::string, const std::string>
            className =
        {
            { typeid(TGL::Test::test_TGL      ).name(), "test_TGL"      }
           ,{ typeid(TGL::Test::test_tglTest  ).name(), "test_tglTest"  }
           ,{ typeid(TGL::Test::test_tglVector).name(), "test_tglVector"}
        };
    }
}

#include "test_tglTest.cpp"
#include "test_TGL.cpp"
#include "test_tglVector.cpp"



#endif // TGL_H_TEST