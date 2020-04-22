#include "databasewindow.h"

DataBaseWindow::DataBaseWindow(QWidget *parent)
    : QWidget(parent)
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

    m_tableChoice   = new QComboBox(this);
    m_tableChoice->setObjectName("TableChoice");

    m_table         = new SQLView;
    m_table->setObjectName("TableDataBase");

    QHBoxLayout * m_filterLayout = new QHBoxLayout();

    m_filter        = new QLineEdit(this);
    m_filter->setObjectName("Filter");
    m_filter->setText("PERSONALIZED SQL STATEMENT");

    m_okButton      = new QPushButton(this);
    m_okButton->setObjectName("okButton");
    m_okButton->setText("OK");


    m_tableChoice->insertItem(0,CSV_ITEMS_NAME);
    m_tableChoice->insertItem(1,CSV_JOBORDER_NAME);
    m_tableChoice->insertItem(2,CSV_TRACEABILITY_BATCH_NAME);
    m_tableChoice->insertItem(3,CSV_TRACEABILITY_BOX_NAME);
    m_tableChoice->insertItem(4,CSV_TRACEABILITY_PALLET_NAME);
    m_tableChoice->insertItem(5,CSV_DELIVERY_NAME);
    m_tableChoice->insertItem(6,CSV_DELIVERY_LIST_NAME);


    //Set style filter line and combo box

    m_filterLayout->addWidget(m_filter,90);
    m_filterLayout->addWidget(m_okButton,10);

    font = m_filter ->font();
    font.setPointSize(16);
    m_filter        ->setFont(font);
    m_tableChoice   ->setFont(font);
    m_okButton      ->setFont(font);

    m_tableChoice   ->setMinimumHeight(40);
    m_filter        ->setMinimumHeight(40);
    m_okButton      ->setMinimumHeight(40);

    m_filter        ->setAlignment(Qt::AlignLeft);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->backgroundRole(), MENU_BACKGROUND_COLOR);
    m_filter        ->setPalette(pal);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->foregroundRole(), MENU_FONT_COLOR);
    m_filter        ->setPalette(pal);
    m_tableChoice   ->setPalette(pal);

    m_tableChoice->setEditable(true);
    QLineEdit *lineComboBox = m_tableChoice->lineEdit();
    pal = lineComboBox->palette();
    pal.setColor(QPalette::Base, MENU_BACKGROUND_COLOR);
    lineComboBox->setPalette(pal);
    lineComboBox->setReadOnly(true);

    // Set style of the button
    styleSheet = QString("#okButton{ ")
                + "background-color: %1 ;"
                + "color : %2;"
                + "border-style: outset;"
                + "border-width: 2px;"
                + "border-color: %2;"
                + "text-align: center center;"
                + "padding : 0 0 0 0;"
                + "margin-top -15 px"
                + "}"
                + "#okButton:hover {"
                + "background-color: %3 ;"
                + "}"
                + "#okButton:pressed {"
                + "background-color: %3 ;"
                + "color : %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_FONT_COLOR.name(), MENU_BACKGROUND_ACTIVE.name()));


    //Signal and Slots connexions
    QObject::connect(m_tableChoice,  SIGNAL(currentIndexChanged(int)),    this,   SLOT(changeTable(int)));
    QObject::connect(m_okButton,  SIGNAL(clicked()),    this,   SLOT(filterTable()));


    //Layout Management

    m_contentLayout->addWidget(m_tableChoice,Qt::AlignCenter);
    m_contentLayout->addWidget(m_table,Qt::AlignCenter);
    m_contentLayout->addLayout(m_filterLayout,Qt::AlignCenter);

    m_dbLayout->addLayout(m_contentLayout,Qt::AlignCenter);
    m_dbLayout->addWidget(m_infobar,Qt::AlignCenter);

    m_contentLayout->setMargin(10);
    m_dbLayout->setMargin(0);

}

void DataBaseWindow::changeTable(int index)
{
    m_filter->setText("PERSONALIZED SQL STATEMENT");
    // fill table with appropriate index

}

void DataBaseWindow::filterTable()
{
    QString statement = m_filter->text();
    /*
    si statement est valide
    alors appliquer le filtre à la table
    sinon
    */
    m_filter->setText("WRONG PERSONALIZED SQL STATEMENT");
}
