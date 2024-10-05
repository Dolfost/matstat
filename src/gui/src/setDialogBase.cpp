#include <setDialogBase.hpp>

SetDialogBase::SetDialogBase(
	QList<VectorEntry*> v, 
	QWidget* p,
	Qt::WindowFlags f): DialogBase(p, f) {
	v_vectorEntry = v;

	s_vectorsGroupBox = new QGroupBox("Вектори:");
	s_vectorsGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	s_vectorsGroupBox->setLayout(new QHBoxLayout);
	s_vectorsGroupBox->layout()->setContentsMargins(2,2,2,2);
	s_vectorsLineEdit = new QLineEdit;
	s_vectorsLineEdit->setReadOnly(true);
	s_vectorsGroupBox->layout()->addWidget(s_vectorsLineEdit);

	makeVectorNames();
}

void SetDialogBase::vectorDeletedHandler(VectorEntry* ve) {
	if (v_vectorEntry.removeAll(ve)) {
		if (!v_vectorEntry.size()) {
			this->close();
			return;
		}
		fill();
	}
}

void SetDialogBase::makeVectorNames() {
	QString vectors;
	for (auto const& v : v_vectorEntry) {
		vectors.append(v->name() + ", ");
	}
	vectors.chop(2);

	s_vectorsLineEdit->setText(vectors);
}

void SetDialogBase::fill() {
	makeVectorNames();
}

void SetDialogBase::sync(VectorEntry* ve) {
	if (std::find(
		v_vectorEntry.begin(), 
		v_vectorEntry.end(), 
		ve) != v_vectorEntry.end()
	) fill();
}
