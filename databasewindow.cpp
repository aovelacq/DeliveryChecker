#include "databasewindow.h"

DataBaseWindow::DataBaseWindow(QWidget *parent)
    : QDialog(parent)
{
    QPalette pal;
    QFont font;
    QString styleSheet;

    setMinimumWidth(1100);
    setMinimumHeight(300);

    setWindowTitle("DataBase");
    setObjectName("DataBaseWindow");

    //Creates all children

    m_dbLayout      = new QVBoxLayout(this);

    QVBoxLayout * m_contentLayout = new QVBoxLayout();
    m_infobar       = new InfoBar(this);
    m_selectTable   = new QComboBox(this);
    m_table         = new SQLView;

    QHBoxLayout * m_filterLayout = new QHBoxLayout();
    m_filter        = new ImprovedLineEdit(this);
    m_filter        ->setText("PERSONALIZED SQL STATEMENT");
    m_okButton      = new QPushButton(this);
    m_okButton      ->setText("OK");

    m_filterCheck   = new QLabel(this);
    m_filterCheck   ->setText("QUERY OK");

    m_dbLayout      ->setObjectName("DataBaseWindow_Layout_dbLayout");
    m_infobar       ->setObjectName("DataBaseWindow_infobar_InfoBar");
    m_selectTable   ->setObjectName("DataBaseWindow_ComboBox_TableIndex");
    m_table         ->setObjectName("DataBaseWindow_SQLView_TableDataBase");
    m_filter        ->setObjectName("DataBaseWindow_LineEdit_Filter");
    m_filterCheck   ->setObjectName("DataBaseWindow_Label_FilterCheck");
    m_okButton      ->setObjectName("DataBaseWindow_PushButton_okButton");

    m_selectTable->insertItem(0," -");
    m_selectTable->insertItem(1,CSV_ITEMS_NAME);
    m_selectTable->insertItem(2,CSV_JOBORDER_NAME);
    m_selectTable->insertItem(3,CSV_TRACEABILITY_BATCH_NAME);
    m_selectTable->insertItem(4,CSV_TRACEABILITY_BOX_NAME);
    m_selectTable->insertItem(5,CSV_TRACEABILITY_PALLET_NAME);
    m_selectTable->insertItem(6,CSV_DELIVERY_NAME);
    m_selectTable->insertItem(7,CSV_DELIVERY_LIST_NAME);


    m_filterLayout->addWidget(m_filter,90);
    m_filterLayout->addWidget(m_okButton,10);

    font = m_filter ->font();
    font.setPointSize(16);
    m_filter        ->setFont(font);
    m_selectTable   ->setFont(font);
    m_okButton      ->setFont(font);
    font.setPointSize(12);
    m_filterCheck   ->setFont(font);

    m_selectTable   ->setMinimumHeight(40);
    m_filter        ->setMinimumHeight(40);
    m_filterCheck   ->setMinimumHeight(20);
    m_okButton      ->setMinimumHeight(40);

    m_filter        ->setAlignment(Qt::AlignLeft);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->backgroundRole(), MENU_BACKGROUND_COLOR);
    m_filter        ->setPalette(pal);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->foregroundRole(), MENU_FONT_COLOR);
    m_filter        ->setPalette(pal);
    m_selectTable   ->setPalette(pal);
    pal.setColor(m_filterCheck->foregroundRole(),Qt::darkGreen);
    m_filterCheck   ->setPalette(pal);

    m_selectTable->setEditable(true);
    QLineEdit *lineComboBox = m_selectTable->lineEdit();
    pal = lineComboBox->palette();
    pal.setColor(QPalette::Base, MENU_BACKGROUND_COLOR);
    lineComboBox->setPalette(pal);
    lineComboBox->setReadOnly(true);

    // Set style of the button
    styleSheet = QString("#DataBaseWindow_PushButton_okButton{ ")
                + "background-color: %1 ;"
                + "color : %2;"
                + "border-style: outset;"
                + "border-width: 2px;"
                + "border-color: %2;"
                + "text-align: center center;"
                + "padding : 0 0 0 0;"
                + "margin-top -15 px"
                + "}"
                + "#DataBaseWindow_PushButton_okButton:hover {"
                + "background-color: %3 ;"
                + "}"
                + "#DataBaseWindow_PushButton_okButton:pressed {"
                + "background-color: %3 ;"
                + "color : %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_FONT_COLOR.name(), MENU_BACKGROUND_ACTIVE.name()));

    //Layout Management

    m_contentLayout->addWidget(m_selectTable,Qt::AlignCenter);
    m_contentLayout->addWidget(m_table,Qt::AlignCenter);
    m_contentLayout->addLayout(m_filterLayout,Qt::AlignCenter);
    m_contentLayout->addWidget(m_filterCheck,Qt::AlignLeft);

    m_dbLayout->addLayout(m_contentLayout,Qt::AlignCenter);
    m_dbLayout->addWidget(m_infobar,Qt::AlignCenter);

    m_contentLayout->setMargin(10);
    m_dbLayout->setMargin(0);

}
