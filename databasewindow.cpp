#include "databasewindow.h"

DataBaseWindow::DataBaseWindow(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    QFont font;


    setWindowTitle("DataBase");
    setObjectName("DataBaseWindow");

    //Creates all children

    m_dbLayout      = new QVBoxLayout(this);

    m_infobar       = new InfoBar(this);

    m_tableChoice   = new QComboBox(this);
    m_tableChoice->setObjectName("TableChoice");

    m_table         = new SQLView;
    m_table->setObjectName("TableDataBase");

    m_filter        = new QLineEdit(this);
    m_filter->setObjectName("Filter");
    m_filter->setText("PERSONALIZED SQL STATEMENT");

    font = m_filter ->font();
    font.setPointSize(16);
    m_filter        ->setFont(font);
    m_tableChoice   ->setFont(font);

    m_tableChoice   ->setMinimumHeight(40);
    m_filter        ->setMinimumHeight(40);

    //m_tableChoice->setAlignment(Qt::AlignLeft);
    m_filter        ->setAlignment(Qt::AlignLeft);

    m_filter        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->backgroundRole(), MENU_BACKGROUND_COLOR);
    m_filter        ->setPalette(pal);

    pal = m_filter  ->palette();
    pal.setColor(m_filter->foregroundRole(), MENU_FONT_COLOR);
    m_filter        ->setPalette(pal);

    //Layout Management

    m_dbLayout->addWidget(m_tableChoice,Qt::AlignCenter);
    m_dbLayout->addWidget(m_table,Qt::AlignCenter);
    m_dbLayout->addWidget(m_filter,Qt::AlignCenter);
    m_dbLayout->addWidget(m_infobar,Qt::AlignCenter);

    setLayout(m_dbLayout);

}
