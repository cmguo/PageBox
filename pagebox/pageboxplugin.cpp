#include "pageboxplugin.h"
#include "pageboxdocitem.h"

#include <QGraphicsItem>

PageBoxPlugin::PageBoxPlugin(QObject * parent)
    : ToolButtonProvider(parent)
    , item_(nullptr)
{
}

PageBoxPlugin::~PageBoxPlugin()
{
    if (item_)
        delete item_;
}

void PageBoxPlugin::onRelayout(int pageCount)
{
    (void) pageCount;
}

void PageBoxPlugin::onPageChanged(int lastPage, int curPage)
{
    (void) lastPage;
    (void) curPage;
}

void PageBoxPlugin::onSizeChanged(const QSizeF &docSize, const QSizeF &pageSize)
{
    (void) docSize;
    (void) pageSize;
}

bool PageBoxPlugin::selectTest(const QPointF &pt)
{
    (void) pt;
    return false;
}

PageBoxPlugin * PageBoxPlugin::clone() const
{

    QObject * clone = metaObject()->newInstance(
                QGenericArgument(metaObject()->className(), this));
    if (clone)
        return qobject_cast<PageBoxPlugin*>(clone);
    return new PageBoxPlugin;
}

PageBoxDocItem *PageBoxPlugin::document()
{
    return static_cast<PageBoxDocItem*>(item_->parentItem());
}
