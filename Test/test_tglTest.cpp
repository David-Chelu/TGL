#ifndef TEST_TGL_TEST_CPP
    #define TEST_TGL_TEST_CPP



TGL::Test::test_tglTest::test_tglTest(TGL::Test::test_TGL &testMaster) : tests{_tests}
{
    TrackClass(testMaster);
}

std::string TGL::Test::test_tglTest::identity(unsigned short indentSize) const
{
    return std::string(indentSize, ' ') + TEST_CLASS_IDENTITY;
}

std::string TGL::Test::test_tglTest::getTestList(unsigned short indentSize) const
{
    std::string
        result;

    auto
        iterator = _tests.begin();
        
    std::vector<std::string>
        reversedTestOrder;
    
    for (auto &test : _tests)
    {
        reversedTestOrder.insert(reversedTestOrder.begin(), test.first);
    }

    unsigned
        test;

    ParseRange(test, 0, reversedTestOrder.size(), ++test)
    {
        result = result + "\n" + std::string(indentSize, ' ') + '[' + TGL::String(test) + "] " + reversedTestOrder[test];
        std::advance(iterator, 1);
    }

    return result;
}

std::string TGL::Test::test_tglTest::getTestCount() const
{
    return TGL::String(_tests.size());
}

void TGL::Test::test_tglTest::TrackClass(TGL::Test::test_TGL &testMaster)
{
    testMaster._testObjects.push_back(this);
}



#endif // TEST_TGL_TEST_CPP