#ifndef APPEDITFORM_H
#define APPEDITFORM_H

#include <QWidget>

namespace Ui {
class AppEditForm;
}

class AppEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit AppEditForm(QWidget *parent = nullptr);
    ~AppEditForm();

private:
    Ui::AppEditForm *ui;
};

#endif // APPEDITFORM_H
