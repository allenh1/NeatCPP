#include "MainWindow.h"

MainWindow::MainWindow()
{
	//! Allocate stuff	
	m_pSaveAction = new QAction(tr("&Save"), this);
	m_pOpenAction = new QAction(tr("&Open"), this);
	m_pQuitAction = new QAction(tr("&Quit"), this);

	m_pAddButton = new QPushButton(tr("Add"));
	m_pRemoveButton = new QPushButton(tr("Remove"));

	m_pTitleEdit = new QLineEdit(this);
	m_pDescriptionEdit = new QTextEdit(this);

	m_pListView = new QListWidget(this);

	m_pCalendar = new QCalendarWidget(this);

	m_pMainLayout = new QHBoxLayout();
	m_pButtonLayout = new QHBoxLayout();
	m_pRightLayout = new QHBoxLayout();

	m_pLeftLayout = new QVBoxLayout();
	m_pLabelCalLayout = new QVBoxLayout();

	m_pMainWidget = new QWidget(this);

	//! Build UI
	m_pButtonLayout->addWidget(m_pAddButton);
	m_pButtonLayout->addWidget(m_pRemoveButton);

	m_pLeftLayout->addWidget(m_pListView);
	m_pLeftLayout->addLayout(m_pButtonLayout);

	m_pLabelCalLayout->addWidget(m_pTitleEdit);
	m_pLabelCalLayout->addWidget(m_pCalendar);

	m_pRightLayout->addLayout(m_pLabelCalLayout);
	m_pRightLayout->addWidget(m_pDescriptionEdit);

	m_pMainLayout->addLayout(m_pLeftLayout);
	m_pMainLayout->addLayout(m_pRightLayout);

	m_pMainWidget->setLayout(m_pMainLayout);
	this->setCentralWidget(m_pMainWidget);

	//! Create File Menu
	m_pFileMenu = menuBar()->addMenu(tr("&File"));

	m_pSaveAction->setShortcut(tr("Ctrl+S"));
	m_pFileMenu->addAction(m_pSaveAction);

	m_pOpenAction->setShortcut(tr("Ctrl+O"));
	m_pFileMenu->addAction(m_pOpenAction);

	m_pQuitAction->setShortcut(tr("Ctrl+Q"));
	m_pFileMenu->addSeparator();
	m_pFileMenu->addAction(m_pQuitAction);

	//! Connect Things
	connect(m_pSaveAction, &QAction::triggered, this, &MainWindow::saveFile);
	connect(m_pOpenAction, &QAction::triggered, this, &MainWindow::loadFile);

	connect(m_pAddButton, &QPushButton::clicked, this, &MainWindow::addApt);
	connect(m_pRemoveButton, &QPushButton::clicked, this, &MainWindow::delApt);

	connect(this, &MainWindow::updateList, this, &MainWindow::doSort);
	connect(this, &MainWindow::listRefresh, this, &MainWindow::updateListDisplay);

	connect(m_pQuitAction, &QAction::triggered, this, &QWidget::close);
	connect(m_pQuitAction, &QAction::triggered, this, &QObject::deleteLater);

	connect(m_pListView, &QListWidget::itemClicked, this, &MainWindow::loadSelected);
}

void MainWindow::addApt()
{
	Appointment toAdd;
	QString title = m_pTitleEdit->text().replace(tr(" "), tr(""));
	QString descn = m_pDescriptionEdit->toPlainText().replace(tr(" "), tr(""));

	if (title == tr("")) {	
		QMessageBox::critical(this, tr("Invalid Title"), 
			tr("Error: Appointment must have a title!"), QMessageBox::Retry);
		return;
	} else if (descn == tr("")) {
		QMessageBox::critical(this, tr("Invalid Description"), 
			tr("Error: Appointment must have a description!"), QMessageBox::Retry);
		return;
	}

	if (m_stringList.indexOf(title) != -1) {
		QMessageBox::critical(this, tr("Invalid Title"), 
			tr("Error: Appointment titles must be unique!"), QMessageBox::Retry);
		return;
	} 

	toAdd.setDate(m_pCalendar->selectedDate());	
	toAdd.setTitle(m_pTitleEdit->text());
	toAdd.setDescription(m_pDescriptionEdit->toPlainText());

	m_list << toAdd;
	m_stringList << toAdd.getTitle();

	Q_EMIT updateList();
}


void MainWindow::delApt()
{
	QList<QListWidgetItem*> selected = m_pListView->selectedItems();

	foreach (QListWidgetItem* pItem, selected) {
		int index = m_stringList.indexOf(pItem->text());
		if (index != -1) {
			m_stringList.removeAt(index);
			m_list.removeAt(index);
		}
	}

	Q_EMIT listRefresh();
}

void MainWindow::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), tr("Appointment Files (*.aDat)"));

	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(this, tr("Could Not Save File"), 
			tr("Error: Could not save file! Check your write permissions!"), 
			QMessageBox::Retry);
		return;
	}

	QDataStream out(&file);

	foreach (Appointment apt, m_list) {
	
		out << apt;
	}
}

void MainWindow::loadFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("Appointment Files (*.aDat)"));

	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(this, tr("Could Not Save File"), 
			tr("Error: Could not save file! Check your write permissions!"), 
			QMessageBox::Retry);
		return;
	}

	QDataStream in(&file);
	m_list.clear();
	m_stringList.clear();

	for (;!in.atEnd();) {
		Appointment apt;
		in >> apt;
		m_list << apt;
		m_stringList << apt.getTitle();
	}

	Q_EMIT listRefresh();
}

void MainWindow::doSort()
{
	std::sort(m_list.begin(), m_list.end(), CompareAppointment());
	m_stringList.clear();
	foreach (Appointment apt, m_list) {
		m_stringList << apt.getTitle();
	}
	Q_EMIT listRefresh();
}

void MainWindow::updateListDisplay()
{
	m_pListView->clear();
	foreach (QString apt, m_stringList) {
		m_pListView->addItem(apt);
	}
}

void MainWindow::loadSelected(QListWidgetItem * item)
{
	Appointment * apt = (Appointment*) &m_list.at(m_stringList.indexOf(item->text()));

	m_pTitleEdit->setText(apt->getTitle());
	m_pDescriptionEdit->setText(apt->getDescription());
	m_pCalendar->setSelectedDate(apt->getDate());
}
