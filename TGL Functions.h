#ifndef TGL_FUNCTIONS_H
    #define TGL_FUNCTIONS_H



#if 1 // TGL functions

#if 1 // miscellaneous functions

const char *TGL::ClassName(TGL::Identity identity)
{
    switch(identity)
    {
        case TGL::Identity::TGL_WINDOW: return "tglWindow";
    }

    return "Invalid Identity";
}

#endif // miscellaneous functions



#if 1 // object monitoring functions

#endif// object monitoring functions

#endif // TGL functions



#endif // TGL_FUNCTIONS_H



































