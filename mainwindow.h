#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <windows.h>
#include <iostream>
#include <QTest>
#include <QFileDialog>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_size_editingFinished();

    void on_pushButton_set_size_10_clicked();

    void on_pushButton_set_size_200_clicked();

    void on_pushButton_set_size_random_clicked();

    void on_pushButton_bubble_clicked();

    void on_pushButton_gnome_clicked();

    void on_pushButton_quick_clicked();

    void on_pushButton_hair_clicked();

    void on_pushButton_makaka_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_avg_clicked();

    void on_pushButton_search_linear_clicked();

    void on_pushButton_search_binary_clicked();

    void on_pushButton_search_auto_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clear_clicked();

    void on_lineEdit_setNumber_editingFinished();

    void on_pushButton_summ_clicked();

    void on_pushButton_multiply_clicked();

    void on_pushButton_remove_duplicates_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_save_to_txt_triggered();

    void on_open_from_txt_triggered();

    void on_save_to_scv_triggered();

    void on_open_from_csv_triggered();

private:
    Ui::MainWindow *ui;
    const int MAX_ARRAY_SIZE = 1000000;
    int *array = nullptr; //указатель на основной массив
    int *selectedArray = nullptr; //указатель на массив выбранных элементов
    int selectedArraySize = 0; //длина массива выбранных элементов
    int size = 0; //длина основного массива
    int swipes = 0; //количество перестановок
    int iterations = 0; //количество итераций
    int last_cell_id = -1; //id последней выбранной ячейки, id = номер в основном массиве (с нуля)

    bool check(); //проверка основного массива на валидность
    bool check_numbers(); //проверка элементов TableWidget на валидность
    bool check_numbers_file(QFile *file); //проверяет текстовый файл на валидность данных, если успешно, то формирует массив

    void setTable(int size); //установить новую таблицу с сохранением старых элементов при наличии
    void clearTable(); //очистить таблицу
    void setArrayNumber(int number); //заполнить таблицу и массив константой
    void removeDuplicates(); //удалить дубликаты (только в отсортированном массиве)
    void table_function( void (*function) (int size, int *array_prt, int *iterations, int *swipes)); //декоратор для функций сортировки, устанавливает количество перестановок и итераций, обновляет состояния таблицы
    void clearTableConnectedLabels(); //очистить надписи с информацией о таблице (кол-во элементов, перестановок, итераций)
    void clear_counters(); //очистить надписи с информацией о минимуме, максимуме и среднем таблицы
    void search_function(int func, QString value); //поиск в таблице
    void paintallwhite(); //покрасить все элементы таблицы в белый
    void filterSelectedValues(); //проверка выделенных элементов таблицы на валидность, формирование массива выделенных элементов (selectedArray, selectedArraySize)

    void testSetTable(); //тесты установки таблицы
    void testRemoveDuplicatesTable(); //тесты удаления дубликатов
    void testClearTable(); //тесты очистки таблицы

    QString table_function( int (*function) (int size, int *array_ptr)); //декоратор для поисков максимума и минимума (overload)
    QString table_function(double (*func)(int, int *)); //декоратор для поиска среднего (overload)
};
#endif // MAINWINDOW_H
