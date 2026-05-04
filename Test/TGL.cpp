#ifndef TGL_CPP_TEST
    #define TGL_CPP_TEST



void TGL::Test::ResetData()
{
    TGL::Test::testPassed = true;
    TGL::Test::failDescription = "";
    TGL::Test::currentExpect = 0;
}

std::string TGL::Test::TestPassedText(bool testPassed)
{
    return TGL::Test::testResult[testPassed];
}

void AddFailDescription(const std::string &text)
{
    std::string
        result = std::string(TGL::Test::indentSize, ' ') + text;

    if (TGL::Test::failDescription.empty())
    {
        TGL::Test::failDescription = ": " + result;
    }
    else
    {
        TGL::Test::failDescription += result;
    }
}

std::string PrepareParameters(bool expression)
{
    return expression? "true" : "false";
}

std::string PrepareParameters(largeint_t leftValue, largeint_t rightValue)
{
    return "(" + TGL::String(leftValue) + ", " + TGL::String(rightValue) + ")";
}

std::string PrepareParameters(largeuint_t leftValue, largeuint_t rightValue)
{
    return "(" + TGL::String(leftValue) + ", " + TGL::String(rightValue) + ")";
}

std::string PrepareParameters(double leftValue, double rightValue)
{
    return "(" + TGL::String(leftValue) + ", " + TGL::String(rightValue) + ")";
}

std::string PrepareParameters(const std::string &leftValue, const std::string &rightValue)
{
    return "(" + leftValue + ", " + rightValue + ")";
}

std::string PrepareParameters(const std::vector<vType> &leftValue, const std::vector<vType> &rightValue)
{
    return "(" + TGL::String(leftValue) + ", " + TGL::String(rightValue) + ")";
}

std::string PrepareParameters(const TGL::tglVector &leftValue, const TGL::tglVector &rightValue)
{
    return "(" + TGL::String(leftValue) + ", " + TGL::String(rightValue) + ")";
}

#define AddFailDescriptionValuesSingleExpression(expectName, expression, expectedText) AddFailDescription("[line " + TGL::String(__LINE__) + ", expect #" + TGL::String(TGL::Test::currentExpect) + ": " + expectName + ", actual " + PrepareParameters(expression) + ", expected " + expectedText + "]; ")
#define AddFailDescriptionValues(expectName, leftValue, rightValue, expectedText) AddFailDescription("[line " + TGL::String(__LINE__) + ", expect #" + TGL::String(TGL::Test::currentExpect) + ": " + expectName + ", actual " + PrepareParameters(leftValue, rightValue) + ", expected " + expectedText + "]; ")

#define ExpectTrue(expression)\
{\
bool e = expression;\
if (!(e))\
{\
    AddFailDescriptionValuesSingleExpression("ExpectTrue", e, "true");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectFalse(expression)\
{\
bool e = expression;\
if (e)\
{\
    AddFailDescriptionValuesSingleExpression("ExpectFalse", e, "false");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (a != b)\
{\
    AddFailDescriptionValues("ExpectEqual", a, b, "equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectNotEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (a == b)\
{\
    AddFailDescriptionValues("ExpectNotEqual", a, b, "not_equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectNear(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!TGL::IsFloatEqual(a, b))\
{\
    AddFailDescriptionValues("ExpectNear", a, b, "near");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectNotNear(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!TGL::IsFloatEqual(a, b))\
{\
    AddFailDescriptionValues("ExpectNotNear", a, b, "not_near");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectNearP(leftValue, rightValue, precision)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!TGL::IsFloatEqual(a, b, precision))\
{\
    AddFailDescriptionValues("ExpectNearP", a, b, "near");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectNotNearP(leftValue, rightValue, precision)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!TGL::IsFloatEqual(a, b, precision))\
{\
    AddFailDescriptionValues("ExpectNotNearP", a, b, "not_near");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectLessThan(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!(a < b))\
{\
    AddFailDescriptionValues("ExpectLessThan", a, b, "less_than");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectLessEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!(a <= b))\
{\
    AddFailDescriptionValues("ExpectLessEqual", a, b, "less_equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectGreaterThan(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!(a > b))\
{\
    AddFailDescriptionValues("ExpectGreaterThan", a, b, "greater_than");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectGreaterEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (!(a >= b))\
{\
    AddFailDescriptionValues("ExpectGreaterEqual", a, b, "greater_equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectStringEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (a != b)\
{\
    AddFailDescriptionValues("ExpectStringEqual", a, b, "equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectStringNotEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (a == b)\
{\
    AddFailDescriptionValues("ExpectStringNotEqual", a, b, "not_equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectVectorEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
\
if (a != b)\
{\
    AddFailDescriptionValues("ExpectVectorEqual", a, b, "equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

#define ExpectVectorNotEqual(leftValue, rightValue)\
{\
auto a = leftValue;\
auto b = rightValue;\
if (a != b)\
{\
    AddFailDescriptionValues("ExpectVectorNotEqual", a, b, "not_equal");\
    TGL::Test::testPassed = false;\
}}\
++TGL::Test::currentExpect

// void (const std::string &leftValue, const std::string &rightValue)
// void (const std::string &leftValue, const std::string &rightValue)
// void ExpectStringEqualCaseInsensitive(const std::string &leftValue, const std::string &rightValue)
// void ExpectStringNotEqualCaseInsensitive(const std::string &leftValue, const std::string &rightValue)



#endif // TGL_CPP_TEST