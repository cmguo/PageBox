#include "pagesource.h"

PageSource::PageSource(Resource * res, Flags flags,
                       Flags clearFlags)
    : ResourceView(res, flags, clearFlags)
{
}

void PageSource::onLoaded()
{
}

bool PageSource::onToolButton(ToolButton *)
{
    return false;
}
