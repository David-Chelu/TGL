#ifndef TGL_OBJECT_H
    #define TGL_OBJECT_H



class TGL::tglObject
{
public:

    tglObject();
    virtual ~tglObject();



    virtual void
        Clear();

    inline virtual void
        DisplayValues() const;

    void
        Reset();

    inline std::string
        GetValues() const;



    largeuint_t
        ID() const;

protected:

    virtual void
        Initialize();

    largeuint_t
        m_ID;

    // TODO: add a member string for object name. By default it'll be class name + class ID

private:

    void
        Monitor(),
        Untrack();
};



#endif // TGL_OBJECT_H



































