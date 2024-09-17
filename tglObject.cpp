#ifndef TGL_OBJECT_CPP
    #define TGL_OBJECT_CPP



TGL::tglObject::tglObject()
{
    this->Monitor();
}

TGL::tglObject::~tglObject()
{
    this->Untrack();
}



void TGL::tglObject::Clear()
{
}

void TGL::tglObject::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

void TGL::tglObject::Reset()
{
    this->Clear();
    this->Initialize();
}

std::string TGL::tglObject::GetValues() const
{
    return CLASS_IDENTITY + ":\n" + OBJECT_ID;
}



largeuint_t TGL::tglObject::ID() const
{
    return this->m_ID;
}



void TGL::tglObject::Initialize()
{
}

void TGL::tglObject::Monitor()
{
    this->m_ID = TGL::oArray.size();

    if (TGL::oArray.size() ==
        TGL::oArray.capacity())
    {
        TGL::oArray.reserve(TGL::oArray.size() + TGL::ALLOCATION);
        TGL::oActive.reserve(TGL::oActive.size() + TGL::ALLOCATION);
    }

    TGL::oArray.push_back(this);
    TGL::oActive.push_back(true);
}

void TGL::tglObject::Untrack()
{
    TGL::oActive[this->m_ID] = false;
}



#endif // TGL_OBJECT_CPP



































