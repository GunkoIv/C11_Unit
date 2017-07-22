#ifndef TABLES_TABLE_H_
#define TABLES_TABLE_H_

namespace TABLES_NAMESPACE {

    struct Cell {
        std::string data;
        bool isBounded;
        Cell(std::string &&_data, bool _isBounded)
            : data(std::move(_data))
            , isBounded(_isBounded)
        {}
        Cell()
            : data{}
            , isBounded(false)
        {}
    };

    class TableData {
    public:
        const std::string & get() const;

    protected:
        TableData() 
            : m_rows{Row{}}
        {}
        using Row = std::vector<Cell>;
        std::vector<Row> m_rows;
        using RowIter = std::vector<Row>::iterator;
        using CellIter = std::vector<Cell>::iterator;


    private:
    // friend CLTableView;
    };

    class TableAccess
    {
    public:
        TableAccess();
        ~TableAccess();
        
    };

    class Table : private TableData {
    public:

        Table() = default;

        template<typename StringArg, bool isBoundCell = false>
        void addCell(StringArg &&str);

        template<typename StringArg>
        void addSubCell(StringArg &&str) {
            addCell<StringArg, true>(std::forward<StringArg>(str));
        }
        // void addCell(const std::string &str);
        // if makeFit == true then: make current row fit with prev row cell count
        void nextRow(bool makeFit = false);
    private:    
        RowIter m_rowPtr = m_rows.begin();
        CellIter m_cellPtr = m_rowPtr->begin();
    };
        // Table::Table()
        //     : 
        // {

        // }
    template<typename StringArg, bool isBoundCell>
    void Table::addCell(StringArg &&str) {
        if (m_cellPtr == m_rowPtr->end()) {
            m_rowPtr->emplace_back(std::forward<StringArg>(str), isBoundCell);
            m_cellPtr = m_rowPtr->end();// TODO can be optimized
        } else {
            *m_cellPtr = Cell(std::forward<StringArg>(str), isBoundCell);
            ++m_cellPtr;
        }
    }

    void Table::nextRow(bool makeFit) {
        if (makeFit && m_rowPtr != m_rows.begin()) {
            m_rowPtr->resize((m_rowPtr - 1)->size());
        }
        ++m_rowPtr;
        if (m_rowPtr == m_rows.end()) {
            m_rows.emplace_back(Row{});
            m_rowPtr = (m_rows.end() - 1);
        }
        m_cellPtr = m_rowPtr->begin();
    }

} // namespace TABLES_NAMESPACE

#endif // TABLES_TABLE_H_
