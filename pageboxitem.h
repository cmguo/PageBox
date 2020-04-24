#ifndef PAGEBOXITEM_H
#define PAGEBOXITEM_H

#include <core/toolbuttonprovider.h>

#include <QGraphicsRectItem>

class PageBoxDocItem;
class ResourceTransform;
class PageBoxToolBar;
class PageNumberWidget;
class PageBoxPlugin;

class PageBoxItem : public ToolButtonProvider, public QGraphicsRectItem
{
    Q_OBJECT

    Q_PROPERTY(PageMode pageMode READ pageMode  WRITE setPageMode)
    Q_PROPERTY(SizeMode sizeMode READ sizeMode  WRITE setSizeMode)
    Q_PROPERTY(int pageNumber READ pageNumber  WRITE setPageNumber)
    Q_PROPERTY(QByteArray pageBoxState READ pageBoxState  WRITE setPageBoxState)

public:
    enum PageMode {
        Paper,
        Book,
    };

    Q_ENUM(PageMode)

    enum SizeMode
    {
        FixedSize,
        MatchContent,
        LargeCanvas
    };

    Q_ENUM(SizeMode)

    enum ScaleMode
    {
        WholePage,
        FitLayout, // when horizontal, fit heigth, else fit width
        ManualScale,
    };

public:
    PageBoxItem(QGraphicsItem * parent = nullptr);

    virtual ~PageBoxItem() override;

public:
    PageBoxDocItem * document() { return document_; }

    QGraphicsItem * toolBar() { return toolBarProxy_; }

    PageMode pageMode() const { return pageMode_; }

    void setPageMode(PageMode mode);

    SizeMode sizeMode() const { return sizeMode_; }

    void setSizeMode(SizeMode mode);

    ScaleMode scaleMode() const { return scaleMode_; }

    void setScaleMode(ScaleMode mode);

    qreal scale() const;

    void setManualScale(qreal scale, bool changeMode = true);

    void transferToManualScale();

    void stepScale(bool up);

    bool canStepScale(bool up);

    void stepMiddleScale();

public:
    // called from PageBoxControl
    void sizeChanged();

    bool selectTest(QPointF const & point);

    void restorePosition();

public:
    void setPlugin(PageBoxPlugin* plugin);

    ResourceTransform * detachTransform();

public slots:
    void duplex();

    void single();

    void scaleUp();

    void scaleDown();

    void exit();

protected:
    int pageNumber();

    void setPageNumber(int n);

    QByteArray pageBoxState();

    void setPageBoxState(QByteArray state);

public:
    virtual void getToolButtons(QList<ToolButton *> &buttons, ToolButton *parent) override;

    virtual void updateToolButton(ToolButton *button) override;

private:
    void rescale();

    QRectF visibleRect() const;

    void documentPageChanged(int page);

    void documentSizeChanged(QSizeF const & size);

    void setDocumentPosition(QPointF const & pos);

    void onTransformChanged();

private:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

private:
    QSizeF calcSize(QSizeF const & size);

private:
    PageBoxDocItem * document_;
    ResourceTransform * transform_;
    PageBoxToolBar * toolBar_;
    QGraphicsItem * toolBarProxy_;
    PageNumberWidget * pageNumber_;

private:
    PageMode pageMode_;
    SizeMode sizeMode_;
    ScaleMode scaleMode_;
    qreal manualScale_;
    qreal scaleInterval_;
    int scaleLevel_;
    int maxScaleLevel_;
    QPointF pos_;

private:
    QPointF start_;
    QRectF direction_;
    int type_;
};

#endif // PAGEBOXITEM_H
