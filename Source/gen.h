#ifndef GEN_H
#define GEN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gen; }
QT_END_NAMESPACE

class gen : public QMainWindow
{
    Q_OBJECT

public:
    explicit gen(QWidget *parent = nullptr);
    ~gen();

private:
    Ui::gen *ui;
private slots:

    void on_exec_clicked();
    void on_upcast_clicked();
};
#endif // GEN_H
