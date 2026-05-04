#ifndef TEST_TGL_CPP
    #define TEST_TGL_CPP



void TGL::Test::test_TGL::Run()
{
    std::string
        testResults = "Running tests\n\n",
        testObjectResults;
    
    bool
        objectPassed = true,
        allObjectsPassed = true;

    for (auto testObject : _testObjects)
    {
        testObjectResults = testObject->identity();

        std::vector<std::string>
            reversedTestOrder;

        for (auto &test : testObject->tests)
        {
            reversedTestOrder.insert(reversedTestOrder.begin(), test.first);
        }

        for (auto &test : reversedTestOrder)
        {
            TGL::Test::ResetData();

            testObject->tests[test]();
            testObjectResults = testObjectResults + "\n    " + TestPassedText() + " - " + test + TGL::Test::failDescription;

            if (!TGL::Test::testPassed)
            {
                objectPassed = false;
                allObjectsPassed = false;
            }
        }

        testObjectResults = TestPassedText(objectPassed) + " - " + testObjectResults;
        testResults += testObjectResults;
    }

    testResults = TestPassedText(allObjectsPassed) + " - " + testResults;
    std::cout << testResults;
}

void TGL::Test::test_TGL::DisplayValues() const
{
    std::string 
        status = "Total test objects found: " + TGL::String(_testObjects.size());
    
    for (auto testObject : _testObjects)
    {
        status = status + "\n" + testObject->identity(4) + " tests found: " + testObject->getTestCount() + testObject->getTestList(8);
    }
    
    std::cout << status + "\n\n\n";
}



#include "test_TGL.cpp"



#endif // TEST_TGL_CPP