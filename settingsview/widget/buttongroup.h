#pragma once

#include <QScopedPointer>
#include <QFrame>

class ButtonGroupPrivate;
class ButtonGroup : public QFrame
{
    Q_OBJECT
public:
    explicit ButtonGroup(QWidget *parent = 0);
    ~ButtonGroup();

signals:
    void buttonChecked(int id);

public slots:
    void setCheckedButton(int id);
    void setButtons(const QStringList &texts);

private:
    QScopedPointer<ButtonGroupPrivate> d_ptr;
    Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_ptr), ButtonGroup)
};

