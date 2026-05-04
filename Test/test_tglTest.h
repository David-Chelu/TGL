#ifndef TEST_TGL_TEST_H
    #define TEST_TGL_TEST_H



class TGL::Test::test_tglTest
{
public:

    using TestFunctionPointer = std::function<void()>;

    test_tglTest(TGL::Test::test_TGL &testMaster);

    virtual std::string
        identity(unsigned short indentSize = 0) const;
    
    std::string
        getTestList(unsigned short indentSize = 4) const,
        getTestCount() const;
    


    std::unordered_map<std::string, TestFunctionPointer>
        &tests;

protected:

    void
        TrackClass(TGL::Test::test_TGL &testMaster);
    
    std::unordered_map<std::string, TestFunctionPointer>
        _tests;
};



#endif // TEST_TGL_TEST_H