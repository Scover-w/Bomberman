#include "SelectedFont.h"

SelectedFont* SelectedFont::instance;

SelectedFont::SelectedFont()
{
    instance = this;
    if (!font.loadFromFile("Font/Chakra_Petch/ChakraPetch-Regular.ttf")) // Quicksand/Quicksand-VariableFont_wght.ttf
    {
        // error...
    }
}

SelectedFont::~SelectedFont()
{

}

Font& SelectedFont::GetFont()
{
    return font;
}