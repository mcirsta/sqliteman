/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QMainWindow>
#include "ui_dataviewer.h"

class QAbstractItemModel;
class QTableView;
class QTextEdit;
class QToolBar;
class QAction;
class QSplitter;
class QSqlQueryModel;
class QResizeEvent;
class QModelIndex;


/*! \brief A Complex widget handling the database outputs and status messages.
\author Petr Vanek <petr@scribus.info>
*/
class DataViewer : public QMainWindow
{
		Q_OBJECT
	public:
		DataViewer(QWidget * parent = 0);
		~DataViewer();

		/*! \brief Set data model. See Qt model/view documentation.
		\retval bool true when the model is set succesfully
		*/
		bool checkForPending();
		void setNotPending();
		bool setTableModel(QAbstractItemModel * model, bool showButtons = false);
		//! \brief Set text to the status widget.
		void setStatusText(const QString & text);
		void removeErrorMessage();
		//! \brief Show/hide status widget
		void showStatusText(bool show);

		QAbstractItemModel * tableData();
		QStringList tableHeader();

		QByteArray saveSplitter() { return ui.splitter->saveState(); };
		void restoreSplitter(QByteArray state) { ui.splitter->restoreState(state); };

		QString canFetchMore;
		bool isTopLevel;
		int columnSelected;

		/*! \brief Free locked resources */
		void freeResources(QAbstractItemModel * old);

		// reselect active row and full/item view after doing some changes
		void saveSelection();
		void reSelect();
		bool incrementalSearch(QKeyEvent *keyEvent);

	signals:
		void tableUpdated();

public slots:
		//! \brief Append the line to the "Script Result" tab.
		void showSqlScriptResult(QString line);
		//! \brief Clean the "Script Result" report
		void sqlScriptStart();
		void rowCountChanged();

	private:
		Ui::DataViewer ui;
		bool dataResized;
		int activeRow;
		int savedActiveRow;
		bool wasItemView;
		QString searchString;
		int topRow;

        QAction * actOpenEditor;
        QAction * actOpenMultiEditor;
        QAction * actInsertNull;
		
		void resizeViewToContents(QAbstractItemModel * model);
		void resizeEvent(QResizeEvent * event);
		//! \brief Show/hide action tools
		void updateButtons();

	private slots:
		void addRow();
		void copyRow();
		void removeRow();
		void deletingRow(int row); // when it actually gets deleted
		void exportData();
		void commit();
		void rollback();
		/*! \brief Handle selection as "excel-like copypasting".
		Qt4 takes only last selected item into clipboard so
		we have to create structure such this:
		val1 [tab] val2 [tab] ... [tab] valN
		valX ...
		...
		valC ...
		\note The DisplayRole of the values is taken!
		*/
		void copyHandler();

		/*! \brief Open current results in a new standalone window.
		Based on the user RFE. Used for e.g. comparing 2 select results etc.
		It's a little bit hackish - the new window shoudl contain read
		only snapshot of the current data result - even if it is a editable
		table snapshot. User is not allowed to edit it as it's "freezed
		in time" to prevent all transaction blocking.
		It means all models are converted to the SqlQueryModel.
		The new window is destroyed on its close. */
		void openStandaloneWindow();

		void handleBlobPreview(bool);
		void tableView_selectionChanged(const QItemSelection &, const QItemSelection &);
		void tableView_currentChanged(const QModelIndex &, const QModelIndex &);
		void tableView_dataResized(int column, int oldWidth, int newWidth);

		//! \brief Set position in the models when user switches his views.
		void tabWidget_currentChanged(int);
		/*! \brief Handle table view and item view cooperation and
		synchronization.
		\warning This slot must be active only when is user in the item view.
		Sync table to items is done only in the tabWidget switch.
		Sync items to table is done by SqlItemView::indexChanged() signal;
		it's catched for sync itself and for BLOB preview as well.
		*/
		void itemView_indexChanged();

		void tableView_dataChanged();
		void gotoLine();

        void actOpenEditor_triggered();
        void actOpenMultiEditor_triggered();
        void actInsertNull_triggered();

		void rowDoubleClicked(int);
		void nonColumnClicked();
		void columnClicked(int);
};


//! \brief Support tools for DataViewer class
namespace DataViewerTools {

	/*! \brief Catch a "Copy to clipboard" key sequence.
	It depends on the OS system - mostly Ctrl+C.
	This class is used as an eventFilter for DataViewer::ui.tableView
	because this widget is handled in designer (I don't want to
	inherit it to live in my code). See DataViewer constructor.
	\author Petr Vanek <petr@scribus.info>
	*/
	class KeyPressEater : public QObject
	{
		Q_OBJECT

		public:
			KeyPressEater(DataViewer * parent = 0) : QObject(parent) {
				m_owner = parent;
			};
			~KeyPressEater(){};

		signals:
			/*! \brief Signal emitted when user press copy sequence.
			Raised in eventFilter() */
			void copyRequest();

		protected:
			//! \brief Just catch keys.
			bool eventFilter(QObject *obj, QEvent *event);

		private:
			DataViewer * m_owner;
	};

}

#endif
