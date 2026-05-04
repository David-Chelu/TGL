#ifndef TEST_TGL_VECTOR_CPP
    #define TEST_TGL_VECTOR_CPP



namespace tglVectorTests
{
using tglVector = TGL::tglVector;
using Vector = std::vector<vType>;


void tglVector_Initialization()
{
    TGL::tglVector
        vector;

    ExpectEqual(vector.dimensions.size(), 0);
    ExpectEqual(vector.Size(), 0);
    ExpectVectorEqual(vector, tglVector());
}

void tglVector_Resize()
{
    TGL::tglVector
        vector;
    
    // checking size only
    vector.Resize(3);
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    ExpectEqual(vector.Size(), 3);
    
    vector.Resize(0);
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    
    vector.Resize(2);
    ExpectVectorEqual(vector, tglVector({0, 0}));
    ExpectEqual(vector.Size(), 2);
    
    vector.Resize(5);
    ExpectVectorEqual(vector, tglVector({0, 0, 0, 0, 0}));
    ExpectEqual(vector.Size(), 5);

    vector.Resize(3);
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    ExpectEqual(vector.Size(), 3);
    
    // use 2nd parameter to fill values
    vector.Resize(0);
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    
    vector.Resize(2, 11);
    ExpectVectorEqual(vector, tglVector({11, 11}));
    ExpectEqual(vector.Size(), 2);
    
    vector.Resize(5, 37);
    ExpectVectorEqual(vector, tglVector({11, 11, 37, 37, 37}));
    ExpectEqual(vector.Size(), 5);

    vector.Resize(3);
    ExpectVectorEqual(vector, tglVector({11, 11, 37}));
    ExpectEqual(vector.Size(), 3);
}

void tglVector_Bool()
{
    TGL::tglVector
        vector;
    
    ExpectTrue(!vector);
    ExpectFalse(vector);

    vector = {1};
    ExpectTrue(vector);
    ExpectFalse(!vector);
}

void tglVector_Assign()
{
    TGL::tglVector
        vector,
        other;
    
    vector = other;
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    vector = 5;
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    
    other = {1, 2};
    vector = other;
    ExpectVectorEqual(vector, tglVector({1, 2}));
    ExpectEqual(vector.Size(), 2);
    vector = 7;
    ExpectVectorEqual(vector, tglVector({7, 7}));
    ExpectEqual(vector.Size(), 2);

    other = {};
    vector = other;
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    vector = 11;
    ExpectVectorEqual(vector, tglVector());
    ExpectEqual(vector.Size(), 0);
    
    other = {3, 4, 5};
    vector = other;
    ExpectVectorEqual(vector, tglVector({3, 4, 5}));
    ExpectEqual(vector.Size(), 3);
    vector = 13;
    ExpectVectorEqual(vector, tglVector({13, 13, 13}));
    ExpectEqual(vector.Size(), 3);
    
    other = {6, 7, 8, 9, 10};
    vector = other;
    ExpectVectorEqual(vector, tglVector({6, 7, 8, 9, 10}));
    ExpectEqual(vector.Size(), 5);
    vector = 17;
    ExpectVectorEqual(vector, tglVector({17, 17, 17, 17, 17}));
    ExpectEqual(vector.Size(), 5);
    
    other = {11, 12};
    vector = other;
    ExpectVectorEqual(vector, tglVector({11, 12}));
    ExpectEqual(vector.Size(), 2);
    vector = 19;
    ExpectVectorEqual(vector, tglVector({19, 19}));
    ExpectEqual(vector.Size(), 2);
}

void tglVector_Subtract()
{
    TGL::tglVector
        vector;
    
    ExpectVectorEqual(vector, tglVector());
    vector -= 2;
    ExpectVectorEqual(vector, tglVector());
    vector -= {3, 5};
    ExpectVectorEqual(vector, tglVector());
    vector -= Vector({7, 11});
    ExpectVectorEqual(vector, tglVector());
    vector -= tglVector({13, 17});
    ExpectVectorEqual(vector, tglVector());
    
    vector = {100, 100, 100};
    ExpectVectorEqual(vector, tglVector({100, 100, 100}));
    vector -= 19;
    ExpectVectorEqual(vector, tglVector({81, 81, 81}));
    vector -= {23, 29};
    ExpectVectorEqual(vector, tglVector({58, 52, 81}));
    vector -= Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({27, 15, 81}));
    vector -= tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({-14, -28, 81}));
}

void tglVector_Add()
{
    TGL::tglVector
        vector;
    
    ExpectVectorEqual(vector, tglVector());
    vector += 2;
    ExpectVectorEqual(vector, tglVector());
    vector += {3, 5};
    ExpectVectorEqual(vector, tglVector());
    vector += Vector({7, 11});
    ExpectVectorEqual(vector, tglVector());
    vector += tglVector({13, 17});
    ExpectVectorEqual(vector, tglVector());
    
    vector = {0, 0, 0};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector += 19;
    ExpectVectorEqual(vector, tglVector({19, 19, 19}));
    vector += {23, 29};
    ExpectVectorEqual(vector, tglVector({42, 48, 19}));
    vector += Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({73, 85, 19}));
    vector += tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({114, 128, 19}));
}

void tglVector_Multiply()
{
    TGL::tglVector
        vector;
    
    ExpectVectorEqual(vector, tglVector());
    vector *= 2;
    ExpectVectorEqual(vector, tglVector());
    vector *= {3, 5};
    ExpectVectorEqual(vector, tglVector());
    vector *= Vector({7, 11});
    ExpectVectorEqual(vector, tglVector());
    vector *= tglVector({13, 17});
    ExpectVectorEqual(vector, tglVector());
    
    vector = {0, 0, 0};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector *= 19;
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector *= {23, 29};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector *= Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector *= tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));

    vector = {1, 1, 1};
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
    vector *= 2;
    ExpectVectorEqual(vector, tglVector({2, 2, 2}));
    vector *= {3, 3};
    ExpectVectorEqual(vector, tglVector({6, 6, 2}));
    vector *= Vector({1, 1});
    ExpectVectorEqual(vector, tglVector({6, 6, 2}));
    vector *= tglVector({3, 3});
    ExpectVectorEqual(vector, tglVector({18, 18, 2}));
    vector *= {1, 0};
    ExpectVectorEqual(vector, tglVector({18, 0, 2}));
    vector *= 0;
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
}

void tglVector_Divide()
{
    TGL::tglVector
        vector;
    
    ExpectVectorEqual(vector, tglVector());
    vector /= 2;
    ExpectVectorEqual(vector, tglVector());
    vector /= {3, 5};
    ExpectVectorEqual(vector, tglVector());
    vector /= Vector({7, 11});
    ExpectVectorEqual(vector, tglVector());
    vector /= tglVector({13, 17});
    ExpectVectorEqual(vector, tglVector());
    
    vector = {0, 0, 0};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector /= 19;
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector /= {23, 29};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector /= Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector /= tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));

    vector = {100, 100, 100};
    ExpectVectorEqual(vector, tglVector({100, 100, 100}));
    vector /= 2;
    ExpectVectorEqual(vector, tglVector({50, 50, 50}));
    vector /= {3, 3};
    ExpectVectorEqual(vector, tglVector({16, 16, 50}));
    vector /= Vector({1, 1});
    ExpectVectorEqual(vector, tglVector({16, 16, 50}));
    vector /= tglVector({3, 3});
    ExpectVectorEqual(vector, tglVector({5, 5, 50}));
    vector /= {1, 0};
    ExpectVectorEqual(vector, tglVector({5, 0, 50}));
    vector /= 0;
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
}

void tglVector_RaisePower()
{
    TGL::tglVector
        vector;
    
    ExpectVectorEqual(vector, tglVector());
    vector ^= 2;
    ExpectVectorEqual(vector, tglVector());
    vector ^= {3, 5};
    ExpectVectorEqual(vector, tglVector());
    vector ^= Vector({7, 11});
    ExpectVectorEqual(vector, tglVector());
    vector ^= tglVector({13, 17});
    ExpectVectorEqual(vector, tglVector());
    
    vector = {0, 0, 0};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector ^= 19;
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector ^= {23, 29};
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector ^= Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    vector ^= tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({0, 0, 0}));
    
    vector = {1, 1, 1};
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
    vector ^= 19;
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
    vector ^= {23, 29};
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
    vector ^= Vector({31, 37});
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
    vector ^= tglVector({41, 43});
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));

    vector = {2, 2, 2};
    ExpectVectorEqual(vector, tglVector({2, 2, 2}));
    vector ^= 2;
    ExpectVectorEqual(vector, tglVector({4, 4, 4}));
    vector ^= {3, 3};
    ExpectVectorEqual(vector, tglVector({64, 64, 4}));
    vector ^= Vector({1, 1});
    ExpectVectorEqual(vector, tglVector({64, 64, 4}));
    vector /= {21, 21};
    vector ^= tglVector({3, 3});
    ExpectVectorEqual(vector, tglVector({27, 27, 4}));
    vector ^= {1, 0};
    ExpectVectorEqual(vector, tglVector({27, 1, 4}));
    vector ^= 0;
    ExpectVectorEqual(vector, tglVector({1, 1, 1}));
}

void tglVector_ExternalOperators()
{
    TGL::tglVector
        vector,
        vectorSame,
        vectorDifferent;
    
    std::vector<vType>
        stdVector({1, 1});

    std::initializer_list<vType>
        ilVector = {1, 1};

    vector = vectorSame = {1, 1};
    vectorDifferent = {4, 4};

    ExpectTrue(vector == vectorSame);
    ExpectFalse(vector == vectorDifferent);
    ExpectTrue(vector != vectorDifferent);
    ExpectFalse(vector != vectorSame);

    ExpectTrue(vector == stdVector);
    ExpectFalse(vectorDifferent == stdVector);
    ExpectTrue(vectorDifferent != stdVector);
    ExpectFalse(vector != stdVector);
    ExpectTrue(stdVector == vector);
    ExpectFalse(stdVector == vectorDifferent);
    ExpectTrue(stdVector != vectorDifferent);
    ExpectFalse(stdVector != vector);

    ExpectTrue(vector == ilVector);
    ExpectFalse(vectorDifferent == ilVector);
    ExpectTrue(vectorDifferent != ilVector);
    ExpectFalse(vector != ilVector);
    ExpectTrue(ilVector == vector);
    ExpectFalse(ilVector == vectorDifferent);
    ExpectTrue(ilVector != vectorDifferent);
    ExpectFalse(ilVector != vector);

    largeint_t
        after = 1,
        before = 5;

    ExpectVectorEqual(vectorDifferent + vector, tglVector({5, 5}));
    ExpectVectorEqual(vectorDifferent + tglVector({6, 6, 6}), tglVector({10, 10, 6}));
    ExpectVectorEqual(vectorDifferent + tglVector(), vectorDifferent);
    ExpectVectorEqual(vectorDifferent + after, tglVector({5, 5}));
    ExpectVectorEqual(tglVector()     + after, tglVector());
    ExpectVectorEqual(before          + vectorDifferent, tglVector({9, 9}));
    ExpectVectorEqual(before          + tglVector(), tglVector());

    ExpectVectorEqual(vectorDifferent - vector, tglVector({3, 3}));
    ExpectVectorEqual(vectorDifferent - tglVector({6, 6, 6}), tglVector({-2, -2, -6}));
    ExpectVectorEqual(vectorDifferent - tglVector(), vectorDifferent);
    ExpectVectorEqual(vectorDifferent - after, tglVector({3, 3}));
    ExpectVectorEqual(tglVector()     - after, tglVector());
    ExpectVectorEqual(before          - vectorDifferent, tglVector({1, 1}));
    ExpectVectorEqual(before          - tglVector(), tglVector());

    ExpectVectorEqual(vectorDifferent / vector, vectorDifferent);
    ExpectVectorEqual(vectorDifferent / tglVector({6, 6, 6}), tglVector({0, 0, 0}));
    ExpectVectorEqual(vectorDifferent / tglVector(), tglVector({0, 0}));
    ExpectVectorEqual(vectorDifferent / after, vectorDifferent);
    ExpectVectorEqual(tglVector()     / after, tglVector());
    ExpectVectorEqual(before          / vectorDifferent, tglVector({1, 1}));
    ExpectVectorEqual(before          / tglVector(), tglVector());

    ExpectVectorEqual(vectorDifferent * vector, vectorDifferent);
    ExpectVectorEqual(vectorDifferent * tglVector({6, 6, 6}), tglVector({24, 24, 0}));
    ExpectVectorEqual(vectorDifferent * tglVector(), tglVector({0, 0}));
    ExpectVectorEqual(vectorDifferent * after, vectorDifferent);
    ExpectVectorEqual(tglVector()     * after, tglVector());
    ExpectVectorEqual(before          * vectorDifferent, tglVector({20, 20}));
    ExpectVectorEqual(before          * tglVector(), tglVector());

    ExpectVectorEqual(vectorDifferent ^ vector, vectorDifferent);
    ExpectVectorEqual(vectorDifferent ^ tglVector({6, 6, 6}), tglVector({4096, 4096, 0}));
    ExpectVectorEqual(vectorDifferent ^ tglVector(), tglVector({0, 0}));
    ExpectVectorEqual(vectorDifferent ^ after, vectorDifferent);
    ExpectVectorEqual(tglVector()     ^ after, tglVector());
    ExpectVectorEqual(before          ^ vectorDifferent, tglVector({625, 625}));
    ExpectVectorEqual(before          ^ tglVector(), tglVector());
}
}

TGL::Test::test_tglVector::test_tglVector(TGL::Test::test_TGL &testMaster) : test_tglTest(testMaster)
{
    _tests =
    {
        {"tglVector_Initialization", tglVectorTests::tglVector_Initialization}
       ,{"tglVector_Resize", tglVectorTests::tglVector_Resize}
       ,{"tglVector_Bool", tglVectorTests::tglVector_Bool}
       ,{"tglVector_Assign", tglVectorTests::tglVector_Assign}
       ,{"tglVector_Subtract", tglVectorTests::tglVector_Subtract}
       ,{"tglVector_Add", tglVectorTests::tglVector_Add}
       ,{"tglVector_Multiply", tglVectorTests::tglVector_Multiply}
       ,{"tglVector_Divide", tglVectorTests::tglVector_Divide}
       ,{"tglVector_RaisePower", tglVectorTests::tglVector_RaisePower}
       ,{"tglVector_ExternalOperators", tglVectorTests::tglVector_ExternalOperators}
    };
}



#endif // TEST_TGL_VECTOR_CPP