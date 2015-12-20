#include "appointment.h"

Appointment::Appointment(){}

Appointment::Appointment(const QDate & _date)
	: m_date(_date)
{/** Constructor **/}

void Appointment::setTitle(QString _title)
{
	m_title = _title;
}

void Appointment::setDescription(QString _description)
{ m_description = _description; }

void Appointment::setDate(QDate _date)
{ m_date = _date; }