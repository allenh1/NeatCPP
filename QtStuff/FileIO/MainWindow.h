#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <QtCore>

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <iostream>
#include <algorithm>

#include "appointment.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();

	Q_SLOT void saveFile();
	Q_SLOT void loadFile();

	Q_SLOT void addApt();
	Q_SLOT void delApt();

	Q_SLOT void loadSelected(QListWidgetItem * item);
	
	Q_SLOT void doSort();
	Q_SLOT void updateListDisplay();
	Q_SIGNAL void updateList();
	Q_SIGNAL void listRefresh();

private:
	QMenu *m_pFileMenu;

	QAction *m_pSaveAction;
	QAction *m_pOpenAction;
	QAction *m_pQuitAction;

	QPushButton *m_pAddButton;
	QPushButton *m_pRemoveButton;

	QLineEdit * m_pTitleEdit;
	QTextEdit * m_pDescriptionEdit;
	QListWidget * m_pListView;

	QCalendarWidget * m_pCalendar;

	QHBoxLayout * m_pMainLayout;
	QHBoxLayout * m_pButtonLayout;
	QHBoxLayout * m_pRightLayout;

	QVBoxLayout * m_pLeftLayout;
	QVBoxLayout * m_pLabelCalLayout;

	QWidget * m_pMainWidget;

	QList<Appointment> m_list;
	QList<QString> m_stringList;
};
#endif