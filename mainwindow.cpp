#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sorts.h"
#include "tools.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->testSetTable();
//    this->testRemoveDuplicatesTable();
//    this->testClearTable();
}

MainWindow::~MainWindow()
{
    if (this->array != nullptr)
    {
        delete [] this->array;
    }
    if (this->selectedArray != nullptr)
    {
        delete [] this->selectedArray;
    }
    delete ui;
}

void MainWindow::clear_counters()
{
    ui->label_avg->clear();
    ui->label_max->clear();
    ui->label_min->clear();
}

void MainWindow::clearTableConnectedLabels()
{
    ui->label_iterations->clear();
    ui->label_swipes->clear();
    ui->label_sum->clear();
    ui->label_multiply->clear();
    ui->label_selected_avg->clear();
    ui->label_selected_min->clear();
    ui->label_selected_max->clear();
    ui->label_selected_selected->clear();
    ui->label_selected_selected_sum->clear();
    ui->label_selected_selected_multiply->clear();
}

void MainWindow::setTable(int size)
{
    if ((size > 0) && (size <= this->MAX_ARRAY_SIZE))
    {
        int last_size = this->size;
        this->size = size;
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setColumnCount(size);

        QTableWidgetItem *table_item;
        try {

            if (this->array != nullptr)
            {
                int min_size = size < last_size ? size : last_size;

                int *array_copy = new int[min_size];
                memcpy(array_copy, array, min_size * sizeof (int));
                delete [] this->array;
                this->array = new int[size];
                memset(this->array, 0, size * sizeof (int));
                memcpy(this->array, array_copy, min_size * sizeof (int));
                delete [] array_copy;
            }
            else
            {
                this->array = new int[size];
                memset(this->array, 0, size * sizeof (int));
            }
            if (size > last_size)
            {
                for (int i = last_size; i < size; i++)
                {

                    table_item = new QTableWidgetItem();
                    table_item->setBackground(Qt::red);
                    ui->tableWidget->setItem(0, i, table_item);

                }
            }

        }  catch (std::bad_alloc) {
            QMessageBox::information(this, "Ошибка", "Недостаточно памяти");
        }


    }
    else
    {
        QMessageBox::information(this, "Ошибка", "Извините, но мы размер должен быть в промежутке [1, " + QString::number(this->MAX_ARRAY_SIZE) + "]");
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget->setRowCount(0);
        this->size = 0;
        this->array = nullptr;
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
}


void MainWindow::testSetTable()
{
    this->array = nullptr;
    this->size = 0;

    this->setTable(10);
    QCOMPARE(this->size, 10);
    cout << "Size test 1 passed" << endl;
    for (int i = 0; i < this->size; i++)
    {
        QCOMPARE(this->array[i], 0);
    }
    cout << "Array test 1 passed" << endl;
    delete [] this->array;
    this->array = new int[5]{2, 8, 6, 8, 4};
    this->size = 5;
    this->setTable(4);
    QCOMPARE(this->size, 4);
    cout << "Size test 2 passed" << endl;

    QCOMPARE(this->array[0], 2);
    QCOMPARE(this->array[1], 8);
    QCOMPARE(this->array[2], 6);
    QCOMPARE(this->array[3], 8);
    cout << "Array test 2 passed" << endl;

    this->setTable(5);
    QCOMPARE(this->size, 5);
    cout << "Size test 3 passed" << endl;

    QCOMPARE(this->array[0], 2);
    QCOMPARE(this->array[1], 8);
    QCOMPARE(this->array[2], 6);
    QCOMPARE(this->array[3], 8);
    QCOMPARE(this->array[4], 0);
    cout << "Array test 3 passed" << endl;

    this->setTable(0);
    QCOMPARE(this->size, 0);
    cout << "Size test 4 passed" << endl;

    QCOMPARE(this->array, nullptr);
    cout << "Array test 4 passed" << endl;

    this->setTable(-1000);
    QCOMPARE(this->size, 0);
    cout << "Size test 5 passed" << endl;

    QCOMPARE(this->array, nullptr);
    cout << "Array test 5 passed" << endl;

    this->setTable(201);
    QCOMPARE(this->size, 0);
    cout << "Size test 6 passed" << endl;

    QCOMPARE(this->array, nullptr);
    cout << "Array test 6 passed" << endl;

    delete [] this->array;
    this->array = nullptr;
    this->size = 0;
}

void MainWindow::removeDuplicates()
{
    if (this->check() && this->check_numbers())
    {
        if (is_sorted(this->size, this->array))
        {
            QTableWidgetItem *item;
            try {
                int *set = new int[this->size];
                int count = 0;
                for (int i = 0; i < this->size; i++)
                {
                    bool is_in_set = false;
                    for (int j = 0; j < count; j++)
                    {
                        if (set[j] == this->array[i])
                        {
                            is_in_set = true;
                        }
                    }
                    if (not is_in_set)
                    {
                        set[count] = this->array[i];
                        count++;
                    }
                }
                delete [] this->array;
                this->array = new int [count];
                this->size = count;
                memcpy(this->array, set, this->size * sizeof (int));
                delete [] set;
            }  catch (std::bad_alloc) {
                QMessageBox::information(this, "Ошибка", "Недостаточно памяти");
                return;
            }

            ui->tableWidget->setColumnCount(this->size);
            for (int i = 0; i < this->size; i++)
            {
                item = ui->tableWidget->item(0, i);
                item->setText(QString::number(this->array[i]));
                item->setBackground(Qt::white);
            }



        }
        else
        {
            QMessageBox::information(this, "Ошибка", "По 'ТЗ' нельзя в неотсортированном");
        }
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
    ui->lineEdit_size->setText(QString::number(this->size));
}

void MainWindow::testRemoveDuplicatesTable()
{
    delete [] this->array;
    this->array = nullptr;
    this->size = 0;

    this->array = new int[5]{1, 2, 2, 5, 8};
    this->size = 5;

    this->removeDuplicates();

    QCOMPARE(this->array[0], 1);
    QCOMPARE(this->array[1], 2);
    QCOMPARE(this->array[2], 5);
    QCOMPARE(this->array[3], 8);
    QCOMPARE(this->size, 4);
    cout << "Remove duplicates test 1 passed" << endl;


    delete [] this->array;

    this->array = new int[5]{1, 2, 4, 5, 8};
    this->size = 5;

    this->removeDuplicates();

    QCOMPARE(this->array[0], 1);
    QCOMPARE(this->array[1], 2);
    QCOMPARE(this->array[2], 4);
    QCOMPARE(this->array[3], 5);
    QCOMPARE(this->array[4], 8);
    QCOMPARE(this->size, 5);
    cout << "Remove duplicates test 2 passed" << endl;


    delete [] this->array;

    this->array = nullptr;
    this->size = 0;

    this->removeDuplicates();

    QCOMPARE(this->array, nullptr);
    QCOMPARE(this->size, 0);
    cout << "Remove duplicates test 3 passed" << endl;


    delete [] this->array;

    this->array = new int[8]{1, 1, 1, 1, 1, 1, 1, 1};
    this->size = 8;

    this->removeDuplicates();

    QCOMPARE(this->array[0], 1);
    QCOMPARE(this->size, 1);
    cout << "Remove duplicates test 4 passed" << endl;


    delete [] this->array;
    this->array = nullptr;
    this->size = 0;
}

void MainWindow::clearTable()
{
    if (this->check()){
        memset(this->array, 0, this->size * sizeof (int));

        for (int i = 0; i < this->size; i++)
        {
            array[i] = 1;
        }
        if (ui->tableWidget->item(0, 0) != nullptr)
        {
            QTableWidgetItem *item;
            for (int i = 0; i < this->size; i++)
            {
                item = ui->tableWidget->item(0, i);
                if (item != nullptr)
                {
                    item->setBackground(Qt::red);
                    item->setText("");
                }
            }
        }
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
}

void MainWindow::testClearTable()
{
    delete [] this->array;
    this->array = nullptr;
    this->size = 0;

    this->setTable(5);
    this->on_pushButton_set_size_random_clicked();
    this->clearTable();
    for (int i = 0; i < this->size; i++)
    {
        cout << this->array[i] << " ";
    }
    cout << endl;
    QCOMPARE(this->array[0], 0);
    QCOMPARE(this->array[1], 0);
    QCOMPARE(this->array[2], 0);
    QCOMPARE(this->array[3], 0);
    QCOMPARE(this->array[4], 0);
    QCOMPARE(this->size, 5);
    cout << "Clear Table test 1 passed" << endl;

    this->array = nullptr;
    this->size = 0;
    ui->tableWidget->setColumnCount(0);
}

void MainWindow::setArrayNumber(int number)
{
    if ((this->array != nullptr) && (this->size > 0) && (ui->tableWidget->item(0, 0) != nullptr))
    {
        QTableWidgetItem *item;
        for (int i = 0; i < this->size; i++)
        {
            this->array[i] = number;
            item = ui->tableWidget->item(0, i);
            item->setText(QString::number(number));
            item->setBackground(Qt::white);
        }
    }
    else
    {
//        cout << this->size << " " << bool(this->array == nullptr) << " " << bool(ui->tableWidget->item(0, 0) == nullptr);
        QMessageBox::information(this, "Ошибка", "Таблица не установлена");
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
}


void MainWindow::on_lineEdit_size_editingFinished()
{
    bool is_int;
    int number;
    if (ui->lineEdit_size->text() != "")
    {
        number = ui->lineEdit_size->text().toInt(&is_int);
        this->setTable(number);
    }
}

void MainWindow::on_pushButton_set_size_10_clicked()
{
    this->setTable(10);
    ui->lineEdit_size->setText("10");
}

void MainWindow::paintallwhite()
{
    bool flag = true;
    for (int i = 0; i < this->size; i++)
    {
        ui->tableWidget->item(0, i)->text().toInt(&flag);
        if (flag == true)
        {
            ui->tableWidget->item(0, i)->setBackground(Qt::white);
        }
    }
}

void MainWindow::on_pushButton_set_size_200_clicked()
{
    this->setTable(200);
    ui->lineEdit_size->setText("200");
}

bool MainWindow::check()
{
    if ((this->size <= 0) or (this->array == nullptr))
    {
        QMessageBox::information(this, "Ошибка", "Программе не с чем работать");
        return false;
    }
    return true;
}

void MainWindow::on_pushButton_set_size_random_clicked()
{
    if (this->check())
    {
        int value;
        QTableWidgetItem *table_item;
        srand(clock());

        ui->tableWidget->setUpdatesEnabled(false);
        for (int i = 0; i < this->size; i++)
        {
            value = rand() % 201 - 100;
            this->array[i] = value;
            table_item = ui->tableWidget->item(0, i);
            if (table_item != nullptr)
            {
                table_item->setText(QString::number(value));
                table_item->setBackground(Qt::white);
            }
        }
        ui->tableWidget->setUpdatesEnabled(true);
        ui->tableWidget->scrollToItem(ui->tableWidget->item(0, 0));
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
}

bool MainWindow::check_numbers()
{
    bool flag = true;
    for (int i = 0; i < this->size; i++)
    {
        ui->tableWidget->item(0, i)->text().toInt(&flag);
        if (flag == false)
        {
            ui->tableWidget->item(0, i)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(0, i));
            QMessageBox::information(this, "Ошибка", "Ячейка содержит невалидные данные");
            return flag;
        }
        else {
            ui->tableWidget->item(0, i)->setBackground(Qt::white);
        }
    }
    return true;
}

void quick_sort_container(int size, int *array_ptr, int *iterations, int *swipes)
{
    quick_sort(array_ptr, 0, size - 1, iterations, swipes);
}

void MainWindow::table_function( void (*func)(int size, int *array_ptr, int *iterations, int *swipes) )
{
    if (this->check() && this->check_numbers())
    {
        this->swipes = 0;
        this->iterations = 0;
        func(this->size, this->array, &this->iterations, &this->swipes);
        for (int i = 0; i < this->size; i++)
        {
            ui->tableWidget->item(0, i)->setText(QString::number(this->array[i]));
        }
        ui->label_swipes->setText(QString::number(this->swipes));
        ui->label_iterations->setText(QString::number(this->iterations));
        if (func == &makaka_sort)
        {
            if (this->swipes >= 1000)
            {
                QMessageBox::information(this, "Ошибка", "Обезьянки не справились за 1000 попыток");
            }
        }
    }
}

QString MainWindow::table_function(int (*func)(int, int *))
{
    if (this->check() && this->check_numbers())
    {
        int value = func(this->size, this->array);
        return QString::number(value);
    }
    return "";
}

QString MainWindow::table_function(double (*func)(int, int *))
{
    if (this->check() && this->check_numbers())
    {
        double value = func(this->size, this->array);
        return QString().setNum(value, 'f', 2);
    }
    return "";
}

void MainWindow::search_function(int func, QString value)
{
    bool flag;
    int number = value.toInt(&flag);
    if (not flag)
    {
        QMessageBox::information(this, "Ошибка", "Данные для поиска не валидны, введите число");
        this->paintallwhite();
        return;
    }
    this->paintallwhite();
    if (this->check() && this->check_numbers())
    {
        int index = 0;
        int count = 0;
        QString result = "";

        if (func == 1) //линейный поиск
        {
            int size = this->size;
            for (int i = 0; i < size; i++)
            {
                if (this->array[i] == number)
                {
                    ui->tableWidget->item(0, i)->setBackground(Qt::green);
                    result += QString::number(i + 1) + " ";
                    count += 1;
                    index = i;
                }
            }

        }
        else if (func == 2) //бинарный поиск
        {
            if (is_sorted(this->size, this->array))
            {
                index = find_binary(this->size, this->array, number);
                if (index != -1)
                {
                    count += 1;
                    ui->tableWidget->item(0, index)->setBackground(Qt::green);
                    result += QString::number(index + 1) + " ";
                    int index2 = index - 1;
                    while (index2 >= 0 && this->array[index2] == number)
                    {
                        ui->tableWidget->item(0, index2)->setBackground(Qt::green);
                        result += QString::number(index2 + 1) + " ";
                        index2 -= 1;
                        count += 1;
                    }
                    while (index + 1 <= this->size && this->array[index + 1] == number)
                    {
                        index += 1;
                        ui->tableWidget->item(0, index)->setBackground(Qt::green);
                        result += QString::number(index + 1) + " ";
                        count += 1;
                    }
                }
            }
            else
            {
                QMessageBox::information(this, "Ошибка", "Бинарный поиск возможен только в отсортированном массиве");
                this->paintallwhite();
                return;
            }
        }
        else //авто поиск
        {
            if (is_sorted(this->size, this->array))
            {
                index = find_binary(this->size, this->array, number);
                if (index != -1)
                {
                    int index2 = index - 1;
                    count += 1;
                    ui->tableWidget->item(0, index)->setBackground(Qt::green);
                    result += QString::number(index + 1) + " ";
                    while (index2 >= 0 && this->array[index2] == number)
                    {
                        ui->tableWidget->item(0, index2)->setBackground(Qt::green);
                        result += QString::number(index2 + 1) + " ";
                        index2 -= 1;
                        count += 1;
                    }
                    while (index + 1 <= this->size && this->array[index + 1] == number)
                    {
                        index += 1;
                        ui->tableWidget->item(0, index)->setBackground(Qt::green);
                        result += QString::number(index + 1) + " ";
                        count += 1;
                    }
                }
            }
            else
            {
                int size = this->size;
                for (int i = 0; i < size; i++)
                {
                    if (this->array[i] == number)
                    {
                        count += 1;
                        ui->tableWidget->item(0, i)->setBackground(Qt::green);
                        result += QString::number(i + 1) + " ";
                        index = i;
                    }
                }
            }
        }
        if (count == 0)
        {
            QMessageBox::information(this, "Ошибка", "Элемент не найден");
            this->paintallwhite();
        }
        else
        {
            ui->tableWidget->scrollToItem(ui->tableWidget->item(0, index));
            result = "Найдено значений: " + QString::number(count) + "\nНомера колонок: " + result;
            QMessageBox::information(this, "Результат операции", result);
        }
    }
}

void MainWindow::on_pushButton_bubble_clicked()
{
    this->table_function(bubble_sort);
}

void MainWindow::on_pushButton_gnome_clicked()
{
    this->table_function(gnome_sort);
}

void MainWindow::on_pushButton_quick_clicked()
{
    this->table_function(quick_sort_container);
}

void MainWindow::on_pushButton_hair_clicked()
{
    this->table_function(hair_sort);
}

void MainWindow::on_pushButton_makaka_clicked()
{
    if (this->size > 5)
    {
        QMessageBox::information(this, "Ошибка", "Обезьянки не сортируют массив с размерностью более 5");
    }
    else
    {
        this->table_function(makaka_sort);
    }
}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    bool is_int;
    int number;
    number = item->text().toInt(&is_int);
    if (item->column() == this->last_cell_id)
    {
        if (not is_int)
        {
            item->setBackground(Qt::red);
        }
        else
        {
            item->setBackground(Qt::white);
            this->array[item->column()] = number;
        }
    }
    else {
        if ( is_int)
        {
//            cout << "replaced item with column: " << item->column() << endl;
//            cout << "prev " << this->array[item->column()] << " " << "next " << number << endl;
            this->array[item->column()] = number;
        }
    }
    this->clearTableConnectedLabels();
    this->clear_counters();
}


void MainWindow::on_pushButton_min_clicked()
{
    ui->label_min->setText(this->table_function(min));
}


void MainWindow::on_pushButton_max_clicked()
{
    ui->label_max->setText(this->table_function(max));
}


void MainWindow::on_pushButton_avg_clicked()
{
    ui->label_avg->setText(this->table_function(avg));
}

void MainWindow::on_pushButton_search_linear_clicked()
{
    this->search_function(1, ui->lineEdit_search_linear->text());
}


void MainWindow::on_pushButton_search_binary_clicked()
{
    this->search_function(2, ui->lineEdit_search_binary->text());
}


void MainWindow::on_pushButton_search_auto_clicked()
{
    this->search_function(3, ui->lineEdit_search_auto->text());
}


void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    this->last_cell_id = item->column();
}


void MainWindow::on_pushButton_clear_clicked()
{
    this->clearTable();
}


void MainWindow::on_lineEdit_setNumber_editingFinished()
{
    bool is_int;
    int number;
    if (ui->lineEdit_setNumber->text() != "")
    {
        number = ui->lineEdit_setNumber->text().toInt(&is_int);
        if (is_int){
            this->setArrayNumber(number);
        }
        else
        {
            QMessageBox::information(this, "Ошибка", "Значение должно быть числом");
        }
    }
}

void MainWindow::on_pushButton_summ_clicked()
{
    if (this->check() && this->check_numbers())
    {
        long long result = 0;
        for (int i = 0; i < this->size; i++)
        {
            if (is_owerflow_operation_sum(result, this->array[i]))
            {
                ui->label_sum->setText("");
                QMessageBox::information(this, "Ошибка", "Результат слишком велик, чтобы его посчитать");
                return;
            }
            else
            {
                result += this->array[i];
            }
        }
        ui->label_sum->setText(QString::number(result));
    }
}


void MainWindow::on_pushButton_multiply_clicked()
{
    if (this->check() && this->check_numbers())
    {
        bool zero_exists = false;
        for (int i = 0; i < this->size; i++)
        {
            if (this->array[i] == 0)
            {
                zero_exists = true;
                break;
            }
        }
        long long result = 1;
        if (zero_exists)
        {
            result = 0;
        }
        else
        {
            result = 1;
            for (int i = 0; i < this->size; i++)
            {
                if (is_owerflow_operation_multiply(result, this->array[i]))
                {
                    ui->label_multiply->setText("");
                    QMessageBox::information(this, "Ошибка", "Результат слишком велик, чтобы его посчитать");
                    return;
                }
                else
                {
                    result *= this->array[i];
                }
            }
        }
        ui->label_multiply->setText(QString::number(result));
    }
}


void MainWindow::on_pushButton_remove_duplicates_clicked()
{
    this->removeDuplicates();
}

void MainWindow::filterSelectedValues()
{
    if ((this->array != nullptr) && (this->size > 0))
    {
        bool checknumber = false;
        int *tempArray = new int[this->size];
        int count = 0;
        int number;
        QTableWidgetItem *item;
        for (int i = 0; i < this->size; i++)
        {
            item = ui->tableWidget->item(0, i);
            if (item == nullptr){
                throw 1;
            }
            number = item->text().toInt(&checknumber);
            if (not checknumber)
            {
                throw 1;
            }
            if (item->isSelected())
            {
                tempArray[count] = number;
                count += 1;
            }
        }

        this->selectedArray = new int[count];
        memcpy(selectedArray, tempArray, count * sizeof (int));
        this->selectedArraySize = count;
        delete [] tempArray;
    }
    else
    {
        if (this->selectedArray != nullptr)
        {
            delete [] this->selectedArray;
            this->selectedArray = nullptr;
        }
        this->selectedArraySize = 0;
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    try {
        this->filterSelectedValues();
    }
    catch (int error) {
        //увы, но выделили бяку
//        cout << "error, " << error << endl;
        ui->label_selected_avg->clear();
        ui->label_selected_min->clear();
        ui->label_selected_max->clear();
        ui->label_selected_selected->clear();
        ui->label_selected_selected_sum->clear();
        ui->label_selected_selected_multiply->clear();
        return;
    }
    catch (std::bad_alloc)
    {
        QMessageBox::information(this, "Ошибка", "Недостаточно памяти");
        ui->label_selected_avg->clear();
        ui->label_selected_min->clear();
        ui->label_selected_max->clear();
        ui->label_selected_selected->clear();
        ui->label_selected_selected_sum->clear();
        ui->label_selected_selected_multiply->clear();
        return;
    }
    if ((this->selectedArray != nullptr) && this->selectedArraySize > 0)
    {
//        cout << "ok, " << this->selectedArraySize << endl;
        double average = avg(this->selectedArraySize, this->selectedArray);
        int minimum = min(this->selectedArraySize, this->selectedArray);
        int maximum = max(this->selectedArraySize, this->selectedArray);
        ui->label_selected_avg->setText(QString::number(average, 'f', 2));
        ui->label_selected_min->setText(QString::number(minimum));
        ui->label_selected_max->setText(QString::number(maximum));
        ui->label_selected_selected->setText(QString::number(this->selectedArraySize));

        try {
            long long result = sum(this->selectedArraySize, this->selectedArray);
            ui->label_selected_selected_sum->setText(QString::number(result));
        } catch (int i) {
            ui->label_selected_selected_sum->setText("Переполнение");
        }

        try {
            long long result = multiply(this->selectedArraySize, this->selectedArray);
            ui->label_selected_selected_multiply->setText(QString::number(result));
        } catch (int i) {
            ui->label_selected_selected_multiply->setText("Переполнение");
        }

    }
    else
    {
//        cout << "trouble, " << (this->selectedArray == nullptr) << " " << (this->selectedArraySize) << endl;
        ui->label_selected_avg->clear();
        ui->label_selected_min->clear();
        ui->label_selected_max->clear();
        ui->label_selected_selected->clear();
        ui->label_selected_selected_sum->clear();
        ui->label_selected_selected_multiply->clear();
    }
}


void MainWindow::on_save_to_txt_triggered()
{
    if (this->check() && this->check_numbers())
    {
        QString path;
        path = QFileDialog::getSaveFileName(this, tr("Сохранить как"), QDir::currentPath(), tr("Text files (*.txt)"));

        if (path.isEmpty())
        {
            QMessageBox::information(this, "Программа", "Ошибка, путь для сохранения файла не выбран");
        }
        else
        {
            QFile file;
            file.setFileName(path);
            file.open(QIODevice::WriteOnly);
            if (not file.isOpen())
            {
                QMessageBox::information(this, "Программа", "Ошибка, файл сохранить не удалось, возможно нехватка прав доступа");
                return;
            }

            QString buffer;
            buffer.setNum(this->size);
            buffer += "\n";
            file.write(buffer.toUtf8());

            for (int i = 0; i < this->size; i++)
            {
                buffer.setNum(this->array[i]);
                buffer += "\n";
                file.write(buffer.toUtf8());
            }
            file.close();
        }
    }
}


bool MainWindow::check_numbers_file(QFile *file)
{
    QString buffer;
    bool isInt;
    int number_buffer;
    buffer = file->readLine();
    buffer.remove("\n");
    int fronFileSize = buffer.toInt(&isInt);
    if (not isInt)
    {
        return false;
    }
    else
    {
        int *fromFileArray = new int[fronFileSize];

        for (int i = 0; i < size; i++)
        {
            buffer = file->readLine();
            buffer.remove("\n");
            number_buffer = buffer.toInt(&isInt);
            if (not isInt)
            {
                delete [] fromFileArray;
                return false;
            }
            else
            {
                fromFileArray[i] = number_buffer;
            }
        }
        delete [] this->array;
        this->array = fromFileArray;
        return true;
    }
}

void MainWindow::on_open_from_txt_triggered()
{
    //получаем путь для открытия файла
    QString path;
    path = QFileDialog::getOpenFileName(this, tr("Считать из txt"), QDir::currentPath(), tr("Text files (*.txt)"));
    if (path.isEmpty())
    {
        QMessageBox::information(this, "Программа", "Файл открыть не удалось, не выбран путь");
    }
    else
    {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadOnly);
        if (not file.isOpen())
        {
            QMessageBox::information(this, "Программа", "Не удалось открыть файл, возможно нехватка прав доступа");
            return;
        }
        else
        {
            //файл открыт, начинаем считывание
            QString buffer; //буфер для считывания
            bool isInt; //является ли буферный элемент числом
            //считываем размер таблицы
            buffer = file.readLine();
            buffer.remove("\n");
            int fromFileSize = buffer.toInt(&isInt);
            if (not isInt) //если размер не валиден
            {
                QMessageBox::information(this, "Программа", QString("Ошибка, файл повреждён в строке 1: ") + buffer);
                return;
            }
            else if (fromFileSize <= 0 or fromFileSize > this->MAX_ARRAY_SIZE)
            {
                QMessageBox::information(this, "Программа", QString("Ошибка, файл повреждён в строке 1: ") + buffer + " , размер таблицы должен быть в диапазоне [1, " + QString::number(this->MAX_ARRAY_SIZE) + "]");
                return;
            }
            else
            {
                //создаём времменный массив для считанных чисел
                int *fromFileArray = new int[fromFileSize];
                for (int i = 0; i < fromFileSize; i++)
                {
                    //построчно записываем данные в массив
                    buffer = file.readLine();
                    buffer.remove("\n");
                    fromFileArray[i] = buffer.toInt(&isInt);
                    if (not isInt) //буферный элемент не валиден
                    {
                        QMessageBox::information(
                                    this, \
                                    "Программа", \
                                    QString("Ошибка, файл повреждён в строке ") + \
                                    QString::number(i + 2) + \
                                    ": " + buffer + "\n" + \
                                    "Считано элементов:" + QString::number(i) + \
                                    " Необходимо считать: " + QString::number(fromFileSize)
                        );
                        delete [] fromFileArray;
                        return;
                    }
                }
                //если все элементы валидны, то заменяем основной массив на временный (с числами) + подтягиваем переменную size и перерисовываем таблицу
                ui->tableWidget->setUpdatesEnabled(false);
                this->setTable(fromFileSize);
                for (int i = 0; i < fromFileSize; i++)
                {
                    ui->tableWidget->item(0, i)->setText(QString::number(fromFileArray[i]));
                    ui->tableWidget->item(0, i)->setBackground(Qt::white);
                }
                ui->tableWidget->setUpdatesEnabled(true);
                ui->tableWidget->repaint();
                delete [] this->array;
                this->array = fromFileArray;
                this->size = fromFileSize;
            }
        }
        this->clearTableConnectedLabels();
        this->clear_counters();
    }
}


void MainWindow::on_save_to_scv_triggered()
{
    if (this->check() && this->check_numbers())
    {
        QString path;
        path = QFileDialog::getSaveFileName(this, tr("Сохранить как"), QDir::currentPath(), tr("Text files (*.txt)"));

        if (path.isEmpty())
        {
            QMessageBox::information(this, "Программа", "Ошибка, путь для сохранения файла не выбран");
        }
        else
        {
            QFile file;
            file.setFileName(path);
            file.open(QIODevice::WriteOnly);
            if (not file.isOpen())
            {
                QMessageBox::information(this, "Программа", "Ошибка, файл сохранить не удалось, возможно нехватка прав доступа");
                return;
            }

            QString buffer;
            buffer.setNum(this->size);
            buffer += ";";
            file.write(buffer.toUtf8());

            int size_minus_one = this->size - 1;

            for (int i = 0; i < size_minus_one; i++)
            {
                buffer.setNum(this->array[i]);
                buffer += ",";
                file.write(buffer.toUtf8());
            }
            buffer.setNum(this->array[size - 1]);
            file.write(buffer.toUtf8());
            file.close();
        }
    }
}


void MainWindow::on_open_from_csv_triggered()
{
    //получаем путь для открытия файла
    QString path;
    path = QFileDialog::getOpenFileName(this, tr("Считать из txt"), QDir::currentPath(), tr("Text files (*.txt)"));
    if (path.isEmpty())
    {
        QMessageBox::information(this, "Программа", "Файл открыть не удалось, не выбран путь");
    }
    else
    {
        QFile file;
        file.setFileName(path);
        file.open(QIODevice::ReadOnly);
        if (not file.isOpen())
        {
            QMessageBox::information(this, "Программа", "Не удалось открыть файл, возможно нехватка прав доступа");
            return;
        }
        else
        {
            //файл открыт, начинаем считывание
            QString buffer; //буфер для считывания
            QStringList strings;
            bool isInt; //является ли буферный элемент числом
            int fromFileSize; //размер таблицы открытого файла

            //считываем размер таблицы
            buffer = file.readLine();
            strings = buffer.split(";");

            if (strings.length() <= 1)
            {
                QMessageBox::information(this, "Программа", QString("Ошибка, файл повреждён"));
                return;
            }
            else
            {
                fromFileSize = strings[0].toInt(&isInt);
            }
            if (not isInt) //если размер не валиден
            {
                QMessageBox::information(this, "Программа", QString("Ошибка, файл повреждён: размер таблицы не валиден"));
                return;
            }
            else if (fromFileSize <= 0 or fromFileSize > this->MAX_ARRAY_SIZE)
            {
                QMessageBox::information(this, "Программа", QString("Ошибка, файл повреждён: ") +  + "размер таблицы должен быть в диапазоне [1, " + QString::number(this->MAX_ARRAY_SIZE) + "]");
                return;
            }
            else
            {
                //создаём времменный массив для считанных чисел
                strings = strings[1].split(",");
                if (strings.length() != fromFileSize)
                {
                    QMessageBox::information(this, "Программа", QString("Размер таблицы не соответствует количеству элементов, заявлено ") + QString::number(fromFileSize) + " Обнаружено " + QString::number(strings.length()));
                    return;
                }
                int *fromFileArray = new int[fromFileSize];
                for (int i = 0; i < fromFileSize; i++)
                {
                    //построчно записываем данные в массив
                    buffer = strings[i];
                    fromFileArray[i] = buffer.toInt(&isInt);
                    if (not isInt) //буферный элемент не валиден
                    {
                        QMessageBox::information(
                                    this, \
                                    "Программа", \
                                    QString("Ошибка, файл повреждён в столбце ") + \
                                    QString::number(i + 2) + \
                                    ": " + buffer + "\n" + \
                                    "Считано элементов:" + QString::number(i) + \
                                    " Необходимо считать: " + QString::number(fromFileSize)
                        );
                        delete [] fromFileArray;
                        return;
                    }
                }
                //если все элементы валидны, то заменяем основной массив на временный (с числами) + подтягиваем переменную size и перерисовываем таблицу
                ui->tableWidget->setUpdatesEnabled(false);
                this->setTable(fromFileSize);
                for (int i = 0; i < fromFileSize; i++)
                {
                    ui->tableWidget->item(0, i)->setText(QString::number(fromFileArray[i]));
                    ui->tableWidget->item(0, i)->setBackground(Qt::white);
                }
                ui->tableWidget->setUpdatesEnabled(true);
                ui->tableWidget->repaint();
                delete [] this->array;
                this->array = fromFileArray;
                this->size = fromFileSize;
            }
        }
        this->clearTableConnectedLabels();
        this->clear_counters();
    }
}

