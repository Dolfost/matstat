#ifndef _VECTOR_PAIR_CONNECTIONS_TABLE_INFO_DIALOG_
#define _VECTOR_PAIR_CONNECTIONS_TABLE_INFO_DIALOG_

#include "vector.hpp"

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QVBoxLayout>

#include <infoDialogBase.hpp>

class VectorPairConnectionsTableInfoDialog: public InfoDialogBase {
public:
  VectorPairConnectionsTableInfoDialog(
		VectorPair*, QWidget* = nullptr,
    Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void fill() override;

	class ConnectionsTableWiget: public QTableWidget {
	public:
		ConnectionsTableWiget();
		void fill(ss::VectorPair*);
	};

protected:
	VectorPair* v_vector;

protected:
	ConnectionsTableWiget* v_con = nullptr;
	InfoTableWidget* v_table = nullptr;
};

#endif // !_VECTOR_PAIR_CONNECTIONS_TABLE_INFO_DIALOG_
