#include <vectorChainPCAInfoDialog.hpp>
#include <iostream>

#include <namedWidget.hpp>
#include <sectionedWidget.hpp>

VectorChainPCAInfoDialog::VectorChainPCAInfoDialog(
	VectorChain* vp, 
	QWidget* p,
	Qt::WindowFlags f 
): InfoDialogBase(vp, p, f) {
	setWindowTitle("Результати МГК для вектора " + vp->name());
	v_chain = vp;
	m_table = new QTableWidget;

	v_mainLayout->insertWidget(0, m_table);

	fill();
};


void VectorChainPCAInfoDialog::fill() {
	ss::VectorChain& vc = *v_chain->chain();
	if (not vc.pca.is_done())
		throw std::logic_error("called pca info dialog for vector without pca performed");

	m_table->setColumnCount(vc.size());
	m_table->setRowCount(vc.size() + 3);
	QStringList cheader, rheader;
	for (std::size_t i = 0; i < vc.size(); i++) {
		cheader << QString("x'_%1").arg(i+1);
		rheader << QString("x_%1").arg(i+1);
	}
	rheader << "λ" << "%" << "Σ%";
	m_table->setHorizontalHeaderLabels(cheader);
	m_table->setVerticalHeaderLabels(rheader);

	for (std::size_t i = 0; i < vc.size(); i++) {
		for (std::size_t j = 0; j < vc.size(); j++) {
			m_table->setItem(
				i, j, new QTableWidgetItem(
					n(vc.pca.eigenvectors()[i][j])
				)
			);
		}
	}
	double esum = std::accumulate(vc.pca.eigenvalues().begin(), vc.pca.eigenvalues().end(), 0.0);
	double pcent = 0;
	for (std::size_t i = 0; i < vc.size(); i++) {
		m_table->setItem(
			vc.size(), i, new QTableWidgetItem(
				n(vc.pca.eigenvalues()[i])
			)
		);
		double direction_pcent = 100*vc.pca.eigenvalues()[i]/esum;
		pcent += direction_pcent;
		m_table->setItem(
			vc.size()+1, i, new QTableWidgetItem(
				n(direction_pcent)
			)
		);
		m_table->setItem(
			vc.size()+2, i, new QTableWidgetItem(
				n(pcent)
			)
		);
	}
}
