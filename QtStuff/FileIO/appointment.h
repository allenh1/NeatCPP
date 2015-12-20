#ifndef APPOINTMENT_H
#define APPOINTMENT_H
/**
 * This class holds information for an appointment.
 */

#include <QtCore>
#include <QDate>

class Appointment
{
public:
	explicit Appointment();
	explicit Appointment(const QDate & _date);
	~Appointment(){/** This doesn't do much **/}

	const QDate & getDate(){ return m_date; }
	
	const QString & getTitle(){ return m_title; }
	const QString & getDescription(){ return m_description; }

	void setTitle(QString _title);
	void setDescription(QString _description);
	void setDate(QDate _date);

	bool operator == (Appointment & d1) {
		return this->m_date == d1.getDate();
	}

	friend QDataStream & operator << (QDataStream & out, Appointment & apt);
	friend QDataStream & operator >> (QDataStream & in, Appointment & apt);
private:
	QDate m_date;

	QString m_title;
	QString m_description;
};

struct CompareAppointment
{
	bool operator () (Appointment & ap1, Appointment & ap2) {
		return ap1.getDate() < ap2.getDate();
	}
};

inline QDataStream & operator << (QDataStream & out, Appointment & apt)
{
	out << apt.m_date;
	out << apt.m_title.toUtf8();
	out << apt.m_description.toUtf8();

	return out;
}

inline QDataStream & operator >> (QDataStream & in, Appointment & apt)
{
	QDate _date; QByteArray _title, _description;
	in >> _date >> _title >> _description;
	apt.m_date = _date; apt.m_title = _title; apt.m_description = _description;

	return in;
}
#endif