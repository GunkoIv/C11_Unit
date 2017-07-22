#ifndef TABLES_CLTABLESVIEW_H_
#define TABLES_CLTABLESVIEW_H_

namespace TABLES_NAMESPACE {

    class CLTableView {
    public:
        struct Border {
            char horizontal;
            char vertical;
            char cross;

            static constexpr Border Default() {
                return {'|', '-', '-'};
            }
        };

        struct TableBorders {
            unsigned int spaceToBorder;
            Border outer;    
            Border inner;    
        };

        // CLTableView(TableBorders borders, unsigned int maxCharWidth = 80);
        // CLTableView(unsigned int maxCharWidth = 80);
        CLTableView(const Table &table);

        void printTo(std::ostream &cout);

    private:
        const Table & m_table;
        const TableBorders m_borders;
    };

    CLTableView::CLTableView(const Table &table)
        : m_table(table) 
        , m_borders{0, Border::Default(), Border::Default()}
    {

    }
    // CLTableView::CLTableView(TableBorders borders, unsigned int maxCharWidth)
    //     : m_borders(borders)
    //     // ,
    // {

    // }

    // CLTableView::CLTableView(unsigned int maxCharWidth)
    //     : m_borders{0, Border::Default(), Border::Default()}
    //     // ,
    // {

    // }

    void CLTableView::printTo(std::ostream &cout) {

    }

} // namespace TABLES_NAMESPACE

#endif // TABLES_CLTABLESVIEW_H_
