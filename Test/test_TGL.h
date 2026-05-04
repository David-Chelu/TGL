#ifndef TEST_TGL_H
    #define TEST_TGL_H


/* Test master for all tglTest derivate objects. Automatically calls all and outputs test results. */
class TGL::Test::test_TGL
{
public:

    void
        Run(), // runs all tests from all tglTest classes
        DisplayValues() const; // lists all tglTest objects linked, as well as their tests



    const std::vector<TGL::Test::test_tglTest*>
        testObjects;

private:

    friend class TGL::Test::test_tglTest;
    std::vector<TGL::Test::test_tglTest*>
        _testObjects;

};



#endif // TEST_TGL_H